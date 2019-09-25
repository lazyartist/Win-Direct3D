#pragma once
#include <d3d9.h>
//#include "CApp.h"
//#include "IApp.h"
#include "CApp.h"
#include <mmsystem.h>//timeBeginPeriod
#pragma comment(lib,"winmm")

class CD3DFramework {
public:
	CD3DFramework();
	~CD3DFramework();
	HRESULT Init(HWND hWnd, CApp *pApp, float fFrameTime);
	bool UpdateFrame();
	void Update();
	void Render();
	void Release();

	LPDIRECT3D9 pD3DInterface;
	LPDIRECT3DDEVICE9 pD3DDevice;
	HWND hWnd;
	CApp *pApp;
	DWORD dPrevFrameTime;
	DWORD dDeltaTime;
	float fFrameTime;
};

