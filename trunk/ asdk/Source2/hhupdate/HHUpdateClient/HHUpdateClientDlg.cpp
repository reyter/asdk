// HHUpdateClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HHUpdateClient.h"
#include "HHUpdateClientDlg.h"
#include ".\hhupdateclientdlg.h"
#include <direct.h> 


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int ADD_BUFF=5*1024*1024; //�ڴ治���ۼ���  5M�ۼ�.
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
#pragma warning(disable: 4244)
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHHUpdateClientDlg �Ի���



CHHUpdateClientDlg::CHHUpdateClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHHUpdateClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Socket = INVALID_SOCKET;
	m_bExit = FALSE;
	m_hThread = NULL;
	m_nNeedDownloadFiles = 0;
	m_nDownloadedFilesCount = 0;

	m_nBuffNum = 10*1024*1024;
	m_pBuff = new Byte[10*1024*1024];//��ʼ��10M�ڴ�
	m_nDownloadedCount = 0;

	//ZeroMemory(m_szGroupID,128);
	//sprintf(m_szGroupID,"רҵ��12.36.5.44");
	m_nIncompletePackages = 0;
	m_bStopThread = TRUE;
	m_pProgress = NULL;
	m_nErrorCrcCount= 0;

	m_bHide = TRUE;

	ZeroMemory((char*)&m_UpgradeInfo,sizeof tagUpgradeInfo);
}

CHHUpdateClientDlg::~CHHUpdateClientDlg()
{
	if (m_pBuff)
	{
		delete []m_pBuff;
		m_pBuff = NULL;
		m_nBuffNum = 0;
	}
	if (m_Socket != INVALID_SOCKET) 
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}
	if (NULL != m_pProgress)
	{
		delete m_pProgress;
	}
	WSACleanup();
}

void CHHUpdateClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_BTN_NOUPDATE, m_btnUpdateLater);
}

BEGIN_MESSAGE_MAP(CHHUpdateClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBnClickedBtnUpdate)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_NOUPDATE, OnBnClickedBtnNoupdate)
	ON_WM_COPYDATA(WM_COPYDATA,OnCopyData)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_SHOWDETAIL, OnBnClickedBtnShowdetail)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	//ON_MESSAGE(IDC_BTN_UPDATE, OnBnClickedBtnUpdate)
END_MESSAGE_MAP()


// CHHUpdateClientDlg ��Ϣ�������

BOOL CHHUpdateClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CBitmap* pBitmap = new CBitmap;
	ASSERT(pBitmap);
	pBitmap->LoadBitmap(IDB_BITMAP_HHBK);//����λͼ��Դ
	m_BKBrush.CreatePatternBrush(pBitmap);//����λͼ��ˢ
	delete pBitmap;
 

	SetTimer(20101,1000,NULL);
	SetTimer(20103,2000,NULL);//ˢ�½���
	

	ChangeClientPos(INIT);//��ʼ��.

	m_pProgress = new CTextProgressCtrl();
	m_pProgress->Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH|WS_BORDER, CRect(0,0,0,0), this, IDC_FILEPROGRESS);
	m_pProgress->SetWindowPos(&CWnd::wndTop, 20,282,440, 20, SWP_SHOWWINDOW);
	m_pProgress->SetRange(0, 100);
	m_pProgress->SetPos(0);
	COLORREF  col = RGB(84,238,32);
	m_pProgress->SetForeColour(col);
	m_pProgress->SetTextBkColour(RGB(0,0,255));

	this->SetWindowText("���NSD�Զ���������");


	short	shBtnColor = 30;
	m_btnUpdate.SetNormalTextColor (RGB(0,0,255));
	m_btnUpdate.SetActiveTextColor (RGB(255,0,0));
	
	//m_btnUpdate.SetBkMode (false);
	//m_btnUpdate.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1),AfxGetApp()->LoadIcon(IDI_ICON2));

	
	m_btnUpdateLater.SetNormalTextColor (RGB(0,0,255));
	m_btnUpdateLater.SetActiveTextColor (RGB(0,255,0));
	//m_btnUpdateLater.SetBkMode (false);

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CHHUpdateClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHHUpdateClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (m_bHide)
		{
			//this->ShowWindow(SW_HIDE);
		}
		else
		{
			//this->ShowWindow(TRUE);
		}
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CHHUpdateClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CHHUpdateClientDlg::WinSockInit()
{
	WSADATA data = {0};
	if(WSAStartup(MAKEWORD(2, 2), &data))
		return FALSE;
	if ( LOBYTE(data.wVersion) !=2 || HIBYTE(data.wVersion) != 2 ){
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}

BOOL CHHUpdateClientDlg::SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut > 100 ? 100 : nTimeOut;
	tv.tv_sec  = 0;
	tv.tv_usec = nTimeOut;

	int iRet = 0;
	if ( bRead ) {
		iRet = select(0, &fdset, NULL , NULL, &tv);
	}else{
		iRet = select(0, NULL , &fdset, NULL, &tv);
	}

	if(iRet <= 0) {
		return FALSE;
	} else if (FD_ISSET(hSocket, &fdset)){
		return TRUE;
	}
	return FALSE;
}
const int  nRecvPackSize= sizeof _tagAnswer;

