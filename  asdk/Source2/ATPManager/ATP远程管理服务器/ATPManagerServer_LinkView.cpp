// ATPManagerServer_LinkView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ATPManager.h"
#include "ATPManagerServer_LinkView.h"
#include "HHNetFrameProcessor_ATPManagerServer.h"

// CATPManagerServer_LinkView
CATPFileDBApi *g_pATPFileDBApi = NULL;
CWndATPManagerBGS g_wndMsgTransfer;

//���ݷ��Ͷ�ջ�б�
CPtrList g_StackList;

IMPLEMENT_DYNCREATE(CATPManagerServer_LinkView, CHHNetFrameProcessor_LinkView)

CATPManagerServer_LinkView::CATPManagerServer_LinkView()
{
	if (!g_pATPFileDBApi)
	{
		g_pATPFileDBApi = new CATPFileDBApi();
	}
	if (!g_pATPFileDBApi)
	{
		AfxMessageBox("���ݿ�����ʼ������!");
		return;
	}
}

CATPManagerServer_LinkView::~CATPManagerServer_LinkView()
{
	g_wndMsgTransfer.DestroyWindow();
	
	if (g_pATPFileDBApi)
	{
		delete g_pATPFileDBApi;
	}
}

BEGIN_MESSAGE_MAP(CATPManagerServer_LinkView, CHHNetFrameProcessor_LinkView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CATPManagerServer_LinkView ��ͼ

void CATPManagerServer_LinkView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CATPManagerServer_LinkView ���

#ifdef _DEBUG
void CATPManagerServer_LinkView::AssertValid() const
{
	CHHNetFrameProcessor_LinkView::AssertValid();
}

#ifndef _WIN32_WCE
void CATPManagerServer_LinkView::Dump(CDumpContext& dc) const
{
	CHHNetFrameProcessor_LinkView::Dump(dc);
}
#endif
#endif //_DEBUG


// CATPManagerServer_LinkView ��Ϣ�������


int CATPManagerServer_LinkView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHHNetFrameProcessor_LinkView::OnCreate(lpCreateStruct) == -1)
	{
		AfxMessageBox("������ܷ��ʹ���!");
		return -1;

	}
		

	int nCreate = g_wndMsgTransfer.Create(ID_ATPSVC_MANAGER,0,this);
	if (nCreate != 0)
	{
		AfxMessageBox("��������ͨ�ŷ���ʧ�ܣ�");
	}

	// TODO:  �ڴ������ר�õĴ�������
	HHLISTCTRL_HEAD headDef[16];
	int i;	
	i=0;headDef[i].Init("���"		,HHIDLT_DEF_ORDER		, 0, 0,	0, 0,	4*6+6);
	//i++;headDef[i].Init("�û�DN"	,HHIDLT_DEF_NFP_DN		, 0, 0,	0, 0,	22*6+6);
	//i++;headDef[i].Init("�û�ID"	,HHIDLT_DEF_NFP_USERID	, 0, 0,	0, 0,	13*6+6);
	i++;headDef[i].Init("�û�����"	,HHIDLT_DEF_NFP_USERNAME, 0, 0,	0, 0,	13*6+6);
	i++;headDef[i].Init("��ע"		,HHIDLT_DEF_NFP_CSTRING2, 0, 0,	0, 0,	20*6+6);
	i++;headDef[i].Init("״̬"		,HHIDLT_DEF_NFP_STATUS	, 0, 0,	0, 0,	28*6+6);
	i++;headDef[i].Init("IP��ַ"	,HHIDLT_DEF_NFP_IP		, 0, 0,	0, 0,	36*6+6);
	i++;headDef[i].Init("��ǰ����"	,HHIDLT_DEF_NFP_SEND0	, 0, 0, 0, 0,	9*6+6);
	i++;headDef[i].Init("��ǰ����"	,HHIDLT_DEF_NFP_RECEIVE0, 0, 0,	0, 0,	9*6+6);
	i++;headDef[i].Init("����"		,HHIDLT_DEF_NFP_SEND	, 0, 0, 0, 0,	10*6+6);
	i++;headDef[i].Init("����"		,HHIDLT_DEF_NFP_RECEIVE	, 0, 0,	0, 0,	10*6+6);
	i++;headDef[i].Init("��½ʱ��"	,HHIDLT_DEF_NFP_LOGTIME	, 0, 0,	0, 0,	19*6+6);
	i++;headDef[i].Init("����"		,HHIDLT_DEF_NFP_CSTRING1, 0, 0,	0, 0,	16*6+6);
	//i++;headDef[i].Init("����"		,HHIDLT_DEF_NFP_DN,		  0, 0,	0, 0,	16*6+6);
	i++;
	
	SetLinkListHeadDef(headDef,i);
	m_WndList.m_ListFont.fontTitle.Init("����_GB2312", 20, TRUE, FALSE);
	char chTitle[128] = {"TDF������"};
	CHHResource::GetResourceData("StartPage", 20, 0, 0, chTitle);
	m_WndList.SetListTitle(chTitle);//"��̬����ת��������");
	m_WndList.SetListStyle(HHIDLT_HEAD);
	//m_pToolBar->SetButtonCheck(IDC_BUTTON_MAP   ,1);
	//m_pToolBar->SetButtonCheck(IDC_BUTTON_LOG   ,1);

	//m_pToolBar->ShowToolBarButton(ID_BUTTON_SAVEDYNDATA, FALSE);
	//m_pToolBar->ShowToolBarButton(IDC_BUTTON_TRANSLATEDATA, FALSE);
	//ShowWindow(SW_HIDE);
	return 0;
}

void CATPManagerServer_LinkView::OnOpenUserDocument(CString strUserDocumentPath, CString strUserDocumentName)
{
	//if(CHHResource::GetResourceData("HHSFEData",0x1000301a/*ID_TRADEDATA_IPXFLAG*/))
	//{
	//	m_pToolBar->ShowToolBarButton(IDC_BUTTON_AUTODOWN   ,0);
	//}
	//CString strFileName;
	//strFileName=(char*)CHHDataChannelCtrl::GetHHNsdSystemInformation(ID_SYSINFO_USERLOCALDIR);
	//strFileName+="\\�����������־.log";
	//SetSaveDataFileName(strFileName);
	//ReadRegistSaveData();
	//_ASSERTE(_CrtCheckMemory());
	int nPort = 0;
	nPort =::GetPrivateProfileInt("ATPManagerConfig","port",0,".\\ATPManager.ini");
// 	if (nPort == 0)
// 	{
// 		AfxMessageBox("������ͨѶ�˿�!");
// 		return;
// 	}
	//int nPort	= 1234;
	BOOL bl		= CHHNetFrameProcessor::RegistServerNetFrameProcessor(1, 53, "ATPԶ�̹������", RUNTIME_CLASS(CHHNetFrameProcessor_ATPManagerServer));
	int nRet	= CHHNetFrameProcessor::CreateIPListen(nPort, "ATPԶ�̹������", "", 1, 53, RUNTIME_CLASS(CHHNetFrameProcessor_ATPManagerServer));
	RegistNetFrameProcessor(RUNTIME_CLASS(CHHNetFrameProcessor_ATPManagerServer));
	
	CHHNetFrameProcessor_LinkView::OnOpenUserDocument(strUserDocumentPath, strUserDocumentName);
}
