#include "stdafx.h"
#include "CApp.h"
#include <iostream>
#include "CD3DFramework.h"
#include "lib.h"

CApp::CApp() {
	dlog("CApp");
}


CApp::~CApp() {
	dlog("~CApp");
}

void CApp::Init(CD3DFramework *pD3DFramework) {
	dlog("Init");
	this->pD3DFramework = pD3DFramework;
	OnInit();
}

void CApp::Update(DWORD fDeltaTime) {
	dlog("Update");
	OnUpdate(fDeltaTime);
}

void CApp::Render(DWORD fDeltaTime) {
	dlog("Render");
	OnRender(fDeltaTime);
}

void CApp::Release() {
	dlog("Release");
	if (pVertexBuffer != nullptr) {
		pVertexBuffer->Release();
	}
	OnRelease();
}
