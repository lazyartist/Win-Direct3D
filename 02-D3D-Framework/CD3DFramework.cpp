#include "stdafx.h"
#include "CD3DFramework.h"
#include "CApp.h"
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")


CD3DFramework::CD3DFramework() {
}


CD3DFramework::~CD3DFramework() {
}

HRESULT CD3DFramework::Init(HWND hWnd, CApp * pApp, float fFrameTime) {
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
	//D3D 파라미터의 z버퍼 설정
	sD3DParam.EnableAutoDepthStencil = true;
	sD3DParam.AutoDepthStencilFormat = D3DFMT_D24S8;
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
	//디바이스의 z버퍼 설정
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	//축 그리기 설정
	pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex) * sizeof(sAxisVertices) / sizeof(SVertex),//버텍스크기*개수
		D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
		D3DFVF_SVertex,//버텍스데이터 사용법
		D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
		&pAxisVertexBufferInterface,//반환된 버텍스버퍼를 받을 포인터
		nullptr//사용하지 않는 변수, nullptr
	);
	void *pVertices;//버텍스를 저장할 메모리의 시작 주소를 받을 변수
	pAxisVertexBufferInterface->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, sAxisVertices, sizeof(sAxisVertices));//버텍스버퍼에 버텍스를 메모리 복사
	pAxisVertexBufferInterface->Unlock();//잠금을 해제

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
	//camera up
	{
		D3DXVECTOR3 vNormal1, vNormal2;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Cross(&vNormal1, &vCameraLook, &vCameraUp);
		D3DXVec3Cross(&vNormal2, &vNormal1, &vCameraLook);
		D3DXVec3Normalize(&vNormal2, &vNormal2);
		vCameraUp = vNormal2;
	}

	if (GetAsyncKeyState('A') < 0) {
		//바라보는 방향에서 좌로 평행이동 
		//시선과 UP벡터를 외적하여 평행이동 벡터를 구한다.
		D3DXVECTOR3 vNormal;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Cross(&vNormal, &vCameraLook, &vCameraUp);
		D3DXVec3Normalize(&vNormal, &vNormal);
		vCameraEye -= vNormal * 0.1;
		vCameraAt -= vNormal * 0.1;
	}
	if (GetAsyncKeyState('D') < 0) {
		//바라보는 방향에서 우로 평행이동 
		D3DXVECTOR3 vNormal;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Cross(&vNormal, &vCameraLook, &vCameraUp);
		D3DXVec3Normalize(&vNormal, &vNormal);
		vCameraEye += vNormal * 0.1;
		vCameraAt += vNormal * 0.1;
	}
	if (GetAsyncKeyState('W') < 0) {
		//바라보는 방향으로 이동 
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Normalize(&vCameraLook, &vCameraLook);
		vCameraEye -= vCameraLook * 0.1;
		vCameraAt -= vCameraLook * 0.1;
	}
	if (GetAsyncKeyState('S') < 0) {
		//바라보는 방향으로 이동 
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Normalize(&vCameraLook, &vCameraLook);
		vCameraEye += vCameraLook * 0.1;
		vCameraAt += vCameraLook * 0.1;
	}
	//카메라 좌로 회전
	if (GetAsyncKeyState('Q') < 0) {
		//바라보는 방향에서 좌로 평행이동 
		D3DXMATRIX matRotation;
		D3DXVECTOR4 vCameraAtResult;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXMatrixRotationAxis(&matRotation, &vCameraUp, -D3DX_PI / 180);
		//DirectX는 벡터x행렬 방식이고 행 지준 저장방식을 사용한다.
		//D3DXVec3Transform() 함수와 같은 연산이다.
		vCameraAtResult = {
			vCameraLook.x * matRotation._11 + vCameraLook.y * matRotation._21 + vCameraLook.z * matRotation._31,
			vCameraLook.x * matRotation._12 + vCameraLook.y * matRotation._22 + vCameraLook.z * matRotation._32,
			vCameraLook.x * matRotation._13 + vCameraLook.y * matRotation._23 + vCameraLook.z * matRotation._33,
			1.0,
		};
		//D3DXVec3Transform(&vCameraAtResult, &vCameraLook, &matRotation);
		vCameraAt = vCameraEye + D3DXVECTOR3(vCameraAtResult.x, vCameraAtResult.y, vCameraAtResult.z);
	}
	if (GetAsyncKeyState('E') < 0) {
		//바라보는 방향에서 좌로 평행이동 
		D3DXMATRIX matRotation;
		D3DXVECTOR4 vCameraAtResult;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;//카메라 위치를 기준으로하는 벡터
		D3DXMatrixRotationAxis(&matRotation, &vCameraUp, D3DX_PI / 180);
		D3DXVec3Transform(&vCameraAtResult, &vCameraLook, &matRotation);//벡터x행렬 연산
		vCameraAt = vCameraEye + D3DXVECTOR3(vCameraAtResult.x, vCameraAtResult.y, vCameraAtResult.z);
	}

	pApp->Update(dDeltaTime);
}

