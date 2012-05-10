#pragma once
#ifdef UNITDLL_EXPORTS
#define UNITDLL_API __declspec(dllexport)
#else
#define UNITDLL_API __declspec(dllimport)
#endif

const int SUBTRADE = 24;//���⽻��

const int SUBCOLLECTSORT = 27;//�ۺ�����
const int SUBORGTRADE = 29;	//��������

#define SUBF10_TITLE	_T("F10��Ϣ")
#define SUBNEWS_TITLE	_T("����")
#define SUBTRADE_TITLE		_T("��Ȩ����")

#define SUBCOLLECTSORT_TITLE _T("�г��״�")
#define SUBORGTRADE_TITLE _T("��������")
class IUserWin
{
public:
	IUserWin(void);
	~IUserWin(void);
	virtual void CreateSelf(CWnd * c_pParent);
	virtual void SetLayout(void);
	virtual void ResetSkin(void);
	virtual void FreshData(void);
	virtual void SetStockCode(CString);
	virtual CWnd * GetWnd() = 0;	
	virtual void GetTitle(CString &);
	virtual void GetViewTitle(CString &);	
	virtual void SetTitle(CString);	
	virtual bool IsTitle(CString);
	virtual void RefreshWin();
	virtual void DoCommand(int);
};

//��������,���ݰ���seq��λΪc_usID,����λΪ���������
typedef int (*_SendFunc)(IUserWin * c_pWnd,char * c_pData,int c_nLen,char * c_pRetBuf,int c_nMaxRetLen,bool c_bWaitReturn);
typedef bool (*_GetStockDatasFunc)(char * c_pStockCodes,char * c_pFields,int c_nFieldCount);

UNITDLL_API IUserWin  * CreateUserWin(int c_nKind,CWnd * c_pParent);
UNITDLL_API void DeleteUserWin(IUserWin *);
UNITDLL_API void UserWinSetData(CData * c_pData,CGroupManager *c_pGroupManager,CSkinManager * c_pSkinManager);
UNITDLL_API void SetAppFunc(_SendFunc c_pFunc,_GetStockDatasFunc c_pGetStockDatasFunc);