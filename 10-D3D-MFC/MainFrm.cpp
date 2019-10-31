
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "10-D3D-MFC.h"
#include "10-D3D-MFCView.h"
#include "CMenuFormView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

extern CMy10D3DMFCView *g_pView;

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept {
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame() {
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this)) {
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext) {
	//CSplitterWnd 생성
	if (!m_wndSplitter.CreateStatic(
		this,//메인프레임
		1,//행
		2//열
		//2,//열
		//WS_CHILD | WS_BORDER,
		//AFX_IDW_PANE_FIRST
	)) {
		return false;
	}
	//분할창 크기 설정
	CRect cRect;
	GetClientRect(&cRect);
	int iClientWidth = cRect.right - cRect.left;
	int iMenuFormViewWidth = iClientWidth / 6;
	//분할창 생성 1
	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CMy10D3DMFCView),
		CSize(iClientWidth - iMenuFormViewWidth, 0), pContext
	)) {
		return false;
	};
	//분할창 생성 2
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CMenuFormView),
		CSize(iMenuFormViewWidth, 0), pContext
	)) {
		return false;
	};

	g_pView = (CMy10D3DMFCView *)m_wndSplitter.GetPane(0, 0);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~FWS_ADDTOTITLE;
	SetTitle(TEXT("MFC Multi View"));

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const {
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const {
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기


BEGIN_MESSAGE_MAP(CSpiltterWndStatic, CSplitterWnd)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

CSpiltterWndStatic::CSpiltterWndStatic() {}
CSpiltterWndStatic::~CSpiltterWndStatic() {}
LRESULT CSpiltterWndStatic::OnNcHitTest(CPoint point) {
	return HTNOWHERE;
}