void CD3DFramework::Render() {
	//render
	//백버퍼를 지정된 색으로 지운다(비운다)
	//첫번재, 두번째 매개변수는 사용되지 않는다.
	//세번째는 백버퍼를 비워야하므로 D3DCLEAR_TARGET을 지정, D3DCLEAR_TARGET: 백버퍼를 지우겠다는 뜻.
	//네번재는 D3DCOLOR_XRGB 매크로를 통해 색을 지정, XRGB는 Alpha값을 안쓴다는 뜻. 255가 1.0이다.
	pD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	//pD3DInterface에서 비디오 메모리를 컨트롤 하기 위해 잠금을 해지한다.
	//용도1. pD3DInterface 메모리 컨트롤
	//용도2. BeginScene()을 호출하면 메모리에 단독으로 액세스 할 수 있기 때문에 비디오 RAM 버퍼를 잠금 또는 해지할 때 사용
	if (SUCCEEDED(pD3DDevice->BeginScene())) {
		//여기서 App에 구현된 화면을 그린다.
		pApp->Render(dDeltaTime);

		//축그리기 ----- s
		//World transformation
		//XMMATRIX matWorld = XMMatrixScaling(1.0, 1.0, 1.0)//크기행렬
		XMMATRIX matWorld = XMMatrixScaling(fAxisScale, fAxisScale, fAxisScale)//크기행렬
			*XMMatrixRotationX(0.0)//회전행렬
			*XMMatrixTranslation(0.0, 0.0, 0.0);//이동행렬
		XMFLOAT4X4 f44;
		XMStoreFloat4x4(&f44, matWorld);
		pD3DDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&f44);
		//View transformation
		D3DXMATRIX pMatView;
		D3DXMatrixLookAtLH(&pMatView, 
			&vCameraEye,//카메라 위치
			&vCameraAt,//바라보는 방향
			&vCameraUp//카메라에서 위쪽으로 향하는 벡터
		);
		//XMStoreFloat4x4(&f44, pMatView);
		pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&pMatView);
		//Projection trasformation(원근법)
		XMMATRIX matProj = XMMatrixPerspectiveFovLH( //Field of view Left Hand
			Const::fPI() / 2.0,
			1.0,
			1.0,//가까운 면의 Z값(음수를 넣으니 WM_SYSCOLORCHANGE가 계속와서 프로그램 진행이 안됨)
			100.0//먼 면의 Z값
		);
		//Projection trasformation(직교투영)
		//XMMATRIX matProj = XMMatrixOrthographicLH(
		//	50.0,
		//	50.0,
		//	1.0,//가까운 면의 Z값(음수를 넣으니 WM_SYSCOLORCHANGE가 계속와서 프로그램 진행이 안됨)
		//	100.0//먼 면의 Z값
		//);
		XMStoreFloat4x4(&f44, matProj);
		pD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&f44);

		//Light Off
		//정점 쉐이더 작업을 하지 않을 때는 라이팅을 꺼줘야 버텍스 색상을 볼 수 있다.
		//그렇지 않으면 검은색으로 출력된다.
		pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		//3축 정점 출력
		//1. 버텍스버퍼와 버텍스 포맷을 D3D 디바이스에 알려준다. 출력할 버텍스버퍼를 출력 스트림과 연결한다.
		pD3DDevice->SetStreamSource(
			0,//0으로 지정
			pAxisVertexBufferInterface, //버텍스버퍼
			0, //메모리시작 위치
			sizeof(SVertex) //버텍스 크기
		);
		//2. D3D에 정점 데이터를 어떻게 해석해하는지 설정한다.
		pD3DDevice->SetFVF(D3DFVF_SVertex);
		//3. 기하 정보를 출력하기 위한 DrawPrimitive() 함수 호출
		//DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()등이 있고
		//DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()함수가 게임개발에 많이 사용된다.
		//DrawIndexedPrimitive()함수가 가장 빠르다.
		pD3DDevice->DrawPrimitive(
			D3DPT_LINELIST,
			//D3DPT_TRIANGLESTRIP,
			0, //출력을 시작할 버텍스 인덱스
			3 //출력할 개수, 첫번째 파라미터 D3DPRIMITIVETYPE에 영향을 받는다.
		);
		//Light Off
		pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		//축그리기 ----- e


		
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
