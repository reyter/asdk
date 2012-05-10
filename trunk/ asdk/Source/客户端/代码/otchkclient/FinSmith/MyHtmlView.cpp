// MyHtmlView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyHtmlView.h"
#include "StockWnd.h"

// CMyHtmlView

IMPLEMENT_DYNCREATE(CMyHtmlView, CHtmlView)

CMyHtmlView::CMyHtmlView()
{
	m_bGotoStock = true;//����stockCode=����������
	//	wpOrigIEProc   =   NULL;
}

CMyHtmlView::~CMyHtmlView()
{
}

void CMyHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyHtmlView, CHtmlView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMyHtmlView ���

#ifdef _DEBUG
void CMyHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CMyHtmlView ��Ϣ�������

void CMyHtmlView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{
	// TODO: �ڴ����ר�ô����/����û���
	ASSERT(ppDisp);
	if (!ppDisp)
		return;

	gpData->m_pNewsView = NULL;
	::SendMessage(gpData->m_hwndMain,WM_GET_NEWSWND,0,0);
	if (gpData->m_pNewsView)
	{
		CHtmlView * pView;
		pView = (CHtmlView *)gpData->m_pNewsView;
		pView->SetRegisterAsBrowser(true);
		*ppDisp = pView->GetApplication();
	}
	/*
	CStockWnd * pWnd;
	CMyHtmlView * pView;
	pWnd = new CStockWnd();
	pView = (CMyHtmlView *)pWnd->m_pView;
	pView->SetRegisterAsBrowser(true);
	*ppDisp = pView->GetApplication();
	pWnd->ShowWindow(SW_SHOW);
	pWnd->CenterWindow();*/
	//CString strTitle;
	//this->GetParentFrame()->GetWindowText(strTitle);
	//pWnd->SetWindowText(strTitle);
	//pWnd->SetControlWnd(GetParentFrame());
}

