#include "stdafx.h"
#include "CAppTexture.h"

CAppTexture::CAppTexture() {
}
CAppTexture::~CAppTexture() {
}
void CAppTexture::OnInit() {
	//camera
	pD3DFramework->vCameraEye = { 0.0, 5, -10 };
	//버텍스버퍼 생성
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(pModelVertices),//버텍스배열의 크기
		D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
		D3DFVF_SVertexTexture,//버텍스데이터 사용법
		D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
		&pVB,//반환된 버텍스버퍼를 받을 포인터
		nullptr//사용하지 않는 변수, nullptr
	);
	//버텍스버퍼에 버텍스를 저장하기 위해 잠금
	//Lock을 하면 다른 자원이 접근할 수 없게되고 정점을 저장할 메모리 포인터를 반환한다.
	void *pVertices;//버텍스를 저장할 메모리의 시작 주소를 받을 변수
	pVB->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, pModelVertices, sizeof(pModelVertices));//버텍스버퍼에 버텍스를 메모리 복사
	pVB->Unlock();//잠금을 해제
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
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);//라이팅 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);//라이팅 설정
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
		0,//0으로 지정
		pVB, //버텍스버퍼
		0, //메모리시작 위치
		sizeof(SVertexTexture) //버텍스 크기
	);
	//2. D3D에 정점 데이터를 어떻게 해석해하는지 설정한다.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertexTexture);
	pD3DFramework->pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
void CAppTexture::OnRelease() {
	if (pVB) {
		pVB->Release();
	}
}