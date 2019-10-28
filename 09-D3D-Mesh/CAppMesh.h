#pragma once
#include "CApp.h"

class CAppMesh :
	public CApp {
public:
	CAppMesh();
	virtual ~CAppMesh();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	LPD3DXMESH m_pMesh;//메쉬를 저장할 변수
	D3DMATERIAL9 *m_pMeshMaterials;//머티리얼을 저장할 변수, 머티리얼은 여러개가 있을 수 있기 때문에 포인터 변수로 받는다.
	LPDIRECT3DTEXTURE9 *m_pMeshTextures;//텍스쳐 저장 변수
	DWORD m_dwNumMaterials;//머티리얼의 개수

	//float m_vScale0 = 2.0f;
	float m_vScale0 = 0.05f;
	D3DXVECTOR3 m_vRotation = { 0.0f, 0.0f , 0.0f };
	//D3DXVECTOR3 m_vRotation = { 3.14 / 3.0f, 3.14f / 3.0f, 0.0f };
	D3DXVECTOR3 m_vPos0 = { 0.0f, 0.0f , 0.0f };

	SVertexTexture pModelVertices[6] = {
		{D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f},
		{D3DXVECTOR3(-0.5f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.5f, 1.0f},
		{D3DXVECTOR3(0.0f, 0.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), 1.0f, 0.0f},

		{D3DXVECTOR3(0.0f, 0.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f},
		{D3DXVECTOR3(0.5f, 1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.5f, 1.0f},
		{D3DXVECTOR3(1.0f, 0.0f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), 1.0f, 0.0f},
	};
	LPDIRECT3DVERTEXBUFFER9 pVB;//버텍스버퍼 인터페이스
	LPDIRECT3DTEXTURE9 m_pTexture;
};

