#include "stdafx.h"
#include "_04_CAppMesh.h"
//#include <d3d12shader.h>
#include <d3dx9shape.h>

CAppMesh::CAppMesh() {
}
CAppMesh::~CAppMesh() {
}
void CAppMesh::OnInit() {
	//Viewport
	//D3DVIEWPORT9 d3dViewport9 = {};
	//d3dViewport9.X = 0;//렌더링타겟 표면에서 뷰포트가 시작될 x위치
	//d3dViewport9.Y = 0;//렌더링타겟 표면에서 뷰포트가 시작될 y위치
	//d3dViewport9.Width = 800;//렌더링타겟에서 출력될 가로 크기
	//d3dViewport9.Height = 800;//렌더링타겟에서 출력될 세로 크기
	//d3dViewport9.MinZ = 0.0;//깊이버퍼의 최소 범위
	//d3dViewport9.MaxZ = 1.0;//깊이버퍼의 최대 범위
	//pD3DFramework->pD3DDevice->SetViewport(&d3dViewport9);
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
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
		&pD3DFramework->vCameraEye,//카메라 위치
		&pD3DFramework->vCameraAt,//바라보는 방향
		&pD3DFramework->vCameraUp//카메라에서 위쪽으로 향하는 벡터
		//{ 10.0, 20.0, -15.0 },//카메라 위치
		//{ 0.0, 0.0, 0.0 },//바라보는 방향
		//{ 0.0, 1.0, 0.0 }//카메라에서 위쪽으로 향하는 벡터
	);
	//XMStoreFloat4x4(&f44, matView);
	//pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&f44);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//Projection trasformation(원근법)
	XMMATRIX matProj = XMMatrixPerspectiveFovLH( //FovLH : Field of view Left Hand
		Const::fPI() / 2.0,
		1.0,
		1.0,//가까운 면의 Z값(음수를 넣으니 WM_SYSCOLORCHANGE가 계속와서 프로그램 진행이 안됨)
		100.0//먼 면의 Z값
	);
	//Projection trasformation(직교투영)
	//XMMATRIX matProj = XMMatrixOrthographicLH(
	//	50.0,
	//	50.0,
	//	1.0,//가까운 면의 Z값(음수를 넣으니 WM_SYSCOLORCHANGE가 계속와서 프로그램 진행이 안됨)
	//	100.0//먼 면의 Z값
	//);
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
	//pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//Box Mesh
	LPD3DXMESH pMesh;
	//D3DXCreateBox(pD3DFramework->pD3DDevice, 10, 10, 10, &pMesh, nullptr);
	//D3DXCreateSphere(pD3DFramework->pD3DDevice, 10, 10, 10, &pMesh, nullptr);
	//D3DXCreateTeapot(pD3DFramework->pD3DDevice, &pMesh, nullptr);
	D3DXCreateCylinder(pD3DFramework->pD3DDevice, 1, 1, 1, 10, 10, &pMesh, nullptr);
	//D3DXCreateCylinder(pD3DFramework->pD3DDevice, 10, 10, 10, 10, 10, &pMesh, nullptr);
	pMesh->DrawSubset(0);

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
