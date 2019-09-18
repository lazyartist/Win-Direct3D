#include "stdafx.h"
#include "CApp.h"
#include <iostream>
#include "CD3DFramework.h"

CApp::CApp() {
}


CApp::~CApp() {
}

void CApp::Init(CD3DFramework *pD3DFramework) {
	this->pD3DFramework = pD3DFramework;

	//버텍스버퍼 생성
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex) * sizeof(sVertices) / sizeof(SVertex),//버텍스크기*개수
		D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
		D3DFVF_SVertex,//버텍스데이터 사용법
		D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
		&pVertexBuffer,//반환된 버텍스버퍼를 받을 포인터
		nullptr//사용하지 않는 변수, nullptr
	);
	//버텍스버퍼에 버텍스를 저장하기 위해 잠금
	//Lock을 하면 다른 자원이 접근할 수 없게되고 정점을 저장할 메모리 포인터를 반환한다.
	void *pVertices;//버텍스를 저장할 메모리의 시작 주소를 받을 변수
	pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, sVertices, sizeof(sVertices));//버텍스버퍼에 버텍스를 메모리 복사
	pVertexBuffer->Unlock();//잠금을 해제
}

void CApp::Update(DWORD fDeltaTime) {
	char szText[99] = {};
	sprintf_s(szText, 99, "Update %d\n", fDeltaTime);
	OutputDebugString(szText);
}

void CApp::Render(DWORD fDeltaTime) {
	OutputDebugString("Render");
	//버텍스 출력
	//1. 버텍스버퍼와 버텍스 포맷을 D3D 디바이스에 알려준다. 출력할 버텍스버퍼를 출력 스트림과 연결한다.
	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0으로 지정
		pVertexBuffer, //버텍스버퍼
		0, //메모리시작 위치
		sizeof(SVertex) //버텍스 크기
	);
	//2. D3D에 정점 셰이더 정보를 지정, 대부분 FVF만 지정한다.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);
	//3. 기하 정보를 출력하기 위한 DrawPrimitive() 함수 호출
	//DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()등이 있고
	//DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()함수가 게임개발에 많이 사용된다.
	//DrawIndexedPrimitive()함수가 가장 빠르다.
	pD3DFramework->pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0, //출력을 시작할 버텍스 인덱스
		1 //출력할 개수, 첫번째 파라미터 D3DPRIMITIVETYPE에 영향을 받는다.
	);
}

void CApp::Release() {
	if (pVertexBuffer != nullptr) {
		pVertexBuffer->Release();
	}
}
