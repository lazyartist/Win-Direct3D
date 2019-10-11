#include "stdafx.h"
#include <d3dx9shape.h>
#include "_05_CAppTerrain.h"

CAppTerrain::CAppTerrain() {
}
CAppTerrain::~CAppTerrain(){
}
void CAppTerrain::OnInit() {
	pD3DFramework->vCameraEye = {10.0f, 10.0f, -10.0f};

	//���� ���ؽ� ����, ��� ���� �����Ѵ�.
	int iTerrainVertexCount = iTerrainVertexRow * iTerrainVertexCol;
	vTerrainVertices = new SVertex[iTerrainVertexCount];
	for (size_t i = 0; i < iTerrainVertexCount; i++)
	{
		int iRow = i / iTerrainVertexCol;
		int iCol = i % iTerrainVertexCol;
		//������ ����
		//vTerrainVertices[i] = { (float)iCol * fTerrainTriangleScale, 0.0f, (float)iRow * -fTerrainTriangleScale, 0xffffffff };
		//����� �ھƿ��� ����
		vTerrainVertices[i] = { (float)iCol * fTerrainTriangleScale, 
			-(sin(D3DX_PI * 2.0f / iTerrainVertexCount * i + D3DX_PI * 0.5f)) * fTerrainHeight + fTerrainHeight, 
			(float)iRow * -fTerrainTriangleScale, 0xffffffff };
	}

	//���ؽ����� ����
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex)*iTerrainVertexCount,//���ؽ��迭�� ũ��
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFVF_SVertex,//���ؽ� Ÿ��
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pVB,//��ȯ�� ���ؽ����۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	//���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	//Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	pVB->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, vTerrainVertices, sizeof(SVertex)*iTerrainVertexCount);//���ؽ����ۿ� ���ؽ��� �޸� ����
	pVB->Unlock();//����� ����

	//���ؽ������� �ﰢ������ ���ϱ�
	//=(���ؽ��ο�-1) * (���ؽ��÷�-1)*2
	//ù��° ���ؽ����� ����(�������� ���ؽ���δ� �ﰢ���� ���� �� ���� ����)
	//�ι�° ���ؽ������ ���� ���� ���ؽ��� �����ϰ� ��� ���ؽ��� �ﰢ���� �ΰ��� ����
	int iTriangleColCount = (iTerrainVertexCol - 1) * 2;//���ٴ� �ﰢ�� ����
	int iTriangleCount = (iTerrainVertexRow - 1) * iTriangleColCount;

	//���ؽ��ε��� ����
	//���1. �»󿡼� ���Ϸ� ������ �ﰢ��
	//�� ����� ������ �簢�� ������ �׸��� ������ ������ �ܼ��ϴ�.
	int iIndicesCount = iTriangleCount * 3;
	vTerrainIndices = new WORD[iIndicesCount];
	for (size_t i = 0; i < iTriangleCount; i+=2)
	{
		int iTriangleRow = i / iTriangleColCount;//���� �ﰢ���� ���ȣ
		int iVerticesIndex = iTriangleRow + i / 2;
		int iIndicesIndex = i * 3;
		//�١��
		vTerrainIndices[iIndicesIndex] = iVerticesIndex;
		vTerrainIndices[iIndicesIndex + 1] = iVerticesIndex + 1 + iTerrainVertexCol;
		vTerrainIndices[iIndicesIndex + 2] = iVerticesIndex + iTerrainVertexCol;
		//����
		vTerrainIndices[iIndicesIndex + 3] = iVerticesIndex;
		vTerrainIndices[iIndicesIndex + 4] = iVerticesIndex + 1;
		vTerrainIndices[iIndicesIndex + 5] = iVerticesIndex + 1 + iTerrainVertexCol;
	}

	////���ؽ��ε��� ����
	////���2. ���Ͽ��� ������� ������ �ﰢ��
	////�� ����� ������ �簢�� ������ �׸��� �ʰ� �ﰢ�� ������ �׸��� ������ ������ �����ϴ�.
	////�ε����� 1���� �����ϸ� ���������� 1�� �����ϴ� �ͺ��� �����ϴ�.
	//int iIndicesCount = iTriangleCount * 3;
	//vTerrainIndices = new WORD[iIndicesCount];
	//for (size_t i = 0; i < iTriangleCount; i++)
	//{
	//	int iTriangleRow = i / iTriangleColCount;//���� �ﰢ���� ���ȣ
	//	//���� ������ ������ �ﰢ���� ������ �����Ƿ� ���� �� ù��° �������� �ǳʶٱ� ���� ���ȣ�� �����ش�.
	//	int iVerticesIndex = iTriangleRow;
	//	int iIndicesIndex = 0;
	//	iIndicesIndex = i * 3;
	//	if (i % 2 == 0) {
	//		//¦����° �ﰢ���� ��ס��̷��� �׸���.
	//		iVerticesIndex += i / 2;
	//		vTerrainIndices[iIndicesIndex] = iVerticesIndex;
	//		vTerrainIndices[iIndicesIndex + 1] = iVerticesIndex + 1;
	//		vTerrainIndices[iIndicesIndex + 2] = iVerticesIndex + iTerrainVertexCol;
	//	}
	//	else {
	//		//Ȧ����° �ﰢ���� �����̷��� �׸���.
	//		iVerticesIndex += i - (int)(i / 2);
	//		vTerrainIndices[iIndicesIndex] = iVerticesIndex;
	//		vTerrainIndices[iIndicesIndex + 1] = iVerticesIndex + iTerrainVertexCol;
	//		vTerrainIndices[iIndicesIndex + 2] = iVerticesIndex + iTerrainVertexCol - 1;
	//	}
	//}

	//�ε������� ����
	pD3DFramework->pD3DDevice->CreateIndexBuffer(
		sizeof(WORD)*iIndicesCount,//�ε����迭�� ũ��
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFMT_INDEX16,//�ε��� Ÿ��
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pIB,//��ȯ�� �ε������۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	//�ε������ۿ� �ε����� �����ϱ� ���� ���
	//Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� �ε����� ������ �޸� �����͸� ��ȯ�Ѵ�.
	void *pIndices;//�ε����� ������ �޸��� ���� �ּҸ� ���� ����
	pIB->Lock(0, sizeof(vTerrainIndices), (void**)&pIndices, 0);
	memcpy(pIndices, vTerrainIndices, sizeof(WORD)*iIndicesCount);//�ε������ۿ� �ε����� �޸� ����
	pIB->Unlock();//����� ����
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

void CAppTerrain::OnUpdate(DWORD fDeltaTime) {
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

void CAppTerrain::OnRender(DWORD fDeltaTime) {
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
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0���� ����
		pVB, //���ؽ�����
		0, //�޸𸮽��� ��ġ
		sizeof(SVertex) //���ؽ� ũ��
	);
	//2. D3D�� ���� �����͸� ��� �ؼ����ϴ��� �����Ѵ�.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);

	int iTriangleColCount = (iTerrainVertexCol - 1) * 2;//���ٴ� �ﰢ�� ����
	int iTriangleCount = (iTerrainVertexRow - 1) * iTriangleColCount;
	//�ε������� �Է�
	pD3DFramework->pD3DDevice->SetIndices(pIB);
	pD3DFramework->pD3DDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,//D3DPT_LINELIST, D3DPT_TRIANGLESTRIP
		0,//���������� �����ε��� ������. ���� 1�� ��� �ε��� ������ 0���� ���� ������ 1�ε����� ����Ų��.
		0,//���������� �ּ��ε���. ���� 1�� ��� 0�� ������ ������ �ʴ´�.
		iTerrainVertexRow * iTerrainVertexCol,//�׷��� ������ ����, BaseVertexIndex + MinIndex ��ŭ ���ָ� �ȴ�.
		0,//�ε��������� �����ε��� ������. ���� 1�� ��� 1�� �ε������ۺ��� �׸���.
		iTriangleCount//�׷��� ����(�ﰢ��)�� ����
	);

	//Light Off
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//�ø��� �ٽ� ���ش�
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CAppTerrain::OnRelease() {
	if (vTerrainVertices != nullptr) {
		delete[] vTerrainVertices;
	}
	if (vTerrainIndices != nullptr) {
		delete[] vTerrainIndices;
	}
	if (pVB != nullptr) {
		pVB->Release();
		pVB = nullptr;
	}
	if (pIB != nullptr) {
		pIB->Release();
		pIB = nullptr;
	}
}
