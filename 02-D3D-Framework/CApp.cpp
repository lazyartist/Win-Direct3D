#include "stdafx.h"
#include "CApp.h"
#include <iostream>
#include "CD3DFramework.h"

CApp::CApp() {
	OutputDebugString("CApp\n");
}


CApp::~CApp() {
	OutputDebugString("~CApp\n");
}

void CApp::Init(CD3DFramework *pD3DFramework) {
	this->pD3DFramework = pD3DFramework;
}

void CApp::Update(DWORD fDeltaTime) {
	
}

void CApp::Render(DWORD fDeltaTime) {
	OutputDebugString("Render parent");
}

void CApp::Release() {
	if (pVertexBuffer != nullptr) {
		pVertexBuffer->Release();
	}
}
