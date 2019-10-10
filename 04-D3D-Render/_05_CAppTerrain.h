#pragma once
#include "CApp.h"
class CAppTerrain :
	public CApp
{
public:
	CAppTerrain();
	virtual ~CAppTerrain();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	const int iTerrainVertexRow = 50 + 1;
	const int iTerrainVertexCol = 50 + 1;
	const float fTerrainTriangleScale = 0.2f;
	const float fTerrainHeight = 3.0f;
	SVertex *vTerrainVertices;
	WORD *vTerrainIndices;

	const D3DXVECTOR3 vMESH_FRONT = { 0, 0, 1 };
	D3DXVECTOR3 vMeshScale = { 1.0, 1.0, 1.0 };
	D3DXVECTOR3 vMeshRotation = { 0.0, 0.0, 0.0 };
	D3DXVECTOR3 vMeshTranslation = { 0.0, 0.0, 0.0 };
	LPDIRECT3DVERTEXBUFFER9 pVB;//버텍스버퍼 인터페이스
	LPDIRECT3DINDEXBUFFER9 pIB;//인덱스버퍼 인터페이스
};

