#pragma once
#include "IApp.h"
#include <d3d9.h>
#include <DirectXMath.h>
//#include <d3d12.h>
//#include <d3dx9math.h>
class CD3DFramework;

using namespace DirectX;
struct SVertex {
	float x, y, z;
	float rhw;
	DWORD color;
};
struct SVertex2 {
	//DirectX::XMFLOAT3 sPosition;
	XMFLOAT3 sPosition;
	//float x, y, z;
	DWORD color;
};
//#define D3DFVF_SVertex (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define D3DFVF_SVertex (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define D3DFVF_SVertex2 (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class CApp : public IApp {
public:
	CApp();
	~CApp();
	void Init(CD3DFramework *pD3DFramework);
	void Update(DWORD fDeltaTime);
	void Render(DWORD fDeltaTime);
	void Release();

	CD3DFramework *pD3DFramework;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;//버텍스버퍼의 인터페이스
	SVertex sVertices[3] = {
		{100.0f, 200.0f, 0.0f, 1.0f, 0xffff0000},
		{200.0f, 100.0f, 0.0f, 1.0f, 0xff00ff00},
		{300.0f, 200.0f, 0.0f, 1.0f, 0xff0000ff}
	};
};

