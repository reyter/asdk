#pragma once

#ifndef __HHSELECT_LIST_H_
#define __HHSELECT_LIST_H_


#include "HHListCtrl.h"
#define WM_SELECTLIST_INPUT				(WM_USER+20)	//����		(wParam=(char*)strKey  lParam=nKey)
#define WM_SELECTLIST_SELECTITEMCHANGED	(WM_USER+21)	//ѡ��ı�	(wParam=(old<<16)|new  lParam=(CWnd*)thislist)
#define WM_SELECTLIST_SELECTITEMCHECKED	(WM_USER+22)	//Check�ı�	(wParam=(rec<<16)|chk  lParam=(CWnd*)thislist)
#define WM_SELECTLIST_LISTRECORDCHANGED	(WM_USER+23)	//��¼���ı�(wParam=(old<<16)|new  lParam=(CWnd*)thislist)
#define WM_SELECTLIST_RBUTTONUP			(WM_USER+24)	//



struct HHLISTCTRL_HEAD
{
	int  nType;		//'j':ѡ���  'o':���   't':����  'c':�ַ���  'l':long  's':short  'n':int  'f':float  'd':double
	char cAddType;	//��������
	char bHideFlag;	//���ر�־
	char bDisable;	//������ʾ��־
	char sdflag;	//0x01:Դ	0x02:Ŀ��   0x03:Ŀ��|Դ(��CHHSelectCtrl��Ч)
	int  databegin;	//���ݿ�ʼλ��
	int  datalen;	//���ݳ���
	int  datadec;	//����С��λ
	char str[64];	//̧ͷ
	int  width;		//��ʾ���(����)
	WPARAM wParam;	//���Ӳ���wParam
	LPARAM lParam;	//���Ӳ���lParam
	HHLISTCTRL_HEAD()
	{
		nType=0;			//'j':ѡ���  'o':���   't':����  'c':�ַ���  'l':long  's':short  'n':int  'f':float  'd':double
		cAddType=0;
		bHideFlag=0;		//���ر�־
		bDisable=0;			//������ʾ��־
		sdflag=0;			//0x01:Դ	0x02:Ŀ��   0x03:Ŀ��|Դ(��CHHSelectCtrl��Ч)
		databegin=0;		//���ݿ�ʼλ��
		datalen=0;			//���ݳ���
		datadec=0;			//����С��λ
		memset(str,0,64);	//̧ͷ
		width=0;			//��ʾ���(����)
		wParam=0;			//���Ӳ���wParam
		lParam=0;			//���Ӳ���lParam
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
		wParam=wparam;	//���Ӳ���wParam
		lParam=lparam;	//���Ӳ���lParam
	};
};

