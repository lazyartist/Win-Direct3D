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
}

void CAppMesh::OnRender(DWORD fDeltaTime) {
	//World transformation
	XMMATRIX matWorld = XMMatrixScaling(1.0, 1.0, 1.0)//ũ�����
		*XMMatrixRotationX(0.0)//ȸ�����
		*XMMatrixTranslation(0.0, 0.0, 0.0);//�̵����
	XMFLOAT4X4 f44;
	XMStoreFloat4x4(&f44, matWorld);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&f44);
	//View transformation
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
		&pD3DFramework->vCameraEye,//ī�޶� ��ġ
		&pD3DFramework->vCameraAt,//�ٶ󺸴� ����
		&pD3DFramework->vCameraUp//ī�޶󿡼� �������� ���ϴ� ����
		//{ 10.0, 20.0, -15.0 },//ī�޶� ��ġ
		//{ 0.0, 0.0, 0.0 },//�ٶ󺸴� ����
		//{ 0.0, 1.0, 0.0 }//ī�޶󿡼� �������� ���ϴ� ����
	);
	//XMStoreFloat4x4(&f44, matView);
	//pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&f44);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//Projection trasformation(���ٹ�)
	XMMATRIX matProj = XMMatrixPerspectiveFovLH( //FovLH : Field of view Left Hand
		Const::fPI() / 2.0,
		1.0,
		1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
		100.0//�� ���� Z��
	);
	//Projection trasformation(��������)
	//XMMATRIX matProj = XMMatrixOrthographicLH(
	//	50.0,
	//	50.0,
	//	1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
	//	100.0//�� ���� Z��
	//);
	XMStoreFloat4x4(&f44, matProj);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&f44);

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
	if (pCubeVertexBufferInterface != nullptr) {
		pCubeVertexBufferInterface->Release();
		pCubeVertexBufferInterface = nullptr;
	}
	if (pCubeIndexedBufferInterface != nullptr) {
		pCubeIndexedBufferInterface->Release();
		pCubeIndexedBufferInterface = nullptr;
	}
}
