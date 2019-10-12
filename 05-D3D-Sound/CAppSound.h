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
	FMOD_SOUND *pFmodSound;//사운드 파일과 일대일 대응
	FMOD_CHANNEL *pFmodChannel;
};

