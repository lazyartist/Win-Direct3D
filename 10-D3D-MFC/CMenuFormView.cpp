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

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
BEGIN_MESSAGE_MAP(CMenuFormView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CMenuFormView::OnEraseBkgnd(CDC* pDC) {
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return false;
	//return CFormView::OnEraseBkgnd(pDC);
}
