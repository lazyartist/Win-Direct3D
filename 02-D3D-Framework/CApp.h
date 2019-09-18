#pragma once
#include "IApp.h"
class CD3DFramework;

class CApp : public IApp {
public:
	CApp();
	~CApp();
	void Init(CD3DFramework *pD3DFramework);
	void Update(DWORD fDeltaTime);
	void Render(DWORD fDeltaTime);

	CD3DFramework *pD3DFramework;
};

