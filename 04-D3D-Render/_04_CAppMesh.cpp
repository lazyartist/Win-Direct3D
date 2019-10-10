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
	if (GetAsyncKeyState(VK_UP) < 0) {
		//메쉬를 앞으로 이동, 메쉬의 정면 벡터의 초기값은 {0, 0, 1}이고 회전에 따라 방향이 바뀐다.
		D3DXVECTOR4 vMeshFront = {};
		D3DXMATRIX matFront;
		D3DXMatrixRotationY(&matFront, vMeshRotation.y);//회전행렬
		D3DXVec3Transform(&vMeshFront, &vMESH_FRONT/*(0,0,1)*/, &matFront);//메쉬정면 벡터를 회전
		D3DXVec4Normalize(&vMeshFront, &vMeshFront);//정면벡터 정규화
		vMeshTranslation += (D3DXVECTOR3)vMeshFront * 0.1;//현재 메쉬의 위치에 정면벡터를 더해서 이동시킨다.
	}
	if (GetAsyncKeyState(VK_DOWN) < 0) {
		//메쉬를 앞으로 이동, 메쉬의 정면 벡터의 초기값은 {0, 0, 1}이고 회전에 따라 방향이 바뀐다.
		D3DXVECTOR4 vMeshFront = {};
		D3DXMATRIX matFront;
		D3DXMatrixRotationY(&matFront, vMeshRotation.y);//회전행렬
		D3DXVec3Transform(&vMeshFront, &vMESH_FRONT/*(0,0,1)*/, &matFront);//메쉬정면 벡터를 회전
		D3DXVec4Normalize(&vMeshFront, &vMeshFront);//정면벡터 정규화
		vMeshTranslation -= (D3DXVECTOR3)vMeshFront * 0.1;//현재 메쉬의 위치에 정면벡터를 더해서 이동시킨다.
	}
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		//메쉬를 좌(CCW)로 회전
		vMeshRotation.y -= 0.1;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		//메쉬를 우(CW)로 회전
		vMeshRotation.y += 0.1;
	}
}

void CAppMesh::OnRender(DWORD fDeltaTime) {
	//World transformation
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMatrixScaling(&matScale, vMeshScale.x, vMeshScale.y, vMeshScale.z);//크기행렬
	D3DXMatrixRotationY(&matRotation, vMeshRotation.y);//회전행렬
	D3DXMatrixTranslation(&matTranslation, vMeshTranslation.x, vMeshTranslation.y, vMeshTranslation.z);//이동행렬
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale * matRotation * matTranslation));
	//View, Projection transformation은 CD3DFramework에서 설정한다.
	
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
	//if (pCubeVertexBufferInterface != nullptr) {
	//	pCubeVertexBufferInterface->Release();
	//	pCubeVertexBufferInterface = nullptr;
	//}
	//if (pCubeIndexedBufferInterface != nullptr) {
	//	pCubeIndexedBufferInterface->Release();
	//	pCubeIndexedBufferInterface = nullptr;
	//}
}
