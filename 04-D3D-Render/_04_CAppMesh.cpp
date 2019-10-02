#include "stdafx.h"
#include "_04_CAppMesh.h"
//#include <d3d12shader.h>
#include <d3dx9shape.h>

CAppMesh::CAppMesh() {
}
CAppMesh::~CAppMesh() {
}
void CAppMesh::OnInit() {
	//버텍스버퍼 생성
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(sCubeVertices),//버텍스배열의 크기
		D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
		D3DFVF_SVertex,//버텍스 타입
		D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
		&pCubeVertexBufferInterface,//반환된 버텍스버퍼를 받을 포인터
		nullptr//사용하지 않는 변수, nullptr
	);
	//버텍스버퍼에 버텍스를 저장하기 위해 잠금
	//Lock을 하면 다른 자원이 접근할 수 없게되고 정점을 저장할 메모리 포인터를 반환한다.
	void *pVertices;//버텍스를 저장할 메모리의 시작 주소를 받을 변수
	pCubeVertexBufferInterface->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, sCubeVertices, sizeof(sCubeVertices));//버텍스버퍼에 버텍스를 메모리 복사
	pCubeVertexBufferInterface->Unlock();//잠금을 해제

	//인덱스버퍼 생성
	pD3DFramework->pD3DDevice->CreateIndexBuffer(
		sizeof(sCubeIndices),//인덱스배열의 크기
		D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
		D3DFMT_INDEX16,//인덱스 타입
		D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
		&pCubeIndexedBufferInterface,//반환된 인덱스버퍼를 받을 포인터
		nullptr//사용하지 않는 변수, nullptr
	);
	//인덱스버퍼에 인덱스를 저장하기 위해 잠금
	//Lock을 하면 다른 자원이 접근할 수 없게되고 인덱스를 저장할 메모리 포인터를 반환한다.
	void *pIndices;//인덱스를 저장할 메모리의 시작 주소를 받을 변수
	pCubeIndexedBufferInterface->Lock(0, sizeof(sCubeIndices), (void**)&pIndices, 0);
	memcpy(pIndices, sCubeIndices, sizeof(sCubeIndices));//인덱스버퍼에 인덱스를 메모리 복사
	pCubeIndexedBufferInterface->Unlock();//잠금을 해제

	//Viewport
	D3DVIEWPORT9 d3dViewport9 = {};
	d3dViewport9.X = 0;//렌더링타겟 표면에서 뷰포트가 시작될 x위치
	d3dViewport9.Y = 0;//렌더링타겟 표면에서 뷰포트가 시작될 y위치
	d3dViewport9.Width = 800;//렌더링타겟에서 출력될 가로 크기
	d3dViewport9.Height = 800;//렌더링타겟에서 출력될 세로 크기
	d3dViewport9.MinZ = 0.0;//깊이버퍼의 최소 범위
	d3dViewport9.MaxZ = 1.0;//깊이버퍼의 최대 범위
	pD3DFramework->pD3DDevice->SetViewport(&d3dViewport9);
}

void CAppMesh::OnUpdate(DWORD fDeltaTime) {
}

