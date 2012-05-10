// HHUpdateClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HHUpdateClient.h"
#include "HHUpdateClientDlg.h"
#include ".\hhupdateclientdlg.h"
#include <direct.h> 


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int ADD_BUFF=5*1024*1024; //内存不够累加数  5M累加.
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#pragma warning(disable: 4244)
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHHUpdateClientDlg 对话框



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
	m_pBuff = new Byte[10*1024*1024];//初始化10M内存
	m_nDownloadedCount = 0;

	//ZeroMemory(m_szGroupID,128);
	//sprintf(m_szGroupID,"专业版12.36.5.44");
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


// CHHUpdateClientDlg 消息处理程序

BOOL CHHUpdateClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CBitmap* pBitmap = new CBitmap;
	ASSERT(pBitmap);
	pBitmap->LoadBitmap(IDB_BITMAP_HHBK);//载入位图资源
	m_BKBrush.CreatePatternBrush(pBitmap);//创建位图画刷
	delete pBitmap;
 

	SetTimer(20101,1000,NULL);
	SetTimer(20103,2000,NULL);//刷新界面
	

	ChangeClientPos(INIT);//初始化.

	m_pProgress = new CTextProgressCtrl();
	m_pProgress->Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH|WS_BORDER, CRect(0,0,0,0), this, IDC_FILEPROGRESS);
	m_pProgress->SetWindowPos(&CWnd::wndTop, 20,282,440, 20, SWP_SHOWWINDOW);
	m_pProgress->SetRange(0, 100);
	m_pProgress->SetPos(0);
	COLORREF  col = RGB(84,238,32);
	m_pProgress->SetForeColour(col);
	m_pProgress->SetTextBkColour(RGB(0,0,255));

	this->SetWindowText("宏汇NSD自动升级服务");


	short	shBtnColor = 30;
	m_btnUpdate.SetNormalTextColor (RGB(0,0,255));
	m_btnUpdate.SetActiveTextColor (RGB(255,0,0));
	
	//m_btnUpdate.SetBkMode (false);
	//m_btnUpdate.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1),AfxGetApp()->LoadIcon(IDI_ICON2));

	
	m_btnUpdateLater.SetNormalTextColor (RGB(0,0,255));
	m_btnUpdateLater.SetActiveTextColor (RGB(0,255,0));
	//m_btnUpdateLater.SetBkMode (false);

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHHUpdateClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
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
		strBuff = _T("新建Socket失败!");
		pThis->ShowMsg(strBuff,TRUE);
		
		goto __Error_End;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(pThis->m_UpgradeInfo.nServerPort);
	server.sin_addr.s_addr = inet_addr(pThis->m_UpgradeInfo.szServerIP);//服务器IP
	if ( connect(pThis->m_Socket, (struct sockaddr *)&server,  sizeof(struct sockaddr)) == SOCKET_ERROR ) 
	{
		CString strBuff;
		strBuff = _T("连接失败!");
		pThis->ShowMsg(strBuff,TRUE);	
		pThis->m_bHide = FALSE;
		pThis->SendMessage(WM_PAINT);
		pThis->ChangeClientPos(CONNECT_S);//连接界面.
		goto __Error_End;
	}

	pThis->m_bStopThread = FALSE;
	
	pThis->ChangeClientPos(UPDATEBEFORE);//升级前界面.

	char szPack[nRecvPackSize]={0};
	int nRecvCount=0;//这次包，接收的总大小.
	//int nPrePackCount=0;//上一次接收包的大小.
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
				///接包下面只有三种情况
				nRecvCount += nRet;
				if (nRecvCount < nRecvPackSize)//接收包不完整.
				{
					memcpy(&szPack[nRecvCount-nRet],(char *)&AnswerBuff,nRet);
					//nPrePackCount = nRet;
					continue;//再接
				}
			
				if (nRecvCount == nRecvPackSize)//接包刚刚好.
				{
					memcpy(&szPack[nRecvCount-nRet],(char *)&AnswerBuff,nRet);
					nRecvCount = 0;//计数清零
					//将完整包拷贝到AnswerBuff
					memcpy((char*)&AnswerBuff,szPack,nRecvPackSize);
					ZeroMemory(szPack,nRecvPackSize);
					goto CompletePack;
				}

				if (nRecvCount > nRecvPackSize)//把下一个包也接收了部分.
				{
					char szTemp[nRecvPackSize]={0};
					memcpy(szTemp,(char *)&AnswerBuff,nRet);
					//将这次接收的包接到szPack后面
					memcpy(&szPack[nRecvCount-nRet],(char *)&AnswerBuff,nRecvPackSize-nRecvCount+nRet);
					//将完整包拷贝到AnswerBuff
					memcpy((char*)&AnswerBuff,szPack,nRecvPackSize);
					//将剩余部分拷贝到szPack
					memcpy(szPack,&szTemp[nRecvPackSize-nRecvCount+nRet],nRecvCount-nRecvPackSize);
					//计数剩余
					nRecvCount = nRecvCount-nRecvPackSize;
					
				}
		
				//完整包处理.
