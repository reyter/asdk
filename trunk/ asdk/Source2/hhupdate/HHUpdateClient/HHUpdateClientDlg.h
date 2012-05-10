// HHUpdateClientDlg.h : 头文件
//

#pragma once

#include <afxtempl.h>
#include <afxmt.h>
#include "..\\include\\Compress\\zconf.h"
#include "..\\include\\HHXml\\HHTyXml.h"
#include "..\\include\\Compress\\HHCompress.h"
#include "TextProgressCtrl.h"
#include "afxwin.h"
#include "TransParentButton.h"
#include "ProcessDetail.h"
#include "ProcessCtrl.h"
#define WM_MYMESSAGE WM_USER+1114
// CHHUpdateClientDlg 对话框

#pragma pack(push)
#pragma pack(1)
typedef struct 
{
	char szAllDataLength[9];		//文件总长度. 
	Byte btBuff[MAX_BUF_SIZE];		//接收内容.
	char szBuffLen[9];				//接收内容长度.
	char szFileType[9];				//文件类型 10101:readme   10102:xml文件    10103:.hh文件
	char szFlag[9];					//1结束   其余0
}_tagAnswer;

typedef struct
{
	int nFlag;
	char szUserID[16];
	char szAppID[16];			// APPID
	char szVersion[16];       // 版本号
	char szFileName[MAX_PATH];
}_tagRequest;
#pragma pack(pop)

class CHHUpdateClientDlg : public CDialog
{
// 构造
public:
	CHHUpdateClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CHHUpdateClientDlg();

// 对话框数据
	enum { IDD = IDD_HHUPDATECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	
	typedef struct tagUpgradeInfo
	{
// 		HWND hWnd;						 // 发送升级信息窗口的句柄,可以用此句柄回发数据
// 		char szExeName[128];				//exe名字
// 		char szUserID[16];             //用户代码
// 		char szBelongGroupID[16];     // 用户属于，当本地用户时可不填
// 		char szHqIP[32];               // 行情服务器IP地址
// 		int  nHqPort;                  // 行情服务器端口 
// 		char szVerID[16];              // 版本ID
// 		char szAppID[16];				// APPID
// 		DWORD dwFlags;                // flags

		HWND hWnd;					// 发送升级信息窗口的句柄,可以用此句柄回发数据
		char chAppName[128];		// 现运行的exe文件名
		char szAppID[16];			// APPID
		char szUserID[16];        //用户代码
		char szServerIP[32];      // 升级服务器IP地址
		int  nServerPort;         // 升级服务器端口
		bool bForce;				//是否强制升级
		char szVersion[16];       // 版本号
		DWORD dwFlags;           // flags
	};

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	virtual void OnCancel();
public:
	HANDLE m_hThread;
	BOOL m_bExit;
	SOCKET m_Socket;
	

	enum REQUEST_TYPE{
		RE_TYPE_README=10101,	//请求readme.txt.
		RE_TYPE_XML,			//请求xml文件列表xml.
		RE_TYPE_HH,				//请求HH压缩文件.
	};

	enum CLIENT_UI_TYPE{
		INIT,					//初始化显示.
		CONNECT_S,				//连接服务器.
		UPDATEBEFORE,			//升级前显示.
		UPDATE,
		DETAIL,					//显示详情.
		STOPUPDATE,				//停止升级显示.
		UPDATEOVER
	};

	typedef struct
	{
		char szFileName[MAX_PATH];	//文件名.
		char szLen[16];				//文件长度.
		char szDate[16];			//创建日期.
		char szTime[16];			//创建时间.
		char szFileVer[MAX_PATH];
		char szCrc[16];
	}_tagAttribute,*PAttribute;
	typedef CList<PAttribute,PAttribute> LSXMLFILES;			//存放读取XML生成所有文件名(含路径).
	typedef CList<PAttribute,PAttribute> LSNEEDDOWNLOADFILES;	//匹配后，需要从服务器上请求的文件名(含路径).
	typedef CList<PAttribute,PAttribute> LSDOWNLOADEDFILES;		//已经下载完成的列表.
	typedef CList<PAttribute,PAttribute> LSNEEDUNCOMPRESSFILES;	//与压缩文件匹配后，可以直接解压的文件名(含路径).

	LSXMLFILES m_lsXmlFiles;
	LSNEEDDOWNLOADFILES m_lsNeedDownloadFiles;
	LSDOWNLOADEDFILES m_lsDownloadedFiles;
	LSNEEDUNCOMPRESSFILES m_lsNeedUncompressFiles;

