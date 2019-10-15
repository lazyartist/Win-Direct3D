#pragma once
#include "CApp.h"

struct SSphere {
	D3DXVECTOR3 vPosition;
	float fRadius;
};
class CAppSphereCollision :
	public CApp {
public:
	CAppSphereCollision();
	virtual ~CAppSphereCollision();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	LPD3DXMESH pSphereMesh;
	SSphere sShpere0 = { {1.0f, 1.0f, 1.0f }, 1.0f };
	SSphere sShpere1 = { {0.0f, 0.0f, 0.0f }, 2.0f };
};

