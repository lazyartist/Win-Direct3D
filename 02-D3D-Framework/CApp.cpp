#include "stdafx.h"
#include "CApp.h"


CApp::CApp() {
}


CApp::~CApp() {
}

void CApp::Init(CD3DFramework * pD3DFramework) {
	this->pD3DFramework = pD3DFramework;
}

void CApp::Update(DWORD fDeltaTime) {
	OutputDebugString("Update");
}
