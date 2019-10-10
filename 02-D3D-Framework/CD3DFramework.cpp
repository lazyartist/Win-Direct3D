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
	//pD3DInterface ����̽� ������ �ʿ��� �Ķ���͸� �����ϰ� �׷��� ��ġ�� ���� ������ �޾ƿ��� ����ü
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
	sD3DParam.hDeviceWindow = hWnd;
	//D3D �Ķ������ z���� ����
	sD3DParam.EnableAutoDepthStencil = true;
	sD3DParam.AutoDepthStencilFormat = D3DFMT_D24S8;
	//Direct3D ����̽� ��ü�� ����
	if (FAILED(pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		//�׷��� ����̽� Ÿ���� ���Ѵ�.
		//�׷��� ������ ���� HAL(Hardware Abstraction Layer)�� ����Ѵ�.
		D3DDEVTYPE_HAL,
		//������ �ڵ�
		hWnd,
		//D3DCREATE_SOFTWARE_VERTEXPROCESSING: 3D ����� ����Ʈ����� �Ѵ�.
		//D3DCREATE_MIXED_VERTEXPROCESSING: ����Ʈ����� �ϵ���� ����ó��
		//D3DCREATE_HARDWARE_VERTEXPROCESSING: �ϵ����� ó��
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		//D3DPRESENT_PARAMETERS�� ������
		&sD3DParam,
		//LPDIRECT3DDEVICE9�� ������(����������)
		&pD3DDevice))) {
		return E_FAIL;
	};
	//����̽��� z���� ����
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	//�� �׸��� ����
	pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex) * sizeof(sAxisVertices) / sizeof(SVertex),//���ؽ�ũ��*����
		D3DUSAGE_WRITEONLY,//���ҽ� ������ ����(D3DUSAGE_WRITEONLY:���ÿ��� ���ؽ������� ���� ���۸� �������� ����)
		D3DFVF_SVertex,//���ؽ������� ����
		D3DPOOL_DEFAULT,//���ҽ����۸� ������ �ý���, ���� �޸𸮸� ����(D3DPOOL_DEFAULT:������ �޸𸮸� �ڵ� ����)
		&pAxisVertexBufferInterface,//��ȯ�� ���ؽ����۸� ���� ������
		nullptr//������� �ʴ� ����, nullptr
	);
	void *pVertices;//���ؽ��� ������ �޸��� ���� �ּҸ� ���� ����
	pAxisVertexBufferInterface->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, sAxisVertices, sizeof(sAxisVertices));//���ؽ����ۿ� ���ؽ��� �޸� ����
	pAxisVertexBufferInterface->Unlock();//����� ����

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
		//�ٶ󺸴� ���⿡�� �·� �����̵� 
		//�ü��� UP���͸� �����Ͽ� �����̵� ���͸� ���Ѵ�.
		D3DXVECTOR3 vNormal;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Cross(&vNormal, &vCameraLook, &vCameraUp);
		D3DXVec3Normalize(&vNormal, &vNormal);
		vCameraEye -= vNormal * 0.1;
		vCameraAt -= vNormal * 0.1;
	}
	if (GetAsyncKeyState('D') < 0) {
		//�ٶ󺸴� ���⿡�� ��� �����̵� 
		D3DXVECTOR3 vNormal;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Cross(&vNormal, &vCameraLook, &vCameraUp);
		D3DXVec3Normalize(&vNormal, &vNormal);
		vCameraEye += vNormal * 0.1;
		vCameraAt += vNormal * 0.1;
	}
	if (GetAsyncKeyState('W') < 0) {
		//�ٶ󺸴� �������� �̵� 
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Normalize(&vCameraLook, &vCameraLook);
		vCameraEye -= vCameraLook * 0.1;
		vCameraAt -= vCameraLook * 0.1;
	}
	if (GetAsyncKeyState('S') < 0) {
		//�ٶ󺸴� �������� �̵� 
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXVec3Normalize(&vCameraLook, &vCameraLook);
		vCameraEye += vCameraLook * 0.1;
		vCameraAt += vCameraLook * 0.1;
	}
	//ī�޶� �·� ȸ��
	if (GetAsyncKeyState('Q') < 0) {
		//�ٶ󺸴� ���⿡�� �·� �����̵� 
		D3DXMATRIX matRotation;
		D3DXVECTOR4 vCameraAtResult;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;
		D3DXMatrixRotationAxis(&matRotation, &vCameraUp, -D3DX_PI / 180);
		//DirectX�� ����x��� ����̰� �� ���� �������� ����Ѵ�.
		//D3DXVec3Transform() �Լ��� ���� �����̴�.
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
		//�ٶ󺸴� ���⿡�� �·� �����̵� 
		D3DXMATRIX matRotation;
		D3DXVECTOR4 vCameraAtResult;
		D3DXVECTOR3 vCameraLook = vCameraEye - vCameraAt;//ī�޶� ��ġ�� ���������ϴ� ����
		D3DXMatrixRotationAxis(&matRotation, &vCameraUp, D3DX_PI / 180);
		D3DXVec3Transform(&vCameraAtResult, &vCameraLook, &matRotation);//����x��� ����
		vCameraAt = vCameraEye + D3DXVECTOR3(vCameraAtResult.x, vCameraAtResult.y, vCameraAtResult.z);
	}

	pApp->Update(dDeltaTime);
}

