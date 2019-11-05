#include "stdafx.h"
#include "CAppMesh.h"

CAppMesh::CAppMesh() {
}
CAppMesh::~CAppMesh() {
}
void CAppMesh::OnInit() {
	//camera
	pD3DFramework->vCameraEye = { 5.0, 5, -5 };
	//버텍스버퍼 생성
	//pD3DFramework->pD3DDevice->CreateVertexBuffer(
	//	sizeof(pModelVertices),//버텍스배열의 크기
	//	D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
	//	D3DFVF_SVertexTexture,//버텍스데이터 사용법
	//	D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
	//	&pVB,//반환된 버텍스버퍼를 받을 포인터
	//	nullptr//사용하지 않는 변수, nullptr
	//);
	////버텍스버퍼에 버텍스를 저장하기 위해 잠금
	////Lock을 하면 다른 자원이 접근할 수 없게되고 정점을 저장할 메모리 포인터를 반환한다.
	//void *pVertices;//버텍스를 저장할 메모리의 시작 주소를 받을 변수
	//pVB->Lock(0, 0, (void**)&pVertices, 0);
	//memcpy(pVertices, pModelVertices, sizeof(pModelVertices));//버텍스버퍼에 버텍스를 메모리 복사
	//pVB->Unlock();//잠금을 해제
	////texture
	//D3DXCreateTextureFromFile(pD3DFramework->pD3DDevice, "../Resources/Textures/darkbrown.png", &m_pTexture);

	//char szPath[] = "../Resources/Meshes/Tiger/%s";
	char szPath[] = "../Resources/Meshes/Nidalee/%s";
	char szFile[MAX_PATH] = {};
	sprintf_s(szFile, szPath, "ND.X");
	//sprintf_s(szFile, szPath, "tiger.x");
	//x파일로부터 데이터를 받을 변수들
	LPD3DXBUFFER pD3DXMtrlBuffer;//머티리얼 정보를 받아올 버퍼, 범용적인 데이터를 다룬는 객체이므로 형 변환이 필요하다.
	//x파일 로드
	D3DXLoadMeshFromX(szFile,//x파일 경로
		D3DXMESH_SYSTEMMEM, //메쉬 데이터를 생성할 메모리 지정, D3DXMESH_MANAGED, D3DXMESH_DYNAMIC
		pD3DFramework->pD3DDevice,//d3d 디바이스
		nullptr,//인접 정점의 정보를 리턴, directx9에서는 사용하지 않는다.
		&pD3DXMtrlBuffer,//머티리얼 정보를 리턴
		nullptr,//effect의 초기값 리턴, directx9에서는 사용하지 않는다.
		&m_dwNumMaterials,//머티리얼 개수 리턴
		&m_pMesh //생성된 메쉬 객체를 리턴(정점 정보를 가진 버퍼)
	);
	//머티리얼 버퍼로부터 머티리얼을 가져올 수 있도록 시작 포인터를 얻는다.
	D3DXMATERIAL *pD3dxMaterial = (D3DXMATERIAL *)pD3DXMtrlBuffer->GetBufferPointer();
	//머티리얼을 저장 할 수 있도록 배열을 생성
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	//텍스쳐를 저장 할 수 있도록 배열을 생성
	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];//머티리얼 하나당 텍스쳐 하나(?)
	//머티리얼 버퍼로부터 머티리얼을 저장
	for (DWORD i = 0; i < m_dwNumMaterials; i++) {
		//material
		m_pMeshMaterials[i] = pD3dxMaterial[i].MatD3D;
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
		//texture
		m_pMeshTextures[i] = nullptr;
		if (pD3dxMaterial[i].pTextureFilename != nullptr && strlen(pD3dxMaterial[i].pTextureFilename) > 0) {
			//텍스쳐 생성
			sprintf_s(szFile, szPath, pD3dxMaterial[i].pTextureFilename);
			D3DXCreateTextureFromFile(pD3DFramework->pD3DDevice, szFile, &m_pMeshTextures[i]);
		}
	}
	//머티리얼 버퍼의 정보를 모두 저장했으므로 해제
	pD3DXMtrlBuffer->Release();
	pD3dxMaterial = nullptr;
	//라이트 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);//메쉬에 정정 벡터가 있으므로 라이트를 켠다.
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);//주변광을 백색으로 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);//z버퍼를 켠다.

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
	//pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);//라이팅 설정
	//pD3DFramework->pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);//라이팅 설정
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