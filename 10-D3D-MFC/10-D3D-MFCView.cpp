
// 10-D3D-MFCView.cpp: CMy10D3DMFCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "10-D3D-MFC.h"
#endif

#include "10-D3D-MFCDoc.h"
#include "10-D3D-MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy10D3DMFCView

IMPLEMENT_DYNCREATE(CMy10D3DMFCView, CView)

BEGIN_MESSAGE_MAP(CMy10D3DMFCView, CView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMy10D3DMFCView 생성/소멸

CMy10D3DMFCView::CMy10D3DMFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy10D3DMFCView::~CMy10D3DMFCView()
{
	m_pD3dFramework.Release();
}

BOOL CMy10D3DMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy10D3DMFCView 그리기

void CMy10D3DMFCView::OnDraw(CDC* /*pDC*/)
{
	CMy10D3DMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy10D3DMFCView 진단

#ifdef _DEBUG
void CMy10D3DMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMy10D3DMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy10D3DMFCDoc* CMy10D3DMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy10D3DMFCDoc)));
	return (CMy10D3DMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy10D3DMFCView 메시지 처리기


void CMy10D3DMFCView::OnInitialUpdate() {
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pD3dFramework.Init(m_hWnd/*View의 Wnd핸들*/, &m_cApp, 1000 / 60);
}


BOOL CMy10D3DMFCView::OnEraseBkgnd(CDC* pDC) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return false;
	//return CView::OnEraseBkgnd(pDC);
}
