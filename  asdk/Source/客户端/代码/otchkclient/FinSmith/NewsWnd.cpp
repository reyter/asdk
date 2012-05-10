// NewsWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "HeadClose.h"
#include "NewsWnd.h"
#include "MyHtmlView.h"
#include "Resource.h"

// CStockWnd

IMPLEMENT_DYNCREATE(CNewsWnd, CFrameWnd)

CNewsWnd::CNewsWnd(CRect &c_rect,BOOL c_bModal,bool c_bTitle)
: m_pView(NULL)
, m_strUrl("")
{
    m_state = true;
	m_bModal = c_bModal;
    b_front = false;

	if (c_bTitle)
		Create(NULL,VERNAME,WS_OVERLAPPEDWINDOW, c_rect,NULL,0,NULL); 
	else		
		Create(NULL,VERNAME,WS_DLGFRAME, c_rect,NULL,0,NULL); 
	
	CRect      rrect; 
 	GetClientRect(rrect);
	
	//m_pView = new CBaseView();
	CMyHtmlView *pMyHtmlView;

	GetClientRect(rrect);
	rrect.left += 10;
	rrect.top += 10;
	rrect.bottom -= 24;
	rrect.right -= 10;
	pMyHtmlView = new CMyHtmlView();
	m_pView = pMyHtmlView;
	pMyHtmlView->Create(NULL, NULL, WS_CHILD |WS_VISIBLE,rrect, this, 0, NULL);
	pMyHtmlView->SetSilent(true);
	pMyHtmlView->ShowWindow(SW_SHOW);
}

CNewsWnd::CNewsWnd()
: m_pView(NULL)
{
	Create(NULL,VERNAME,WS_OVERLAPPEDWINDOW, CRect(0,0,900,600),NULL,0,NULL); 
	m_bModal = false;
	CRect      rrect; 
 	GetClientRect(rrect);
		
	CMyHtmlView *pView;
	pView = new CMyHtmlView();
	m_pView = pView;
	pView->Create(NULL, NULL, WS_CHILD |WS_VISIBLE,rrect, this, 0, NULL);
	pView->ShowWindow(SW_SHOW);
	
}

CNewsWnd::~CNewsWnd()
{
}


BEGIN_MESSAGE_MAP(CNewsWnd, CFrameWnd)
	ON_WM_CLOSE()
	ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CStockWnd 消息处理程序

BOOL CNewsWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	//cs.dwExStyle |=WS_EX_TOOLWINDOW;//不显示任务按钮
	//cs.style   &=   ~WS_CAPTION;
	//cs.style&=WS_BORDER;       //   
	//cs.style&=WS_DLGFRAME;
	return CFrameWnd::PreCreateWindow(cs);
}

void CNewsWnd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

    CRect rect;
    GetWindowRect(rect);
    char acBuf[24];
    sprintf(acBuf,"%d",rect.left);

    WritePrivateProfileString(_T("SHOWNEWS"),_T("left"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
    sprintf(acBuf,"%d",rect.top);
    WritePrivateProfileString(_T("SHOWNEWS"),_T("top"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
    sprintf(acBuf,"%d",rect.right);
    WritePrivateProfileString(_T("SHOWNEWS"),_T("right"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
    sprintf(acBuf,"%d",rect.bottom);
    WritePrivateProfileString(_T("SHOWNEWS"),_T("bottom"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));


	if (m_bModal)/*模式显示*/
	{
		EndModalLoop( TRUE );
		::EnableWindow( GetControlWnd()->m_hWnd, TRUE ); 
		ShowWindow(SW_HIDE);

	}
	else
		CFrameWnd::OnClose();
}

void CNewsWnd::SetControlWnd(CWnd  * c_pwndCtrl)
{
	m_pwndCtrl = c_pwndCtrl;
}

CWnd * CNewsWnd::GetControlWnd(void)
{
	return m_pwndCtrl;
}

void CNewsWnd::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	RECT rect;		
	GetClientRect(&rect);
	if (m_pView)
		m_pView->MoveWindow(&rect,1);
}

int CNewsWnd::ShowUrl(CString c_strUrl)
{
	((CMyHtmlView *)m_pView)->Navigate2(c_strUrl,0,0,0,0);
	return 0;
}

BOOL CNewsWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_MAINFRAME),RT_GROUP_ICON);
	HICON m_hIcon = (HICON)::LoadImage(hInstResource,MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 32, 32, 0);
	if( m_hIcon != 0 )
	{
		SetIcon(m_hIcon,TRUE);
    }

    
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CNewsWnd::PostNcDestroy()
{
    // TODO: 在此添加专用代码和/或调用基类

    //CFrameWnd::PostNcDestroy();
    //DestroyWindow();
    m_state = false;
    //delete this;
}

int CNewsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    //CMenu *pMenu = new CMenu();
    //pMenu->LoadMenu(IDR_MENU1);
    //SetMenu(pMenu);
    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        pSysMenu->AppendMenu(MF_SEPARATOR);  
        pSysMenu->AppendMenu(MF_STRING, IDM_SETTOP, _T("始终保持在其他窗口前端"));
    }

    return 0;
}

void CNewsWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (nID == IDM_SETTOP)
    {
        CMenu* pSysMenu = GetSystemMenu(FALSE);
        if (pSysMenu != NULL)
        {
            CRect rect;
            GetWindowRect(rect);
            if (!b_front)
            {
                b_front = true;
                pSysMenu->CheckMenuItem(nID,MF_CHECKED);
                this->SetWindowPos(&this->wndTopMost ,rect.left, rect.top,0,0,SWP_NOSIZE);
                this->BringWindowToTop();
            }
            else
            {
                b_front = false;
                pSysMenu->CheckMenuItem(nID,MF_UNCHECKED);
                this->SetWindowPos(&this->wndNoTopMost ,rect.left, rect.top,0,0,SWP_NOSIZE);
                this->BringWindowToTop();
            }            
        }
        
    }
    else
    {
        CFrameWnd::OnSysCommand(nID, lParam);
    }
}

    
