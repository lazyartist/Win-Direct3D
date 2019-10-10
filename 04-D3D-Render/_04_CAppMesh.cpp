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
	//d3dViewport9.X = 0;//������Ÿ�� ǥ�鿡�� ����Ʈ�� ���۵� x��ġ
	//d3dViewport9.Y = 0;//������Ÿ�� ǥ�鿡�� ����Ʈ�� ���۵� y��ġ
	//d3dViewport9.Width = 800;//������Ÿ�ٿ��� ��µ� ���� ũ��
	//d3dViewport9.Height = 800;//������Ÿ�ٿ��� ��µ� ���� ũ��
	//d3dViewport9.MinZ = 0.0;//���̹����� �ּ� ����
	//d3dViewport9.MaxZ = 1.0;//���̹����� �ִ� ����
	//pD3DFramework->pD3DDevice->SetViewport(&d3dViewport9);
}

void CAppMesh::OnUpdate(DWORD fDeltaTime) {
	if (GetAsyncKeyState(VK_UP) < 0) {
		//�޽��� ������ �̵�, �޽��� ���� ������ �ʱⰪ�� {0, 0, 1}�̰� ȸ���� ���� ������ �ٲ��.
		D3DXVECTOR4 vMeshFront = {};
		D3DXMATRIX matFront;
		D3DXMatrixRotationY(&matFront, vMeshRotation.y);//ȸ�����
		D3DXVec3Transform(&vMeshFront, &vMESH_FRONT/*(0,0,1)*/, &matFront);//�޽����� ���͸� ȸ��
		D3DXVec4Normalize(&vMeshFront, &vMeshFront);//���麤�� ����ȭ
		vMeshTranslation += (D3DXVECTOR3)vMeshFront * 0.1;//���� �޽��� ��ġ�� ���麤�͸� ���ؼ� �̵���Ų��.
	}
	if (GetAsyncKeyState(VK_DOWN) < 0) {
		//�޽��� ������ �̵�, �޽��� ���� ������ �ʱⰪ�� {0, 0, 1}�̰� ȸ���� ���� ������ �ٲ��.
		D3DXVECTOR4 vMeshFront = {};
		D3DXMATRIX matFront;
		D3DXMatrixRotationY(&matFront, vMeshRotation.y);//ȸ�����
		D3DXVec3Transform(&vMeshFront, &vMESH_FRONT/*(0,0,1)*/, &matFront);//�޽����� ���͸� ȸ��
		D3DXVec4Normalize(&vMeshFront, &vMeshFront);//���麤�� ����ȭ
		vMeshTranslation -= (D3DXVECTOR3)vMeshFront * 0.1;//���� �޽��� ��ġ�� ���麤�͸� ���ؼ� �̵���Ų��.
	}
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		//�޽��� ��(CCW)�� ȸ��
		vMeshRotation.y -= 0.1;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		//�޽��� ��(CW)�� ȸ��
		vMeshRotation.y += 0.1;
	}
}

void CAppMesh::OnRender(DWORD fDeltaTime) {
	//World transformation
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMatrixScaling(&matScale, vMeshScale.x, vMeshScale.y, vMeshScale.z);//ũ�����
	D3DXMatrixRotationY(&matRotation, vMeshRotation.y);//ȸ�����
	D3DXMatrixTranslation(&matTranslation, vMeshTranslation.x, vMeshTranslation.y, vMeshTranslation.z);//�̵����
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale * matRotation * matTranslation));
	//View, Projection transformation�� CD3DFramework���� �����Ѵ�.
	
	//������ ���� ����
	//Light Off
	//���� ���̴� �۾��� ���� ���� ���� �������� ����� ���ؽ� ������ �� �� �ִ�.
	//�׷��� ������ ���������� ��µȴ�.
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//ä����带 ���̾����������� ����
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//�ø��� ���� �ʵ��� ����
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
	//�ø��� �ٽ� ���ش�
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
