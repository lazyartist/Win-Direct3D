#pragma once
#include "X:\StudySources\Win-Direct3D\02-D3D-Framework\CApp.h"
class CAppFont :
	public CApp
{
public:
	CAppFont();
	virtual ~CAppFont();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();
};