UINT CHHUpdateClientDlg::ThreadProc(LPVOID pParam)
{
	
	ASSERT(pParam);
	CHHUpdateClientDlg *pThis = (CHHUpdateClientDlg *)pParam;
	pThis->m_bExit = 0;
	_tagAnswer AnswerBuff = {0};
	pThis->WinSockInit();
	pThis->m_Socket = INVALID_SOCKET;
	pThis->m_Socket = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
	if ( pThis->m_Socket == INVALID_SOCKET ) 
	{
		CString strBuff;
		strBuff = _T("�½�Socketʧ��!");
		pThis->ShowMsg(strBuff,TRUE);
		
		goto __Error_End;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(pThis->m_UpgradeInfo.nServerPort);
	server.sin_addr.s_addr = inet_addr(pThis->m_UpgradeInfo.szServerIP);//������IP
	if ( connect(pThis->m_Socket, (struct sockaddr *)&server,  sizeof(struct sockaddr)) == SOCKET_ERROR ) 
	{
		CString strBuff;
		strBuff = _T("����ʧ��!");
		pThis->ShowMsg(strBuff,TRUE);	
		pThis->m_bHide = FALSE;
		pThis->SendMessage(WM_PAINT);
		pThis->ChangeClientPos(CONNECT_S);//���ӽ���.
		goto __Error_End;
	}

	pThis->m_bStopThread = FALSE;
	
	pThis->ChangeClientPos(UPDATEBEFORE);//����ǰ����.

	char szPack[nRecvPackSize]={0};
	int nRecvCount=0;//��ΰ������յ��ܴ�С.
	//int nPrePackCount=0;//��һ�ν��հ��Ĵ�С.
	while(TRUE) 
	{

		if ( pThis->SOCKET_Select(pThis->m_Socket) /*&& !pThis->m_bExit */) 
		{
			ZeroMemory((char*)&AnswerBuff,sizeof(_tagAnswer));
			CString strBuff;
			int nRet = recv(pThis->m_Socket, (char *)&AnswerBuff, sizeof(_tagAnswer), 0);
			//while(nRet>)
			if ( nRet > 0 ) 
			{
				///�Ӱ�����ֻ���������
				nRecvCount += nRet;
				if (nRecvCount < nRecvPackSize)//���հ�������.
				{
					memcpy(&szPack[nRecvCount-nRet],(char *)&AnswerBuff,nRet);
					//nPrePackCount = nRet;
					continue;//�ٽ�
				}
			
				if (nRecvCount == nRecvPackSize)//�Ӱ��ոպ�.
				{
					memcpy(&szPack[nRecvCount-nRet],(char *)&AnswerBuff,nRet);
					nRecvCount = 0;//��������
					//��������������AnswerBuff
					memcpy((char*)&AnswerBuff,szPack,nRecvPackSize);
					ZeroMemory(szPack,nRecvPackSize);
					goto CompletePack;
				}

				if (nRecvCount > nRecvPackSize)//����һ����Ҳ�����˲���.
				{
					char szTemp[nRecvPackSize]={0};
					memcpy(szTemp,(char *)&AnswerBuff,nRet);
					//����ν��յİ��ӵ�szPack����
					memcpy(&szPack[nRecvCount-nRet],(char *)&AnswerBuff,nRecvPackSize-nRecvCount+nRet);
					//��������������AnswerBuff
					memcpy((char*)&AnswerBuff,szPack,nRecvPackSize);
					//��ʣ�ಿ�ֿ�����szPack
					memcpy(szPack,&szTemp[nRecvPackSize-nRecvCount+nRet],nRecvCount-nRecvPackSize);
					//����ʣ��
					nRecvCount = nRecvCount-nRecvPackSize;
					
				}
		
				//����������.
CompletePack:
				//����ڴ�ʹ�����������.
				if (!pThis->CheckBuff(pThis->m_nBuffNum,pThis->m_nDownloadedCount,atoi(AnswerBuff.szBuffLen)))
				{
					CString strBuff;
					strBuff = _T("�ڴ����!");
					pThis->ShowMsg(strBuff,TRUE);
					break;
				}
				
				//���յ����ݱ��浽�����ڴ�.
				memcpy(&pThis->m_pBuff[pThis->m_nDownloadedCount],AnswerBuff.btBuff,atoi(AnswerBuff.szBuffLen));
				pThis->m_nDownloadedCount += atoi(AnswerBuff.szBuffLen);//�Ѿ�ʹ���ڴ�����ۼ�

				if (1 == atoi(AnswerBuff.szFlag))//�����ļ��������.
				{
					//nRecvCount = 0;
					switch (atoi(AnswerBuff.szFileType))
					{
					case RE_TYPE_README://readme�������
						{
							
							//������յ��ļ�
							//дreadme�ļ�
							mkdir("..\\Upgrade");
							
							CFile fs(_T("..\\Upgrade\\readme.txt"),CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //���ļ�
							fs.Write(pThis->m_pBuff,pThis->m_nDownloadedCount);
							fs.Close();
							
							//��ʾ�ı�
							strBuff.Format("%s",AnswerBuff.btBuff);
							pThis->ShowMsg(strBuff,TRUE);

							
							pThis->m_bHide = FALSE;

							pThis->SendMessage(WM_PAINT);
							if (pThis->m_UpgradeInfo.bForce)//ǿ������
							{
								pThis->PostMessage( WM_COMMAND, MAKELONG(IDC_BTN_UPDATE,BN_CLICKED), (LPARAM)( pThis->GetDlgItem(IDC_BTN_UPDATE)->GetSafeHwnd()));  
							}
							
							//��ʼ���ڴ���Ϣ.
							pThis->m_nDownloadedCount = 0;//��������
							memset(pThis->m_pBuff,0,pThis->m_nBuffNum);//�ڴ��������.
							
						}
						break;
					case RE_TYPE_XML://xml�������
						{
							//pThis->ShowUpdateProgress(FALSE);
							//������յ��ļ�.
							//дxml�ļ�.
							CFile fs(_T("..\\Upgrade\\update.xml"),CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //���ļ�
							fs.Write("",0);
							fs.Write(pThis->m_pBuff,pThis->m_nDownloadedCount);
							fs.Close();

							//��ʾ�ı�.
							strBuff = "���أ��ļ������б� ...";
							pThis->ShowMsg(strBuff,TRUE);

							if (pThis->m_bExit)
							{
								goto __Error_End;
							}

							//��ʼ���ڴ���Ϣ.
							pThis->m_nDownloadedCount = 0;//��������.
							memset(pThis->m_pBuff,0,pThis->m_nBuffNum);//�ڴ��������.
							//
							_tagRequest Requrst = {0};
							pThis->m_lsXmlFiles.RemoveAll();
							pThis->m_lsNeedDownloadFiles.RemoveAll();
							//��ȡXML
							if (-1 == pThis->m_hhTyXml.HHDecomposeXML(_T("..\\Upgrade\\update.xml"),(CHHTyXml::LSXMLFILES*)&pThis->m_lsXmlFiles))
							{
								//�����ļ�ʧ��
								pThis->ShowMsg("��ȡupdate.xmlʧ��");
								pThis->ShowMsg("�ж�......");
								break;
							}

							//strBuff = ;
							pThis->ShowMsg("�����Ҫ�����ļ�......");
							//ƥ�䱾���ļ�
							pThis->IsSameFile("..");
							pThis->m_nNeedDownloadFiles = (int)pThis->m_lsNeedDownloadFiles.GetCount();//��ȡ��Ҫ�����ļ�����
							//pThis->ShowMsg("�����Ҫ�����ļ�......");
							if (pThis->m_nNeedDownloadFiles)
							{
								//ƥ���Ѿ����ص��ļ� ͬʱ (�����Ҫ)��ѹ��
								int nTemp = pThis->HHUncompress();//����CRCУ����������. -1����Ҫ����.
								if (0 == nTemp)
								{
									pThis->ShowMsg("�������...");
									pThis->ChangeClientPos(UPDATEOVER);
									goto __Error_End;
								}
								else if (nTemp > 0)
								{
									//CRCУ�����д�.
									//�ٴ�ƥ�䱾���ļ�.
									pThis->m_lsNeedDownloadFiles.RemoveAll();
									pThis->m_lsNeedUncompressFiles.RemoveAll();
									pThis->IsSameFile("..");
									
									pThis->m_nErrorCrcCount = 0;//CRCУ��������������.
								}
							}
							else
							{
								//����Ҫ���� �ļ��Ѿ�����
								pThis->ShowMsg("�Ѿ������°����,����Ҫ������");
								pThis->ChangeClientPos(UPDATEOVER);
								goto __Error_End;
							}


							Requrst.nFlag = RE_TYPE_HH;
							pThis->m_nNeedDownloadFiles = (int)pThis->m_lsNeedDownloadFiles.GetCount();//��ȡ��Ҫ�����ļ�����
							if (pThis->m_nNeedDownloadFiles>0)
							{
								PAttribute pAttribute = pThis->m_lsNeedDownloadFiles.GetAt(pThis->m_lsNeedDownloadFiles.FindIndex(pThis->m_nDownloadedFilesCount++));
								if (pAttribute)
								{
									pThis->m_pProgress->SetPos(0);
									pThis->m_pProgress->OnSetText("�����ļ�","");
									CString strGroupID;
									strGroupID.Format("%s%s",pThis->m_UpgradeInfo.szAppID,pThis->m_UpgradeInfo.szVersion);
									///��װ����
									sprintf(Requrst.szFileName,"%s\\update%s.hh",strGroupID,pAttribute->szFileName);
									strcpy(Requrst.szAppID,pThis->m_UpgradeInfo.szAppID);
									strcpy(Requrst.szVersion,pThis->m_UpgradeInfo.szVersion);
									if (pThis->SOCKET_Select(pThis->m_Socket, 100, FALSE)) 
									{
										send(pThis->m_Socket, (char *)&Requrst, sizeof(_tagRequest), 0);
									}
								}
							}
						}
						break;
					case RE_TYPE_HH://.hh�������.
						{
							PAttribute pAttribute = pThis->m_lsNeedDownloadFiles.GetAt(pThis->m_lsNeedDownloadFiles.FindIndex(pThis->m_nDownloadedFilesCount-1));
							//�����ļ�.
							//д.hh�ļ�.
							if (pAttribute)
							{
								if (pThis->m_nDownloadedCount == atoi(AnswerBuff.szAllDataLength))//�����İ�.
								{
									
									CString strFileName;
									strFileName.Format("..\\Upgrade%s.hh",pAttribute->szFileName);
									try
									{
										float fDownloadedCount = pThis->m_nDownloadedFilesCount*1.0;
										pThis->m_pProgress->SetPos((fDownloadedCount/pThis->m_nNeedDownloadFiles*1.0)*100);
										//�������ص��ļ�.
										CFile fs(strFileName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); 
										fs.Write(pThis->m_pBuff,pThis->m_nDownloadedCount);
										_ASSERTE(_CrtCheckMemory());
										fs.Close();
									}
									catch (CFileException *e)
									{
										if (e->m_cause == CFileException::badPath)//ȫ���򲿷�·����Ч�� 
										{
											if (!pThis->HHMkdir(strFileName))//�����ļ���  ����0 �ɹ�
											{
												CFile fs(strFileName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //���ļ�.
												fs.Write(pThis->m_pBuff,pThis->m_nDownloadedCount);
												_ASSERTE(_CrtCheckMemory());
												fs.Close();
											}
										}
									}
									
									
									//��ʾ�ı�.
									strBuff.Format("���أ�%s ...",strFileName);
									pThis->ShowMsg(strBuff);
								}
								else//����.
								{
									pThis->m_nIncompletePackages++;
								}
								
							}
							
							if (pThis->m_bExit)
							{
								goto __Error_End;
							}

							//��������.
							pThis->m_nDownloadedCount = 0;
							//�ڴ��������.
							memset(pThis->m_pBuff,0,pThis->m_nBuffNum);
							_ASSERTE(_CrtCheckMemory());

							//������һ��.
							if (pThis->m_nNeedDownloadFiles > pThis->m_nDownloadedFilesCount)
							{
								_tagRequest Requrst = {0};
								Requrst.nFlag = RE_TYPE_HH;
								pAttribute = pThis->m_lsNeedDownloadFiles.GetAt(pThis->m_lsNeedDownloadFiles.FindIndex(pThis->m_nDownloadedFilesCount++));
								if (pAttribute)
								{
									CString strGroupID;
									strGroupID.Format("%s%s",pThis->m_UpgradeInfo.szAppID,pThis->m_UpgradeInfo.szVersion);
									//��װ����ṹ��.
									sprintf(Requrst.szFileName,"%s\\update%s.hh",strGroupID,pAttribute->szFileName);
									strcpy(Requrst.szAppID,pThis->m_UpgradeInfo.szAppID);
									strcpy(Requrst.szVersion,pThis->m_UpgradeInfo.szVersion);
									if (pThis->SOCKET_Select(pThis->m_Socket, 100, FALSE)) 
									{
										send(pThis->m_Socket, (char *)&Requrst, sizeof(_tagRequest), 0);
									}
								}
							}
							else//���������ļ����.
							{
								//������������.
								if (0 < pThis->HHUncompress())
								{
									//��ʾ�ı�.
									strBuff.Format("CRCУ�����Ҫ��������%d�ļ������ٴ�����",pThis->m_nErrorCrcCount);
									pThis->ShowMsg(strBuff);
									pThis->ChangeClientPos(CONNECT_S);
									goto __Error_End;//����
								}

									//����������.
									if (0 != pThis->m_nIncompletePackages)
									{
										//��ʾ�ı�.
										strBuff.Format("���綪������Ҫ����%d�ļ������ٴ�����",pThis->m_nIncompletePackages);
										pThis->ShowMsg(strBuff);
										pThis->ChangeClientPos(CONNECT_S);
										goto __Error_End;//����
									}
									else
									{
										//��ʾ�ı�.
										strBuff.Format("�������...");
										pThis->ShowMsg(strBuff);
										pThis->ChangeClientPos(UPDATEOVER);
										goto __Error_End;
									}
							}
						}
						break;
					default://���ճ���  ����
						break;
					}
				}			
			}
			else
			{
				//close socket;
				strBuff = _T("��������Ͽ����ӣ�");
				pThis->ShowMsg(strBuff,TRUE);
				break;//����while
			}
		}

	}

__Error_End:
	//�����̣߳���������ڴ治�ͷţ�Ϊ���ٴ�������Ҫ����new .������ջ���շ�����ڴ�.
	pThis->ResetData();//��������

	if (pThis->m_Socket != INVALID_SOCKET) 
	{
		//�ر�socket.
		closesocket(pThis->m_Socket);
		pThis->m_Socket = INVALID_SOCKET;
	}
	WSACleanup();

	if (!pThis->m_bStopThread)
	{
		pThis->m_Event.SetEvent();
	}
	

	return TRUE;
}


int CHHUpdateClientDlg::HHMkdir(const LPCTSTR pFileName)
{
	int nErr = 0;
	char szFileName[MAX_PATH] = {0};
	strcpy(szFileName,pFileName);

	char dir[MAX_PATH]={0};
	char temp[MAX_PATH] = {0};

	char c='\\';
	char *ptr = NULL;

	ptr = strchr(szFileName,c);//ƥ�� "\\"
	for (; NULL!= ptr;ptr = strchr(szFileName,c))
	{
		strncpy(temp,szFileName,ptr-szFileName+1);
		strcat(dir,temp);

		if (strcmpi("..\\",temp))//����� ������"..\\..\\"������ļ���
		{
			mkdir(dir);	
		}
		strcpy(szFileName,&szFileName[ptr-szFileName+1]);
		memset(temp,0,MAX_PATH);
	}
	return nErr;
}


void CHHUpdateClientDlg::ShowMsg(CString strMsg,BOOL bClear)
{
	CRichEditCtrl *pEditShow = (CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT2_SHOW);
	ASSERT(pEditShow);
	if (bClear)
	{
		//pEditShow->Clear();
		pEditShow->SetWindowText("");
	}
		
	pEditShow->SetSel(-1, -1);
	pEditShow->ReplaceSel(strMsg+_T("\r\n"));
}



void CHHUpdateClientDlg::OnCancel()
{
	m_bExit = TRUE;

	if (m_Socket != INVALID_SOCKET) {
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}

	if (m_pBuff)
	{
		delete []m_pBuff;
		m_pBuff = NULL;
		_ASSERTE(_CrtCheckMemory());
		m_nBuffNum = 0;
	}
	
	if (NULL != m_pProgress)
	{
		delete m_pProgress;
		m_pProgress = NULL;
	}
	WSACleanup();
	CDialog::OnCancel();
}

void CHHUpdateClientDlg::OnBnClickedBtnUpdate()
{
	CString strWinText="";
	GetDlgItem(IDC_BTN_UPDATE)->GetWindowText(strWinText);
	UpdateWindow();
		if (m_Socket != INVALID_SOCKET)
		{
			//����xml
			_tagRequest Requrst = {0};
			Requrst.nFlag = RE_TYPE_XML;
			//strcpy();
			CString strAppID;
			strAppID.Format("%s%s",m_UpgradeInfo.szAppID,m_UpgradeInfo.szVersion);
			strcpy(Requrst.szAppID,m_UpgradeInfo.szAppID);
			strcpy(Requrst.szVersion,m_UpgradeInfo.szVersion);
			sprintf(Requrst.szFileName,"%s%s",strAppID,"\\update.xml");
			if (SOCKET_Select(m_Socket, 100, FALSE)) 
			{
				ChangeClientPos(UPDATE);
				send(m_Socket, (char *)&Requrst, sizeof(_tagRequest), 0);//����xml
			}
		}
		else
		{
			//���ӷ�����
			SetTimer(20101,1000,NULL);
		}	
}

BOOL CHHUpdateClientDlg::IsSameFile(const LPCTSTR pFileName)
{
	BOOL bRet = TRUE;
	char szFileName[MAX_PATH];
	_tagAttribute Attribute = {0};
	long lLen=0,lDate=0,lTime=0;
	POSITION  pos = m_lsXmlFiles.GetHeadPosition();
	int count = m_lsXmlFiles.GetCount();
	float count2=0;
	m_pProgress->SetRange(0,100);
	m_pProgress->OnSetText("������","");
	while(NULL != pos)
	{
		count2++;
		m_pProgress->SetPos((count2/count*1.0)*100);
		PAttribute pAttribute = m_lsXmlFiles.GetNext(pos);
		if (pAttribute)
		{
			//�ļ��Ƿ����.
			lLen=0;lDate=0;lTime=0;
			int nCrc=0;
			char szFileVer[MAX_PATH]={0};
			memset(szFileName,0,MAX_PATH);
			memset((char*)&Attribute,0,sizeof(_tagAttribute));
			strcpy(szFileName,pFileName);
			strcat(szFileName,pAttribute->szFileName);

			//��ȡ�����ļ� ��ȡ�����Ϣ�ͷ��������ļ����Ƚ�
			if (m_hhTyXml.GetLocalFileStatus(szFileName,lLen,lDate,lTime,szFileVer,nCrc))
			{
				sprintf(Attribute.szLen,"%ld",lLen);	//�ļ�����
				sprintf(Attribute.szDate,"%ld",lDate);	//�ļ�����޸�����
				sprintf(Attribute.szTime,"%ld",lTime);	//�ļ�����޸�ʱ��
				strcpy(Attribute.szFileVer,szFileVer);	//�ļ����°汾
				sprintf(Attribute.szCrc,"%d",nCrc);		//�ļ�CRCУ����
			
				//�Ƚϰ汾���ļ��� DLL �� EXE �������ļ�
				if (!strcmpi((char *)&szFileName[strlen(szFileName)-4],".dll") || !strcmpi((char *)&szFileName[strlen(szFileName)-4],".exe"))
				{
					if (!strcmpi(pAttribute->szLen,Attribute.szLen) && !strcmpi(pAttribute->szFileVer,Attribute.szFileVer) 
						&& atoi(Attribute.szDate)>=atoi(pAttribute->szDate))
					{
						if (!strcmpi(Attribute.szDate,pAttribute->szDate))//������ͬ
						{
							if (atoi(Attribute.szTime)<atoi(pAttribute->szTime))//�Ƚ�ʱ����
							{
								m_lsNeedDownloadFiles.AddTail(pAttribute);//��ӵ���Ҫ�����ļ��б���
								bRet = FALSE;
							}
						}
						continue;
					}
					else//�ļ�����ͬ.
					{
						m_lsNeedDownloadFiles.AddTail(pAttribute);//��ӵ���Ҫ�����ļ��б���
						bRet = FALSE;
					}
				} 
				else
				{
					if (atoi(Attribute.szDate)>=atoi(pAttribute->szDate))
					{
						if (!strcmpi(Attribute.szDate,pAttribute->szDate))//������ͬ
						{
							if (atoi(Attribute.szTime)<atoi(pAttribute->szTime))//�Ƚ�ʱ����
							{
								m_lsNeedDownloadFiles.AddTail(pAttribute);//��ӵ���Ҫ�����ļ��б���
								bRet = FALSE;
							}
						}
						continue;
					}
					else//���ڲ��    �ļ�����ͬ.
					{
						m_lsNeedDownloadFiles.AddTail(pAttribute);//��ӵ���Ҫ�����ļ��б���
						bRet = FALSE;
					}
				}		
			}
			else//�ļ�������.
			{
				m_lsNeedDownloadFiles.AddTail(pAttribute);//��ӵ���Ҫ�����ļ��б���
				bRet = FALSE;
			}
		}
	}
	return bRet;
}
 //GetProcessHeap();
//ERROR_SHARING_VIOLATION
int CHHUpdateClientDlg::ExitFileInTheUpgradeFloder(const LPCTSTR pFileName)
{
	char szFileName[MAX_PATH]={0};
	int nDownloadCount = 0;//��Ҫ�����ļ���Ŀ

	PAttribute pAttribute = NULL;
	int nCount = m_lsNeedDownloadFiles.GetCount();//��ȡû�к�Upgrade�Ƚ�ǰ��Ҫ�����ļ���Ŀ.
	for (int i = 0;i<nCount;)
	{
		try
		{
			pAttribute = m_lsNeedDownloadFiles.GetAt(m_lsNeedDownloadFiles.FindIndex(i));
		}
		catch(...)
		{
			continue;
		}
		
		if (pAttribute)
		{
			strcpy(szFileName,pFileName);
			strcat(szFileName,pAttribute->szFileName);
			strcat(szFileName,".hh");//UpgradeĿ¼�µ��ļ����Ǻ�׺��.hh��ѹ���ļ�
			CFileFind  fileFind;
			BOOL bResult=fileFind.FindFile(szFileName);
			if(bResult)//UpgradeĿ¼���Ѿ������غõ�ѹ���ļ�.
			{
				//�����Ҫ��ѹ�ļ����б���.
				m_lsNeedUncompressFiles.AddTail(pAttribute);
				//����Ҫ�ٴ�����
				m_lsNeedDownloadFiles.RemoveAt(m_lsNeedDownloadFiles.FindIndex(i));
				nCount--;//������һ
			}
			else
			{
				i++;//��һ��
				nDownloadCount++;
			}
			fileFind.Close();
			ZeroMemory(szFileName,MAX_PATH);
		}
	}
	ShowMsg("���...");
	CString str;
	str.Format("��Ҫ����%d���ļ�",nDownloadCount);
	ShowMsg(str);
	return nDownloadCount;
}
/*
void CHHUpdateClientDlg::ReleaseXMLFILESList(LSXMLFILES *pList)
{
	
	if(pList == NULL)
		return;

	PAttribute  pStruct = NULL;
	POSITION pos;
	int i;
	i = 0;

	for (; i<pList->GetCount(); i++)
	{
		if (NULL==(pos=pList->FindIndex(i)))
		{
			continue;
		}
		pStruct = pList->GetAt(pos);
		if (pStruct!=NULL)
		{
			delete pStruct;
			pStruct = NULL;
		}
	}

	pList->RemoveAll();
}
*/
/*
void CHHUpdateClientDlg::ReleaseNEEDDOWNLOADFILESList(LSNEEDDOWNLOADFILES *pList)
{
	if(pList == NULL)
		return;

	PAttribute pStruct = NULL;
	POSITION pos;
	int i;
	i = 0;

	for (; i<pList->GetCount(); i++)
	{
		if (NULL==(pos=pList->FindIndex(i)))
		{
			continue;
		}
		pStruct = pList->GetAt(pos);
		if (pStruct!=NULL)
		{
			delete pStruct;
			pStruct = NULL;
		}
	}

	pList->RemoveAll();
}
*/
BOOL CHHUpdateClientDlg::CheckBuff(int nBuffNum,int nBuffCount,int nNeedBuffNum)
{
	if (nBuffNum <= nBuffCount+nNeedBuffNum)//�����ڴ治����Ҫ.
	{
		Byte *pBuff = new Byte[m_nBuffNum+ADD_BUFF];//�ڴ治��ÿ������5M.
		if (pBuff)
		{
			m_nBuffNum += ADD_BUFF;
			memcpy(pBuff,m_pBuff,nBuffCount);
			_ASSERTE(_CrtCheckMemory());
			delete []m_pBuff;
			_ASSERTE(_CrtCheckMemory());
			m_pBuff = pBuff;//��ԭ����ָ��ָ����������ڴ�����.
			_ASSERTE(_CrtCheckMemory());
			pBuff = NULL;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CHHUpdateClientDlg::OnTimer(UINT nIDEvent)
{
	if (20101 == nIDEvent)
	{
		KillTimer(nIDEvent);
		CWinThread *pThread = AfxBeginThread(ThreadProc, this);
		m_hThread = pThread->m_hThread;
		Sleep(1000);
		//����readme�ļ�
		ASSERT(m_Socket != INVALID_SOCKET);
		if (m_Socket != INVALID_SOCKET)
		{
			_tagRequest Requrst = {0};
			Requrst.nFlag = RE_TYPE_README;
			CString strAppID;
			strAppID.Format("%s%s",m_UpgradeInfo.szAppID,m_UpgradeInfo.szVersion);
			sprintf(Requrst.szFileName,"%s%s",strAppID,"\\readme.txt");
			sprintf(Requrst.szUserID,"%s",m_UpgradeInfo.szUserID);
			strcpy(Requrst.szAppID,m_UpgradeInfo.szAppID);
			strcpy(Requrst.szVersion,m_UpgradeInfo.szVersion);
			if (SOCKET_Select(m_Socket, 100, FALSE)) 
			{
				send(m_Socket, (char *)&Requrst, sizeof(_tagRequest), 0);
			}		
		}
	}
	if (20102 == nIDEvent)
	{
		if (IsWindow(m_UpgradeInfo.hWnd))
		{
			AfxMessageBox("���������Ҫ�ر�NSD����ر�!");
		}
	}
	if (20103 == nIDEvent)
	{
		GetDlgItem(IDC_BTN_UPDATE)->Invalidate(TRUE);
		GetDlgItem(IDC_BTN_NOUPDATE)->Invalidate(TRUE);
	}

	CDialog::OnTimer(nIDEvent);
}


int CHHUpdateClientDlg::ResetData()
{
	m_lsXmlFiles.RemoveAll();
	m_lsNeedDownloadFiles.RemoveAll();
	//m_lsDownloadedFiles.RemoveAll();
	m_lsNeedUncompressFiles.RemoveAll();
	m_nNeedDownloadFiles = 0;//��Ҫ����.hh�ļ�����.
	m_nDownloadedFilesCount = 0;//�Ѿ�����.hh�ļ�������.

	ZeroMemory(m_pBuff,m_nBuffNum);//m_nBuffNum��������
	_ASSERTE(_CrtCheckMemory());
	
	m_nDownloadedCount = 0;//һ���ļ��Ѿ����س��ȼ���.
	m_nIncompletePackages = 0;//���ع����� �������İ�����.

	m_nErrorCrcCount = 0;//CRCУ��������������.
	return 0;
}


void CHHUpdateClientDlg::ShowUpdateProgress(BOOL bShow)
{
	static CRect reDlgRectLarge(0, 0, 0, 0);
	static CRect reDlgRectSmall(0, 0, 0, 0);


	if ( reDlgRectLarge.IsRectNull() ) {
		GetWindowRect(&reDlgRectLarge);
		reDlgRectSmall = reDlgRectLarge;
		reDlgRectSmall.bottom -= 135;

	
	}
	if ( bShow ) 
	{
		SetWindowPos(NULL, 0, 0, reDlgRectLarge.Width(), reDlgRectLarge.Height(), SWP_NOZORDER | SWP_NOMOVE);
		
	}else
	{
		SetWindowPos(NULL, 0, 0, reDlgRectSmall.Width(), reDlgRectSmall.Height(), SWP_NOZORDER | SWP_NOMOVE);
		
	}
}
void CHHUpdateClientDlg::OnBnClickedBtnNoupdate()
{
	CString strText;
	GetDlgItem(IDC_BTN_NOUPDATE)->GetWindowText(strText);
	if (!strcmpi(strText,"�ݲ�����") || !strcmpi(strText,"�ر�"))
	{
		//OnCancel(); 
		SendMessage(WM_CLOSE);
	} 
	else//ȡ������
	{
		m_bExit = TRUE;
        ChangeClientPos(STOPUPDATE);
	}
	
}

int CHHUpdateClientDlg::HHUncompress()
{
	if (!ExitFileInTheUpgradeFloder("..\\Upgrade"))
	{
		CProcessDetail ProcessDlg;
		if (IsWindow(m_UpgradeInfo.hWnd))
		{
			AfxMessageBox("���������Ҫ�ر�NSD����ر�!");
		}
		SetTimer(20102,5000,NULL);
		while (IsWindow(m_UpgradeInfo.hWnd))
		{
			Sleep(1000);
		}
		KillTimer(20102);
		//����Ҫ����  ֱ�ӽ�ѹ��
		int i ,n ;
		i = n = 0;
		uLongf ulLen = 0;
		PAttribute pAttribute = NULL;
		n = m_lsNeedUncompressFiles.GetCount();
		char szResFileName[MAX_PATH]={0};//��ѹԴ�ļ���ַ
		char szDesFileName[MAX_PATH]={0};//��ѹĿ���ļ���ַ
		m_pProgress->SetPos(0);
		m_pProgress->OnSetText("��ѹ������","");
		char szfullpath[MAX_PATH]={0};
		GetModuleFileName(NULL,szfullpath,MAX_PATH);
		char *ptr, c = '\\'; 
		ptr = strrchr(szfullpath,c);
		memset(&szfullpath[ptr-szfullpath],0,strlen(ptr));
		ptr = strrchr(szfullpath,c);
		memset(&szfullpath[ptr-szfullpath],0,strlen(ptr));
		m_processCtrl.EnumProcess(NULL);
		//m_lsOccupation.RemoveAll();
		for (i = 0;i<n;i++)
		{
			pAttribute = m_lsNeedUncompressFiles.GetAt(m_lsNeedUncompressFiles.FindIndex(i));
			if (pAttribute)
			{
				sprintf(szDesFileName,"%s%s",szfullpath,pAttribute->szFileName);
				for (int j = 0;j<m_processCtrl.m_lsProcessFiles.GetCount();j++)
				{
					if (!strcmpi(szDesFileName,m_processCtrl.m_lsProcessFiles.GetAt(m_processCtrl.m_lsProcessFiles.FindIndex(j)).path))
					{
						ProcessDlg.m_ListMD.AddTail(m_processCtrl.m_lsProcessFiles.GetAt(m_processCtrl.m_lsProcessFiles.FindIndex(j)));
					}					
				}	
			}
		}
		if (ProcessDlg.m_ListMD.GetCount()>0)
		{
			
			
			ProcessDlg.DoModal();
			//aa.InitListData();
		}
		float fCmopressedCount = 0;
		
		int nCrc=0;
		for (i=0;i<n;i++)
		{
			fCmopressedCount = i*1.0;
			m_pProgress->SetPos(((fCmopressedCount+1.0)/n*1.0)*100);
			pAttribute = m_lsNeedUncompressFiles.GetAt(m_lsNeedUncompressFiles.FindIndex(i));
			if (pAttribute)
			{
				sprintf(szResFileName,"%s%s","..\\Upgrade",pAttribute->szFileName);//"..\\Upgrade"���������Ŀ¼
				strcat(szResFileName,".hh");//��Ҫ��ѹ�ļ�����.hh���ļ�
				sprintf(szDesFileName,"%s%s","..",pAttribute->szFileName);
				nCrc = atoi(pAttribute->szCrc);
				if (-5 == m_hhCompress.HHUncompress2(szDesFileName,szResFileName,&ulLen,nCrc))
				{
					m_nErrorCrcCount++;
				}
				try
				{
					CFile::Remove(szResFileName);//ɾ��.hh�ļ�.
				}
				catch (...)
				{
				}

				nCrc = 0;
				ZeroMemory(szResFileName,sizeof(szResFileName));
			}
		}
		return m_nErrorCrcCount;
	}
	return -1;
}



BOOL CHHUpdateClientDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{

	tagUpgradeInfo *pProcessMsg = NULL;
	pProcessMsg=(tagUpgradeInfo *)pCopyDataStruct->lpData;
	memcpy(&m_UpgradeInfo,(tagUpgradeInfo *)pCopyDataStruct->lpData,sizeof tagUpgradeInfo);
	
	return CWnd::OnCopyData(pWnd, pCopyDataStruct);
}
void CHHUpdateClientDlg::OnClose()
{
	m_bExit = TRUE;

	if (!m_bStopThread)
	{
		WaitForSingleObject(m_Event.m_hObject,1000);
		Sleep(1000);
	}
	
	CDialog::OnClose();
}

void CHHUpdateClientDlg::ChangeClientPos(int nType)
{
	switch(nType)
	{
	case INIT:
		{
			ShowUpdateProgress(FALSE);
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(FALSE);//����
			GetDlgItem(IDC_BTN_NOUPDATE)->ShowWindow(FALSE);//����
			GetDlgItem(IDC_STATIC_Update)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_UpdateLater)->ShowWindow(FALSE);
		}
		break;
	case CONNECT_S:
		{
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_BTN_NOUPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_Update)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_UpdateLater)->ShowWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->SetWindowText("���ӷ�����");
		}
		break;
	case UPDATEBEFORE:
		{
			GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->SetWindowText("��������");
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(TRUE);//����
			GetDlgItem(IDC_BTN_NOUPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_Update)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_UpdateLater)->ShowWindow(TRUE);
		}
		break;
	case UPDATE:
		{
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_Update)->ShowWindow(FALSE);
			GetDlgItem(IDC_BTN_NOUPDATE)->SetWindowText("ȡ��");
			GetDlgItem(IDC_STATIC_NEWS)->ShowWindow(FALSE);
			GetDlgItem(IDC_RICHEDIT2_SHOW)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_PROCESS)->SetWindowPos(&CWnd::wndTop, 15,10,345, 45, SWP_SHOWWINDOW);
			m_pProgress->SetWindowPos(&CWnd::wndTop, 20,28,335, 15, SWP_SHOWWINDOW);
			GetDlgItem(IDC_BTN_SHOWDETAIL)->SetWindowPos(&CWnd::wndTop, 15,60,60, 20, SWP_SHOWWINDOW);
		}
		break;
	case DETAIL:
		{
			GetDlgItem(IDC_BTN_SHOWDETAIL)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_NEWS)->SetWindowPos(&CWnd::wndTop, 15,60,345, 120, SWP_SHOWWINDOW);
			GetDlgItem(IDC_RICHEDIT2_SHOW)->SetWindowPos(&CWnd::wndTop, 20,75,335, 100, SWP_SHOWWINDOW);
		}
		break;
	case STOPUPDATE:
		{
			m_pProgress->SetPos(0);
			GetDlgItem(IDC_BTN_NOUPDATE)->SetWindowText("�ݲ�����");
			GetDlgItem(IDC_BTN_NOUPDATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_Update)->ShowWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->SetWindowText("���ӷ�����");
		}
		break;
	case UPDATEOVER:
		{
			StartNSD();
			GetDlgItem(IDC_BTN_NOUPDATE)->SetWindowText("�ر�");
		}
		break;
	default:break;
	}

	GetDlgItem(IDC_BTN_UPDATE)->Invalidate(TRUE);
	GetDlgItem(IDC_BTN_NOUPDATE)->Invalidate(TRUE);
	Invalidate(TRUE);

}

