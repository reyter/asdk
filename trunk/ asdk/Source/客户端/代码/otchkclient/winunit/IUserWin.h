#pragma once
#ifdef UNITDLL_EXPORTS
#define UNITDLL_API __declspec(dllexport)
#else
#define UNITDLL_API __declspec(dllimport)
#endif

const int SUBTRADE = 24;//虚拟交易

const int SUBCOLLECTSORT = 27;//综合排名
const int SUBORGTRADE = 29;	//机构买卖

#define SUBF10_TITLE	_T("F10信息")
#define SUBNEWS_TITLE	_T("新闻")
#define SUBTRADE_TITLE		_T("股权交易")

#define SUBCOLLECTSORT_TITLE _T("市场雷达")
#define SUBORGTRADE_TITLE _T("机构买卖")
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

//发送数据,数据包中seq高位为c_usID,低两位为真正的序号
typedef int (*_SendFunc)(IUserWin * c_pWnd,char * c_pData,int c_nLen,char * c_pRetBuf,int c_nMaxRetLen,bool c_bWaitReturn);
typedef bool (*_GetStockDatasFunc)(char * c_pStockCodes,char * c_pFields,int c_nFieldCount);

UNITDLL_API IUserWin  * CreateUserWin(int c_nKind,CWnd * c_pParent);
UNITDLL_API void DeleteUserWin(IUserWin *);
UNITDLL_API void UserWinSetData(CData * c_pData,CGroupManager *c_pGroupManager,CSkinManager * c_pSkinManager);
UNITDLL_API void SetAppFunc(_SendFunc c_pFunc,_GetStockDatasFunc c_pGetStockDatasFunc);