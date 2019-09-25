#pragma once
#include "CApp.h"
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
};

