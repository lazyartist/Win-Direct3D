#pragma once
#include <CApp.h>
#include "fmod.h"

class CAppSound :
	public CApp
{
public:
	CAppSound();
	virtual ~CAppSound();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	FMOD_SYSTEM *pFmodSystem;
	FMOD_SOUND *pFmodSound;//���� ���ϰ� �ϴ��� ����
	FMOD_CHANNEL *pFmodChannel;
};

