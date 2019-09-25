#pragma once
#include "CApp.h"
#include "lib.h"
//#include "X:\StudySources\Win-Direct3D\2-d3d-framework22\app.h"
class CAppRender :
	public CApp {
public:
	CAppRender();
	~CAppRender();

	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	SVertex sVertices[3] = {
		{0.0, 10.0, 0.0, 0xffff0000},
		{10.0, -10.0, 0.0, 0xff00ff00},
		{-10.0, -10.0, 0.0, 0xff0000ff},
	};
};

