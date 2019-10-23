#include "stdafx.h"
#include "CAppTexture.h"

CAppTexture::CAppTexture() {
}
CAppTexture::~CAppTexture() {
}
void CAppTexture::OnInit() {
	//camera
	pD3DFramework->vCameraEye = { 0.0, 5, -10 };
	//���ؽ����� ����
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(pModelVertices),//���ؽ��迭�� ũ��
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFVF_SVertexTexture,//���ؽ������� ����
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pVB,//��ȯ�� ���ؽ����۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	//���ؽ����ۿ� ���ؽ��� �����ϱ� ���� ���
	//Lock�� �ϸ� �ٸ� �ڿ��� ������ �� ���Եǰ� ������ ������ �޸� �����͸� ��ȯ�Ѵ�.
	void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	pVB->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, pModelVertices, sizeof(pModelVertices));//���ؽ����ۿ� ���ؽ��� �޸� ����
	pVB->Unlock();//����� ����
	//texture
	D3DXCreateTextureFromFile(pD3DFramework->pD3DDevice, "../Resources/Textures/darkbrown.png", &m_pTexture);
}
void CAppTexture::OnUpdate(DWORD fDeltaTime) {
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
void CAppTexture::OnRender(DWORD fDeltaTime) {
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
	//material
	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(material));
	material.Ambient = material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Ambient = material.Diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	//material.Diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
	pD3DFramework->pD3DDevice->SetMaterial(&material);
	//transformation
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMatrixRotationYawPitchRoll(&matRotation, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixScaling(&matScale, m_vScale0, m_vScale0, m_vScale0);
	D3DXMatrixTranslation(&matTranslation, m_vPos0.x, m_vPos0.y, m_vPos0.z);
	//draw mesh
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale*matRotation*matTranslation));
	//texture
	pD3DFramework->pD3DDevice->SetTexture(0, m_pTexture);

	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0���� ����
		pVB, //���ؽ�����
		0, //�޸𸮽��� ��ġ
		sizeof(SVertexTexture) //���ؽ� ũ��
	);
	//2. D3D�� ���� �����͸� ��� �ؼ����ϴ��� �����Ѵ�.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertexTexture);
	pD3DFramework->pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
void CAppTexture::OnRelease() {
	if (pVB) {
		pVB->Release();
	}
}