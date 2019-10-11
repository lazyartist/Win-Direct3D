#include "stdafx.h"
#include "_06_CAppFont.h"


CAppFont::CAppFont()
{
}


CAppFont::~CAppFont()
{
}

void CAppFont::OnInit() {
	LPD3DXFONT pFont;
	D3DXCreateFont(pD3DFramework->pD3DDevice, 20, 0, FW_NORMAL,
		1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		"Arial", &pFont);

	RECT rect;
	SetRect(&rect, 100, 100, 0, 0);
	pFont->DrawText(nullptr, "Text",
		-1/*���ڰ���, -1:NULL���ڱ��� ���*/, &rect, DT_NOCLIP, 
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	////���ؽ����� ����
	////Axis Vertices
	//pD3DFramework->pD3DDevice->CreateVertexBuffer(
	//	sizeof(SVertex) * sizeof(sAxisVertices) / sizeof(SVertex),//���ؽ�ũ��*����
	//	D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
	//	D3DFVF_SVertex,//���ؽ������� ����
	//	D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
	//	&pAxisVertexBufferInterface,//��ȯ�� ���ؽ����۸� ���� ������
	//	nullptr//������� �ʴ� ����, nullptr
	//);
	////���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	////Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	//void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	//pAxisVertexBufferInterface->Lock(0, 0, (void**)&pVertices, 0);
	//memcpy(pVertices, sAxisVertices, sizeof(sAxisVertices));//���ؽ����ۿ� ���ؽ��� �޸� ����
	//pAxisVertexBufferInterface->Unlock();//����� ����
	////Triangle Vertices
	//pD3DFramework->pD3DDevice->CreateVertexBuffer(
	//	sizeof(SVertex) * sizeof(sTriangleVertices) / sizeof(SVertex),//���ؽ�ũ��*����
	//	D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
	//	D3DFVF_SVertex,//���ؽ������� ����
	//	D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
	//	&pTriangleVertexBufferInterface,//��ȯ�� ���ؽ����۸� ���� ������
	//	nullptr//������� �ʴ� ����, nullptr
	//);
	////���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	////Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	////void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	//pTriangleVertexBufferInterface->Lock(0, 0, (void**)&pVertices, 0);
	//memcpy(pVertices, sTriangleVertices, sizeof(sTriangleVertices));//���ؽ����ۿ� ���ؽ��� �޸� ����
	//pTriangleVertexBufferInterface->Unlock();//����� ����

	////Viewport
	//D3DVIEWPORT9 d3dViewport9 = {};
	//d3dViewport9.X = 0;//������Ÿ�� ǥ�鿡�� ����Ʈ�� ���۵� x��ġ
	//d3dViewport9.Y = 0;//������Ÿ�� ǥ�鿡�� ����Ʈ�� ���۵� y��ġ
	//d3dViewport9.Width = 800;//������Ÿ�ٿ��� ��µ� ���� ũ��
	//d3dViewport9.Height = 800;//������Ÿ�ٿ��� ��µ� ���� ũ��
	//d3dViewport9.MinZ = 0.0;//���̹����� �ּ� ����
	//d3dViewport9.MaxZ = 1.0;//���̹����� �ִ� ����
	//pD3DFramework->pD3DDevice->SetViewport(&d3dViewport9);
}

void CAppFont::OnUpdate(DWORD fDeltaTime) {
}

void CAppFont::OnRender(DWORD fDeltaTime) {
	//LPD3DXFONT pFont;
	//D3DXCreateFont(pD3DFramework->pD3DDevice, 20, 0, FW_NORMAL,
	//	1, false, DEFAULT_CHARSET,
	//	OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
	//	DEFAULT_PITCH | FF_DONTCARE,
	//	"Arial", &pFont);

	//RECT rect;
	//SetRect(&rect, 100, 100, 0, 0);
	//pFont->DrawText(nullptr, "Text",
	//	-1/*���ڰ���, -1:NULL���ڱ��� ���*/, &rect, DT_NOCLIP,
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	////World transformation
	//XMMATRIX matWorld = XMMatrixScaling(1.0, 1.0, 1.0)//ũ�����
	//	*XMMatrixRotationX(0.0)//ȸ�����
	//	*XMMatrixTranslation(0.0, 0.0, 0.0);//�̵����
	//XMFLOAT4X4 f44;
	//XMStoreFloat4x4(&f44, matWorld);
	//pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&f44);
	////View transformation
	//XMMATRIX matView = XMMatrixLookAtLH(
	//	{ 10.0, 10.0, -10.0 },//ī�޶� ��ġ
	//	{ 0.0, 0.0, 0.0 },//�ٶ󺸴� ����
	//	{ 0.0, 1.0, 0.0 }//ī�޶󿡼� �������� ���ϴ� ����
	//);
	//XMStoreFloat4x4(&f44, matView);
	//pD3DFramework->pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&f44);
	////Projection trasformation(���ٹ�)
	////XMMATRIX matProj = XMMatrixPerspectiveFovLH( //Field of view Left Hand
	//	//Const::fPI() / 2.0,
	//	//1.0,
	//	//1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
	//	//100.0//�� ���� Z��
	////);
	////Projection trasformation(��������)
	//XMMATRIX matProj = XMMatrixOrthographicLH(
	//	50.0,
	//	50.0,
	//	1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
	//	100.0//�� ���� Z��
	//);
	//XMStoreFloat4x4(&f44, matProj);
	//pD3DFramework->pD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&f44);

	////Light Off
	////���� ���̴� �۾��� ���� ���� ���� �������� ����� ���ؽ� ������ �� �� �ִ�.
	////�׷��� ������ ���������� ��µȴ�.
	//pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	////3�� ���� ���
	////1. ���ؽ����ۿ� ���ؽ� ������ D3D ����̽��� �˷��ش�. ����� ���ؽ����۸� ��� ��Ʈ���� �����Ѵ�.
	//pD3DFramework->pD3DDevice->SetStreamSource(
	//	0,//0���� ����
	//	pAxisVertexBufferInterface, //���ؽ�����
	//	0, //�޸𸮽��� ��ġ
	//	sizeof(SVertex) //���ؽ� ũ��
	//);
	////2. D3D�� ���� �����͸� ��� �ؼ����ϴ��� �����Ѵ�.
	//pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);
	////3. ���� ������ ����ϱ� ���� DrawPrimitive() �Լ� ȣ��
	////DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()���� �ְ�
	////DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()�Լ��� ���Ӱ��߿� ���� ���ȴ�.
	////DrawIndexedPrimitive()�Լ��� ���� ������.
	//pD3DFramework->pD3DDevice->DrawPrimitive(
	//	D3DPT_LINELIST,
	//	//D3DPT_TRIANGLESTRIP,
	//	0, //����� ������ ���ؽ� �ε���
	//	3 //����� ����, ù��° �Ķ���� D3DPRIMITIVETYPE�� ������ �޴´�.
	//);
	////�ﰢ�� ���� ���
	//pD3DFramework->pD3DDevice->SetStreamSource(
	//	0,//0���� ����
	//	pTriangleVertexBufferInterface, //���ؽ�����
	//	0, //�޸𸮽��� ��ġ
	//	sizeof(SVertex) //���ؽ� ũ��
	//);
	////2. D3D�� ���� �����͸� ��� �ؼ����ϴ��� �����Ѵ�.
	//pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);
	////3. ���� ������ ����ϱ� ���� DrawPrimitive() �Լ� ȣ��
	////DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()���� �ְ�
	////DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()�Լ��� ���Ӱ��߿� ���� ���ȴ�.
	////DrawIndexedPrimitive()�Լ��� ���� ������.
	//pD3DFramework->pD3DDevice->DrawPrimitive(
	//	D3DPT_TRIANGLESTRIP,
	//	0, //����� ������ ���ؽ� �ε���
	//	1 //����� ����, ù��° �Ķ���� D3DPRIMITIVETYPE�� ������ �޴´�.
	//);


	////Light Off
	//pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void CAppFont::OnRelease() {
	//if (pAxisVertexBufferInterface != nullptr) {
	//	pAxisVertexBufferInterface->Release();
	//	pAxisVertexBufferInterface = nullptr;
	//}
	//if (pTriangleVertexBufferInterface != nullptr) {
	//	pTriangleVertexBufferInterface->Release();
	//	pTriangleVertexBufferInterface = nullptr;
	//}
}