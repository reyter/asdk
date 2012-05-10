// HHUpdateClientDlg.h : ͷ�ļ�
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
// CHHUpdateClientDlg �Ի���

#pragma pack(push)
#pragma pack(1)
typedef struct 
{
	char szAllDataLength[9];		//�ļ��ܳ���. 
	Byte btBuff[MAX_BUF_SIZE];		//��������.
	char szBuffLen[9];				//�������ݳ���.
	char szFileType[9];				//�ļ����� 10101:readme   10102:xml�ļ�    10103:.hh�ļ�
	char szFlag[9];					//1����   ����0
}_tagAnswer;

typedef struct
{
	int nFlag;
	char szUserID[16];
	char szAppID[16];			// APPID
	char szVersion[16];       // �汾��
	char szFileName[MAX_PATH];
}_tagRequest;
#pragma pack(pop)

class CHHUpdateClientDlg : public CDialog
{
// ����
public:
	CHHUpdateClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CHHUpdateClientDlg();

// �Ի�������
	enum { IDD = IDD_HHUPDATECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	
	typedef struct tagUpgradeInfo
	{
// 		HWND hWnd;						 // ����������Ϣ���ڵľ��,�����ô˾���ط�����
// 		char szExeName[128];				//exe����
// 		char szUserID[16];             //�û�����
// 		char szBelongGroupID[16];     // �û����ڣ��������û�ʱ�ɲ���
// 		char szHqIP[32];               // ���������IP��ַ
// 		int  nHqPort;                  // ����������˿� 
// 		char szVerID[16];              // �汾ID
// 		char szAppID[16];				// APPID
// 		DWORD dwFlags;                // flags

		HWND hWnd;					// ����������Ϣ���ڵľ��,�����ô˾���ط�����
		char chAppName[128];		// �����е�exe�ļ���
		char szAppID[16];			// APPID
		char szUserID[16];        //�û�����
		char szServerIP[32];      // ����������IP��ַ
		int  nServerPort;         // �����������˿�
		bool bForce;				//�Ƿ�ǿ������
		char szVersion[16];       // �汾��
		DWORD dwFlags;           // flags
	};

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
		RE_TYPE_README=10101,	//����readme.txt.
		RE_TYPE_XML,			//����xml�ļ��б�xml.
		RE_TYPE_HH,				//����HHѹ���ļ�.
	};

	enum CLIENT_UI_TYPE{
		INIT,					//��ʼ����ʾ.
		CONNECT_S,				//���ӷ�����.
		UPDATEBEFORE,			//����ǰ��ʾ.
		UPDATE,
		DETAIL,					//��ʾ����.
		STOPUPDATE,				//ֹͣ������ʾ.
		UPDATEOVER
	};

	typedef struct
	{
		char szFileName[MAX_PATH];	//�ļ���.
		char szLen[16];				//�ļ�����.
		char szDate[16];			//��������.
		char szTime[16];			//����ʱ��.
		char szFileVer[MAX_PATH];
		char szCrc[16];
	}_tagAttribute,*PAttribute;
	typedef CList<PAttribute,PAttribute> LSXMLFILES;			//��Ŷ�ȡXML���������ļ���(��·��).
	typedef CList<PAttribute,PAttribute> LSNEEDDOWNLOADFILES;	//ƥ�����Ҫ�ӷ�������������ļ���(��·��).
	typedef CList<PAttribute,PAttribute> LSDOWNLOADEDFILES;		//�Ѿ�������ɵ��б�.
	typedef CList<PAttribute,PAttribute> LSNEEDUNCOMPRESSFILES;	//��ѹ���ļ�ƥ��󣬿���ֱ�ӽ�ѹ���ļ���(��·��).

	LSXMLFILES m_lsXmlFiles;
	LSNEEDDOWNLOADFILES m_lsNeedDownloadFiles;
	LSDOWNLOADEDFILES m_lsDownloadedFiles;
	LSNEEDUNCOMPRESSFILES m_lsNeedUncompressFiles;

	CHHTyXml m_hhTyXml;					//XML������.
	CHHCompress m_hhCompress;			//��ѹ��������.
	CTextProgressCtrl *m_pProgress;		//������.
	//tagUpgradeInfo _tagProcessMsg;			//������Ϣ.

