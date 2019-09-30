#pragma once
#include "CApp.h"
#include "lib.h"
//#include "X:\StudySources\Win-Direct3D\2-d3d-framework22\app.h"
class CAppAxisTriangle :
	public CApp {
public:
	CAppAxisTriangle();
	~CAppAxisTriangle();

	virtual void OnInit();
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();

	//SVertex sAxisVertices[6] = {
	//{{-100.0, 0.0, 0.0}, 0xffff0000},
	//{{100.0, 0.0, 0.0}, 0xffff0000},
	//{{0.0, -100.0, 0.0}, 0xff00ff00},
	//{{0.0, 100.0, 0.0}, 0xff00ff00},
	//{{0.0, 0.0, -100.0}, 0xff0000ff},
	//{{0.0, 0.0, 100.0}, 0xff0000ff},
	//};
	//SVertex sTriangleVertices[3] = {
	//	{{0.0, 10.0, 0.0}, 0xffff0000 },
	//	{{10.0, -10.0, 0.0}, 0xff00ff00},
	//	{{-10.0, -10.0, 0.0}, 0xff0000ff},
	//};
	SVertex sAxisVertices[6] = {
	{-100.0, 0.0, 0.0, 0xffff0000},
	{100.0, 0.0, 0.0, 0xffff0000},
	{0.0, -100.0, 0.0, 0xff00ff00},
	{0.0, 100.0, 0.0, 0xff00ff00},
	{0.0, 0.0, -100.0, 0xff0000ff},
	{0.0, 0.0, 100.0, 0xff0000ff},
	};
	SVertex sTriangleVertices[3] = {
		{0.0, 10.0, 0.0, 0xffff0000},
		{10.0, -10.0, 0.0, 0xff00ff00},
		{-10.0, -10.0, 0.0, 0xff0000ff},
	};
	LPDIRECT3DVERTEXBUFFER9 pAxisVertexBufferInterface;//버텍스버퍼 인터페이스
	LPDIRECT3DVERTEXBUFFER9 pTriangleVertexBufferInterface;//버텍스버퍼 인터페이스
};

