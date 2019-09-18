#include "stdafx.h"
#include "CD3DFramework.h"
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")


CD3DFramework::CD3DFramework() {
}


CD3DFramework::~CD3DFramework() {
}

HRESULT CD3DFramework::Init(HWND hWnd, IApp * pD3DApp, float fFrameTime) {
	this->g_hWnd = hWnd;
	this->pD3DApp = pD3DApp;
	this->fFrameTime = fFrameTime;

	if ((g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr) {
		return E_FAIL;
	}
	//g_pD3DInterface ����̽� ������ �ʿ��� �Ķ���͸� �����ϰ� �׷��� ��ġ�� ���� ������ �޾ƿ��� ����ü
	D3DPRESENT_PARAMETERS sD3DParam;
	//sD3DParam�� �޸𸮸� �ʱ�ȭ�Ѵ�.
	//����� sD3DParam�� �⺻���� ��κ� 0�̱� ������ 0���� �ʱ�ȭ�ϰ� �ʿ��� ���� �����ϸ� �ȴ�.
	ZeroMemory(&sD3DParam, sizeof(sD3DParam));
	//true:â, false:��üȭ��
	sD3DParam.Windowed = true;
	//ȭ�� ���۸� ��� ����
	//D3DSWAPEFFECT_DISCARD: �ø�������� ������� ���� �������� �ʴ� ���. ���� �ø��� �� �ּҸ� ��ȯ�ϹǷ� ������.
	//D3DSWAPEFFECT_FLIP: �ø�������� ������� ���� �����ϴ� ���. �ø��� �� ���� �� ������ ������ ���� ����ۿ� �����ϰ� ����Ʈ ���۷� �����ǹǷ� ������. ����۰� �������� �� �ִ�.
	//D3DSWAPEEFECT_COPY: ����۸� �����ϴ� ������� ����Ʈ ���ۿ� �� ������ �ȼ��� �����Ѵ�.
	sD3DParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//���� ������� ������ ���� ������ ���� ����۸� ���
	sD3DParam.BackBufferFormat = D3DFMT_UNKNOWN;
	//Direct3D�� ����� ������ �ڵ�
	sD3DParam.hDeviceWindow = g_hWnd;
	//Direct3D ����̽� ��ü�� ����
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		//�׷��� ����̽� Ÿ���� ���Ѵ�.
		//�׷��� ������ ���� HAL(Hardware Abstraction Layer)�� ����Ѵ�.
		D3DDEVTYPE_HAL,
		//������ �ڵ�
		g_hWnd,
		//D3DCREATE_SOFTWARE_VERTEXPROCESSING: 3D ����� ����Ʈ����� �Ѵ�.
		//D3DCREATE_MIXED_VERTEXPROCESSING: ����Ʈ����� �ϵ���� ����ó��
		//D3DCREATE_HARDWARE_VERTEXPROCESSING: �ϵ����� ó��
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		//D3DPRESENT_PARAMETERS�� ������
		&sD3DParam,
		//LPDIRECT3DDEVICE9�� ������(����������)
		&g_pD3DDevice))) {
		return E_FAIL;
	};

	timeBeginPeriod(1);
	dPrevFrameTime = timeGetTime();
}

bool CD3DFramework::UpdateFrame() {
	DWORD dTime = timeGetTime();
	if (dTime - dPrevFrameTime > fFrameTime) {
		dDeltaTime = dTime - dPrevFrameTime;
		return true;
	}
	return false;
}

void CD3DFramework::Update() {
	pD3DApp->Update(dDeltaTime);
}

void CD3DFramework::Render() {
	//render
	//����۸� ������ ������ �����(����)
	//ù����, �ι�° �Ű������� ������ �ʴ´�.
	//����°�� ����۸� ������ϹǷ� D3DCLEAR_TARGET�� ����, D3DCLEAR_TARGET: ����۸� ����ڴٴ� ��.
	//�׹���� D3DCOLOR_XRGB ��ũ�θ� ���� ���� ����, XRGB�� Alpha���� �Ⱦ��ٴ� ��. 255�� 1.0�̴�.
	g_pD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	//g_pD3DInterface���� ���� �޸𸮸� ��Ʈ�� �ϱ� ���� ����� �����Ѵ�.
	//�뵵1. g_pD3DInterface �޸� ��Ʈ��
	//�뵵2. BeginScene()�� ȣ���ϸ� �޸𸮿� �ܵ����� �׼��� �� �� �ֱ� ������ ���� RAM ���۸� ��� �Ǵ� ������ �� ���
	if (SUCCEEDED(g_pD3DDevice->BeginScene())) {
		//���⼭ ȭ���� �׸���.

		//BeginScene()�� ��������� ���� �޸𸮸� ��ٴ�.
		g_pD3DDevice->EndScene();
		//����۸� ����Ʈ���۷� ��ȯ(�ø���)�Ѵ�.
		g_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	};
}

void CD3DFramework::Release() {
	timeEndPeriod(1);
}
