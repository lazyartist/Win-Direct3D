#pragma once
#include "CApp.h"
class CAppBoxCollision :
	public CApp {
public:
	CAppBoxCollision();
	virtual ~CAppBoxCollision();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	LPD3DXMESH m_pMesh;
	LPD3DXMESH m_pBoundingBoxMesh;
	D3DXVECTOR3 m_vBoundingBoxMin;
	D3DXVECTOR3 m_vBoundingBoxMax;
	float m_vScale0 = 1.0f;
	float m_vScale1 = 2.0f;
	D3DXVECTOR3 m_vRotation = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 m_vPos0 = { 0.0f, 0.0f , 0.0f };
	D3DXVECTOR3 m_vPos1 = { 3.0f, 0.0f , 0.0f };
};