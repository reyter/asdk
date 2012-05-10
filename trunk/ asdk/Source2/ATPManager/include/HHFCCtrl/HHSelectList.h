#pragma once

#ifndef __HHSELECT_LIST_H_
#define __HHSELECT_LIST_H_


#include "HHListCtrl.h"
#define WM_SELECTLIST_INPUT				(WM_USER+20)	//输入		(wParam=(char*)strKey  lParam=nKey)
#define WM_SELECTLIST_SELECTITEMCHANGED	(WM_USER+21)	//选择改变	(wParam=(old<<16)|new  lParam=(CWnd*)thislist)
#define WM_SELECTLIST_SELECTITEMCHECKED	(WM_USER+22)	//Check改变	(wParam=(rec<<16)|chk  lParam=(CWnd*)thislist)
#define WM_SELECTLIST_LISTRECORDCHANGED	(WM_USER+23)	//记录数改变(wParam=(old<<16)|new  lParam=(CWnd*)thislist)
#define WM_SELECTLIST_RBUTTONUP			(WM_USER+24)	//



struct HHLISTCTRL_HEAD
{
	int  nType;		//'j':选择框  'o':序号   't':日期  'c':字符串  'l':long  's':short  'n':int  'f':float  'd':double
	char cAddType;	//附加类型
	char bHideFlag;	//隐藏标志
	char bDisable;	//不能显示标志
	char sdflag;	//0x01:源	0x02:目标   0x03:目标|源(对CHHSelectCtrl有效)
	int  databegin;	//数据开始位置
	int  datalen;	//数据长度
	int  datadec;	//数字小数位
	char str[64];	//抬头
	int  width;		//显示宽度(像素)
	WPARAM wParam;	//附加参数wParam
	LPARAM lParam;	//附加参数lParam
	HHLISTCTRL_HEAD()
	{
		nType=0;			//'j':选择框  'o':序号   't':日期  'c':字符串  'l':long  's':short  'n':int  'f':float  'd':double
		cAddType=0;
		bHideFlag=0;		//隐藏标志
		bDisable=0;			//不能显示标志
		sdflag=0;			//0x01:源	0x02:目标   0x03:目标|源(对CHHSelectCtrl有效)
		databegin=0;		//数据开始位置
		datalen=0;			//数据长度
		datadec=0;			//数字小数位
		memset(str,0,64);	//抬头
		width=0;			//显示宽度(像素)
		wParam=0;			//附加参数wParam
		lParam=0;			//附加参数lParam
	}
	void Init(char *name, int ntype, int nsdflag, int nbegin, int ndatalen, int ndatadec, int nwidth, BOOL bhideflag=FALSE, BOOL bdisable=FALSE, WPARAM wparam=0, LPARAM lparam=0)
	{
		nType=ntype;
		databegin=nbegin;
		datalen=ndatalen;
		datadec=ndatadec;
		sdflag=nsdflag;
		width=nwidth;
		strncpy(str,name,64);
		str[63]=0;
		bHideFlag=bhideflag;
		bDisable=bdisable;
		wParam=wparam;	//附加参数wParam
		lParam=lparam;	//附加参数lParam
	};
};

struct HHLISTCTRL_TREERELATION
{
	int   nFlag;
	unsigned char  cRelation;	//关系树
	unsigned char  bRetract;		//缩进
	char  bCheck;		//Check标志
	char  bResv;		//保留
	int   nX;
	HICON hIcon;		//图标
	HICON hIconExpend;	//展开图标
	HICON hIconSel;		//选中图标
	LPARAM lParam;
	HHLISTCTRL_TREERELATION()
	{
		nFlag=0;
		cRelation=0;	//关系树
		bRetract=0;		//缩进
		bCheck=0;		//Check标志
		bResv=0;		//保留
		nX=0;
		hIcon=0;		//图标
		hIconExpend=0;	//展开图标
		hIconSel=0;		//选中图标
		lParam=0;
	}
	void Init(unsigned char relation, unsigned char check=0, char retract=0, HICON icon=NULL, HICON iconExpend=NULL, HICON iconSel=NULL, LPARAM lParam=0)
	{
		nFlag=0;
		cRelation=relation;	//关系树
		bRetract=retract;		//缩进
		bCheck=check;		//Check标志
		bResv=0;		//保留
		nX=0;
		hIcon=icon;		//图标
		hIconExpend=iconExpend;	//图标
		hIconSel=iconSel;		//图标
		lParam=lParam;
	}
};

// CHHSelectList

class AFX_EXT_CLASS CHHSelectList : public CHHListCtrl
{
	DECLARE_DYNAMIC(CHHSelectList)

public:
	char	m_bSetFocus_Delete;
	char	m_bDataPointerFlag;
	char	m_bDirSortFlag;
	CHHSelectList();
	virtual ~CHHSelectList();

	int				m_nSetingCheck;

	HHLISTCTRL_HEAD *m_pHeadDef;
	int  *m_pHeadOrder;
	char *m_pListData;
	int  *m_pSortTable;
	int  m_nListItems;		//总记录数
	int  m_nRecordSize;
	int  m_nHeadItems;
	int  m_nListBufferSize;
	int  m_nRecordDrawing;
	int  m_nResv;
	char m_bCheck;
	char m_bSort;
	char m_bListItemOrder;
	char m_resv;
	int  m_nListItemOrderWidth;
	char *m_pCheck;
	int  m_nCheckSize;
	int  m_nColSort;	//排序字段
	int  m_nSortFlag;	