	CHHTyXml m_hhTyXml;					//XML处理类.
	CHHCompress m_hhCompress;			//解压缩处理类.
	CTextProgressCtrl *m_pProgress;		//进度条.
	//tagUpgradeInfo _tagProcessMsg;			//进程信息.

	int m_nNeedDownloadFiles;			//需要下载.hh文件个数.
	int m_nDownloadedFilesCount;		//已经下载.hh文件数计数.
	Byte *m_pBuff;						//读写文件需要用到的内存.
	int m_nBuffNum;						//已经开辟内存数量.
	int m_nDownloadedCount;				//一个文件已经下载长度计数.
	int m_nIncompletePackages;			//下载过程中 不完整的包数量.

	BOOL m_bStopThread;
	int m_nErrorCrcCount;				//错误的校验码计数.

	CEvent m_Event;	//事件对象
	BOOL m_bHide;

	tagUpgradeInfo m_UpgradeInfo;
	CBrush m_BKBrush;//画刷

	CProcessCtrl m_processCtrl;
	//THELSMD m_lsOccupation;//被占用文件列表.
public:
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnNoupdate();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnShowdetail();

	/**
	*	释放LSXMLFILES列表的内存.
	*	@param pList LSXMLFILES列表指针.
	*/
	//void ReleaseXMLFILESList(LSXMLFILES *pList);

	/**
	*	释放LSNEEDDOWNLOADFILES列表的内存.
	*	@param pList LSNEEDDOWNLOADFILES列表指针.
	*/
	//void ReleaseNEEDDOWNLOADFILESList(LSNEEDDOWNLOADFILES *pList);

	/**
	*	显示信息.
	*	@param strMsg 信息.
	*	@param bClear 清空之前信息.
	*/
	void ShowMsg(CString strMsg,BOOL bClear = FALSE);

	/**
	*	初始化socket.
	*/
	BOOL WinSockInit();

	/**
	*	封装select函数.
	*	@param hSocket 监控的SOCKET.
	*	@param nTimeOut 超时.
	*	@param bRead 读写操作.
	*/
	BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut = 100, BOOL bRead = TRUE);

	/**
	*	线程函数.
	*/
	static UINT __cdecl ThreadProc(LPVOID pParam);

	/**
	*	匹配本地已经存在或不存在文件，是否需要下载.
	*	@param pFileName 路径名.
	*/
	BOOL IsSameFile(const LPCTSTR pFileName);
	
	/**
	*	检查内存使用情况，不够则重新开辟大的.
	*	@param nBuffNum 已经开辟内存数量.
	*	@param nBuffCount 已经使用内存数量.
	*	@param nNeedBuffNum 这次操作需要使用内存数量.
	*/
	BOOL CheckBuff(int nBuffNum,int nBuffCount,int nNeedBuffNum);
	
	/**
	*	创建文件夹.
	*	@param pFileName 文件路径.
	*	例如:	"..\\..\\123\\456\\789.exe" 创建123 456.
	*			"..\\..\\123\\456\\789\\"	创建123 456 789.
	**/
	int HHMkdir(const LPCTSTR pFileName);

	/**
	*	重设部分数据.
	*/
	int ResetData();

	/**
	*	显示进度条.
	*	@param bShow true显示 false不显示.
	*/
	void ShowUpdateProgress(BOOL bShow);
	
	/**
	*	查看升级的临时目录是否已经存在下载的压缩文件.
	*	在HHUncompress函数中调用.
	*	@param pFileName 路径名 例如："..\\Upgrade"
	*/
	int ExitFileInTheUpgradeFloder(const LPCTSTR pFileName);

	/**
	*	解压缩.为了防止部分解压缩出现问题，所有文件都存在的情况下才能解压缩.
	**/
	int HHUncompress();

	/**
	*	改变一些控件位置.
	*	@param nType CLIENT_UI_TYPE.
	*/
	void ChangeClientPos(int nType);

	/**
	*	开启NSD.
	*	@return 0成功   -1失败.
	*/
	int StartNSD();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//BOOL SaveBitmapToFile(HBITMAP hBitmap, CString FileName);
	//HBITMAP CopyScreenToBitmap(LPRECT lpRect);
	CTransParentButton m_btnUpdate;
	CTransParentButton m_btnUpdateLater;
};