void CHHUpdateClientDlg::OnBnClickedBtnShowdetail()
{
	ChangeClientPos(DETAIL);
}

int CHHUpdateClientDlg::StartNSD()
{

	if (!IsWindow(m_UpgradeInfo.hWnd))
	{
		STARTUPINFO si; //һЩ�ر���������
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOW;
		PROCESS_INFORMATION pi; //�ر��������ý���
		if(!CreateProcess(m_UpgradeInfo.chAppName,NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}

		

}

HBRUSH CHHUpdateClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_DLG ) 
		return (HBRUSH)m_BKBrush.GetSafeHandle(); //���ش�����λͼ��ˢ
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	switch(pWnd->GetDlgCtrlID()) 
	{ 
	case IDC_STATIC_CZKJ: 
		{
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		}
	default: 
		break; 
	} 
	return hbr;
}

void CHHUpdateClientDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//����WM_NCLBUTTONDOWN��Ϣ��ʹWindows��Ϊ����ڱ�������
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}
/*
//��������������CopyScreenToBitmap��������Ļָ��������ͼƬ��SaveBitmapToFile������ͼƬ����ļ���

HBITMAP CHHUpdateClientDlg::CopyScreenToBitmap(LPRECT lpRect)
{

	HDC   hScrDC,   hMemDC;               
	//   ��Ļ���ڴ��豸������   
	HBITMAP   hBitmap,hOldBitmap;         
	//   λͼ���   
	int               nX,   nY,   nX2,   nY2;               
	//   ѡ����������   
	int               nWidth,   nHeight;               
	//   λͼ��Ⱥ͸߶�   
	int               xScrn,   yScrn;                     
	//   ��Ļ�ֱ���   
	//   ȷ��ѡ������Ϊ�վ���   
	if   (IsRectEmpty(lpRect))   
		return   NULL;   
	//Ϊ��Ļ�����豸������   
	hScrDC   =   CreateDC("DISPLAY",   NULL,   NULL,   NULL);  
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������   
	hMemDC   =   CreateCompatibleDC(hScrDC);   
	//   ���ѡ����������   
	nX   =   lpRect->left;   
	nY   =   lpRect->top;   
	nX2   =   lpRect->right;   
	nY2   =   lpRect->bottom;   
	//   �����Ļ�ֱ���   
	xScrn   =   GetDeviceCaps(hScrDC,   HORZRES);   
	yScrn   =   GetDeviceCaps(hScrDC,   VERTRES);   
	//ȷ��ѡ�������ǿɼ���   
	if   (nX   <   0)   
		nX   =   0;   
	if   (nY   <   0)   
		nY   =   0;   
	if   (nX2   >   xScrn)   
		nX2   =   xScrn;   
	if   (nY2   >   yScrn)   
		nY2   =   yScrn;   
	nWidth   =   nX2   -   nX;   
	nHeight   =   nY2   -   nY;   
	//   ����һ������Ļ�豸��������ݵ�λͼ   
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);   
	// hBitmap = (HBITMAP)LoadImage(NULL, ".\\MyData\\SnapStill.bmp", IMAGE_BITMAP,
	//  0, 0, LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
	//   ����λͼѡ���ڴ��豸��������   
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);   
	//   ����Ļ�豸�����������ڴ��豸��������   
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC,   nX,   nY,   SRCCOPY);   
	//�õ���Ļλͼ�ľ��   
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);   
	//���     
	DeleteDC(hScrDC);   
	DeleteDC(hMemDC);   
	//   ����λͼ���   

	return   hBitmap;

}

BOOL CHHUpdateClientDlg::SaveBitmapToFile(HBITMAP hBitmap, CString FileName)
{
	HDC   hDC;   
	//��ǰ�ֱ�����ÿ������ռ�ֽ���   
	int   iBits;   
	//λͼ��ÿ������ռ�ֽ���   
	WORD   wBitCount;   
	//�����ɫ���С��   λͼ�������ֽڴ�С   ��λͼ�ļ���С   ��   д���ļ��ֽ���     
	DWORD   dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;     
	//λͼ���Խṹ     
	BITMAP   Bitmap;       
	//λͼ�ļ�ͷ�ṹ   
	BITMAPFILEHEADER   bmfHdr;       
	//λͼ��Ϣͷ�ṹ     
	BITMAPINFOHEADER   bi;       
	//ָ��λͼ��Ϣͷ�ṹ       
	LPBITMAPINFOHEADER   lpbi;       
	//�����ļ��������ڴ�������ɫ����     
	HANDLE   fh,   hDib,   hPal,hOldPal=NULL;     

	//����λͼ�ļ�ÿ��������ռ�ֽ���     
	hDC   =   CreateDC("DISPLAY",   NULL,   NULL,   NULL);   
	iBits   =   GetDeviceCaps(hDC,   BITSPIXEL)   *   GetDeviceCaps(hDC,   PLANES);     
	DeleteDC(hDC);     
	if   (iBits   <=   1) wBitCount   =   1;     
	else   if   (iBits   <=   4)   wBitCount   =   4;     
	else   if   (iBits   <=   8)   wBitCount   =   8;     
	else   wBitCount   =   24;     

	GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);   
	bi.biSize =   sizeof(BITMAPINFOHEADER);   
	bi.biWidth =   Bitmap.bmWidth;   
	bi.biHeight =   Bitmap.bmHeight;   
	bi.biPlanes =   1;   
	bi.biBitCount =   wBitCount;   
	bi.biCompression =   BI_RGB;   
	bi.biSizeImage =   0;   
	bi.biXPelsPerMeter =   0;   
	bi.biYPelsPerMeter =   0;   
	bi.biClrImportant =   0;   
	bi.biClrUsed =   0;   

	dwBmBitsSize   =   ((Bitmap.bmWidth   *   wBitCount   +   31)   /   32)   *   4   *   Bitmap.bmHeight;   

	//Ϊλͼ���ݷ����ڴ�     
	hDib   =   GlobalAlloc(GHND,dwBmBitsSize   +   dwPaletteSize   +   sizeof(BITMAPINFOHEADER));     
	lpbi   =   (LPBITMAPINFOHEADER)GlobalLock(hDib);     
	*lpbi   =   bi;     

	//   �����ɫ��       
	hPal   =   GetStockObject(DEFAULT_PALETTE);     
	if   (hPal)     
	{     
		hDC   =   ::GetDC(NULL);     
		hOldPal   =   ::SelectPalette(hDC,   (HPALETTE)hPal,   FALSE);     
		RealizePalette(hDC);     
	}   

	//   ��ȡ�õ�ɫ�����µ�����ֵ     
	GetDIBits(hDC,   hBitmap,   0,   (UINT)   Bitmap.bmHeight,   (LPSTR)lpbi   +   sizeof(BITMAPINFOHEADER)     
		+dwPaletteSize, (BITMAPINFO   *)lpbi,   DIB_RGB_COLORS);     

	//�ָ���ɫ��       
	if   (hOldPal)     
	{     
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);     
		RealizePalette(hDC);     
		::ReleaseDC(NULL,   hDC);     
	}     

	//����λͼ�ļ�       
	fh   =   CreateFile(FileName,   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,     
		FILE_ATTRIBUTE_NORMAL   |   FILE_FLAG_SEQUENTIAL_SCAN,   NULL);     

	if   (fh   ==   INVALID_HANDLE_VALUE)     return   FALSE;     

	//   ����λͼ�ļ�ͷ     
	bmfHdr.bfType   =   0x4D42;   //   "BM"     
	dwDIBSize   =   sizeof(BITMAPFILEHEADER)   +   sizeof(BITMAPINFOHEADER)   +   dwPaletteSize   +   dwBmBitsSize;       
	bmfHdr.bfSize   =   dwDIBSize;     
	bmfHdr.bfReserved1   =   0;     
	bmfHdr.bfReserved2   =   0;     
	bmfHdr.bfOffBits   =   (DWORD)sizeof(BITMAPFILEHEADER)   +   (DWORD)sizeof(BITMAPINFOHEADER)   +   dwPaletteSize;     
	//   д��λͼ�ļ�ͷ     
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);     
	//   д��λͼ�ļ���������     
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);     
	//���       
	GlobalUnlock(hDib);     
	GlobalFree(hDib);     
	CloseHandle(fh);     

	return   TRUE;  

}
*/

