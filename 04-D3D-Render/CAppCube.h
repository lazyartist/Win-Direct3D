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
	//정육면체 정점
	SVertex2 sCubeVertices[8] = {
	{{-10.0f, -10.0f, 0.0f}, 0xffffffff},
	{{-10.0f, 10.0f, 0.0f}, 0xffff0000},
	{{10.0f, 10.0f, 0.0f}, 0xff00ff00},
	{{10.0f, -10.0f, 0.0f}, 0xff00ff},

	{{-10.0f, -10.0f, 20.0f}, 0xffffffff},
	{{-10.0f, 10.0f, 20.0f}, 0xffff0000},
	{{10.0f, 10.0f, 20.0f}, 0xff00ff00},
	{{10.0f, -10.0f, 20.0f}, 0xff0000ff},
	};
	//정육면체 인덱스, 면의 방향이 바깥을 향하도록 시계방향으로 그린다.
	WORD sCubeIndices[36] = {
		//앞
		0, 1, 2,
		0, 2, 3,
		//뒤
		7, 6, 5,
		7, 5, 4,
		//좌
		4, 5, 1,
		4, 1, 0,
		//우
		3, 2, 6,
		3, 6, 7,
		//상
		1, 5, 6,
		1, 6, 2,
		//하
		3, 7, 4,
		3, 4, 0,
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

