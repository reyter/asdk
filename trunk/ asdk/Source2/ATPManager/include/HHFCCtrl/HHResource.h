#pragma once

//ϵͳͼ������
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
#define HHIMG_CLOCK			32		//��ʷ
#define HHIMG_SPEAKER		33		//����
#define HHIMG_LZW			34		//ѹ���ļ�
#define HHIMG_MDP_PLAY		35		//����
#define HHIMG_MDP_STOP		36		//ֹͣ
#define HHIMG_MDP_PAUSE		37		//��ͣ
#define HHIMG_MDP_NEXT		38		//��һ��
#define HHIMG_MDP_PRE		39		//��һ��
#define HHIMG_MDP_FF		40		//���
#define HHIMG_MDP_FB		41		//����
#define HHIMG_MDP_RECORD	42		//��¼
#define HHIMG_UPGRADESOFT	43		//��������
//ϵͳ��ɫ����
#define HHCOLOR_MAINLABELBK					0
#define HHCOLOR_3DFACE						1
#define HHCOLOR_MENU						10	//�˵�0:ǰ�� 1:����
#define HHCOLOR_MENUBAR						11	//�˵�0:ǰ�� 1:����0  2:����1
#define HHCOLOR_MENUITEM					12  //�˵�0:ǰ�� 1:����0  2:����1  3:�߿�
#define HHCOLOR_MENUITEMDISABLE				13	//�˵�0:ǰ�� 1:����0  2:����1  3:�߿�
#define HHCOLOR_MENUBOX						14	//�˵��߿���
#define HHCOLOR_MENUSEPARATOR				15	//�˵���ָ���
#define HHCOLOR_MENUCHECK					16	//�˵�Check��Radio: 0:ǰ�� 1:����0  2:����1  3:�߿�
#define HHCOLOR_MENUCHECKSELECTED			17	//�˵�Check��Radio: 0:ǰ�� 1:����0  2:����1  3:�߿�					
#define HHCOLOR_MENUCHECKDISABLE			18	//�˵�Check��Radio: 0:ǰ�� 1:����0  2:����1  3:�߿�

#define HHCOLOR_VIEWBOX						20	//View�߿�
#define HHCOLOR_ARCHIVESLABLEBOX			21	//Archives�ı߿���ɫ(3��)

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

#define HHCOLOR_TRAYBACKGROUND				50	//���̱���ɫ

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
	//����������Ϊ��͸��(nTranslucence=255ʱΪ��͸��)
	static void SetWindowTranslucence(HWND hWnd, int nTranslucence);
	//ȡϵͳ��ɫ
	static int GetFrameColor(COLORREF &colorBk1, COLORREF &colorBk2, COLORREF &colorBk3);
	static COLORREF GetFrameColor(int nIndex, int nOrder=0);

public:
	// ������תGBK�룺 ���ؤH���@�M�� --> ���A���񹲺͇�
	static void ChnCode_BIG5toGBK(char *szBuf);
	// GBKת�����룺 ���A���񹲺͇� --> ���ؤH���@�M��
	static void ChnCode_GBKtoBIG5(char *szBuf);
	// GB2312��תGBK�룺 �л����񹲺͹� --> ���A���񹲺͇�
	static void ChnCode_GBtoGBK(char *szBuf);
	// GBK��תGB2312�룺 ���A���񹲺͇� --> �л����񹲺͹�
	static void ChnCode_GBKtoGB(char *szBuf);
	// BIG5��תGB2312�룺 ���ؤH���@�M�� --> �л����񹲺͹�
	static void ChnCode_BIG5toGB(char *szBuf);
	// BIG5��תGB2312�룺�л����񹲺͹� -->  ���ؤH���@�M��
	static void ChnCode_GBtoBIG5(char *szBuf);

public:
	//����ѭ��������
	static int CreateClipboard(CString strType, int nDragDrop, HICON hIcon, HCURSOR hCursor, UINT message, WPARAM wParam);
};
