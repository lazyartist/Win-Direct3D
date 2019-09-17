// Win-Direct3D.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Win-Direct3D.h"
//Direct3D 9버전의 헤더 추가
#include <d3d9.h>
//Direct3D 9 라이브러리 추가
//#pragma comment는 프로젝트 속성에서 lib를 포함하지 않아도 사용할 수 있게 한다.
//첫번째 인자는 등록할 확장명, 두번째 인자는 파일 이름
#pragma comment (lib, "d3d9.lib")

#define MAX_LOADSTRING 100

//DirectX 시스템 객체 포인터, COM interface이다.
LPDIRECT3D9 g_pD3DInterface;
//DirectX 디바이스 객체(실제 화면을 출력하는 역할)
//디바이스 인터페이스, 그래픽 드라이버, 비디오 카드에 대한 정보를 가지고 있다.
//렌더링을 위해 사용한다.
LPDIRECT3DDEVICE9 g_pD3DDevice;

HWND g_hWnd;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDIRECT3D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	//g_pD3DInterface 
	//Direct3D COM interface를 생성
	//Direct3D 9C 버전에서는 32를 리턴한다.
	if ((g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr) {
		return E_FAIL;
	}
	//g_pD3DInterface 디바이스 생성에 필요한 파라미터를 전달하고 그래픽 장치에 대한 정보를 받아오는 구조체
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
	sD3DParam.hDeviceWindow = g_hWnd;
	//Direct3D 디바이스 객체를 생성
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		//그래픽 디바이스 타입을 정한다.
		//그래픽 가속을 위해 HAL(Hardware Abstraction Layer)를 사용한다.
		D3DDEVTYPE_HAL,
		//윈도우 핸들
		g_hWnd,
		//D3DCREATE_SOFTWARE_VERTEXPROCESSING: 3D 계산을 소프트웨어로 한다.
		//D3DCREATE_MIXED_VERTEXPROCESSING: 소프트웨어와 하드웨어 분할처리
		//D3DCREATE_HARDWARE_VERTEXPROCESSING: 하드웨어에서 처리
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		//D3DPRESENT_PARAMETERS의 포인터
		&sD3DParam,
		//LPDIRECT3DDEVICE9의 포인터(이중포인터)
		&g_pD3DDevice))) {
		return E_FAIL;
	};

	//render
	//백버퍼를 지정된 색으로 지운다(비운다)
	//첫번재, 두번째 매개변수는 사용되지 않는다.
	//세번째는 백버퍼를 비워야하므로 D3DCLEAR_TARGET을 지정, D3DCLEAR_TARGET: 백버퍼를 지우겠다는 뜻.
	//네번재는 D3DCOLOR_XRGB 매크로를 통해 색을 지정, XRGB는 Alpha값을 안쓴다는 뜻. 255가 1.0이다.
	g_pD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	//g_pD3DInterface에서 비디오 메모리를 컨트롤 하기 위해 잠금을 해지한다.
	//용도1. g_pD3DInterface 메모리 컨트롤
	//용도2. BeginScene()을 호출하면 메모리에 단독으로 액세스 할 수 있기 때문에 비디오 RAM 버퍼를 잠금 또는 해지할 때 사용
	if (SUCCEEDED(g_pD3DDevice->BeginScene())) {
		//여기서 화면을 그린다.

		//BeginScene()로 잠금해지된 비디오 메모리를 잠근다.
		g_pD3DDevice->EndScene();
		//백버퍼를 프론트버퍼로 교환(플리핑)한다.
		g_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	};

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	//release g_pD3DInterface
	//디바이스를 먼저 해제한다.
	if(g_pD3DDevice != nullptr) g_pD3DDevice->Release();
	if (g_pD3DInterface != nullptr) g_pD3DInterface->Release();

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDIRECT3D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDIRECT3D);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
		//direct3d를 사용하므로 GDI를 사용하지 않는다.
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps);
            //// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            //EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);//WM_QUIT 메시지를 발생
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}