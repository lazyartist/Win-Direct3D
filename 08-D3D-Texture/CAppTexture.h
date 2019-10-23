#pragma once
#include "CApp.h"
class CAppTexture :
	public CApp {
public:
	CAppTexture();
	virtual ~CAppTexture();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	float m_vScale0 = 2.0f;
	D3DXVECTOR3 m_vRotation = { 3.14 / 3.0f, 3.14f / 3.0f, 0.0f };
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