void CAppMesh::OnRender(DWORD fDeltaTime) {
	//World transformation
	XMMATRIX matWorld = XMMatrixScaling(1.0, 1.0, 1.0)//크기행렬
		*XMMatrixRotationX(0.0)//회전행렬
		*XMMatrixTranslation(0.0, 0.0, 0.0);//이동행렬
	XMFLOAT4X4 f44;
	XMStoreFloat4x4(&f44, matWorld);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&f44);
	//View transformation
	XMMATRIX matView = XMMatrixLookAtLH(
		{ 10.0, 20.0, -15.0 },//카메라 위치
		{ 0.0, 0.0, 0.0 },//바라보는 방향
		{ 0.0, 1.0, 0.0 }//카메라에서 위쪽으로 향하는 벡터
	);
	XMStoreFloat4x4(&f44, matView);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&f44);
	//Projection trasformation(원근법)
	//XMMATRIX matProj = XMMatrixPerspectiveFovLH( //Field of view Left Hand
		//Const::fPI() / 2.0,
		//1.0,
		//1.0,//가까운 면의 Z값(음수를 넣으니 WM_SYSCOLORCHANGE가 계속와서 프로그램 진행이 안됨)
		//100.0//먼 면의 Z값
	//);
	//Projection trasformation(직교투영)
	XMMATRIX matProj = XMMatrixOrthographicLH(
		50.0,
		50.0,
		1.0,//가까운 면의 Z값(음수를 넣으니 WM_SYSCOLORCHANGE가 계속와서 프로그램 진행이 안됨)
		100.0//먼 면의 Z값
	);
	XMStoreFloat4x4(&f44, matProj);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&f44);

	//렌더링 상태 설정
	//Light Off
	//정점 쉐이더 작업을 하지 않을 때는 라이팅을 꺼줘야 버텍스 색상을 볼 수 있다.
	//그렇지 않으면 검은색으로 출력된다.
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//채우기모드를 와이어프레임으로 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//컬링을 하지 않도록 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//3축 정점 출력
	//1. 버텍스버퍼와 버텍스 포맷을 D3D 디바이스에 알려준다. 출력할 버텍스버퍼를 출력 스트림과 연결한다.
	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0으로 지정
		pCubeVertexBufferInterface, //버텍스버퍼
		0, //메모리시작 위치
		sizeof(SVertex2) //버텍스 크기
	);
	//2. D3D에 정점 데이터를 어떻게 해석해하는지 설정한다.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);
	//인덱스버퍼 입력
	pD3DFramework->pD3DDevice->SetIndices(pCubeIndexedBufferInterface);
	//3. 기하 정보를 출력하기 위한 DrawPrimitive() 함수 호출
	//DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()등이 있고
	//DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()함수가 게임개발에 많이 사용된다.
	//DrawIndexedPrimitive()함수가 가장 빠르다.
	//pD3DFramework->pD3DDevice->DrawPrimitive(
	pD3DFramework->pD3DDevice->DrawIndexedPrimitive(
		//D3DPT_LINELIST,
		//D3DPT_TRIANGLESTRIP,
		D3DPT_TRIANGLELIST,
		0,//정점버퍼의 시작인덱스 오프셋. 만약 1일 경우 인덱스 버퍼의 0값이 정점 버퍼의 1인덱스를 가리킨다.
		0,//정점버퍼의 최소인덱스. 만약 1일 경우 0번 정점은 사용되지 않는다.
		8,//그려질 정점의 개수, BaseVertexIndex + MinIndex 만큼 빼주면 된다.
		0,//인덱스버퍼의 시작인덱스 오프셋. 만약 1일 경우 1번 인덱스버퍼부터 그린다.
		12//그려질 도형(삼각형)의 개수
	);

	//Box Mesh
	LPD3DXMESH pBoxMesh;
	D3DXCreateBox(pD3DFramework->pD3DDevice, 10, 10, 10, &pBoxMesh, nullptr);
	D3DXCreateSphere(pD3DFramework->pD3DDevice, 10, 10, 10, &pBoxMesh, nullptr);
	D3DXCreateTeapot(pD3DFramework->pD3DDevice, &pBoxMesh, nullptr);
	D3DXCreateCylinder(pD3DFramework->pD3DDevice, 10, 10, 10, 10, 10, &pBoxMesh, nullptr);
	pBoxMesh->DrawSubset(0);

	//Light Off
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//컬링을 다시 켜준다
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CAppMesh::OnRelease() {
	if (pCubeVertexBufferInterface != nullptr) {
		pCubeVertexBufferInterface->Release();
		pCubeVertexBufferInterface = nullptr;
	}
	if (pCubeIndexedBufferInterface != nullptr) {
		pCubeIndexedBufferInterface->Release();
		pCubeIndexedBufferInterface = nullptr;
	}
}
