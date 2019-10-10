#pragma once
#include "CApp.h"

class CAppMesh : public CApp
{
public:
	CAppMesh();
	virtual ~CAppMesh();
	virtual void OnInit();;
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	const D3DXVECTOR3 vMESH_FRONT = { 0, 0, 1 };
	D3DXVECTOR3 vMeshScale = { 1.0, 1.0, 1.0 };
	D3DXVECTOR3 vMeshRotation = { 0.0, 0.0, 0.0 };
	D3DXVECTOR3 vMeshTranslation = { 0.0, 0.0, 0.0 };
	//LPDIRECT3DVERTEXBUFFER9 pCubeVertexBufferInterface;//���ؽ����� �������̽�
	//LPDIRECT3DINDEXBUFFER9 pCubeIndexedBufferInterface;//�ε������� �������̽�
};

