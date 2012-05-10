// StockWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StockWnd.h"
#include "MyHtmlView.h"
#include "Resource.h"

// CStockWnd

IMPLEMENT_DYNCREATE(CStockWnd, CFrameWnd)

CStockWnd::CStockWnd(CRect &c_rect,BOOL c_bModal,bool c_bTitle)
: m_pView(NULL)
, m_strUrl("")
{
    m_state = true;
	m_bModal = c_bModal;
    b_front = false;

	if (c_bTitle)
		Create(NULL,VERNAME,WS_OVERLAPPEDWINDOW, c_rect,NULL,0,NULL); 
	else
		Create(NULL,VERNAME,WS_CAPTION|WS_DLGFRAME, c_rect,NULL,0,NULL); 
	
	CRect      rrect; 
 	GetClientRect(rrect);
	
	//m_pView = new CBaseView();
	CMyHtmlView *pMyHtmlView;

	rrect.left += 10;
	rrect.top += 10;
	rrect.bottom -= 10;
	rrect.right -= 10;
	pMyHtmlView = new CMyHtmlView();
	m_pView = pMyHtmlView;
	pMyHtmlView->Create(NULL, NULL, WS_CHILD |WS_VISIBLE,rrect, this, 0, NULL);
	pMyHtmlView->SetSilent(true);
	pMyHtmlView->ShowWindow(SW_SHOW);
}

CStockWnd::CStockWnd()
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

CStockWnd::~CStockWnd()
{

}


BEGIN_MESSAGE_MAP(CStockWnd, CFrameWnd)
	ON_WM_CLOSE()
	ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CStockWnd ��Ϣ�������

BOOL CStockWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	//cs.dwExStyle |=WS_EX_TOOLWINDOW;//����ʾ����ť
	//cs.style   &=   ~WS_CAPTION;
	//cs.style&=WS_BORDER;       //   
	//cs.style&=WS_DLGFRAME;
	return CFrameWnd::PreCreateWindow(cs);
}

void CStockWnd::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    CRect rect;
    GetWindowRect(rect);
    char acBuf[24];
    sprintf(acBuf,"%d",rect.left);

    WritePrivateProfileString(_T("SHOWURL"),_T("left"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
    sprintf(acBuf,"%d",rect.top);
    WritePrivateProfileString(_T("SHOWURL"),_T("top"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
    sprintf(acBuf,"%d",rect.right);
    WritePrivateProfileString(_T("SHOWURL"),_T("right"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
    sprintf(acBuf,"%d",rect.bottom);
    WritePrivateProfileString(_T("SHOWURL"),_T("bottom"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));


	if (m_bModal)/*ģʽ��ʾ*/
	{
		EndModalLoop( TRUE );
		::EnableWindow( GetControlWnd()->m_hWnd, TRUE ); 
		ShowWindow(SW_HIDE);

	}
	else
		CFrameWnd::OnClose();
}

void CStockWnd::SetControlWnd(CWnd  * c_pwndCtrl)
{
	m_pwndCtrl = c_pwndCtrl;
}

CWnd * CStockWnd::GetControlWnd(void)
{
	return m_pwndCtrl;
}

void CStockWnd::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	RECT rect;
	GetClientRect(&rect);
	if (m_pView)
		m_pView->MoveWindow(&rect,1);
}

int CStockWnd::ShowUrl(CString c_strUrl)
{
	((CMyHtmlView *)m_pView)->Navigate2(c_strUrl,0,0,0,0);
	return 0;
}

BOOL CStockWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_MAINFRAME),RT_GROUP_ICON);
	HICON m_hIcon = (HICON)::LoadImage(hInstResource,MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 32, 32, 0);
	if( m_hIcon != 0 )
	{
		SetIcon(m_hIcon,TRUE);
    }

    
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CStockWnd::PostNcDestroy()
{
    // TODO: �ڴ����ר�ô����/����û���

    //CFrameWnd::PostNcDestroy();
    //DestroyWindow();
    m_state = false;
    //delete this;
}

int CStockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������
    //CMenu *pMenu = new CMenu();
    //pMenu->LoadMenu(IDR_MENU1);
    //SetMenu(pMenu);
    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        pSysMenu->AppendMenu(MF_SEPARATOR);  
        pSysMenu->AppendMenu(MF_STRING, IDM_SETTOP, _T("ʼ�ձ�������������ǰ��"));        
    }

    return 0;
}

void CStockWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

    