void CD3DFramework::Render() {
	//render
	//����۸� ������ ������ �����(����)
	//ù����, �ι�° �Ű������� ������ �ʴ´�.
	//����°�� ����۸� ������ϹǷ� D3DCLEAR_TARGET�� ����, D3DCLEAR_TARGET: ����۸� ����ڴٴ� ��.
	//�׹���� D3DCOLOR_XRGB ��ũ�θ� ���� ���� ����, XRGB�� Alpha���� �Ⱦ��ٴ� ��. 255�� 1.0�̴�.
	pD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	//pD3DInterface���� ���� �޸𸮸� ��Ʈ�� �ϱ� ���� ����� �����Ѵ�.
	//�뵵1. pD3DInterface �޸� ��Ʈ��
	//�뵵2. BeginScene()�� ȣ���ϸ� �޸𸮿� �ܵ����� �׼��� �� �� �ֱ� ������ ���� RAM ���۸� ��� �Ǵ� ������ �� ���
	if (SUCCEEDED(pD3DDevice->BeginScene())) {
		//���⼭ App�� ������ ȭ���� �׸���.
		pApp->Render(dDeltaTime);

		//��׸��� ----- s
		//World transformation
		//XMMATRIX matWorld = XMMatrixScaling(1.0, 1.0, 1.0)//ũ�����
		XMMATRIX matWorld = XMMatrixScaling(fAxisScale, fAxisScale, fAxisScale)//ũ�����
			*XMMatrixRotationX(0.0)//ȸ�����
			*XMMatrixTranslation(0.0, 0.0, 0.0);//�̵����
		XMFLOAT4X4 f44;
		XMStoreFloat4x4(&f44, matWorld);
		pD3DDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&f44);
		//View transformation
		D3DXMATRIX pMatView;
		D3DXMatrixLookAtLH(&pMatView, 
			&vCameraEye,//ī�޶� ��ġ
			&vCameraAt,//�ٶ󺸴� ����
			&vCameraUp//ī�޶󿡼� �������� ���ϴ� ����
		);
		//XMStoreFloat4x4(&f44, pMatView);
		pD3DDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&pMatView);
		//Projection trasformation(���ٹ�)
		XMMATRIX matProj = XMMatrixPerspectiveFovLH( //Field of view Left Hand
			Const::fPI() / 2.0,
			1.0,
			1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
			100.0//�� ���� Z��
		);
		//Projection trasformation(��������)
		//XMMATRIX matProj = XMMatrixOrthographicLH(
		//	50.0,
		//	50.0,
		//	1.0,//����� ���� Z��(������ ������ WM_SYSCOLORCHANGE�� ��ӿͼ� ���α׷� ������ �ȵ�)
		//	100.0//�� ���� Z��
		//);
		XMStoreFloat4x4(&f44, matProj);
		pD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&f44);

		//Light Off
		//���� ���̴� �۾��� ���� ���� ���� �������� ����� ���ؽ� ������ �� �� �ִ�.
		//�׷��� ������ ���������� ��µȴ�.
		pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		//3�� ���� ���
		//1. ���ؽ����ۿ� ���ؽ� ������ D3D ����̽��� �˷��ش�. ����� ���ؽ����۸� ��� ��Ʈ���� �����Ѵ�.
		pD3DDevice->SetStreamSource(
			0,//0���� ����
			pAxisVertexBufferInterface, //���ؽ�����
			0, //�޸𸮽��� ��ġ
			sizeof(SVertex) //���ؽ� ũ��
		);
		//2. D3D�� ���� �����͸� ��� �ؼ����ϴ��� �����Ѵ�.
		pD3DDevice->SetFVF(D3DFVF_SVertex);
		//3. ���� ������ ����ϱ� ���� DrawPrimitive() �Լ� ȣ��
		//DrawIndexedPrimitive(), DrawPrimitiveUP(), DrawIndexedPrimitiveUP()���� �ְ�
		//DrawIndexedPrimitive(), DrawIndexedPrimitiveUP()�Լ��� ���Ӱ��߿� ���� ���ȴ�.
		//DrawIndexedPrimitive()�Լ��� ���� ������.
		pD3DDevice->DrawPrimitive(
			D3DPT_LINELIST,
			//D3DPT_TRIANGLESTRIP,
			0, //����� ������ ���ؽ� �ε���
			3 //����� ����, ù��° �Ķ���� D3DPRIMITIVETYPE�� ������ �޴´�.
		);
		//Light Off
		pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		//��׸��� ----- e


		
		//BeginScene()�� ��������� ���� �޸𸮸� ��ٴ�.
		pD3DDevice->EndScene();
		//����۸� ����Ʈ���۷� ��ȯ(�ø���)�Ѵ�.
		pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	};
}

void CD3DFramework::Release() {
	pApp->Release();
	timeEndPeriod(1);
}