	BOOL m_bProRataWidth;		//按比例调整列宽
	float m_fProRataWidth[HHLISTCTRL_MAXCOLS];	
	void SetProRataWidth(float *pProRata, int nCols);
	void GetProRataWidth(float *pProRata, int &nCols);
	//设置抬头字段
	void SetHeadDef(HHLISTCTRL_HEAD *pHeadDef, int nHeadItems, int nRecordSize);
	//设置抬头顺序(*pnOrder不能小于定义的抬头字段数)
	void SetHeadOrder(int *pnOrder);

	//设置列表数据指针(不能进行插入、删除操作)
	void SetListDataPointer(char *pDataObject, int nListRecords);
	//设置有效记录
	int  *m_pRecordTable;
	void SetListRecordPointer(int *pDataRecord);
	virtual BOOL OnSortList(HHLISTCTRL_HEAD *pHeadDef, int nOrderFlag);
	//设置列表数据
	void SetListData(char *pDataObject, int nListRecords);
	void InsertListData(char *pDataObject, int nListRecords, int nInsertPos=-1);

	void EnableCheck(BOOL bCheck);
	void EnableSort(BOOL bSort);

	////////////////////////////////////////
	//设置Tree关系
	int  m_nTreeCol;
	BOOL m_bTreeRelation;
	HHLISTCTRL_TREERELATION *m_pRelation;

	void EnableTreeRelation(BOOL bTreeRelation, int nTreeCol);
	void SetTreeRelation(HHLISTCTRL_TREERELATION *pRelation);
	void SetTreeRelation(char *pRelation);
	void SetTreeRelation(int nRecord, char cRelation);
	//设置排序字段
	void SetListItemOrder(BOOL bOrder=TRUE, int nWidth=4*6+10);
protected:
	void CalcTreeRelation();
	void CalcTreeRecordTable();
	void CalcListRecordTable();
	void NewCheckBuffer();
	DECLARE_MESSAGE_MAP()
public:
	virtual int  OnGetListItemInfo(int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF *colorFr, COLORREF *colorBk, COLORREF *colorBk1, int *sFlag=NULL, COLORREF *colorFlag=NULL, int flag=0);
	virtual void OnAfterDrawListLine(CDC *pDC, int record, BOOL bCursor, int nPaintFlag, RECT rectLine);//行输出后处理
	virtual int  OnGetListHeadColumeInfo(int nIndex, char *pDataInfo, int *pnWidth, int *pnTa, int *pnSort, int nPaintFlag=1);
	virtual int  OnSetListHeadColumeWidth(int nIndex, int nWidth);
	virtual int  OnAdjustHeadOrder(int nOld, int nNew);

	int  GetDataBufferRecord(int record);
	int  GetListRecord(int record);
	int  SetCheck(char *pData, int nCheck);
	int  SetCheck(int nRecord, int nCheck);
	int  GetCheck(int nRecord);
	int  GetCheckedCount();
	int  GetSelected(int nRecord);
	int  GetMultiSelectedCount();
	void DeleteAllItems();
	//当前输出记录号
	int  GetDrawingRecord();

	int DeleteItem(int nRecord);
	int DeleteItem(char *pData);
	int InsertItem(char *pData, BOOL bChange=FALSE);

	char *GetSelectedData();
	char *GetItemData(int record);
	int GetItemCount();
	int SetItemData(char *pData, int record);
	int InsertItemData(char *pData, int record, char cRelation=0);
	int DeleteItemData(int record);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

public:
	//重写函数
	//输出数据
	virtual int  OnGetListItemInfo(HHLISTCTRL_HEAD *pHeadDef, BOOL bCursor, char *pListData, char *pDataInfo, COLORREF *colorFr, COLORREF *colorBk, COLORREF *colorBk1, int *sFlag=NULL, COLORREF *colorFlag=NULL, int flag=0);
	virtual void OnAfterDrawListLine(CDC *pDC, BOOL bCursor, char *pListData, int nPaintFlag, RECT rectLine);//行输出后处理
	//自定义输出Item(OnGetListItemInfo返回值0x0fffffff)
	virtual void OnDrawOwnerItem(CDC *pDC, RECT rect, int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF colorFr, COLORREF colorBk, COLORREF colorBk1, int sFlag, COLORREF colorFlag, int flag);
	//自定义输出Item(OnGetListItemInfoSplit返回值0x0fffffff)
	virtual void OnDrawOwnerItemSplit(CDC *pDC, RECT rect, int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF colorFr, COLORREF colorBk, COLORREF colorBk1, int sFlag, COLORREF colorFlag, int flag);

	virtual int  OnSetListColWidthToMaxItemWidth(int nSplit, int nCol, int nWidth);
	//处理
	virtual LRESULT OnHHProcessor(WPARAM wParam, LPARAM lParam);
	virtual int  OnChangeInput(char *strInput, int nKey);
	virtual void OnChangedSelectItem(int oldItem, int newItem, int nSplit, int oldCol, int newCol);
	virtual void OnCheckSelectItem(int nRecord, BOOL nCheck);
	virtual void OnTreeCheckChanged(HHLISTCTRL_TREERELATION *pRelation);
	virtual void OnSetCheck(HHLISTCTRL_HEAD *pHeadDef, char *pSelData);
	//数据
	virtual char *OnNewListData(int nItems);
	virtual BOOL OnDeleteListData(void);
	//
	void    SortList();
	void    SortList(int nCol, int nOrderFlag=1);	//nOrderFlag=1:升序  -1:降序  0:无序
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};


#endif //__HHSELECT_LIST_H_