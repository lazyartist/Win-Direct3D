#include "stdafx.h"
#include "CAppRender.h"


CAppRender::CAppRender() {
}


CAppRender::~CAppRender() {
}

void CAppRender::OnInit() {
	//���ؽ����� ����
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex) * sizeof(sVertices) / sizeof(SVertex),//���ؽ�ũ��*����
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFVF_SVertex,//���ؽ������� ����
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pVertexBufferInterface,//��ȯ�� ���ؽ����۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	//���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	//Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	pVertexBufferInterface->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, sVertices, sizeof(sVertices));//���ؽ����ۿ� ���ؽ��� �޸� ����
	pVertexBufferInterface->Unlock();//����� ����

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
	XMMATRIX matWorld = XMMatrixScaling(1.0, 1.0, 1.0)//ũ�����
		*XMMatrixRotationX(0.0)//ȸ�����
		*XMMatrixTranslation(0.0, 0.0, 0.0);//�̵����
	XMFLOAT4X4 f44;
	XMStoreFloat4x4(&f44, matWorld);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&f44);
	//View transformation
	XMMATRIX matView = XMMatrixLookAtLH(
		{ 0.0, 0.0, -10.0 },//ī�޶� ��ġ
		{ 0.0, 0.0, 0.0 },//�ٶ󺸴� ����
		{ 0.0, 1.0, 0.0 }//ī�޶󿡼� �������� ���ϴ� ����
	);
	//XMFLOAT4X4 f44_2;
	XMStoreFloat4x4(&f44, matView);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&f44);
	//Projection trasformation
	XMMATRIX matProj = XMMatrixPerspectiveFovLH(
		Const::fPI() / 2.0,
		1.0,
		1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
		100.0//�� ���� Z��
	);
	//XMFLOAT4X4 f44_3;
	XMStoreFloat4x4(&f44, matProj);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&f44);

	//Light Off
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//���ؽ� ���
	//1. ���ؽ����ۿ� ���ؽ� ������ D3D ����̽��� �˷��ش�. ����� ���ؽ����۸� ��� ��Ʈ���� �����Ѵ�.
	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0���� ����
		pVertexBufferInterface, //���ؽ�����
		0, //�޸𸮽��� ��ġ
		sizeof(SVertex) //���ؽ� ũ��
	);
	//2. D3D�� ���� ���̴� ������ ����, ��κ� FVF�� �����Ѵ�.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);
	//3. ���� ������ ����ϱ� ���� DrawPrimitive() �Լ� ȣ��
	//DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()���� �ְ�
	//DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()�Լ��� ���Ӱ��߿� ���� ���ȴ�.
	//DrawIndexedPrimitive()�Լ��� ���� ������.
	pD3DFramework->pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0, //����� ������ ���ؽ� �ε���
		1 //����� ����, ù��° �Ķ���� D3DPRIMITIVETYPE�� ������ �޴´�.
	);

	//Light Off
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void CAppRender::OnRelease() {
}
