#include "stdafx.h"
#include "CD3DFramework.h"
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")


CD3DFramework::CD3DFramework() {
}


CD3DFramework::~CD3DFramework() {
}

HRESULT CD3DFramework::Init(HWND hWnd, IApp * pApp, float fFrameTime) {
	this->hWnd = hWnd;
	this->pApp = pApp;
	this->fFrameTime = fFrameTime;

	if ((pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr) {
		return E_FAIL;
	}
	//pD3DInterface 디바이스 생성에 필요한 파라미터를 전달하고 그래픽 장치에 대한 정보를 받아오는 구조체
	D3DPRESENT_PARAMETERS sD3DParam;
	//sD3DParam의 메모리를 초기화한다.
	//참고로 sD3DParam의 기본값은 대부분 0이기 때문에 0으로 초기화하고 필요한 값만 변경하면 된다.
	ZeroMemory(&sD3DParam, sizeof(sD3DParam));
	//true:창, false:전체화면
	sD3DParam.Windowed = true;
	//화면 버퍼링 방식 지정
	//D3DSWAPEFFECT_DISCARD: 플립방식으로 백버퍼의 값을 보존하지 않는 방식. 따라서 플리핑 시 주소만 교환하므로 빠르다.
	//D3DSWAPEFFECT_FLIP: 플립방식으로 백버퍼의 값을 보존하는 방식. 플리핑 시 이전 백 버퍼의 내용을 다음 백버퍼에 복사하고 프론트 버퍼로 지정되므로 느리다. 백버퍼가 여러개일 수 있다.
	//D3DSWAPEEFECT_COPY: 백버퍼를 고정하는 방식으로 프론트 버퍼에 백 버퍼의 픽셀을 복사한다.
	sD3DParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//현재 윈도우와 동일한 색상 정보를 갖는 백버퍼를 사용
	sD3DParam.BackBufferFormat = D3DFMT_UNKNOWN;
	//Direct3D를 사용할 윈도우 핸들
	sD3DParam.hDeviceWindow = hWnd;
	//Direct3D 디바이스 객체를 생성
	if (FAILED(pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		//그래픽 디바이스 타입을 정한다.
		//그래픽 가속을 위해 HAL(Hardware Abstraction Layer)를 사용한다.
		D3DDEVTYPE_HAL,
		//윈도우 핸들
		hWnd,
		//D3DCREATE_SOFTWARE_VERTEXPROCESSING: 3D 계산을 소프트웨어로 한다.
		//D3DCREATE_MIXED_VERTEXPROCESSING: 소프트웨어와 하드웨어 분할처리
		//D3DCREATE_HARDWARE_VERTEXPROCESSING: 하드웨어에서 처리
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		//D3DPRESENT_PARAMETERS의 포인터
		&sD3DParam,
		//LPDIRECT3DDEVICE9의 포인터(이중포인터)
		&pD3DDevice))) {
		return E_FAIL;
	};

	pApp->Init(this);

	timeBeginPeriod(1);
	dPrevFrameTime = timeGetTime();
}

bool CD3DFramework::UpdateFrame() {
	DWORD dTime = timeGetTime();
	if (dTime - dPrevFrameTime >= fFrameTime) {
		dDeltaTime = dTime - dPrevFrameTime;
		dPrevFrameTime = dTime;
		return true;
	}
	return false;
}

void CD3DFramework::Update() {
	pApp->Update(dDeltaTime);
}

void CD3DFramework::Render() {
	//render
	//백버퍼를 지정된 색으로 지운다(비운다)
	//첫번재, 두번째 매개변수는 사용되지 않는다.
	//세번째는 백버퍼를 비워야하므로 D3DCLEAR_TARGET을 지정, D3DCLEAR_TARGET: 백버퍼를 지우겠다는 뜻.
	//네번재는 D3DCOLOR_XRGB 매크로를 통해 색을 지정, XRGB는 Alpha값을 안쓴다는 뜻. 255가 1.0이다.
	pD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	//pD3DInterface에서 비디오 메모리를 컨트롤 하기 위해 잠금을 해지한다.
	//용도1. pD3DInterface 메모리 컨트롤
	//용도2. BeginScene()을 호출하면 메모리에 단독으로 액세스 할 수 있기 때문에 비디오 RAM 버퍼를 잠금 또는 해지할 때 사용
	if (SUCCEEDED(pD3DDevice->BeginScene())) {
		//여기서 화면을 그린다.
		pApp->Render(dDeltaTime);
		//BeginScene()로 잠금해지된 비디오 메모리를 잠근다.
		pD3DDevice->EndScene();
		//백버퍼를 프론트버퍼로 교환(플리핑)한다.
		pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	};
}

void CD3DFramework::Release() {
	pApp->Release();
	timeEndPeriod(1);
}
