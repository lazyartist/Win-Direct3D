#pragma once
#include "CApp.h"

class CAppMesh : public CApp
{
public:
	CAppMesh();
	~CAppMesh();

	virtual void OnInit();;
	virtual void OnUpdate(DWORD fDeltaTime);
	virtual void OnRender(DWORD fDeltaTime);
	virtual void OnRelease();
	//������ü ����
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
	//������ü �ε���, ���� ������ �ٱ��� ���ϵ��� �ð�������� �׸���.
	WORD sCubeIndices[36] = {
		//��
		0, 1, 2,
		0, 2, 3,
		//��
		7, 6, 5,
		7, 5, 4,
		//��
		4, 5, 1,
		4, 1, 0,
		//��
		3, 2, 6,
		3, 6, 7,
		//��
		1, 5, 6,
		1, 6, 2,
		//��
		3, 7, 4,
		3, 4, 0,
	};
	LPDIRECT3DVERTEXBUFFER9 pCubeVertexBufferInterface;//���ؽ����� �������̽�
	LPDIRECT3DINDEXBUFFER9 pCubeIndexedBufferInterface;//�ε������� �������̽�
};

