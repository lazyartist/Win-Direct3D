#pragma once
#include <afxext.h>
class CMenuFormView :
	public CFormView {
public:
	CMenuFormView();
	DECLARE_DYNCREATE(CMenuFormView)
	~CMenuFormView();
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};