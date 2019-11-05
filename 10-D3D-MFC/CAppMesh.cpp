#include "stdafx.h"
#include "CAppMesh.h"

CAppMesh::CAppMesh() {
}
CAppMesh::~CAppMesh() {
}
void CAppMesh::OnInit() {
	//camera
	pD3DFramework->vCameraEye = { 5.0, 5, -5 };
	//���ؽ����� ����
	//pD3DFramework->pD3DDevice->CreateVertexBuffer(
	//	sizeof(pModelVertices),//���ؽ��迭�� ũ��
	//	D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
	//	D3DFVF_SVertexTexture,//���ؽ������� ����
	//	D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
	//	&pVB,//��ȯ�� ���ؽ����۸� ���� ������
	//	nullptr//������� �ʴ� ����, nullptr
	//);
	////���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	////Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	//void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	//pVB->Lock(0, 0, (void**)&pVertices, 0);
	//memcpy(pVertices, pModelVertices, sizeof(pModelVertices));//���ؽ����ۿ� ���ؽ��� �޸� ����
	//pVB->Unlock();//����� ����
	////texture
	//D3DXCreateTextureFromFile(pD3DFramework->pD3DDevice, "../Resources/Textures/darkbrown.png", &m_pTexture);

	//char szPath[] = "../Resources/Meshes/Tiger/%s";
	char szPath[] = "../Resources/Meshes/Nidalee/%s";
	char szFile[MAX_PATH] = {};
	sprintf_s(szFile, szPath, "ND.X");
	//sprintf_s(szFile, szPath, "tiger.x");
	//x���Ϸκ��� �����͸� ���� ������
	LPD3DXBUFFER pD3DXMtrlBuffer;//��Ƽ���� ������ �޾ƿ� ����, �������� �����͸� �ٷ�� ��ü�̹Ƿ� �� ��ȯ�� �ʿ��ϴ�.
	//x���� �ε�
	D3DXLoadMeshFromX(szFile,//x���� ���
		D3DXMESH_SYSTEMMEM, //�޽� �����͸� ������ �޸� ����, D3DXMESH_MANAGED, D3DXMESH_DYNAMIC
		pD3DFramework->pD3DDevice,//d3d ����̽�
		nullptr,//���� ������ ������ ����, directx9������ ������� �ʴ´�.
		&pD3DXMtrlBuffer,//��Ƽ���� ������ ����
		nullptr,//effect�� �ʱⰪ ����, directx9������ ������� �ʴ´�.
		&m_dwNumMaterials,//��Ƽ���� ���� ����
		&m_pMesh //������ �޽� ��ü�� ����(���� ������ ���� ����)
	);
	//��Ƽ���� ���۷κ��� ��Ƽ������ ������ �� �ֵ��� ���� �����͸� ��´�.
	D3DXMATERIAL *pD3dxMaterial = (D3DXMATERIAL *)pD3DXMtrlBuffer->GetBufferPointer();
	//��Ƽ������ ���� �� �� �ֵ��� �迭�� ����
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	//�ؽ��ĸ� ���� �� �� �ֵ��� �迭�� ����
	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];//��Ƽ���� �ϳ��� �ؽ��� �ϳ�(?)
	//��Ƽ���� ���۷κ��� ��Ƽ������ ����
	for (DWORD i = 0; i < m_dwNumMaterials; i++) {
		//material
		m_pMeshMaterials[i] = pD3dxMaterial[i].MatD3D;
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
		//texture
		m_pMeshTextures[i] = nullptr;
		if (pD3dxMaterial[i].pTextureFilename != nullptr && strlen(pD3dxMaterial[i].pTextureFilename) > 0) {
			//�ؽ��� ����
			sprintf_s(szFile, szPath, pD3dxMaterial[i].pTextureFilename);
			D3DXCreateTextureFromFile(pD3DFramework->pD3DDevice, szFile, &m_pMeshTextures[i]);
		}
	}
	//��Ƽ���� ������ ������ ��� ���������Ƿ� ����
	pD3DXMtrlBuffer->Release();
	pD3dxMaterial = nullptr;
	//����Ʈ ����
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);//�޽��� ���� ���Ͱ� �����Ƿ� ����Ʈ�� �Ҵ�.
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);//�ֺ����� ������� ����
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);//z���۸� �Ҵ�.

	//light
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	light.Specular = light.Ambient = light.Diffuse;
	D3DXVECTOR3 direction = { 10.0f, -10.0f, 10.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &direction);
	pD3DFramework->pD3DDevice->SetLight(0, &light);
	pD3DFramework->pD3DDevice->LightEnable(0, true);
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);//������ ����
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);//������ ����
}
void CAppMesh::OnUpdate(DWORD fDeltaTime) {
	float fSpeed = GetAsyncKeyState(VK_CONTROL) < 0 ? 0.01f : 0.1f;
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		m_vRotation.y -= fSpeed;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		m_vRotation.y += fSpeed;
	}
	if (GetAsyncKeyState(VK_UP) < 0) {
		m_vPos0.y += fSpeed;
	}
	if (GetAsyncKeyState(VK_DOWN) < 0) {
		m_vPos0.y -= fSpeed;
	}
}
void CAppMesh::OnRender(DWORD fDeltaTime) {
	//transformation
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMatrixRotationYawPitchRoll(&matRotation, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixScaling(&matScale, m_vScale0, m_vScale0, m_vScale0);
	D3DXMatrixTranslation(&matTranslation, m_vPos0.x, m_vPos0.y, m_vPos0.z);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale*matRotation*matTranslation));
	////light
	//D3DLIGHT9 light;
	//ZeroMemory(&light, sizeof(light));
	//light.Type = D3DLIGHT_DIRECTIONAL;
	//light.Diffuse.r = 1.0f;
	//light.Diffuse.g = 1.0f;
	//light.Diffuse.b = 1.0f;
	//light.Diffuse.a = 1.0f;
	//light.Specular = light.Ambient = light.Diffuse;
	//D3DXVECTOR3 direction = { 10.0f, -10.0f, 10.0f };
	//D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &direction);
	//pD3DFramework->pD3DDevice->SetLight(0, &light);
	//pD3DFramework->pD3DDevice->LightEnable(0, true);
	//pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);//������ ����
	//pD3DFramework->pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);//������ ����
	//model
	for (DWORD i = 0; i < m_dwNumMaterials; i++) {
		//material
		pD3DFramework->pD3DDevice->SetMaterial(&m_pMeshMaterials[i]);
		//texture
		pD3DFramework->pD3DDevice->SetTexture(0, m_pMeshTextures[i]);
		//mesh
		m_pMesh->DrawSubset(i);
	}
}
void CAppMesh::OnRelease() {
	//if (pVB) {
	//	pVB->Release();
	//}
	if (m_pMeshMaterials) {
		delete[] m_pMeshMaterials;
	}
	if (m_pMeshTextures) {
		delete[] m_pMeshTextures;
	}
}