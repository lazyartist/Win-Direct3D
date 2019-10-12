#include "stdafx.h"
#include "CAppSound.h"

CAppSound::CAppSound()
{
}
CAppSound::~CAppSound()
{
}
void CAppSound::OnInit() {
	FMOD_System_Create(&pFmodSystem);
	FMOD_System_Init(pFmodSystem, 32, FMOD_INIT_NORMAL, nullptr);

	FMOD_System_CreateSound(pFmodSystem, "../Resources/Sounds/sawing-wood-daniel_simon.mp3", 
		//FMOD_DEFAULT = FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE
		//FMOD_LOOP_NORMAL : ������� ���� �ݺ��� �ʿ��� ���
		FMOD_DEFAULT,
		0, &pFmodSound);

	//���� ���
	FMOD_System_PlaySound(pFmodSystem, pFmodSound, nullptr, false, &pFmodChannel);
}
void CAppSound::OnUpdate(DWORD fDeltaTime) {
	if (GetAsyncKeyState(VK_SPACE) < 0) {
		//���� ����
		FMOD_Channel_Stop(pFmodChannel);
	}
	if (GetAsyncKeyState(VK_DOWN) < 0) {
		//���� ���� ����
		FMOD_Channel_SetVolume(pFmodChannel, 0.1f/*0~1*/);
	}
	//���� ��Ʈ���� ������ ����
	FMOD_System_Update(pFmodSystem);
}
void CAppSound::OnRender(DWORD fDeltaTime) {
	
}
void CAppSound::OnRelease() {
	//���� ����
	if (pFmodSound) {
		FMOD_Sound_Release(pFmodSound);
	}
	//FMOD ����
	if (pFmodSystem) {
		FMOD_System_Close(pFmodSystem);
		FMOD_System_Release(pFmodSystem);
	}
}