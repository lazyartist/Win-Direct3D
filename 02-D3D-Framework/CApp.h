#pragma once
#include "lib.h"
//#include <d3d9.h>
//#include <DirectXMath.h>
#include "CD3DFramework.h"

using namespace DirectX;

class CApp {
public:
	CApp();
	virtual ~CApp();
	virtual void Init(CD3DFramework *pD3DFramework);
	virtual void Update(DWORD fDeltaTime);
	virtual void Render(DWORD fDeltaTime);
	virtual void Release();
	virtual void OnInit() = 0;
	virtual void OnUpdate(DWORD fDeltaTime) = 0;
	virtual void OnRender(DWORD fDeltaTime) = 0;
	virtual void OnRelease() = 0;

	CD3DFramework *pD3DFramework;
};

