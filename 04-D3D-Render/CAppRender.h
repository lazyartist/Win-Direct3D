#pragma once
#include "IApp.h"
//#include "X:\StudySources\Win-Direct3D\2-d3d-framework22\app.h"
class CAppRender :
	public IApp {
public:
	CAppRender();
	~CAppRender();

	void Init(CD3DFramework * pD3DFramework);
	void Update(unsigned long fDeltaTime);
	void Render(unsigned long fDeltaTime);
	void Release();
};

