#include "stdafx.h"
#include "_04_CAppMesh.h"
//#include <d3d12shader.h>
#include <d3dx9shape.h>

CAppMesh::CAppMesh() {
}
CAppMesh::~CAppMesh() {
}
void CAppMesh::OnInit() {
	//���ؽ����� ����
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(sCubeVertices),//���ؽ��迭�� ũ��
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFVF_SVertex,//���ؽ� Ÿ��
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pCubeVertexBufferInterface,//��ȯ�� ���ؽ����۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	//���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	//Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	pCubeVertexBufferInterface->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, sCubeVertices, sizeof(sCubeVertices));//���ؽ����ۿ� ���ؽ��� �޸� ����
	pCubeVertexBufferInterface->Unlock();//����� ����

	//�ε������� ����
	pD3DFramework->pD3DDevice->CreateIndexBuffer(
		sizeof(sCubeIndices),//�ε����迭�� ũ��
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFMT_INDEX16,//�ε��� Ÿ��
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pCubeIndexedBufferInterface,//��ȯ�� �ε������۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	//�ε������ۿ� �ε����� �����ϱ� ���� ���
	//Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� �ε����� ������ �޸� �����͸� ��ȯ�Ѵ�.
	void *pIndices;//�ε����� ������ �޸��� ���� �ּҸ� ���� ����
	pCubeIndexedBufferInterface->Lock(0, sizeof(sCubeIndices), (void**)&pIndices, 0);
	memcpy(pIndices, sCubeIndices, sizeof(sCubeIndices));//�ε������ۿ� �ε����� �޸� ����
	pCubeIndexedBufferInterface->Unlock();//����� ����

	//Viewport
	D3DVIEWPORT9 d3dViewport9 = {};
	d3dViewport9.X = 0;//������Ÿ�� ǥ�鿡�� ����Ʈ�� ���۵� x��ġ
	d3dViewport9.Y = 0;//������Ÿ�� ǥ�鿡�� ����Ʈ�� ���۵� y��ġ
	d3dViewport9.Width = 800;//������Ÿ�ٿ��� ��µ� ���� ũ��
	d3dViewport9.Height = 800;//������Ÿ�ٿ��� ��µ� ���� ũ��
	d3dViewport9.MinZ = 0.0;//���̹����� �ּ� ����
	d3dViewport9.MaxZ = 1.0;//���̹����� �ִ� ����
	pD3DFramework->pD3DDevice->SetViewport(&d3dViewport9);
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
	XMMATRIX matView = XMMatrixLookAtLH(
		{ 10.0, 20.0, -15.0 },//ī�޶� ��ġ
		{ 0.0, 0.0, 0.0 },//�ٶ󺸴� ����
		{ 0.0, 1.0, 0.0 }//ī�޶󿡼� �������� ���ϴ� ����
	);
	XMStoreFloat4x4(&f44, matView);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&f44);
	//Projection trasformation(���ٹ�)
	//XMMATRIX matProj = XMMatrixPerspectiveFovLH( //Field of view Left Hand
		//Const::fPI() / 2.0,
		//1.0,
		//1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
		//100.0//�� ���� Z��
	//);
	//Projection trasformation(��������)
	XMMATRIX matProj = XMMatrixOrthographicLH(
		50.0,
		50.0,
		1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
		100.0//�� ���� Z��
	);
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
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//3�� ���� ���
	//1. ���ؽ����ۿ� ���ؽ� ������ D3D ����̽��� �˷��ش�. ����� ���ؽ����۸� ��� ��Ʈ���� �����Ѵ�.
	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0���� ����
		pCubeVertexBufferInterface, //���ؽ�����
		0, //�޸𸮽��� ��ġ
		sizeof(SVertex2) //���ؽ� ũ��
	);
	//2. D3D�� ���� �����͸� ��� �ؼ����ϴ��� �����Ѵ�.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);
	//�ε������� �Է�
	pD3DFramework->pD3DDevice->SetIndices(pCubeIndexedBufferInterface);
	//3. ���� ������ ����ϱ� ���� DrawPrimitive() �Լ� ȣ��
	//DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()���� �ְ�
	//DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()�Լ��� ���Ӱ��߿� ���� ���ȴ�.
	//DrawIndexedPrimitive()�Լ��� ���� ������.
	//pD3DFramework->pD3DDevice->DrawPrimitive(
	pD3DFramework->pD3DDevice->DrawIndexedPrimitive(
		//D3DPT_LINELIST,
		//D3DPT_TRIANGLESTRIP,
		D3DPT_TRIANGLELIST,
		0,//���������� �����ε��� ������. ���� 1�� ��� �ε��� ������ 0���� ���� ������ 1�ε����� ����Ų��.
		0,//���������� �ּ��ε���. ���� 1�� ��� 0�� ������ ������ �ʴ´�.
		8,//�׷��� ������ ����, BaseVertexIndex + MinIndex ��ŭ ���ָ� �ȴ�.
		0,//�ε��������� �����ε��� ������. ���� 1�� ��� 1�� �ε������ۺ��� �׸���.
		12//�׷��� ����(�ﰢ��)�� ����
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