CompletePack:
				//检查内存使用情况及操作.
				if (!pThis->CheckBuff(pThis->m_nBuffNum,pThis->m_nDownloadedCount,atoi(AnswerBuff.szBuffLen)))
				{
					CString strBuff;
					strBuff = _T("内存出错!");
					pThis->ShowMsg(strBuff,TRUE);
					break;
				}
				
				//接收的数据保存到本地内存.
				memcpy(&pThis->m_pBuff[pThis->m_nDownloadedCount],AnswerBuff.btBuff,atoi(AnswerBuff.szBuffLen));
				pThis->m_nDownloadedCount += atoi(AnswerBuff.szBuffLen);//已经使用内存计数累加

				if (1 == atoi(AnswerBuff.szFlag))//请求文件结束标记.
				{
					//nRecvCount = 0;
					switch (atoi(AnswerBuff.szFileType))
					{
					case RE_TYPE_README://readme接收完毕
						{
							
							//处理接收的文件
							//写readme文件
							mkdir("..\\Upgrade");
							
							CFile fs(_T("..\\Upgrade\\readme.txt"),CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //存文件
							fs.Write(pThis->m_pBuff,pThis->m_nDownloadedCount);
							fs.Close();
							
							//显示文本
							strBuff.Format("%s",AnswerBuff.btBuff);
							pThis->ShowMsg(strBuff,TRUE);

							
							pThis->m_bHide = FALSE;

							pThis->SendMessage(WM_PAINT);
							if (pThis->m_UpgradeInfo.bForce)//强制升级
							{
								pThis->PostMessage( WM_COMMAND, MAKELONG(IDC_BTN_UPDATE,BN_CLICKED), (LPARAM)( pThis->GetDlgItem(IDC_BTN_UPDATE)->GetSafeHwnd()));  
							}
							
							//初始化内存信息.
							pThis->m_nDownloadedCount = 0;//计数清零
							memset(pThis->m_pBuff,0,pThis->m_nBuffNum);//内存重新填充.
							
						}
						break;
					case RE_TYPE_XML://xml接收完毕
						{
							//pThis->ShowUpdateProgress(FALSE);
							//处理接收的文件.
							//写xml文件.
							CFile fs(_T("..\\Upgrade\\update.xml"),CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //存文件
							fs.Write("",0);
							fs.Write(pThis->m_pBuff,pThis->m_nDownloadedCount);
							fs.Close();

							//显示文本.
							strBuff = "下载：文件升级列表 ...";
							pThis->ShowMsg(strBuff,TRUE);

							if (pThis->m_bExit)
							{
								goto __Error_End;
							}

							//初始化内存信息.
							pThis->m_nDownloadedCount = 0;//计数清零.
							memset(pThis->m_pBuff,0,pThis->m_nBuffNum);//内存重新填充.
							//
							_tagRequest Requrst = {0};
							pThis->m_lsXmlFiles.RemoveAll();
							pThis->m_lsNeedDownloadFiles.RemoveAll();
							//读取XML
							if (-1 == pThis->m_hhTyXml.HHDecomposeXML(_T("..\\Upgrade\\update.xml"),(CHHTyXml::LSXMLFILES*)&pThis->m_lsXmlFiles))
							{
								//加载文件失败
								pThis->ShowMsg("读取update.xml失败");
								pThis->ShowMsg("中断......");
								break;
							}

							//strBuff = ;
							pThis->ShowMsg("检查需要更新文件......");
							//匹配本地文件
							pThis->IsSameFile("..");
							pThis->m_nNeedDownloadFiles = (int)pThis->m_lsNeedDownloadFiles.GetCount();//获取需要下载文件数量
							//pThis->ShowMsg("检查需要更新文件......");
							if (pThis->m_nNeedDownloadFiles)
							{
								//匹配已经下载的文件 同时 (如果需要)解压缩
								int nTemp = pThis->HHUncompress();//返回CRC校验码错误个数. -1则不需要处理.
								if (0 == nTemp)
								{
									pThis->ShowMsg("升级完毕...");
									pThis->ChangeClientPos(UPDATEOVER);
									goto __Error_End;
								}
								else if (nTemp > 0)
								{
									//CRC校验码有错.
									//再次匹配本地文件.
									pThis->m_lsNeedDownloadFiles.RemoveAll();
									pThis->m_lsNeedUncompressFiles.RemoveAll();
									pThis->IsSameFile("..");
									
									pThis->m_nErrorCrcCount = 0;//CRC校验码错误个数归零.
								}
							}
							else
							{
								//不需要下载 文件已经存在
								pThis->ShowMsg("已经是最新版软件,不需要升级！");
								pThis->ChangeClientPos(UPDATEOVER);
								goto __Error_End;
							}


							Requrst.nFlag = RE_TYPE_HH;
							pThis->m_nNeedDownloadFiles = (int)pThis->m_lsNeedDownloadFiles.GetCount();//获取需要下载文件数量
							if (pThis->m_nNeedDownloadFiles>0)
							{
								PAttribute pAttribute = pThis->m_lsNeedDownloadFiles.GetAt(pThis->m_lsNeedDownloadFiles.FindIndex(pThis->m_nDownloadedFilesCount++));
								if (pAttribute)
								{
									pThis->m_pProgress->SetPos(0);
									pThis->m_pProgress->OnSetText("下载文件","");
									CString strGroupID;
									strGroupID.Format("%s%s",pThis->m_UpgradeInfo.szAppID,pThis->m_UpgradeInfo.szVersion);
									///组装请求
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
					case RE_TYPE_HH://.hh接收完毕.
						{
							PAttribute pAttribute = pThis->m_lsNeedDownloadFiles.GetAt(pThis->m_lsNeedDownloadFiles.FindIndex(pThis->m_nDownloadedFilesCount-1));
							//处理文件.
							//写.hh文件.
							if (pAttribute)
							{
								if (pThis->m_nDownloadedCount == atoi(AnswerBuff.szAllDataLength))//完整的包.
								{
									
									CString strFileName;
									strFileName.Format("..\\Upgrade%s.hh",pAttribute->szFileName);
									try
									{
										float fDownloadedCount = pThis->m_nDownloadedFilesCount*1.0;
										pThis->m_pProgress->SetPos((fDownloadedCount/pThis->m_nNeedDownloadFiles*1.0)*100);
										//保存下载的文件.
										CFile fs(strFileName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); 
										fs.Write(pThis->m_pBuff,pThis->m_nDownloadedCount);
										_ASSERTE(_CrtCheckMemory());
										fs.Close();
									}
									catch (CFileException *e)
									{
										if (e->m_cause == CFileException::badPath)//全部或部分路径无效。 
										{
											if (!pThis->HHMkdir(strFileName))//创建文件夹  返回0 成功
											{
												CFile fs(strFileName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //存文件.
												fs.Write(pThis->m_pBuff,pThis->m_nDownloadedCount);
												_ASSERTE(_CrtCheckMemory());
												fs.Close();
											}
										}
									}
									
									
									//显示文本.
									strBuff.Format("下载：%s ...",strFileName);
									pThis->ShowMsg(strBuff);
								}
								else//丢包.
								{
									pThis->m_nIncompletePackages++;
								}
								
							}
							
							if (pThis->m_bExit)
							{
								goto __Error_End;
							}

							//计数清零.
							pThis->m_nDownloadedCount = 0;
							//内存重新填充.
							memset(pThis->m_pBuff,0,pThis->m_nBuffNum);
							_ASSERTE(_CrtCheckMemory());

							//请求下一个.
							if (pThis->m_nNeedDownloadFiles > pThis->m_nDownloadedFilesCount)
							{
								_tagRequest Requrst = {0};
								Requrst.nFlag = RE_TYPE_HH;
								pAttribute = pThis->m_lsNeedDownloadFiles.GetAt(pThis->m_lsNeedDownloadFiles.FindIndex(pThis->m_nDownloadedFilesCount++));
								if (pAttribute)
								{
									CString strGroupID;
									strGroupID.Format("%s%s",pThis->m_UpgradeInfo.szAppID,pThis->m_UpgradeInfo.szVersion);
									//组装请求结构体.
									sprintf(Requrst.szFileName,"%s\\update%s.hh",strGroupID,pAttribute->szFileName);
									strcpy(Requrst.szAppID,pThis->m_UpgradeInfo.szAppID);
									strcpy(Requrst.szVersion,pThis->m_UpgradeInfo.szVersion);
									if (pThis->SOCKET_Select(pThis->m_Socket, 100, FALSE)) 
									{
										send(pThis->m_Socket, (char *)&Requrst, sizeof(_tagRequest), 0);
									}
								}
							}
							else//请求所有文件完毕.
							{
								//其他升级工作.
								if (0 < pThis->HHUncompress())
								{
									//显示文本.
									strBuff.Format("CRC校验后，需要重新下载%d文件，请再次请求",pThis->m_nErrorCrcCount);
									pThis->ShowMsg(strBuff);
									pThis->ChangeClientPos(CONNECT_S);
									goto __Error_End;//结束
								}

									//处理不完整包.
									if (0 != pThis->m_nIncompletePackages)
									{
										//显示文本.
										strBuff.Format("网络丢包还需要下载%d文件，请再次请求",pThis->m_nIncompletePackages);
										pThis->ShowMsg(strBuff);
										pThis->ChangeClientPos(CONNECT_S);
										goto __Error_End;//结束
									}
									else
									{
										//显示文本.
										strBuff.Format("升级完毕...");
										pThis->ShowMsg(strBuff);
										pThis->ChangeClientPos(UPDATEOVER);
										goto __Error_End;
									}
							}
						}
						break;
					default://接收出错  丢包
						break;
					}
				}			
			}
			else
			{
				//close socket;
				strBuff = _T("与服务器断开连接！");
				pThis->ShowMsg(strBuff,TRUE);
				break;//跳出while
			}
		}

	}

__Error_End:
	//结束线程，但分配的内存不释放，为了再次请求不需要重新new .程序接收会回收分配的内存.
	pThis->ResetData();//重置数据

	if (pThis->m_Socket != INVALID_SOCKET) 
	{
		//关闭socket.
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

	ptr = strchr(szFileName,c);//匹配 "\\"
	for (; NULL!= ptr;ptr = strchr(szFileName,c))
	{
		strncpy(temp,szFileName,ptr-szFileName+1);
		strcat(dir,temp);

		if (strcmpi("..\\",temp))//不相等 不创建"..\\..\\"这类的文件夹
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
			//请求xml
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
				send(m_Socket, (char *)&Requrst, sizeof(_tagRequest), 0);//请求xml
			}
		}
		else
		{
			//连接服务器
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
	m_pProgress->OnSetText("检查更新","");
	while(NULL != pos)
	{
		count2++;
		m_pProgress->SetPos((count2/count*1.0)*100);
		PAttribute pAttribute = m_lsXmlFiles.GetNext(pos);
		if (pAttribute)
		{
			//文件是否存在.
			lLen=0;lDate=0;lTime=0;
			int nCrc=0;
			char szFileVer[MAX_PATH]={0};
			memset(szFileName,0,MAX_PATH);
			memset((char*)&Attribute,0,sizeof(_tagAttribute));
			strcpy(szFileName,pFileName);
			strcat(szFileName,pAttribute->szFileName);

			//读取本地文件 获取相关信息和服务器上文件做比较
			if (m_hhTyXml.GetLocalFileStatus(szFileName,lLen,lDate,lTime,szFileVer,nCrc))
			{
				sprintf(Attribute.szLen,"%ld",lLen);	//文件长度
				sprintf(Attribute.szDate,"%ld",lDate);	//文件最后修改日期
				sprintf(Attribute.szTime,"%ld",lTime);	//文件最后修改时间
				strcpy(Attribute.szFileVer,szFileVer);	//文件最新版本
				sprintf(Attribute.szCrc,"%d",nCrc);		//文件CRC校验码
			
				//比较版本的文件是 DLL 和 EXE 这两种文件
				if (!strcmpi((char *)&szFileName[strlen(szFileName)-4],".dll") || !strcmpi((char *)&szFileName[strlen(szFileName)-4],".exe"))
				{
					if (!strcmpi(pAttribute->szLen,Attribute.szLen) && !strcmpi(pAttribute->szFileVer,Attribute.szFileVer) 
						&& atoi(Attribute.szDate)>=atoi(pAttribute->szDate))
					{
						if (!strcmpi(Attribute.szDate,pAttribute->szDate))//日期相同
						{
							if (atoi(Attribute.szTime)<atoi(pAttribute->szTime))//比较时间差别
							{
								m_lsNeedDownloadFiles.AddTail(pAttribute);//添加到需要下载文件列表中
								bRet = FALSE;
							}
						}
						continue;
					}
					else//文件不相同.
					{
						m_lsNeedDownloadFiles.AddTail(pAttribute);//添加到需要下载文件列表中
						bRet = FALSE;
					}
				} 
				else
				{
					if (atoi(Attribute.szDate)>=atoi(pAttribute->szDate))
					{
						if (!strcmpi(Attribute.szDate,pAttribute->szDate))//日期相同
						{
							if (atoi(Attribute.szTime)<atoi(pAttribute->szTime))//比较时间差别
							{
								m_lsNeedDownloadFiles.AddTail(pAttribute);//添加到需要下载文件列表中
								bRet = FALSE;
							}
						}
						continue;
					}
					else//日期差别    文件不相同.
					{
						m_lsNeedDownloadFiles.AddTail(pAttribute);//添加到需要下载文件列表中
						bRet = FALSE;
					}
				}		
			}
			else//文件不存在.
			{
				m_lsNeedDownloadFiles.AddTail(pAttribute);//添加到需要下载文件列表中
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
	int nDownloadCount = 0;//需要下载文件数目

	PAttribute pAttribute = NULL;
	int nCount = m_lsNeedDownloadFiles.GetCount();//获取没有和Upgrade比较前需要下载文件数目.
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
			strcat(szFileName,".hh");//Upgrade目录下的文件都是后缀名.hh的压缩文件
			CFileFind  fileFind;
			BOOL bResult=fileFind.FindFile(szFileName);
			if(bResult)//Upgrade目录下已经存在载好的压缩文件.
			{
				//添加需要解压文件到列表中.
				m_lsNeedUncompressFiles.AddTail(pAttribute);
				//不需要再次下载
				m_lsNeedDownloadFiles.RemoveAt(m_lsNeedDownloadFiles.FindIndex(i));
				nCount--;//总数减一
			}
			else
			{
				i++;//下一个
				nDownloadCount++;
			}
			fileFind.Close();
			ZeroMemory(szFileName,MAX_PATH);
		}
	}
	ShowMsg("检查...");
	CString str;
	str.Format("需要下载%d个文件",nDownloadCount);
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
	if (nBuffNum <= nBuffCount+nNeedBuffNum)//现在内存不足需要.
	{
		Byte *pBuff = new Byte[m_nBuffNum+ADD_BUFF];//内存不足每次增加5M.
		if (pBuff)
		{
			m_nBuffNum += ADD_BUFF;
			memcpy(pBuff,m_pBuff,nBuffCount);
			_ASSERTE(_CrtCheckMemory());
			delete []m_pBuff;
			_ASSERTE(_CrtCheckMemory());
			m_pBuff = pBuff;//把原来的指针指向新申请的内存区域.
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
		//请求readme文件
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
			AfxMessageBox("完成升级需要关闭NSD，请关闭!");
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
	m_nNeedDownloadFiles = 0;//需要下载.hh文件个数.
	m_nDownloadedFilesCount = 0;//已经下载.hh文件数计数.

	ZeroMemory(m_pBuff,m_nBuffNum);//m_nBuffNum不能重设
	_ASSERTE(_CrtCheckMemory());
	
	m_nDownloadedCount = 0;//一个文件已经下载长度计数.
	m_nIncompletePackages = 0;//下载过程中 不完整的包数量.

	m_nErrorCrcCount = 0;//CRC校验码错误计数清零.
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
	if (!strcmpi(strText,"暂不升级") || !strcmpi(strText,"关闭"))
	{
		//OnCancel(); 
		SendMessage(WM_CLOSE);
	} 
	else//取消下载
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
			AfxMessageBox("完成升级需要关闭NSD，请关闭!");
		}
		SetTimer(20102,5000,NULL);
		while (IsWindow(m_UpgradeInfo.hWnd))
		{
			Sleep(1000);
		}
		KillTimer(20102);
		//不需要下载  直接解压缩
		int i ,n ;
		i = n = 0;
		uLongf ulLen = 0;
		PAttribute pAttribute = NULL;
		n = m_lsNeedUncompressFiles.GetCount();
		char szResFileName[MAX_PATH]={0};//解压源文件地址
		char szDesFileName[MAX_PATH]={0};//解压目的文件地址
		m_pProgress->SetPos(0);
		m_pProgress->OnSetText("解压、复制","");
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
				sprintf(szResFileName,"%s%s","..\\Upgrade",pAttribute->szFileName);//"..\\Upgrade"是升级存放目录
				strcat(szResFileName,".hh");//需要解压文件都是.hh的文件
				sprintf(szDesFileName,"%s%s","..",pAttribute->szFileName);
				nCrc = atoi(pAttribute->szCrc);
				if (-5 == m_hhCompress.HHUncompress2(szDesFileName,szResFileName,&ulLen,nCrc))
				{
					m_nErrorCrcCount++;
				}
				try
				{
					CFile::Remove(szResFileName);//删除.hh文件.
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
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(FALSE);//隐藏
			GetDlgItem(IDC_BTN_NOUPDATE)->ShowWindow(FALSE);//隐藏
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
			GetDlgItem(IDC_BTN_UPDATE)->SetWindowText("连接服务器");
		}
		break;
	case UPDATEBEFORE:
		{
			GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->SetWindowText("立即升级");
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(TRUE);//隐藏
			GetDlgItem(IDC_BTN_NOUPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_Update)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_UpdateLater)->ShowWindow(TRUE);
		}
		break;
	case UPDATE:
		{
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_Update)->ShowWindow(FALSE);
			GetDlgItem(IDC_BTN_NOUPDATE)->SetWindowText("取消");
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
			GetDlgItem(IDC_BTN_NOUPDATE)->SetWindowText("暂不升级");
			GetDlgItem(IDC_BTN_NOUPDATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_Update)->ShowWindow(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->SetWindowText("连接服务器");
		}
		break;
	case UPDATEOVER:
		{
			StartNSD();
			GetDlgItem(IDC_BTN_NOUPDATE)->SetWindowText("关闭");
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
		STARTUPINFO si; //一些必备参数设置
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOW;
		PROCESS_INFORMATION pi; //必备参数设置结束
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

	// TODO:  在此更改 DC 的任何属性
	if (nCtlColor == CTLCOLOR_DLG ) 
		return (HBRUSH)m_BKBrush.GetSafeHandle(); //返回创建的位图画刷
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//发送WM_NCLBUTTONDOWN消息，使Windows认为鼠标在标题条上
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}
/*
//这有两个函数，CopyScreenToBitmap（）将屏幕指定区域存成图片。SaveBitmapToFile（）将图片存成文件。

HBITMAP CHHUpdateClientDlg::CopyScreenToBitmap(LPRECT lpRect)
{

	HDC   hScrDC,   hMemDC;               
	//   屏幕和内存设备描述表   
	HBITMAP   hBitmap,hOldBitmap;         
	//   位图句柄   
	int               nX,   nY,   nX2,   nY2;               
	//   选定区域坐标   
	int               nWidth,   nHeight;               
	//   位图宽度和高度   
	int               xScrn,   yScrn;                     
	//   屏幕分辨率   
	//   确保选定区域不为空矩形   
	if   (IsRectEmpty(lpRect))   
		return   NULL;   
	//为屏幕创建设备描述表   
	hScrDC   =   CreateDC("DISPLAY",   NULL,   NULL,   NULL);  
	//为屏幕设备描述表创建兼容的内存设备描述表   
	hMemDC   =   CreateCompatibleDC(hScrDC);   
	//   获得选定区域坐标   
	nX   =   lpRect->left;   
	nY   =   lpRect->top;   
	nX2   =   lpRect->right;   
	nY2   =   lpRect->bottom;   
	//   获得屏幕分辨率   
	xScrn   =   GetDeviceCaps(hScrDC,   HORZRES);   
	yScrn   =   GetDeviceCaps(hScrDC,   VERTRES);   
	//确保选定区域是可见的   
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
	//   创建一个与屏幕设备描述表兼容的位图   
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);   
	// hBitmap = (HBITMAP)LoadImage(NULL, ".\\MyData\\SnapStill.bmp", IMAGE_BITMAP,
	//  0, 0, LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
	//   把新位图选到内存设备描述表中   
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);   
	//   把屏幕设备描述表拷贝到内存设备描述表中   
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC,   nX,   nY,   SRCCOPY);   
	//得到屏幕位图的句柄   
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);   
	//清除     
	DeleteDC(hScrDC);   
	DeleteDC(hMemDC);   
	//   返回位图句柄   

	return   hBitmap;

}

BOOL CHHUpdateClientDlg::SaveBitmapToFile(HBITMAP hBitmap, CString FileName)
{
	HDC   hDC;   
	//当前分辨率下每象素所占字节数   
	int   iBits;   
	//位图中每象素所占字节数   
	WORD   wBitCount;   
	//定义调色板大小，   位图中像素字节大小   ，位图文件大小   ，   写入文件字节数     
	DWORD   dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;     
	//位图属性结构     
	BITMAP   Bitmap;       
	//位图文件头结构   
	BITMAPFILEHEADER   bmfHdr;       
	//位图信息头结构     
	BITMAPINFOHEADER   bi;       
	//指向位图信息头结构       
	LPBITMAPINFOHEADER   lpbi;       
	//定义文件，分配内存句柄，调色板句柄     
	HANDLE   fh,   hDib,   hPal,hOldPal=NULL;     

	//计算位图文件每个像素所占字节数     
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

	//为位图内容分配内存     
	hDib   =   GlobalAlloc(GHND,dwBmBitsSize   +   dwPaletteSize   +   sizeof(BITMAPINFOHEADER));     
	lpbi   =   (LPBITMAPINFOHEADER)GlobalLock(hDib);     
	*lpbi   =   bi;     

	//   处理调色板       
	hPal   =   GetStockObject(DEFAULT_PALETTE);     
	if   (hPal)     
	{     
		hDC   =   ::GetDC(NULL);     
		hOldPal   =   ::SelectPalette(hDC,   (HPALETTE)hPal,   FALSE);     
		RealizePalette(hDC);     
	}   

	//   获取该调色板下新的像素值     
	GetDIBits(hDC,   hBitmap,   0,   (UINT)   Bitmap.bmHeight,   (LPSTR)lpbi   +   sizeof(BITMAPINFOHEADER)     
		+dwPaletteSize, (BITMAPINFO   *)lpbi,   DIB_RGB_COLORS);     

	//恢复调色板       
	if   (hOldPal)     
	{     
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);     
		RealizePalette(hDC);     
		::ReleaseDC(NULL,   hDC);     
	}     

	//创建位图文件       
	fh   =   CreateFile(FileName,   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,     
		FILE_ATTRIBUTE_NORMAL   |   FILE_FLAG_SEQUENTIAL_SCAN,   NULL);     

	if   (fh   ==   INVALID_HANDLE_VALUE)     return   FALSE;     

	//   设置位图文件头     
	bmfHdr.bfType   =   0x4D42;   //   "BM"     
	dwDIBSize   =   sizeof(BITMAPFILEHEADER)   +   sizeof(BITMAPINFOHEADER)   +   dwPaletteSize   +   dwBmBitsSize;       
	bmfHdr.bfSize   =   dwDIBSize;     
	bmfHdr.bfReserved1   =   0;     
	bmfHdr.bfReserved2   =   0;     
	bmfHdr.bfOffBits   =   (DWORD)sizeof(BITMAPFILEHEADER)   +   (DWORD)sizeof(BITMAPINFOHEADER)   +   dwPaletteSize;     
	//   写入位图文件头     
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);     
	//   写入位图文件其余内容     
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);     
	//清除       
	GlobalUnlock(hDib);     
	GlobalFree(hDib);     
	CloseHandle(fh);     

	return   TRUE;  

}
*/

