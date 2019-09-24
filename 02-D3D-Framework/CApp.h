#pragma once
#include "IApp.h"
#include <d3d9.h>
#include <DirectXMath.h>

using namespace DirectX;
class CD3DFramework;
class CApp : public IApp {
public:
	CApp();
	virtual ~CApp();
	virtual void Init(CD3DFramework *pD3DFramework);
	virtual void Update(DWORD fDeltaTime);
	virtual void Render(DWORD fDeltaTime);
	virtual void Release();

	CD3DFramework *pD3DFramework;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;//버텍스버퍼의 인터페이스
};

