#include "stdafx.h"
#include "CAppRender.h"


CAppRender::CAppRender() {
}


CAppRender::~CAppRender() {
}

void CAppRender::OnInit() {
	//버텍스버퍼 생성
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex) * sizeof(sVertices) / sizeof(SVertex),//버텍스크기*개수
		D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
		D3DFVF_SVertex,//버텍스데이터 사용법
		D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
		&pVertexBufferInterface,//반환된 버텍스버퍼를 받을 포인터
		nullptr//사용하지 않는 변수, nullptr
	);
	//버텍스버퍼에 버텍스를 저장하기 위해 잠금
	//Lock을 하면 다른 자원이 접근할 수 없게되고 정점을 저장할 메모리 포인터를 반환한다.
	void *pVertices;//버텍스를 저장할 메모리의 시작 주소를 받을 변수
	pVertexBufferInterface->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, sVertices, sizeof(sVertices));//버텍스버퍼에 버텍스를 메모리 복사
	pVertexBufferInterface->Unlock();//잠금을 해제

	//Viewport
	D3DVIEWPORT9 d3dViewport9 = {};
	d3dViewport9.X = 0;
	d3dViewport9.Y = 0;
	d3dViewport9.Width = 800;
	d3dViewport9.Height = 800;
	d3dViewport9.MinZ = 0.0;
	d3dViewport9.MaxZ = 0.0;
	pD3DFramework->pD3DDevice->SetViewport(&d3dViewport9);
}

void CAppRender::OnUpdate(DWORD fDeltaTime) {
}

void CAppRender::OnRender(DWORD fDeltaTime) {
	//World transformation
	XMMATRIX matWorld = XMMatrixScaling(1.0, 1.0, 1.0)//크기행렬
		*XMMatrixRotationX(0.0)//회전행렬
		*XMMatrixTranslation(0.0, 0.0, 0.0);//이동행렬
	XMFLOAT4X4 f44;
	XMStoreFloat4x4(&f44, matWorld);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&f44);
	//View transformation
	XMMATRIX matView = XMMatrixLookAtLH(
		{ 0.0, 0.0, -10.0 },//카메라 위치
		{ 0.0, 0.0, 0.0 },//바라보는 방향
		{ 0.0, 1.0, 0.0 }//카메라에서 위쪽으로 향하는 벡터
	);
	//XMFLOAT4X4 f44_2;
	XMStoreFloat4x4(&f44, matView);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&f44);
	//Projection trasformation
	XMMATRIX matProj = XMMatrixPerspectiveFovLH(
		Const::fPI() / 2.0,
		1.0,
		1.0,//가까운 면의 Z값(음수를 넣으니 WM_SYSCOLORCHANGE가 계속와서 프로그램 진행이 안됨)
		100.0//먼 면의 Z값
	);
	//XMFLOAT4X4 f44_3;
	XMStoreFloat4x4(&f44, matProj);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&f44);

	//Light Off
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//버텍스 출력
	//1. 버텍스버퍼와 버텍스 포맷을 D3D 디바이스에 알려준다. 출력할 버텍스버퍼를 출력 스트림과 연결한다.
	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0으로 지정
		pVertexBufferInterface, //버텍스버퍼
		0, //메모리시작 위치
		sizeof(SVertex) //버텍스 크기
	);
	//2. D3D에 정점 셰이더 정보를 지정, 대부분 FVF만 지정한다.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);
	//3. 기하 정보를 출력하기 위한 DrawPrimitive() 함수 호출
	//DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()등이 있고
	//DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()함수가 게임개발에 많이 사용된다.
	//DrawIndexedPrimitive()함수가 가장 빠르다.
	pD3DFramework->pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0, //출력을 시작할 버텍스 인덱스
		1 //출력할 개수, 첫번째 파라미터 D3DPRIMITIVETYPE에 영향을 받는다.
	);

	//Light Off
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void CAppRender::OnRelease() {
}
