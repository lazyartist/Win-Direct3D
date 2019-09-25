#pragma once
#include "CApp.h"
//#include "X:\StudySources\Win-Direct3D\02-D3D-Framework\CApp.h"
class CAppTriangle :
	public CApp {
public:
	CAppTriangle();
	virtual ~CAppTriangle();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	struct SVertex {
		float x, y, z, rhw;
		DWORD color;
	};
	struct SVertex2 {
		//DirectX::XMFLOAT3 sPosition;
		XMFLOAT3 sPosition;
		//float x, y, z;
		DWORD color;
	};
#define D3DFVF_SVertex (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define D3DFVF_SVertex2 (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

	SVertex sVertices[3] = {
	{100.0f, 200.0f, 0.0f, 1.0f, 0xffff0000},
	{200.0f, 100.0f, 0.0f, 1.0f, 0xff00ff00},
	{300.0f, 200.0f, 0.0f, 1.0f, 0xff0000ff}
	};
};

