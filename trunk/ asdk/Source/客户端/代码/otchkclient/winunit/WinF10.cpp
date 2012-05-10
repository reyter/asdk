///-#include "WinF10.h"
// WinF10.cpp : 实现文件
//

#include "stdafx.h"
#include "winunit.h"
#include "MyHtmlView.h"
#include "WinF10.h"
#include "DlgTest.h"

// CWinF10

IMPLEMENT_DYNAMIC(CWinF10, CWnd)

CWinF10::CWinF10()
{
	m_pWeb = NULL;
	m_nViewPage = 0;
}

CWinF10::~CWinF10()
{
}


BEGIN_MESSAGE_MAP(CWinF10, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CWinF10 消息处理程序



BOOL CWinF10::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	return __super::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CWinF10::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}

void CWinF10::ShowUrl()
{
	if(m_pWeb)
	{
		CString str;
		CString strCode = m_strStockCode.Left(6);
		 
		//str.Format(_T("http://www.w5178.com/jsp/f10/gl.jsp?stockCode=%s&navName=公司概览"),strCode.GetBuffer());		
		str.Format(gpData->m_strF10Url,strCode.GetBuffer());
		strCode.ReleaseBuffer();		
		int nPos = str.Find(_T("公司概览"));
		if (nPos && m_nViewPage == 1)
		{
			str = str.Left(nPos);
			str += _T("盈利预测");
			str.Replace(_T("gl.jsp"),_T("yc1.jsp"));
		}

		if (nPos && m_nViewPage == 2)
		{
			str = str.Left(nPos);
			str += _T("投资评级");
			str.Replace(_T("gl.jsp"),_T("pj1.jsp"));
		}

		m_pWeb->Navigate2(str);		
	}
}
void CWinF10::SetStockCode(CString c_strCode)
{
	SetNoFlash();
	m_strStockCode = c_strCode;
	ShowUrl();
}
WNDPROC   wpOrigIEProc   =   NULL;   //   最好定义成类成员 
LRESULT   APIENTRY   IESubclassProc(HWND   hwnd,   UINT   uMsg,   WPARAM   wParam,   LPARAM   lParam) 
{ 
        if   (uMsg   ==   WM_ERASEBKGND) 
                return   TRUE; 

        return   CallWindowProc(wpOrigIEProc,   hwnd,   uMsg,   wParam,   lParam); 
} 

void CWinF10::SetNoFlash()
{
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

void CWinF10::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	SetNoFlash();
	if (m_pWeb)
	{
		SetLayout();
	}
}

void CWinF10::SetLayout(void)
{
	CRect rect;
	GetClientRect(rect);
	if (m_pWeb)
	m_pWeb->MoveWindow(rect);
}

void CWinF10::CreateSelf(CWnd * c_pParent)
{	
	Create(NULL,_T(""),WS_CHILDWINDOW, CRect(10,10,100,100),c_pParent,0,NULL);

	m_pWeb = new CMyHtmlView();	
	m_pWeb->Create(NULL, NULL, WS_CHILD |WS_VISIBLE,CRect(), this, 0, NULL);
	m_pWeb->m_bGotoStock = false;
	//m_pWeb->Navigate(_T("http://std.investoday.com.cn/jsp/f10/yc1.jsp?stockCode=600036&navName=盈利预测"));
}

CWnd * CWinF10::GetWnd()
{
	return this;
}

void CWinF10::ResetSkin()
{
	if (m_pWeb)
	{
		m_pWeb->Refresh();
	}
}
bool CWinF10::IsTitle(CString c_strIn)
{
	CString strTitle;
	GetWindowText(strTitle);
	if (c_strIn.Find(strTitle) == 0)
		return true;
	return false;
}

void CWinF10::GetViewTitle(CString &c_strIn)
{
	GetWindowText(c_strIn);

	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock)
	{
		c_strIn += "-";
		c_strIn += pStock->m_strName;
	}
}

BOOL CWinF10::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	return __super::DestroyWindow();
}

void CWinF10::SetViewPage(int c_n)
{
	if (c_n == 99)
	{
		m_pWeb->Navigate(_T("http://std.investoday.com.cn/jsp/f10/yc1.jsp?stockCode=600036&navName=盈利预测"));
		return;
	}
	m_nViewPage = c_n;
}

void CWinF10::DoCommand(int c_nCommand)
{	
	SetViewPage(c_nCommand);
}