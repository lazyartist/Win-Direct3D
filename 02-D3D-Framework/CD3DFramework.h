#pragma once
#include <d3d9.h>
//#include "CApp.h"
#include "IApp.h"
#include <mmsystem.h>//timeBeginPeriod
#pragma comment(lib,"winmm")

class CD3DFramework {
public:
	CD3DFramework();
	~CD3DFramework();
	HRESULT Init(HWND hWnd, IApp *pD3DApp, float fFrameTime);
	bool UpdateFrame();
	void Update();
	void Render();
	void Release();

	LPDIRECT3D9 g_pD3DInterface;
	LPDIRECT3DDEVICE9 g_pD3DDevice;
	HWND g_hWnd;
	IApp *pD3DApp;
	DWORD dPrevFrameTime;
	DWORD dDeltaTime;
	float fFrameTime;
};

