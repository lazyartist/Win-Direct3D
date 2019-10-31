#include "stdafx.h"
#include "CMenuFormView.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CMenuFormView, CFormView)

CMenuFormView::CMenuFormView():CFormView(IDD_FORMVIEW){
}

CMenuFormView::~CMenuFormView() {
}


void CMenuFormView::OnInitialUpdate() {
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
BEGIN_MESSAGE_MAP(CMenuFormView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CMenuFormView::OnEraseBkgnd(CDC* pDC) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return false;
	//return CFormView::OnEraseBkgnd(pDC);
}
