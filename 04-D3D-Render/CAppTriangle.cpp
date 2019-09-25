#include "stdafx.h"
#include <iostream>
#include "CAppTriangle.h"
#include "CD3DFramework.h"
#include "lib.h"

CAppTriangle::CAppTriangle() {
	dlog("CAppTriangle");
}
CAppTriangle::~CAppTriangle() {
	dlog("~CAppTriangle");
}
void CAppTriangle::OnInit() {
	dlog("OnInit");
	//���ؽ����� ����
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex) * sizeof(sVertices) / sizeof(SVertex),//���ؽ�ũ��*����
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFVF_SVertex,//���ؽ������� ����
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pVertexBuffer,//��ȯ�� ���ؽ����۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	//���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	//Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, sVertices, sizeof(sVertices));//���ؽ����ۿ� ���ؽ��� �޸� ����
	pVertexBuffer->Unlock();//����� ����
}

void CAppTriangle::OnUpdate(DWORD fDeltaTime) {
	/*char szText[99] = {};
	sprintf_s(szText, 99, "OnUpdate %d", fDeltaTime);
	dlog(szText);*/
	dlog("OnUpdate", (int)fDeltaTime);
}

void CAppTriangle::OnRender(DWORD fDeltaTime) {
	dlog("OnRender");
	//���ؽ� ���
	//1. ���ؽ����ۿ� ���ؽ� ������ D3D ����̽��� �˷��ش�. ����� ���ؽ����۸� ��� ��Ʈ���� �����Ѵ�.
	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0���� ����
		pVertexBuffer, //���ؽ�����
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
}

void CAppTriangle::OnRelease() {
	dlog("OnRelease");
}