// MyHtmlView.cpp : 实现文件
//

#include "stdafx.h"
#include "MyHtmlView.h"
#include "StockWnd.h"

// CMyHtmlView

IMPLEMENT_DYNCREATE(CMyHtmlView, CHtmlView)

CMyHtmlView::CMyHtmlView()
{
	m_bGotoStock = true;//根据stockCode=来跳到个股
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


// CMyHtmlView 诊断

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


// CMyHtmlView 消息处理程序

void CMyHtmlView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{
	// TODO: 在此添加专用代码和/或调用基类
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
	// TODO: 在此添加专用代码和/或调用基类
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

WNDPROC   wpOrigIEProc   =   NULL;   //   最好定义成类成员 
LRESULT   APIENTRY   IESubclassProc(HWND   hwnd,   UINT   uMsg,   WPARAM   wParam,   LPARAM   lParam) 
{ 
	if   (uMsg   ==   WM_ERASEBKGND) 
		return   TRUE; 

	return   CallWindowProc(wpOrigIEProc,   hwnd,   uMsg,   wParam,   lParam); 
} 


void CMyHtmlView::OnSize(UINT nType, int cx, int cy)
{
	//modified by wangchao 2009-07-03
	//原因：排除运行CHtmlView后出现的COleException异常
	//描述：
	//    由原来的CHtmlView::OnSize(nType, cx, cy)改为
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
	//	// TODO: 在此处添加消息处理程序代码

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
	// TODO: 在此添加专用代码和/或调用基类
	CHtmlView::OnDownloadBegin();
}

void CMyHtmlView::OnDownloadComplete()
{
	// TODO: 在此添加专用代码和/或调用基类

	CHtmlView::OnDownloadComplete();
}

BOOL CMyHtmlView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CHtmlView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	return true;
}

void CMyHtmlView::OnNavigateError(LPCTSTR lpszURL, LPCTSTR lpszFrame, DWORD dwError, BOOL *pbCancel)
{
	// TODO: 在此添加专用代码和/或调用基类
	CHtmlView::OnNavigateError(lpszURL, lpszFrame, dwError, pbCancel);
}


BOOL CMyHtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CHtmlView::PreCreateWindow(cs);
}

void CMyHtmlView::OnDocumentComplete(LPCTSTR lpszURL)
{
	CHtmlView::OnDocumentComplete(lpszURL);
}

BOOL CMyHtmlView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((pMsg->message == WM_RBUTTONDOWN)||(pMsg->message == WM_RBUTTONDBLCLK))
		return true;
	return CHtmlView::PreTranslateMessage(pMsg);
}

void CMyHtmlView::OnCommandStateChange(long nCommand, BOOL bEnable)
{
	// TODO: 在此添加专用代码和/或调用基类

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//CBrush br;
	//br.CreateSolidBrush(RGB(0,0,0));
	//return (HBRUSH)br.GetSafeHandle();
	return hbr;
}

void CMyHtmlView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//SetClassLong(this-> m_hWnd,GCL_HBRBACKGROUND,NULL); 

}
