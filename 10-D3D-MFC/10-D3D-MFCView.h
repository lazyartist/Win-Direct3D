
// 10-D3D-MFCView.h: CMy10D3DMFCView 클래스의 인터페이스
//

#pragma once
#include "10-D3D-MFCDoc.h"

class CMy10D3DMFCView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy10D3DMFCView() noexcept;
	DECLARE_DYNCREATE(CMy10D3DMFCView)

// 특성입니다.
public:
	CMy10D3DMFCDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy10D3DMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 10-D3D-MFCView.cpp의 디버그 버전
inline CMy10D3DMFCDoc* CMy10D3DMFCView::GetDocument() const
   { return reinterpret_cast<CMy10D3DMFCDoc*>(m_pDocument); }
#endif

