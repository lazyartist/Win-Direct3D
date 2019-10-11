#pragma once
#include <d3d9.h>
//#include "CApp.h"
#include <mmsystem.h>//timeBeginPeriod
#pragma comment(lib,"winmm")
#include "lib.h"

class CApp;
class CD3DFramework {
public:
	CD3DFramework();
	~CD3DFramework();
	HRESULT Init(HWND hWnd, CApp *pApp, float fFrameTime);
	bool UpdateFrame();
	void Update();
	void Render();
	void Release();

	//Axis
	const float fAxisScale = 100.0;
	SVertex sAxisVertices[6] = {
		{-1.0, 0.0, 0.0, 0xffff0000},
		{1.0, 0.0, 0.0, 0xffff0000},
		{0.0, -1.0, 0.0, 0xff00ff00},
		{0.0, 1.0, 0.0, 0xff00ff00},
		{0.0, 0.0, -1.0, 0xff0000ff},
		{0.0, 0.0, 1.0, 0xff0000ff},
	};
	//Camera
	D3DXVECTOR3 vCameraEye = { 0.0, 0.0, -10.0 };
	//D3DXVECTOR3 vCameraEye = { 10.0, 10.0, -10.0 };
	D3DXVECTOR3 vCameraAt = { 0.0, 0.0 , 0.0 };
	D3DXVECTOR3 vCameraUp = { 0.0, 1.0 , 0.0 };
	LPDIRECT3DVERTEXBUFFER9 pAxisVertexBufferInterface;//축 버텍스버퍼 인터페이스
	LPDIRECT3D9 pD3DInterface;
	LPDIRECT3DDEVICE9 pD3DDevice;
	LPD3DXFONT pFont;
	HWND hWnd;
	CApp *pApp;
	DWORD dPrevFrameTime;
	DWORD dDeltaTime;
	float fFrameTime;
};

