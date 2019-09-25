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

	SVertexRHW sVertexRHWs[3] = {
	{100.0f, 200.0f, 0.0f, 1.0f, 0xffff0000},
	{200.0f, 100.0f, 0.0f, 1.0f, 0xff00ff00},
	{300.0f, 200.0f, 0.0f, 1.0f, 0xff0000ff}
	};
};

