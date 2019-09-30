#include "stdafx.h"
#include "CAppCube.h"


CAppCube::CAppCube() {
}


CAppCube::~CAppCube() {
}
void CAppCube::OnInit() {
	//���ؽ����� ����
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex2) * sizeof(sCubeVertices) / sizeof(SVertex2),//���ؽ�ũ��*����
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFVF_SVertex,//���ؽ������� ����
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
		sizeof(WORD) * sizeof(sCubeIndices) / sizeof(WORD),//���ؽ�ũ��*����
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFMT_INDEX16,//���ؽ������� ����
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pCubeIndexedBufferInterface,//��ȯ�� ���ؽ����۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	//���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	//Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	void *pIndices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	pCubeIndexedBufferInterface->Lock(0, sizeof(sCubeIndices), (void**)&pIndices, 0);
	memcpy(pIndices, sCubeIndices, sizeof(sCubeIndices));//���ؽ����ۿ� ���ؽ��� �޸� ����
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

void CAppCube::OnUpdate(DWORD fDeltaTime) {
}

void CAppCube::OnRender(DWORD fDeltaTime) {
	//World transformation
	XMMATRIX matWorld = XMMatrixScaling(1.0, 1.0, 1.0)//ũ�����
		*XMMatrixRotationX(0.0)//ȸ�����
		*XMMatrixTranslation(0.0, 0.0, 0.0);//�̵����
	XMFLOAT4X4 f44;
	XMStoreFloat4x4(&f44, matWorld);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&f44);
	//View transformation
	XMMATRIX matView = XMMatrixLookAtLH(
		{ 10.0, 10.0, -10.0 },//ī�޶� ��ġ
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

	//Light Off
	//���� ���̴� �۾��� ���� ���� ���� �������� ����� ���ؽ� ������ �� �� �ִ�.
	//�׷��� ������ ���������� ��µȴ�.
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//3�� ���� ���
	//1. ���ؽ����ۿ� ���ؽ� ������ D3D ����̽��� �˷��ش�. ����� ���ؽ����۸� ��� ��Ʈ���� �����Ѵ�.
	//pD3DFramework->pD3DDevice->SetStreamSource(
	//	0,//0���� ����
	//	pCubeVertexBufferInterface, //���ؽ�����
	//	0, //�޸𸮽��� ��ġ
	//	sizeof(SVertex) //���ؽ� ũ��
	//);
	pD3DFramework->pD3DDevice->SetRenderState(
		D3DRS_FILLMODE, D3DFILL_WIREFRAME
	);
	//2. D3D�� ���� �����͸� ��� �ؼ����ϴ��� �����Ѵ�.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);
	//3. ���� ������ ����ϱ� ���� DrawPrimitive() �Լ� ȣ��
	//DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()���� �ְ�
	//DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()�Լ��� ���Ӱ��߿� ���� ���ȴ�.
	//DrawIndexedPrimitive()�Լ��� ���� ������.
	pD3DFramework->pD3DDevice->DrawPrimitive(
		//D3DPT_LINELIST,
		D3DPT_TRIANGLESTRIP,
		0, //����� ������ ���ؽ� �ε���
		2 //����� ����, ù��° �Ķ���� D3DPRIMITIVETYPE�� ������ �޴´�.
	);

	//Light Off
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void CAppCube::OnRelease() {
	if (pCubeVertexBufferInterface != nullptr) {
		pCubeVertexBufferInterface->Release();
		pCubeVertexBufferInterface = nullptr;
	}
}
