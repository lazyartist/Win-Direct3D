#pragma once
#include "CApp.h"

class CAppCube :
	public CApp {
public:
	CAppCube();
	~CAppCube();
	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	SVertex2 sCubeVertices[4] = {
	{{-10.0f, -10.0f, 0.0f}, 0xffff0000},
	{{-10.0f, 10.0f, 0.0f}, 0xffff0000},
	{{10.0f, 10.0f, 0.0f}, 0xffff0000},
	{{10.0f, -10.0f, 0.0f}, 0xffff0000},
	};
	WORD sCubeIndices[6] = {
		0, 1, 2,
		0, 2, 3,
	};
	//SVertex2 sCubeVertices[6] = {
	//{{-100.0f, 0.0f, 0.0f}, 0xffff0000},
	//{{100.0f, 0.0f, 0.0f}, 0xffff0000},
	//{{0.0f, -100.0f, 0.0f}, 0xff00ff00},
	//{{0.0f, 100.0f, 0.0f}, 0xff00ff00},
	//{{0.0f, 0.0f, -100.0f}, 0xff0000ff},
	//{{0.0f, 0.0f, 100.0f}, 0xff0000ff},
	//};
//	{ -100.0, 0.0, 0.0, 0xffff0000},
//	{ 100.0, 0.0, 0.0, 0xffff0000 },
//	{ 0.0, -100.0, 0.0, 0xff00ff00 },
//	{ 0.0, 100.0, 0.0, 0xff00ff00 },
//	{ 0.0, 0.0, -100.0, 0xff0000ff },
//	{ 0.0, 0.0, 100.0, 0xff0000ff },
//};
	LPDIRECT3DVERTEXBUFFER9 pCubeVertexBufferInterface;//버텍스버퍼 인터페이스
	LPDIRECT3DINDEXBUFFER9 pCubeIndexedBufferInterface;//인덱스버퍼 인터페이스

};