struct HHLISTCTRL_TREERELATION
{
	int   nFlag;
	unsigned char  cRelation;	//��ϵ��
	unsigned char  bRetract;		//����
	char  bCheck;		//Check��־
	char  bResv;		//����
	int   nX;
	HICON hIcon;		//ͼ��
	HICON hIconExpend;	//չ��ͼ��
	HICON hIconSel;		//ѡ��ͼ��
	LPARAM lParam;
	HHLISTCTRL_TREERELATION()
	{
		nFlag=0;
		cRelation=0;	//��ϵ��
		bRetract=0;		//����
		bCheck=0;		//Check��־
		bResv=0;		//����
		nX=0;
		hIcon=0;		//ͼ��
		hIconExpend=0;	//չ��ͼ��
		hIconSel=0;		//ѡ��ͼ��
		lParam=0;
	}
	void Init(unsigned char relation, unsigned char check=0, char retract=0, HICON icon=NULL, HICON iconExpend=NULL, HICON iconSel=NULL, LPARAM lParam=0)
	{
		nFlag=0;
		cRelation=relation;	//��ϵ��
		bRetract=retract;		//����
		bCheck=check;		//Check��־
		bResv=0;		//����
		nX=0;
		hIcon=icon;		//ͼ��
		hIconExpend=iconExpend;	//ͼ��
		hIconSel=iconSel;		//ͼ��
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
	int  m_nListItems;		//�ܼ�¼��
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
	int  m_nColSort;	//�����ֶ�
	int  m_nSortFlag;	

	BOOL m_bProRataWidth;		//�����������п�
	float m_fProRataWidth[HHLISTCTRL_MAXCOLS];	
	void SetProRataWidth(float *pProRata, int nCols);
	void GetProRataWidth(float *pProRata, int &nCols);
	//����̧ͷ�ֶ�
	void SetHeadDef(HHLISTCTRL_HEAD *pHeadDef, int nHeadItems, int nRecordSize);
	//����̧ͷ˳��(*pnOrder����С�ڶ����̧ͷ�ֶ���)
	void SetHeadOrder(int *pnOrder);

	//�����б�����ָ��(���ܽ��в��롢ɾ������)
	void SetListDataPointer(char *pDataObject, int nListRecords);
	//������Ч��¼
	int  *m_pRecordTable;
	void SetListRecordPointer(int *pDataRecord);
	virtual BOOL OnSortList(HHLISTCTRL_HEAD *pHeadDef, int nOrderFlag);
	//�����б�����
	void SetListData(char *pDataObject, int nListRecords);
	void InsertListData(char *pDataObject, int nListRecords, int nInsertPos=-1);

	void EnableCheck(BOOL bCheck);
	void EnableSort(BOOL bSort);

	////////////////////////////////////////
	//����Tree��ϵ
	int  m_nTreeCol;
	BOOL m_bTreeRelation;
	HHLISTCTRL_TREERELATION *m_pRelation;

	void EnableTreeRelation(BOOL bTreeRelation, int nTreeCol);
	void SetTreeRelation(HHLISTCTRL_TREERELATION *pRelation);
	void SetTreeRelation(char *pRelation);
	void SetTreeRelation(int nRecord, char cRelation);
	//���������ֶ�
	void SetListItemOrder(BOOL bOrder=TRUE, int nWidth=4*6+10);
protected:
	void CalcTreeRelation();
	void CalcTreeRecordTable();
	void CalcListRecordTable();
	void NewCheckBuffer();
	DECLARE_MESSAGE_MAP()
public:
	virtual int  OnGetListItemInfo(int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF *colorFr, COLORREF *colorBk, COLORREF *colorBk1, int *sFlag=NULL, COLORREF *colorFlag=NULL, int flag=0);
	virtual void OnAfterDrawListLine(CDC *pDC, int record, BOOL bCursor, int nPaintFlag, RECT rectLine);//���������
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
	//��ǰ�����¼��
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
	//��д����
	//�������
	virtual int  OnGetListItemInfo(HHLISTCTRL_HEAD *pHeadDef, BOOL bCursor, char *pListData, char *pDataInfo, COLORREF *colorFr, COLORREF *colorBk, COLORREF *colorBk1, int *sFlag=NULL, COLORREF *colorFlag=NULL, int flag=0);
	virtual void OnAfterDrawListLine(CDC *pDC, BOOL bCursor, char *pListData, int nPaintFlag, RECT rectLine);//���������
	//�Զ������Item(OnGetListItemInfo����ֵ0x0fffffff)
	virtual void OnDrawOwnerItem(CDC *pDC, RECT rect, int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF colorFr, COLORREF colorBk, COLORREF colorBk1, int sFlag, COLORREF colorFlag, int flag);
	//�Զ������Item(OnGetListItemInfoSplit����ֵ0x0fffffff)
	virtual void OnDrawOwnerItemSplit(CDC *pDC, RECT rect, int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF colorFr, COLORREF colorBk, COLORREF colorBk1, int sFlag, COLORREF colorFlag, int flag);

	virtual int  OnSetListColWidthToMaxItemWidth(int nSplit, int nCol, int nWidth);
	//����
	virtual LRESULT OnHHProcessor(WPARAM wParam, LPARAM lParam);
	virtual int  OnChangeInput(char *strInput, int nKey);
	virtual void OnChangedSelectItem(int oldItem, int newItem, int nSplit, int oldCol, int newCol);
	virtual void OnCheckSelectItem(int nRecord, BOOL nCheck);
	virtual void OnTreeCheckChanged(HHLISTCTRL_TREERELATION *pRelation);
	virtual void OnSetCheck(HHLISTCTRL_HEAD *pHeadDef, char *pSelData);
	//����
	virtual char *OnNewListData(int nItems);
	virtual BOOL OnDeleteListData(void);
	//
	void    SortList();
	void    SortList(int nCol, int nOrderFlag=1);	//nOrderFlag=1:����  -1:����  0:����
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};


#endif //__HHSELECT_LIST_H_