#pragma once

//系统图表索引
#define HHIMG_HHREMARK		5
#define HHIMG_HHNSD			6
#define HHIMG_STUDIO		7
#define HHIMG_USERRES		8
#define HHIMG_PROPERTY		9
#define HHIMG_TOOLBOX		10
#define HHIMG_PROPERTYPAGE	11
#define HHIMG_EDITCUT		12
#define HHIMG_EDITCOPY		13
#define HHIMG_EDITPASTE		14
#define HHIMG_EDITDELETE	15
#define HHIMG_EDITUNDO		16
#define HHIMG_EDITDO		17
#define HHIMG_REFLASH		18
#define HHIMG_SAVE			19
#define HHIMG_SAVEALL		20
#define HHIMG_NEW			21
#define HHIMG_OPEN			22
#define HHIMG_CLOSE			23
#define HHIMG_WWWHHCOMCN	24
#define HHIMG_IE			25
#define HHIMG_IE0			26
#define HHIMG_SOFTUPDATE	27
#define HHIMG_HHEMAIL		28
#define HHIMG_SYSTEMHELP	29
#define HHIMG_CERT			30
#define HHIMG_STOP			31
#define HHIMG_CLOCK			32		//历史
#define HHIMG_SPEAKER		33		//喇叭
#define HHIMG_LZW			34		//压缩文件
#define HHIMG_MDP_PLAY		35		//播放
#define HHIMG_MDP_STOP		36		//停止
#define HHIMG_MDP_PAUSE		37		//暂停
#define HHIMG_MDP_NEXT		38		//下一个
#define HHIMG_MDP_PRE		39		//上一个
#define HHIMG_MDP_FF		40		//快进
#define HHIMG_MDP_FB		41		//快退
#define HHIMG_MDP_RECORD	42		//记录
#define HHIMG_UPGRADESOFT	43		//在线升级
//系统颜色索引
#define HHCOLOR_MAINLABELBK					0
#define HHCOLOR_3DFACE						1
#define HHCOLOR_MENU						10	//菜单0:前景 1:背景
#define HHCOLOR_MENUBAR						11	//菜单0:前景 1:背景0  2:背景1
#define HHCOLOR_MENUITEM					12  //菜单0:前景 1:背景0  2:背景1  3:边框
#define HHCOLOR_MENUITEMDISABLE				13	//菜单0:前景 1:背景0  2:背景1  3:边框
#define HHCOLOR_MENUBOX						14	//菜单边框线
#define HHCOLOR_MENUSEPARATOR				15	//菜单项分割线
#define HHCOLOR_MENUCHECK					16	//菜单Check和Radio: 0:前景 1:背景0  2:背景1  3:边框
#define HHCOLOR_MENUCHECKSELECTED			17	//菜单Check和Radio: 0:前景 1:背景0  2:背景1  3:边框					
#define HHCOLOR_MENUCHECKDISABLE			18	//菜单Check和Radio: 0:前景 1:背景0  2:背景1  3:边框

#define HHCOLOR_VIEWBOX						20	//View边框
#define HHCOLOR_ARCHIVESLABLEBOX			21	//Archives的边框颜色(3组)

#define HHCOLOR_CAPTIONTEXT					30
#define HHCOLOR_ACTIVECAPTION				31
#define HHCOLOR_GRADIENTACTIVECAPTION		32
#define HHCOLOR_ACTIVEBORDER				33
#define HHCOLOR_INACTIVECAPTIONTEXT			34
#define HHCOLOR_INACTIVECAPTION				35
#define HHCOLOR_GRADIENTINACTIVECAPTION		36
#define HHCOLOR_INACTIVEBORDER				37

#define HHCOLOR_CAPTIONTEXT_TOP				40
#define HHCOLOR_ACTIVECAPTION_TOP			41
#define HHCOLOR_GRADIENTACTIVECAPTION_TOP	42
#define HHCOLOR_ACTIVEBORDER_TOP			43
#define HHCOLOR_INACTIVECAPTIONTEXT_TOP		44
#define HHCOLOR_INACTIVECAPTION_TOP			45
#define HHCOLOR_GRADIENTINACTIVECAPTION_TOP	46
#define HHCOLOR_INACTIVEBORDER_TOP			47

#define HHCOLOR_TRAYBACKGROUND				50	//托盘背景色

#define HHCOLOR_VIEWCAPTIONTEXT				60	
#define HHCOLOR_VIEWCAPTION					61
#define HHCOLOR_ACTIVEVIEWCAPTIONTEXT		62
#define HHCOLOR_ACTIVEVIEWCAPTION			63


class AFX_EXT_CLASS CHHResource
{
public:
	CHHResource(void);
	~CHHResource(void);

public:
	static BOOL InitilizeHHFCCtrl();

public:
	//将窗口设置为半透明(nTranslucence=255时为不透明)
	static void SetWindowTranslucence(HWND hWnd, int nTranslucence);
	//取系统颜色
	static int GetFrameColor(COLORREF &colorBk1, COLORREF &colorBk2, COLORREF &colorBk3);
	static COLORREF GetFrameColor(int nIndex, int nOrder=0);

public:
	// 大五码转GBK码： い地チ㎝瓣 --> 中華人民共和國
	static void ChnCode_BIG5toGBK(char *szBuf);
	// GBK转大五码： 中華人民共和國 --> い地チ㎝瓣
	static void ChnCode_GBKtoBIG5(char *szBuf);
	// GB2312码转GBK码： 中华人民共和国 --> 中華人民共和國
	static void ChnCode_GBtoGBK(char *szBuf);
	// GBK码转GB2312码： 中華人民共和國 --> 中华人民共和国
	static void ChnCode_GBKtoGB(char *szBuf);
	// BIG5码转GB2312码： い地チ㎝瓣 --> 中华人民共和国
	static void ChnCode_BIG5toGB(char *szBuf);
	// BIG5码转GB2312码：中华人民共和国 -->  い地チ㎝瓣
	static void ChnCode_GBtoBIG5(char *szBuf);

public:
	//创建循环剪贴板
	static int CreateClipboard(CString strType, int nDragDrop, HICON hIcon, HCURSOR hCursor, UINT message, WPARAM wParam);
};
