#include "stdafx.h"
#include "CApp.h"
#include <iostream>

CApp::CApp() {
}


CApp::~CApp() {
}

void CApp::Init(CD3DFramework * pD3DFramework) {
	this->pD3DFramework = pD3DFramework;
}

void CApp::Update(DWORD fDeltaTime) {
	char szText[99] = {};
	sprintf_s(szText, 99, "Update %d\n", fDeltaTime);
	OutputDebugString(szText);
}

void CApp::Render(DWORD fDeltaTime) {
	OutputDebugString("Render");
}