void CMyHtmlView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel)
{
	// TODO: �ڴ����ר�ô����/����û���
	CString strUrl;
	strUrl = lpszURL;
	if (m_bGotoStock)
	{
		int nPos = strUrl.Find(_T("stockCode="));
		if (nPos > 0)
		{
			nPos += 10;
			strUrl = strUrl.Right(strUrl.GetLength() - nPos);
			SStock * pStock = gpData->GetStock(strUrl);
			if (pStock)
				::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
			*pbCancel = true;
			return;
		}
	}
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

WNDPROC   wpOrigIEProc   =   NULL;   //   ��ö�������Ա 
LRESULT   APIENTRY   IESubclassProc(HWND   hwnd,   UINT   uMsg,   WPARAM   wParam,   LPARAM   lParam) 
{ 
	if   (uMsg   ==   WM_ERASEBKGND) 
		return   TRUE; 

	return   CallWindowProc(wpOrigIEProc,   hwnd,   uMsg,   wParam,   lParam); 
} 


void CMyHtmlView::OnSize(UINT nType, int cx, int cy)
{
	//modified by wangchao 2009-07-03
	//ԭ���ų�����CHtmlView����ֵ�COleException�쳣
	//������
	//    ��ԭ����CHtmlView::OnSize(nType, cx, cy)��Ϊ
	//    CFormView::OnSize(nType, cx, cy)    
	CFormView::OnSize(nType, cx, cy);

	CRect rect;  
	if (::IsWindow(m_wndBrowser.m_hWnd))  
	{
		GetClientRect(rect);  

		::AdjustWindowRectEx(rect, GetStyle(), FALSE, WS_EX_CLIENTEDGE); 
		m_wndBrowser.SetWindowPos(NULL, 
			rect.left, 
			rect.top, 
			rect.Width(),   
			rect.Height(),   
			SWP_NOACTIVATE | SWP_NOZORDER);  
	}
	//	// TODO: �ڴ˴������Ϣ����������

	if(wpOrigIEProc==NULL)
	{  
		TCHAR class_name[MAX_PATH+1];
		bool found;
		found=false;
		CWnd * child;
		for(child=GetWindow(GW_CHILD);child!=NULL;child=child->GetWindow(GW_HWNDNEXT))
		{
			//GetClassName(pWnd->GetSafeHwnd(),szClass,MAX_PATH);
			//if(strcmp(szClass,"ShellEmbedding")==0)
			{
				CWnd * grand_child;
				for(grand_child=child->GetWindow(GW_CHILD);grand_child!=NULL;grand_child=grand_child->GetWindow(GW_HWNDNEXT))
				{
					GetClassName(grand_child->GetSafeHwnd(),class_name,MAX_PATH);
					if(class_name==CString("Internet Explorer_Server"))
					{
						found=true;
						wpOrigIEProc=(WNDPROC)SetWindowLong(grand_child->GetSafeHwnd(),GWL_WNDPROC,(LONG)IESubclassProc);
						break;
					}
					CWnd * great_grand_child;
					for(great_grand_child=grand_child->GetWindow(GW_CHILD);great_grand_child!=NULL;great_grand_child=great_grand_child->GetWindow(GW_HWNDNEXT))
					{
						GetClassName(great_grand_child->GetSafeHwnd(),class_name,MAX_PATH);
						if(class_name==CString("Internet Explorer_Server"))
						{
							found=true;
							wpOrigIEProc=(WNDPROC)SetWindowLong(great_grand_child->GetSafeHwnd(),GWL_WNDPROC,(LONG)IESubclassProc);
							break;
						}
						CWnd * great_great_grand_child;
						for(great_great_grand_child=great_grand_child->GetWindow(GW_CHILD);great_great_grand_child!=NULL;great_great_grand_child=great_great_grand_child->GetWindow(GW_HWNDNEXT))
						{
							GetClassName(great_great_grand_child->GetSafeHwnd(),class_name,MAX_PATH);
							if(class_name==CString("Internet Explorer_Server"))
							{
								found=true;
								wpOrigIEProc=(WNDPROC)SetWindowLong(great_great_grand_child->GetSafeHwnd(),GWL_WNDPROC,(LONG)IESubclassProc);
								break;
							}
						}
						if(found)
							break;
					}
					if(found)
						break;
				}//end of for grand child
			}
			if(found)
				break;
		}//end of for child
	}

}

void CMyHtmlView::OnDownloadBegin()
{
	// TODO: �ڴ����ר�ô����/����û���
	CHtmlView::OnDownloadBegin();
}

void CMyHtmlView::OnDownloadComplete()
{
	// TODO: �ڴ����ר�ô����/����û���

	CHtmlView::OnDownloadComplete();
}

BOOL CMyHtmlView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	CHtmlView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	return true;
}

void CMyHtmlView::OnNavigateError(LPCTSTR lpszURL, LPCTSTR lpszFrame, DWORD dwError, BOOL *pbCancel)
{
	// TODO: �ڴ����ר�ô����/����û���
	CHtmlView::OnNavigateError(lpszURL, lpszFrame, dwError, pbCancel);
}


BOOL CMyHtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	return CHtmlView::PreCreateWindow(cs);
}

void CMyHtmlView::OnDocumentComplete(LPCTSTR lpszURL)
{
	CHtmlView::OnDocumentComplete(lpszURL);
}

BOOL CMyHtmlView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ((pMsg->message == WM_RBUTTONDOWN)||(pMsg->message == WM_RBUTTONDBLCLK))
		return true;
	return CHtmlView::PreTranslateMessage(pMsg);
}

void CMyHtmlView::OnCommandStateChange(long nCommand, BOOL bEnable)
{
	// TODO: �ڴ����ר�ô����/����û���

	CHtmlView::OnCommandStateChange(nCommand, bEnable);
}

void CMyHtmlView::RefreshWin()
{
	Refresh();
}

void CMyHtmlView::ResetSkin()
{
	Refresh();
}

void CMyHtmlView::SetStockCode(CString c_strCode)
{
	//Refresh();
}
BOOL CMyHtmlView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	/*
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(rect,&CBrush(RGB(0,0,0)));
	return TRUE;*/
	return __super::OnEraseBkgnd(pDC);
}

HBRUSH CMyHtmlView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//CBrush br;
	//br.CreateSolidBrush(RGB(0,0,0));
	//return (HBRUSH)br.GetSafeHandle();
	return hbr;
}

void CMyHtmlView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//SetClassLong(this-> m_hWnd,GCL_HBRBACKGROUND,NULL); 

}