	int m_nNeedDownloadFiles;			//��Ҫ����.hh�ļ�����.
	int m_nDownloadedFilesCount;		//�Ѿ�����.hh�ļ�������.
	Byte *m_pBuff;						//��д�ļ���Ҫ�õ����ڴ�.
	int m_nBuffNum;						//�Ѿ������ڴ�����.
	int m_nDownloadedCount;				//һ���ļ��Ѿ����س��ȼ���.
	int m_nIncompletePackages;			//���ع����� �������İ�����.

	BOOL m_bStopThread;
	int m_nErrorCrcCount;				//�����У�������.

	CEvent m_Event;	//�¼�����
	BOOL m_bHide;

	tagUpgradeInfo m_UpgradeInfo;
	CBrush m_BKBrush;//��ˢ

	CProcessCtrl m_processCtrl;
	//THELSMD m_lsOccupation;//��ռ���ļ��б�.
public:
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnNoupdate();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnShowdetail();

	/**
	*	�ͷ�LSXMLFILES�б���ڴ�.
	*	@param pList LSXMLFILES�б�ָ��.
	*/
	//void ReleaseXMLFILESList(LSXMLFILES *pList);

	/**
	*	�ͷ�LSNEEDDOWNLOADFILES�б���ڴ�.
	*	@param pList LSNEEDDOWNLOADFILES�б�ָ��.
	*/
	//void ReleaseNEEDDOWNLOADFILESList(LSNEEDDOWNLOADFILES *pList);

	/**
	*	��ʾ��Ϣ.
	*	@param strMsg ��Ϣ.
	*	@param bClear ���֮ǰ��Ϣ.
	*/
	void ShowMsg(CString strMsg,BOOL bClear = FALSE);

	/**
	*	��ʼ��socket.
	*/
	BOOL WinSockInit();

	/**
	*	��װselect����.
	*	@param hSocket ��ص�SOCKET.
	*	@param nTimeOut ��ʱ.
	*	@param bRead ��д����.
	*/
	BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut = 100, BOOL bRead = TRUE);

	/**
	*	�̺߳���.
	*/
	static UINT __cdecl ThreadProc(LPVOID pParam);

	/**
	*	ƥ�䱾���Ѿ����ڻ򲻴����ļ����Ƿ���Ҫ����.
	*	@param pFileName ·����.
	*/
	BOOL IsSameFile(const LPCTSTR pFileName);
	
	/**
	*	����ڴ�ʹ����������������¿��ٴ��.
	*	@param nBuffNum �Ѿ������ڴ�����.
	*	@param nBuffCount �Ѿ�ʹ���ڴ�����.
	*	@param nNeedBuffNum ��β�����Ҫʹ���ڴ�����.
	*/
	BOOL CheckBuff(int nBuffNum,int nBuffCount,int nNeedBuffNum);
	
	/**
	*	�����ļ���.
	*	@param pFileName �ļ�·��.
	*	����:	"..\\..\\123\\456\\789.exe" ����123 456.
	*			"..\\..\\123\\456\\789\\"	����123 456 789.
	**/
	int HHMkdir(const LPCTSTR pFileName);

	/**
	*	���貿������.
	*/
	int ResetData();

	/**
	*	��ʾ������.
	*	@param bShow true��ʾ false����ʾ.
	*/
	void ShowUpdateProgress(BOOL bShow);
	
	/**
	*	�鿴��������ʱĿ¼�Ƿ��Ѿ��������ص�ѹ���ļ�.
	*	��HHUncompress�����е���.
	*	@param pFileName ·���� ���磺"..\\Upgrade"
	*/
	int ExitFileInTheUpgradeFloder(const LPCTSTR pFileName);

	/**
	*	��ѹ��.Ϊ�˷�ֹ���ֽ�ѹ���������⣬�����ļ������ڵ�����²��ܽ�ѹ��.
	**/
	int HHUncompress();

	/**
	*	�ı�һЩ�ؼ�λ��.
	*	@param nType CLIENT_UI_TYPE.
	*/
	void ChangeClientPos(int nType);

	/**
	*	����NSD.
	*	@return 0�ɹ�   -1ʧ��.
	*/
	int StartNSD();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//BOOL SaveBitmapToFile(HBITMAP hBitmap, CString FileName);
	//HBITMAP CopyScreenToBitmap(LPRECT lpRect);
	CTransParentButton m_btnUpdate;
	CTransParentButton m_btnUpdateLater;
};
