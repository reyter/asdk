// SkinManager.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinManager.h"

// CSkinManger

int nFontIndex;
BOOL CALLBACK EnumFonts(CONST LOGFONT* lplf, CONST TEXTMETRIC *lptm,DWORD dwType,LPARAM aFontName)
{
	CString far *strFontNames=(CString far*)aFontName;
	nFontIndex++;
	if (nFontIndex < MAX_PATH * 2)
	strFontNames[nFontIndex]=lplf->lfFaceName;
	return true;
}

CSkinManager::CSkinManager()
{
	SetSkin(_T("comm"));
	m_nSkinType = 1;	
	sprintf(m_acFiles[0],"zhongdd.bmp");
	sprintf(m_acFiles[1],"zhuangdd.bmp");
	sprintf(m_acFiles[2],"zldd.bmp");
	sprintf(m_acFiles[3],"zhonghongdd.bmp");
	sprintf(m_acFiles[4],"zhonghuangdd.bmp");
	sprintf(m_acFiles[5],"zhongldd.bmp");
	sprintf(m_acFiles[6],"yhongdd.bmp");
	sprintf(m_acFiles[7],"yhuangdd.bmp");
	sprintf(m_acFiles[8],"yldd.bmp");

	sprintf(m_acFiles[9],"zhongxd.bmp");
	sprintf(m_acFiles[10],"zhuangxd.bmp");
	sprintf(m_acFiles[11],"zlxd.bmp");
	sprintf(m_acFiles[12],"zhonghongxd.bmp");
	sprintf(m_acFiles[13],"zhonghuangxd.bmp");
	sprintf(m_acFiles[14],"zhonglxd.bmp");
	sprintf(m_acFiles[15],"yhongxd.bmp");
	sprintf(m_acFiles[16],"yhuangxd.bmp");
	sprintf(m_acFiles[17],"ylxd.bmp");

	sprintf(m_acFiles[18],"ggzdkzt.bmp");
	sprintf(m_acFiles[19],"ggzdkpt.bmp");
	sprintf(m_acFiles[20],"ggzdkdt.bmp");
	sprintf(m_acFiles[21],"ggzdsydt.bmp");
	sprintf(m_acFiles[22],"ggzdsywdj.bmp");
	sprintf(m_acFiles[23],"ggzdsywdjh.bmp");
	sprintf(m_acFiles[24],"zbtdxt.bmp");

	sprintf(m_acFiles[25],"tbz.bmp");
	sprintf(m_acFiles[26],"tbd.bmp");
	sprintf(m_acFiles[27],"tbdyt.bmp");

	sprintf(m_acFiles[28],"tsxan.bmp");
	sprintf(m_acFiles[29],"tsxanb.bmp");
	sprintf(m_acFiles[30],"tfdan.bmp");
	sprintf(m_acFiles[31],"tfdanb.bmp");
	sprintf(m_acFiles[32],"tgban.bmp");
	sprintf(m_acFiles[33],"tgbanb.bmp");
	
	sprintf(m_acFiles[34],"zsbtds.bmp");
	sprintf(m_acFiles[35],"zsnrds.bmp");//white no
	sprintf(m_acFiles[36],"zsxsjt.bmp");
	sprintf(m_acFiles[37],"zsxxjt.bmp");
	
	sprintf(m_acFiles[38],"xwzxds.bmp");

	sprintf(m_acFiles[39],"zbtbqh.bmp");
	sprintf(m_acFiles[40],"zbtbqhb.bmp");
	sprintf(m_acFiles[41],"zbtbqhxx.bmp");
	sprintf(m_acFiles[42],"bwds.bmp");
	sprintf(m_acFiles[43],"zxgnrd.bmp");//no
	sprintf(m_acFiles[44],"zbzhdt.bmp");	
	sprintf(m_acFiles[45],"zbqhtds.bmp");	
	sprintf(m_acFiles[46],"syjbds.bmp");//所有渐变底色
	sprintf(m_acFiles[47],"zbzxgbtd.bmp");
	sprintf(m_acFiles[48],"ybtbdt.bmp");
	sprintf(m_acFiles[49],"a.bmp");
	sprintf(m_acFiles[50],"b.bmp");
	sprintf(m_acFiles[51],"c.bmp");//white no
	
	sprintf(m_acFiles[52],"d.bmp");
	sprintf(m_acFiles[53],"e.bmp");
	sprintf(m_acFiles[54],"f.bmp");
	sprintf(m_acFiles[55],"j.bmp");
	sprintf(m_acFiles[56],"k.bmp");
	sprintf(m_acFiles[57],"i.bmp");
	sprintf(m_acFiles[58],"h.bmp");

	sprintf(m_acFiles[59],"m.bmp");
	sprintf(m_acFiles[60],"n.bmp");

	sprintf(m_acFiles[61],"g.bmp");
	sprintf(m_acFiles[62],"o.bmp");

	sprintf(m_acFiles[63],"qing.bmp");
	sprintf(m_acFiles[64],"yin.bmp");
	sprintf(m_acFiles[65],"duoyun.bmp");
	sprintf(m_acFiles[66],"yu.bmp");

	sprintf(m_acFiles[67],"p.bmp");
	sprintf(m_acFiles[68],"q.bmp");
	
	sprintf(m_acFiles[69],"r.bmp");
	sprintf(m_acFiles[70],"s.bmp");
	
	sprintf(m_acFiles[71],"w.bmp");
	sprintf(m_acFiles[72],"ww.bmp");

	sprintf(m_acFiles[73],"aa.bmp");
	sprintf(m_acFiles[74],"aa1.bmp");

	sprintf(m_acFiles[75],"hh.bmp");//white no

	sprintf(m_acFiles[76],"onewin.bmp");
	sprintf(m_acFiles[77],"twowin.bmp");

	sprintf(m_acFiles[78],"jjj.bmp");
	sprintf(m_acFiles[79],"ggg.bmp");
	sprintf(m_acFiles[80],"sss.bmp");
	sprintf(m_acFiles[81],"a1.bmp");
	
	sprintf(m_acFiles[82],"a3.bmp");
	sprintf(m_acFiles[83],"a2.bmp");

	sprintf(m_acFiles[84],"ee.bmp");
	sprintf(m_acFiles[85],"ff.bmp");
	sprintf(m_acFiles[86],"gg.bmp");

	sprintf(m_acFiles[87],"dd.bmp");

	sprintf(m_acFiles[88],"H_THUMB.bmp");
	sprintf(m_acFiles[89],"H_BACK.bmp");
	sprintf(m_acFiles[90],"V_THUMB.bmp");
	sprintf(m_acFiles[91],"V_BACK.bmp");
	sprintf(m_acFiles[92],"V_UP.bmp");
	sprintf(m_acFiles[93],"V_DOWN.bmp");
	sprintf(m_acFiles[94],"H_RIGHT.bmp");
	sprintf(m_acFiles[95],"H_LEFT.bmp");


	sprintf(m_acFiles[96],"bb.bmp");
	sprintf(m_acFiles[97],"cc.bmp");

	sprintf(m_acFiles[98],"watchlist.bmp");

	m_nBmpCount = 99;
	for(int n=0; n<m_nBmpCount; n++)
	{
		m_hBmp[n] = 0;
	}	
#ifdef CCTV_TV
	m_nQuoteListFontSize = -18;	
	m_nButtonFontSize - 18;
	m_nMenuFontSize = -18;
	m_nGraphFontSize = -12;
	m_nTextFontSize = -18;
#else
	m_nQuoteListFontSize = -12;	
	m_nButtonFontSize - 12;
	m_nMenuFontSize = -12;
	m_nGraphFontSize = -12;
	m_nTextFontSize = -12;
#endif

	m_pQuoteListFont = NULL;
	m_pButtonFont = NULL;
	m_pTextFont = NULL;
	m_pMenuFont = NULL;
	m_pGraphFont = NULL;
}

CSkinManager::~CSkinManager()
{
	delete m_pFontReport;
	delete m_pFontGraph;
	delete m_pFontTitle;
	delete m_pFontList;
	delete m_pFontSmall;
	delete m_pFontTiny;
	delete m_pFontSmallHT;
	delete m_pFontSmallBold;
	delete m_pFontThick;
	delete m_pFontBig;
}


// CSkinManager 成员函数
/**/
void CSkinManager::SetSkin(CString  c_strSkinName)
{
	WCHAR wcBuf[MAX_PATH];
	m_strSkinName = c_strSkinName;
	::GetCurrentDirectory(MAX_PATH,wcBuf);
	
	m_strSkinPath.Format(_T("%s\\Skin\\%s"),wcBuf,c_strSkinName);
}
/*
LoadSkin 装载皮肤的图形文件
c_pSkinName，皮肤名称，在Skin目录下，有此对应此名称的目录
*/
bool CSkinManager::LoadSkin(char * c_pSkinName)
{	
    return true;
}

HBITMAP CSkinManager::LoadCommBmp(unsigned int c_unID)
{	
	CString strFile;
	if (c_unID == ID_LOG_HEAD)
		strFile.Format(_T("%s\\loghead.bmp"),m_strSkinPath);
	else
	if (c_unID == ID_LOG_GG)
		strFile.Format(_T("%s\\loggg.bmp"),m_strSkinPath);
	else
	if (c_unID == ID_LOG_BODY)
		strFile.Format(_T("%s\\logbody.bmp"),m_strSkinPath);
	else
	if (c_unID == ID_REG_1)
		strFile.Format(_T("%s\\reglicbk.bmp"),m_strSkinPath);
	else
	if (c_unID == ID_REG_2)
		strFile.Format(_T("%s\\reg.bmp"),m_strSkinPath);
	if (c_unID == ID_REG_3)
		strFile.Format(_T("%s\\regsucc.bmp"),m_strSkinPath);
	else
	if (c_unID == ID_UPGRADE_BK)
		strFile.Format(_T("%s\\upgradebk.bmp"),m_strSkinPath);
	else
	if (c_unID == ID_WAIT_DATA1)
		strFile.Format(_T("%s\\log1.bmp"),m_strSkinPath);
	else
	if (c_unID == ID_WAIT_DATA2)
		strFile.Format(_T("%s\\log2.bmp"),m_strSkinPath);
	else
	if (c_unID == ID_WAIT_DATA3)
		strFile.Format(_T("%s\\log3.bmp"),m_strSkinPath);

	if (strFile.IsEmpty())
		return 0;
	
	return (HBITMAP)LoadImage(AfxGetInstanceHandle(),strFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
}

bool CSkinManager::LoadSkinBmp()
{
	CString strFile;
	CString strPath;
	if (m_nSkinType == 1)
		strPath.Format(_T(".\\Skin\\black\\"));
	else
		strPath.Format(_T(".\\Skin\\white\\"));
	for(int n=0; n<m_nBmpCount; n++)
	{
		strFile.Format(_T("%s%s"),strPath,toUnicodeString(m_acFiles[n],strlen(m_acFiles[n])));
		if (m_hBmp[n] > 0)
		{
			DeleteObject(m_hBmp[n]);
		}
		m_hBmp[n] = (HBITMAP)LoadImage(AfxGetInstanceHandle(),strFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	}
	return true;
}

HBITMAP CSkinManager::LoadSpecialBmp(int c_nIndex)
{
	CString strFile;
	CString strPath;
	if (m_nSkinType == 1)
		strPath.Format(_T(".\\Skin\\black\\"));
	else
		strPath.Format(_T(".\\Skin\\white\\"));
	if (c_nIndex >= m_nBmpCount)
		return 0;
	strFile.Format(_T("%s%s"),strPath,toUnicodeString(m_acFiles[c_nIndex],strlen(m_acFiles[c_nIndex])));
	return (HBITMAP)LoadImage(AfxGetInstanceHandle(),strFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);	
}

/**/
HBITMAP CSkinManager::GetBitmap(unsigned int c_unID)
{
	if (c_unID < m_nBmpCount)
		return m_hBmp[c_unID];
	return NULL;
}

CSize CSkinManager::FillRectImage(unsigned int c_unDB,CDC *pDC,CRect &rect)
{
	CBitmap bitmap;
	if (bitmap.LoadBitmap(c_unDB))
	{
		return FillRectImage(bitmap,pDC,rect);
	}
	return CSize(-1,-1);
}

CSize CSkinManager::FillRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rect)
{
	CSize size(-1,-1);
	if (c_hBmp <= 0)
		return size;
	CBitmap bitmap;
	
	if (bitmap.Attach(c_hBmp))
	{
		size = FillRectImage(bitmap,pDC,rect);
		bitmap.Detach();
	}
	return size;
}
/*
CSize CSkinManager::FillRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect)
{
	BITMAP m;
	bitmap.GetBitmap(&m);
	CSize size;
	size.cx = m.bmWidth;
	size.cy = m.bmHeight;
	CBrush brush;
	brush.CreatePatternBrush(&bitmap);

	pDC->FillRect(&rect,&brush);

	brush.DeleteObject();
	
	return size;
}*/

CSize CSkinManager::FillRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect)
{
	CDC MemDC;
	BITMAP m;
	bitmap.GetBitmap(&m);
	CSize size;
	size.cx = m.bmWidth;
	size.cy = m.bmHeight;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap *pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp); 
	CBrush brush;
	brush.CreatePatternBrush(&bitmap);

	// bitmap.GetBitmap(&bm);

	// int li_Width = bm.bmWidth;

	// int li_Height = bm.bmHeight;
	CRect r;
	r.left = 0;
	r.top = 0;
	r.right = rect.Width();//right;
	r.bottom = rect.Height();//bottom;
	MemDC.FillRect(&r,&brush);
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);    

	MemDC.SelectObject(pOldBitmap);
	brush.DeleteObject();
	bmp.DeleteObject();
	MemDC.DeleteDC();
	
	return size;
}

void CSkinManager::StretchIntoRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rect)
{	
	if (c_hBmp <= 0)
		return;
	CBitmap bitmap;
	
	if (bitmap.Attach(c_hBmp))
	{
		StretchIntoRectImage(bitmap,pDC,rect);
		bitmap.Detach();
	}
	return;
}

void CSkinManager::StretchIntoRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rectSrc,CRect &rect)
{	
	if (c_hBmp <= 0)
		return;
	CBitmap bitmap;
	
	if (bitmap.Attach(c_hBmp))
	{
		StretchIntoRectImage(bitmap,pDC,rectSrc,rect);
		bitmap.Detach();
	}
	return;
}

void CSkinManager::StretchIntoRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect)
{
	CDC MemDC;
	BITMAP m;
	bitmap.GetBitmap(&m);
	CSize size;
	size.cx = m.bmWidth;
	size.cy = m.bmHeight;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,size.cx,size.cy);
	CBitmap *pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp); 
	CBrush brush;
	brush.CreatePatternBrush(&bitmap);

	CRect r;
	r.left = 0;
	r.top = 0;
	r.right = size.cx;
	r.bottom = size.cy;
	MemDC.FillRect(&r,&brush);
	
	pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MemDC, 0, 0,size.cx,size.cy, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	brush.DeleteObject();
	bmp.DeleteObject();
	MemDC.DeleteDC();
	
}

void CSkinManager::StretchIntoRectImage(CBitmap &bitmap,CDC *pDC,CRect &rectSrc,CRect &rect)
{
	CDC MemDC;
	BITMAP m;
	bitmap.GetBitmap(&m);
	CSize size;
	size.cx = m.bmWidth;
	size.cy = m.bmHeight;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,size.cx,size.cy);
	CBitmap *pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp); 
	CBrush brush;
	brush.CreatePatternBrush(&bitmap);

	CRect r;
	r.left = 0;
	r.top = 0;
	r.right = size.cx;
	r.bottom = size.cy;
	MemDC.FillRect(&r,&brush);
	
	pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MemDC, rectSrc.left, rectSrc.top,rectSrc.Width(),rectSrc.Height(), SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	brush.DeleteObject();
	bmp.DeleteObject();
	MemDC.DeleteDC();
	
}

COLORREF CSkinManager::getLineColor(unsigned int c_nIndex)
{
	if (c_nIndex > 20)
		return c_nIndex;
	if (m_nSkinType == 0)
	{
		switch(c_nIndex)
		{
		case 1:
			return RGB(0,0,132);
		case 0:
			return RGB(255,0,255);
		case 2:
			return RGB(128,128,128);
		case 3:
			return RGB(128,0,0);
		case 4:
			return RGB(0,128,0);
		case 5:
			return RGB(0,255,255);		
		default:
			return RGB(0,0,0);
		}
	}
	else
	{
		switch(c_nIndex)
		{
		case 1:        
			return RGB(255,255,255);
		case 0:
			return RGB(255,255,0);
		case 2:
			return RGB(255,0,255);
		case 3:
			return RGB(0,255,0);
		case 4:
			return RGB(192,192,192);
		case 5:
			return RGB(0,0,255);		
		default:
			return RGB(0,255,255);
		}
	}
}
/*
COLORREF CSkinManager::getColor(int c_nDef)
{
	switch(c_nDef)
	{
		case AIXLINE://坐标线
			return RGB(176,0,0);
		case AIXTEXT://坐标文字
			return RGB(255,50,50);
		case PRICEUP://上涨色
			return RGB(255,50,50);
		case PRICEDOWN://下跌色
			return RGB(0,230,0);
		case PRICENORMAL://平
			return RGB(255,255,255);
		case TRENDVOL://分时量
			return RGB(192,192,0);
		case KUP://K阳线
			return RGB(255,50,50);
		case KDOWN://K阴线
			return RGB(84,255,255);
		case KNORMAL://K平
			return RGB(255,255,255);
	}
	return RGB(0,0,0);
}
*/

COLORREF CSkinManager::getColor(int c_nDef)
{
	if (m_nSkinType == 0)
	{
	switch(c_nDef)
	{
		case MAINTITLECOLOR://标题字色
			return RGB(255,255,255);
		case AIXLINE://坐标线
			return RGB(127,127,127);
		case AIXTEXT://坐标文字
			return RGB(128,128,128);
		case PRICEUP://上涨色
			return RGB(255,0,0);
		case PRICEDOWN://下跌色
			return RGB(0,128,0);
		case PRICENORMAL://平
			return RGB(0,0,0);
		case TRENDVOL://分时量
			return RGB(230,80,10);
		case KUP://K阳线
			return RGB(255,0,0);
		case KDOWN://K阴线
			return RGB(0,128,0);
		case KNORMAL://K平
			return RGB(0,0,0);
		case BKCOLOR:
			return RGB(255,255,255);
		case EDITBKCOLOR:
			return RGB(230,230,230);
		case EDITTEXTCOLOR:
			return RGB(0,0,0);
		case SELCOLOR:
			return RGB(128,128,0);
		case TRENDLINE:
			return RGB(0,0,132);
		case TRENDMALINE:
			return RGB(255,0,255);
		case VOLCOLOR:
			return RGB(230,50,10);
		case STOCKCODECOLOR:
		case RIGHTSTOCKCODECOLOR:
			return RGB(128,128,0);
		case RIGHTSTOCKNAMECOLOR:
		case STOCKNAMECOLOR:
			return RGB(0,0,200);							
		case RIGHTTEXTCOLOR:
			return RGB(0,0,0);
		case SAFECOLOR:
			return RGB(0,255,0);
		case DANGERCOLOR:
			return RGB(255,0,0);
		case TITLECOLOR:
			return RGB(127,127,127);
		case RIGHTTIMECOLOR:
			return RGB(0,0,0);
		case LISTBKCOLOR1:
			return 0xFFFFFF;
		case LISTBKCOLOR2:
			return RGB(240,247,253);
		case LISTNAMECOLOR:		
			return RGB(0,0,0);
		case BTNTEXTCOLOR:
			return RGB(0,0,0);
		case NEWSLISTHILIGHTCOLOR:
			return RGB(0,0,255);
		case BTNSHILIGHTCOLOR:
			return RGB(0,0,255);
		case NEWSLISTCOLOR:
			return RGB(0,0,0);
		case NEWSLISTOVERCOLOR:
			return RGB(128,128,128);
		case LISTSELBACK:
			return 0xC4DFFD;
		case CHGSTKBACKCOLOR:
			return RGB(236,239,244);
		case GRAPHBACKCOLOR:
			return RGB(236,239,244);
		case CHGSTKBTNTEXTCOLOR:
		case CHGSTKBTNSELTEXTCOLOR:
			return RGB(0,0,0);
		case GRAPHBARBACKCOLOR:
			return 0xEFF1F4;
		case INDEX_LINE_COLOR:
			return RGB(200,200,200);
		case MANUAL_DRAW_LINE_COLOR:
			return RGB(20,20,20);
		case MANUAL_DRAW_TEXT_COLOR:
			return RGB(0,255,255);
		case BOLL_MIDS:
			return RGB(0,0,0);
		case BOLL_MIDL:
			return RGB(64,64,64);
	}
	return RGB(0,0,0);
	}
	else
	{
	switch(c_nDef)
	{
		case MAINTITLECOLOR://标题字色
			return RGB(255,255,255);
		case AIXLINE://坐标线
			return RGB(176,0,0);;
		case AIXTEXT://坐标文字
			return RGB(210,50,50);
		case PRICEUP://上涨色
			return RGB(255,50,50);
		case PRICEDOWN://下跌色
			return RGB(0,230,0);
		case PRICENORMAL://平
			return RGB(255,255,255);
		case TRENDVOL://分时量
			return RGB(192,192,0);
		case KUP://K阳线
			return RGB(255,50,50);
		case KDOWN://K阴线
			return RGB(84,255,255);
		case KNORMAL://K平
			return RGB(255,255,255);
		case BKCOLOR:
			return RGB(0,0,0);
		case EDITBKCOLOR:
			return RGB(230,230,230);
		case EDITTEXTCOLOR:
			return RGB(0,0,0);
		case SELCOLOR:
			return RGB(128,128,0);
		case TRENDLINE:
			return RGB(255,255,255);
		case TRENDMALINE:
			return RGB(255,255,0);
		case VOLCOLOR:
			return RGB(192,192,0);
		case STOCKCODECOLOR:
			return RGB(128,128,0);
		case STOCKNAMECOLOR:
			return RGB(192,192,192);
		case RIGHTSTOCKCODECOLOR:
		case RIGHTSTOCKNAMECOLOR:
			return RGB(255,255,0);
		case RIGHTTEXTCOLOR:
			return RGB(192,192,192);
		case SAFECOLOR:
			return RGB(0,255,0);
		case DANGERCOLOR:
			return RGB(255,0,0);
		case TITLECOLOR:
			return RGB(192,192,192);
		case RIGHTTIMECOLOR:
			return RGB(255,255,255);
		case LISTBKCOLOR1:
		case LISTBKCOLOR2:
			return RGB(0,0,0);
		case LISTNAMECOLOR:
			return RGB(255,255,0);
		case BTNTEXTCOLOR:
			return RGB(255,255,255);
		case NEWSLISTHILIGHTCOLOR:
			return RGB(255,255,255);
		case BTNSHILIGHTCOLOR:
			return RGB(0,0,255);
		case NEWSLISTCOLOR:
			return RGB(225,225,225);
		case NEWSLISTOVERCOLOR:
			return RGB(128,128,128);
		case LISTSELBACK:
			return RGB(30,30,30);
		case CHGSTKBACKCOLOR:
			return 0x4d4d4d;
		case GRAPHBACKCOLOR:
			return 0x3c3c3c;
		case CHGSTKBTNTEXTCOLOR:
			return RGB(240,240,240);
		case CHGSTKBTNSELTEXTCOLOR:
			return RGB(0,0,0);
		case GRAPHBARBACKCOLOR:
			return RGB(150,150,150);
		case INDEX_LINE_COLOR:
			return RGB(0,0,0);
		case MANUAL_DRAW_LINE_COLOR:
			return RGB(255,255,255);
		case MANUAL_DRAW_TEXT_COLOR:
			return RGB(255,255,0);
		case BOLL_MIDS:
			return RGB(192,192,192);
		case BOLL_MIDL:
			return RGB(210,210,0);
	}
	return RGB(255,255,255);
	}

}


void CSkinManager::FillGradient(HDC hDC,CRect rect,COLORREF cl1,COLORREF cl2)
{	
	GRADIENT_RECT gRct;
	TRIVERTEX gVert[2];

	//cl1 = RGB(255,255,255);
	//cl2 = RGB(236,239,244);
	gVert[0].x = rect.left;
	gVert[0].y = rect.bottom;
	gVert[0].Red = (GetRValue(cl1)<<8);
	gVert[0].Green =(GetGValue(cl1)<<8);
	gVert[0].Blue = (GetBValue(cl1)<<8);
	gVert[0].Alpha = 0x0000;

	gVert[1].x = rect.right;
	gVert[1].y = rect.top;
	gVert[1].Red = (GetRValue(cl2)<<8);
	gVert[1].Green = (GetGValue(cl2)<<8);
	gVert[1].Blue = (GetBValue(cl2)<<8);
	gVert[1].Alpha = 0x000;

	gRct.UpperLeft = 0;
	gRct.LowerRight = 1;
	::GradientFill( hDC, gVert, 2, &gRct, 1, GRADIENT_FILL_RECT_H );
/*
	gVert[0].x = rect.left + rect.Width()/2;
	gVert[0].y = rect.bottom;
	gVert[0].Red = (GetRValue(cl2)<<8);
	gVert[0].Green = (GetGValue(cl2)<<8);
	gVert[0].Blue = (GetBValue(cl2)<<8);
	gVert[0].Alpha = 0x000;

	gVert[1].x = rect.right;
	gVert[1].y = rect.top;
	gVert[1].Red = (GetRValue(cl1)<<8);
	gVert[1].Green =(GetGValue(cl1)<<8);
	gVert[1].Blue = (GetBValue(cl1)<<8);
	gVert[1].Alpha = 0x0000;

	gRct.UpperLeft = 0;
	gRct.LowerRight = 1;
	::GradientFill( hDC, gVert, 2, &gRct, 1, GRADIENT_FILL_RECT_H );
*/
}

void CSkinManager::FillGradient(HDC hDC,CRect rect,COLORREF cl1,COLORREF cl2,COLORREF cl3)
{	
	GRADIENT_RECT gRct;
	TRIVERTEX gVert[2];

	//cl1 = RGB(255,255,255);
	//cl2 = RGB(236,239,244);
	gVert[0].x = rect.left;
	gVert[0].y = rect.bottom;
	gVert[0].Red = (GetRValue(cl1)<<8);
	gVert[0].Green =(GetGValue(cl1)<<8);
	gVert[0].Blue = (GetBValue(cl1)<<8);
	gVert[0].Alpha = 0x0000;

	gVert[1].x = rect.left + rect.Width()/2;
	gVert[1].y = rect.top;
	gVert[1].Red = (GetRValue(cl2)<<8);
	gVert[1].Green = (GetGValue(cl2)<<8);
	gVert[1].Blue = (GetBValue(cl2)<<8);
	gVert[1].Alpha = 0x000;

	gRct.UpperLeft = 0;
	gRct.LowerRight = 1;
	::GradientFill( hDC, gVert, 2, &gRct, 1, GRADIENT_FILL_RECT_H );

	gVert[0].x = rect.left + rect.Width()/2;
	gVert[0].y = rect.bottom;
	gVert[0].Red = (GetRValue(cl2)<<8);
	gVert[0].Green = (GetGValue(cl2)<<8);
	gVert[0].Blue = (GetBValue(cl2)<<8);
	gVert[0].Alpha = 0x000;

	gVert[1].x = rect.right;
	gVert[1].y = rect.top;
	gVert[1].Red = (GetRValue(cl3)<<8);
	gVert[1].Green =(GetGValue(cl3)<<8);
	gVert[1].Blue = (GetBValue(cl3)<<8);
	gVert[1].Alpha = 0x0000;

	gRct.UpperLeft = 0;
	gRct.LowerRight = 1;
	::GradientFill( hDC, gVert, 2, &gRct, 1, GRADIENT_FILL_RECT_H );

}

void CSkinManager::SetSkinType(int c_n)
{
	m_nSkinType = c_n;
	LoadSkinBmp();
}

CSize CSkinManager::GetBmpSize(int c_nId)
{
	CBitmap bmp;
	bmp.LoadBitmap(c_nId);
	BITMAP m;
	bmp.GetBitmap(&m);
	CSize size;
	size.cx = m.bmWidth;
	size.cy = m.bmHeight;
	bmp.DeleteObject();
	return size;
}

CSize CSkinManager::GetBmpSize(HBITMAP c_hBmp)
{
	if (c_hBmp == 0)
		return CSize(-1,-1);

	CBitmap bmp;
	BITMAP m;
	bmp.Attach(c_hBmp);
	bmp.GetBitmap(&m);
	CSize size;
	size.cx = m.bmWidth;
	size.cy = m.bmHeight;
	bmp.Detach();
	return size;
}


void CSkinManager::InitFont()
{
	LOGFONT LogFont;
	memset(&LogFont,0,sizeof(LogFont));
#ifdef CCTV_TV
	LogFont.lfHeight = -14;
#else
	LogFont.lfHeight = -12;
#endif
	LogFont.lfWeight = FW_MEDIUM;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY ;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("System"));
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	m_pFontReport = new CFont();
	m_pFontReport->CreateFontIndirect(&LogFont);
	
	memset(&LogFont,0,sizeof(LogFont));
#ifdef CCTV_TV
	LogFont.lfHeight = -14;
#else
	LogFont.lfHeight = -12;
#endif
	LogFont.lfWeight = FW_MEDIUM;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("System"));
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	m_pFontGraph = new CFont();
	m_pFontGraph->CreateFontIndirect(&LogFont);	

	memset(&LogFont,0,sizeof(LogFont));
#ifdef CCTV_TV
	LogFont.lfHeight = -14;
#else
	LogFont.lfHeight = -12;
#endif
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("System"));
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	m_pFontTitle = new CFont();
	m_pFontTitle->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
#ifdef CCTV_TV
	LogFont.lfHeight = -14;
#else
	LogFont.lfHeight = -10;
#endif
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	//lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	lstrcpy(LogFont.lfFaceName,_T("System"));
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	m_pFontList = new CFont();
	m_pFontList->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
#ifdef CCTV_TV
	LogFont.lfHeight = -14;//-14;
#else
	LogFont.lfHeight = -12;
#endif
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	m_pFontSmall = new CFont();
	m_pFontSmall->CreateFontIndirect(&LogFont);

	LogFont.lfHeight = -10;
	m_pFontTiny = new CFont();
	m_pFontTiny->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = -14;
	LogFont.lfWeight = FW_SEMIBOLD;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY;	
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("黑体"));
	m_pFontSmallHT = new CFont();
	m_pFontSmallHT->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = m_nMenuFontSize;
	LogFont.lfWeight = FW_MEDIUM;//FW_BOLD;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());

	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	
	m_pFontThick = new CFont();
	m_pFontThick->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = -14;
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());

	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	memset(&LogFont,0,sizeof(LogFont));
#ifdef CCTV_TV
	LogFont.lfHeight = -14;
#else
	LogFont.lfHeight = -12;
#endif
	LogFont.lfWeight = FW_BOLD;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	m_pFontSmallBold = new CFont();
	m_pFontSmallBold->CreateFontIndirect(&LogFont);

#ifdef CCTV_TV
	LogFont.lfWeight = FW_BOLD;
#else
	LogFont.lfWeight = FW_NORMAL;
#endif
	m_pFontBig = new CFont();
	m_pFontBig->CreateFontIndirect(&LogFont);

}

void CSkinManager::CreateFont()
{
	LOGFONT LogFont;
	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = m_nQuoteListFontSize;
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	if (m_pQuoteListFont)
		delete m_pQuoteListFont;
	m_pQuoteListFont = new CFont();
	m_pQuoteListFont->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = m_nButtonFontSize;
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	if (m_pButtonFont)
		delete m_pButtonFont;
	m_pButtonFont = new CFont();
	m_pButtonFont->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = m_nTextFontSize;
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	if(m_pTextFont)
		delete m_pTextFont;
	m_pTextFont = new CFont();
	m_pTextFont->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = m_nMenuFontSize;
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	if(m_pMenuFont)
		delete m_pMenuFont;
	m_pMenuFont = new CFont();
	m_pMenuFont->CreateFontIndirect(&LogFont);

	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = m_nGraphFontSize;
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	if(m_pGraphFont)
		delete m_pGraphFont;
	m_pGraphFont = new CFont();
	m_pGraphFont->CreateFontIndirect(&LogFont);

	if (m_pFontThick)
		delete m_pFontThick;
	memset(&LogFont,0,sizeof(LogFont));	
	LogFont.lfHeight = m_nMenuFontSize;
	LogFont.lfWeight = FW_BOLD;
	LogFont.lfCharSet = DEFAULT_CHARSET;//GB2312_CHARSET;
	lstrcpy(LogFont.lfFaceName,GetDefaultFontName());

	//lstrcpy(LogFont.lfFaceName,_T("微软雅黑"));
	
	m_pFontThick = new CFont();
	m_pFontThick->CreateFontIndirect(&LogFont);

}

void CSkinManager::drawSJXUP(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,int c_nRectWidth,COLORREF c_cl)
{
	CPoint pt;
	pt = c_ptPoint;
	
	CBrush br(c_cl);
	CPen tpen(PS_SOLID,1,c_cl);
	POINT *pp = new POINT[8];
	pp[0].x = pt.x - c_nRectWidth/2;		pp[0].y = pt.y;
	pp[1].x = pt.x - c_nRectWidth/2;		pp[1].y = pt.y - c_nHeight + c_nWidth;
	pp[2].x = pt.x - c_nRectWidth / 2 - c_nWidth/2; pp[2].y = pt.y - c_nHeight + c_nWidth;
	pp[3].x = pt.x; pp[3].y = pt.y - c_nHeight;	

	pp[4].x = pt.x + c_nRectWidth/2 + c_nWidth / 2; pp[4].y = pt.y - c_nHeight + c_nWidth;

	pp[5].x = pt.x + c_nRectWidth/2; pp[5].y = pt.y - c_nHeight  + c_nWidth;

	pp[6].x = pt.x + c_nRectWidth/2; pp[6].y = pt.y;
	pp[7].x = pt.x - c_nRectWidth/2;		pp[7].y = pt.y;
	CBrush *old = c_pDC->SelectObject(&br);
	CPen *oldt = c_pDC->SelectObject(&tpen);
	c_pDC->Polygon(pp,8);
	c_pDC->SelectObject(old);
	c_pDC->SelectObject(oldt);
	delete [] pp;
}
//从底往上画
void CSkinManager::drawSJXDOWN(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,int c_nRectWidth,COLORREF c_cl)
{
	CBrush br(c_cl);
	CPen tpen(PS_SOLID,1,c_cl);
	POINT *pp = new POINT[8];
	pp[0].x = c_ptPoint.x;		pp[0].y = c_ptPoint.y;
	pp[1].x = c_ptPoint.x - c_nWidth/2 - c_nRectWidth/2;		pp[1].y = c_ptPoint.y - c_nWidth;

	pp[2].x = c_ptPoint.x - c_nRectWidth/2; pp[2].y = c_ptPoint.y - c_nWidth;

	pp[3].x = c_ptPoint.x - c_nRectWidth/2; pp[3].y = c_ptPoint.y - c_nHeight;

	pp[4].x = c_ptPoint.x + c_nRectWidth/2; pp[4].y = c_ptPoint.y - c_nHeight;

	pp[5].x = c_ptPoint.x + c_nRectWidth/2; pp[5].y =  c_ptPoint.y - c_nWidth;

	pp[6].x = c_ptPoint.x + c_nRectWidth/2 + c_nWidth/2; pp[6].y = c_ptPoint.y  - c_nWidth;
	pp[7].x = c_ptPoint.x;		pp[7].y = c_ptPoint.y;
	CBrush *old = c_pDC->SelectObject(&br);
	CPen *oldt = c_pDC->SelectObject(&tpen);
	c_pDC->Polygon(pp,8);
	c_pDC->SelectObject(old);
	c_pDC->SelectObject(oldt);
	delete [] pp;
}

void CSkinManager::drawArrowInRect(CDC * c_pDC,CRect c_rect,COLORREF c_cl)
{
	CBrush br(c_cl);
	CPen tpen(PS_SOLID,1,c_cl);
	int h1 = c_rect.Height()/2;
	int h2 = c_rect.Height()/4;
	POINT *pp = new POINT[8];
	pp[0].x = c_rect.right;			pp[0].y = c_rect.top + c_rect.Height()/2;
	pp[1].x = c_rect.right - h1;	pp[1].y = pp[0].y - h1;
	pp[2].x = pp[1].x;				pp[2].y = pp[0].y - h2;
	pp[3].x = c_rect.left;			pp[3].y = pp[2].y;
	pp[4].x = pp[3].x;				pp[4].y = pp[0].y + h2;
	pp[5].x = pp[2].x;				pp[5].y = pp[0].y + h2;
	pp[6].x = pp[5].x;				pp[6].y = pp[0].y + h1;
	pp[7].x = pp[0].x;				pp[7].y = pp[0].y;
	CBrush *old = c_pDC->SelectObject(&br);
	CPen *oldt = c_pDC->SelectObject(&tpen);
	c_pDC->Polygon(pp,8);
	c_pDC->SelectObject(old);
	c_pDC->SelectObject(oldt);
	delete [] pp;

}

void CSkinManager::drawSJXZERO(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,COLORREF c_cl)
{
	CBrush br(c_cl);
	CPen tpen(PS_SOLID,1,c_cl);
	int nH,nW;
	nH = 2;
	nW = c_nWidth / 2;
	POINT *pp = new POINT[5];
	pp[0].x = c_ptPoint.x + nW;	pp[0].y = c_ptPoint.y - (c_nHeight - nH) / 2;
	pp[1].x = c_ptPoint.x - nW; pp[1].y = c_ptPoint.y - (c_nHeight - nH) / 2;

	pp[2].x = c_ptPoint.x - nW; pp[2].y = c_ptPoint.y - (c_nHeight - nH) / 2 - nH;
	pp[3].x = c_ptPoint.x + nW; pp[3].y = c_ptPoint.y - (c_nHeight - nH) / 2 - nH;
	pp[4].x = c_ptPoint.x + nW;	pp[4].y = c_ptPoint.y - (c_nHeight - nH) / 2;
	CBrush *old = c_pDC->SelectObject(&br);
	CPen *oldt = c_pDC->SelectObject(&tpen);
	c_pDC->Polygon(pp,5);
	c_pDC->SelectObject(old);
	c_pDC->SelectObject(oldt);
	delete [] pp;
}

void CSkinManager::GetFonts(HDC c_hdc)
{		
	nFontIndex = -1;
	::EnumFonts(c_hdc,NULL,(FONTENUMPROC)EnumFonts,(LPARAM)m_strFontNames);
}

bool CSkinManager::ExistsFont(CString c_strFontName)
{
	for(int n=0; n<MAX_PATH*2; n++)
	{
		if (m_strFontNames[n] == c_strFontName)
			return true;
	}
	return false;
}

void CSkinManager::SetDefaultFontName(CString c_strFontNameA,CString c_strFontNameB)
{
	if (ExistsFont(c_strFontNameA))
		m_strDefaultFontName = c_strFontNameA;
	else
		m_strDefaultFontName = c_strFontNameB;
}

CString CSkinManager::GetDefaultFontName()
{
	return m_strDefaultFontName;
}

void CSkinManager::DrawWeakStrong(CDC * c_pDC,CRect c_rect,float c_f)
{
	bool bRed = false;
	float f = c_f;
	if (f > 70.0)
	{
		f -= 70;
		f /= 30;
		bRed = true;
	}
	else
	if (f > 0.0)
	{
		f = 70 - f;
		f /= 70;
		bRed = false;
	}
	else
	{
		f = 0;
		bRed = false;
	}
#ifdef CCTV_TV
	CBrush brBack(RGB(66,66,66));
	CPen penBack(PS_SOLID,1,RGB(66,66,66));
#else
	CBrush brBack(RGB(222,222,222));
	CPen penBack(PS_SOLID,1,RGB(222,222,222));
#endif
	CBrush brFrontRed(RGB(255,0,0));
	CBrush brFrontGreen(RGB(0,255,0));

	CPen penFrontRed(PS_SOLID,1,RGB(222,0,0));
	CPen penFrontGreen(PS_SOLID,1,RGB(0,222,0));
	CPen *pOldPen = c_pDC->SelectObject(&penBack);
	CBrush *pOld = c_pDC->SelectObject(&brBack);
	CRect r;
	r = c_rect;
	POINT *pp = new POINT[4];
	pp[0].x = r.left;		pp[0].y = r.bottom;
	pp[1].x = r.right;		pp[1].y = r.top;
	pp[2].x = r.right;		pp[2].y = r.bottom;
	pp[3].x = r.left;		pp[3].y = r.bottom;
	c_pDC->Polygon(pp,4);
	
	r.right = r.left + int(c_rect.Width() * f);
	if (r.right == r.left)
		r.right++;
	
	r.top = r.bottom - int(r.Height() * f) - 1;
	if (r.top == r.bottom)
		r.top = r.bottom - 1;

	pp[0].x = r.left;		pp[0].y = r.bottom;
	pp[1].x = r.right;		pp[1].y = r.top;
	pp[2].x = r.right;		pp[2].y = r.bottom;
	pp[3].x = r.left;		pp[3].y = r.bottom;				
	
	if (bRed && f > 0.0)
	{
		c_pDC->SelectObject(&brFrontRed);
		c_pDC->SelectObject(&penFrontRed);
	}
	else
	if (f > 0.0)
	{
		c_pDC->SelectObject(&brFrontGreen);
		c_pDC->SelectObject(&penFrontGreen);
	}
	c_pDC->Polygon(pp,4);
	c_pDC->SelectObject(pOldPen);
	c_pDC->SelectObject(pOld);
	delete pp;

}
void CSkinManager::DrawLeds(CDC * c_pDC,CRect c_rect,char *c_pLeds)
{
	int unA,unB,unC;
	unA = INVALID_INT;
	unB = INVALID_INT;
	unC = INVALID_INT;

	if (c_pLeds)
	{
		if (c_pLeds[0] == 'G')	unA = ID_L_G_S_LED;
		else
		if (c_pLeds[0] == 'Y')	unA = ID_L_Y_S_LED;
		else 
		if (c_pLeds[0] == 'R')	unA = ID_L_R_S_LED;

		if (c_pLeds[1] == 'G') 	unC = ID_R_G_S_LED;//IDB_R_G_S;
		else
		if (c_pLeds[1] == 'Y')	unC = ID_R_Y_S_LED;//IDB_R_Y_S;
		else
		if (c_pLeds[1] == 'R')	unC = ID_R_R_S_LED;//IDB_R_R_S

		if (c_pLeds[2] == 'G')	unB = ID_M_G_S_LED;//IDB_M_G_S
		else
		if (c_pLeds[2] == 'Y')	unB = ID_M_Y_S_LED;//IDB_M_Y_S
		else
		if (c_pLeds[2] == 'R')	unB = ID_M_R_S_LED;//IDB_M_R_S
	}
					
	CRect r;
	r = c_rect;
	r.left = r.left;
	r.top += (c_rect.Height() - 20) / 2;
	r.bottom = r.top + 20;
	r.left += 3;
	CSize sz = GetBmpSize(GetBitmap(unA));
	r.right = r.left + sz.cx;//19;
	if (unA != INVALID_INT)
		FillRectImage(GetBitmap(unA),c_pDC,r);
	r.left = r.right;
	sz = GetBmpSize(GetBitmap(unB));
	r.right = r.left + sz.cx;//19;					
	if (unB != INVALID_INT)
		FillRectImage(GetBitmap(unB),c_pDC,r);
	r.left = r.right;
	sz = GetBmpSize(GetBitmap(unC));
	r.right = r.left + sz.cx;//21;					
	if (unC != INVALID_INT)
		FillRectImage(GetBitmap(unC),c_pDC,r);
}

COLORREF CSkinManager::GetStockValueColor(void * c_pStock,CString c_strName,CString c_strValue,COLORREF c_clDef)
{
	SStock * pStock = (SStock *)c_pStock;
	if (pStock == NULL)
		return c_clDef;
	if (c_strName == STR_XJ || c_strName == STR_ZDF || c_strName == STR_ZD)
	{
		if (pStock->m_sQuote.zdfd < 0)
			return getColor(PRICEDOWN);
		else
			if (pStock->m_sQuote.zdfd > 0)
				return getColor(PRICEUP);
			else
				return getColor(PRICENORMAL);
	}
	else
		if (c_strName == STR_ZGJG)
		{
			if (pStock->m_sQuote.zgjg > 0)
			{
				if (pStock->m_sQuote.zgjg < pStock->m_sQuote.zrsp)
					return getColor(PRICEDOWN);
				else
					if (pStock->m_sQuote.zgjg > pStock->m_sQuote.zrsp)
						return getColor(PRICEUP);
					else
						return getColor(PRICENORMAL);
			}
		}
		else
			if (c_strName == STR_ZDJG)
			{
				if (pStock->m_sQuote.zdjg > 0)
				{
					if (pStock->m_sQuote.zdjg < pStock->m_sQuote.zrsp)
						return getColor(PRICEDOWN);
					else
						if (pStock->m_sQuote.zdjg > pStock->m_sQuote.zrsp)
							return getColor(PRICEUP);
						else
							return getColor(PRICENORMAL);
				}
			}
			else
				if (c_strName == STR_JRKP)
				{
					if (pStock->m_sQuote.jrkp > pStock->m_sQuote.zrsp)
						return getColor(PRICEUP);			
					else
						if (pStock->m_sQuote.jrkp < pStock->m_sQuote.zrsp)			
							return getColor(PRICEDOWN);
						else
							return getColor(PRICENORMAL);
				}
				else
					if (c_strName == STR_BUY)
					{
						if (pStock->m_sQuote.jrkp > 0 && pStock->m_sQuote.zrsp > 0)
						{
							if (pStock->m_sQuote.BP1 > pStock->m_sQuote.zrsp)
								return getColor(PRICEUP);
							else
								if (pStock->m_sQuote.BP1 < pStock->m_sQuote.zrsp)
									return getColor(PRICEDOWN);
								else
									return getColor(PRICENORMAL);
						}
					}
					else
						if (c_strName == STR_SELL)
						{
							if (pStock->m_sQuote.jrkp > 0 && pStock->m_sQuote.zrsp > 0)
							{
								if (pStock->m_sQuote.SP1 > pStock->m_sQuote.zrsp)
									return getColor(PRICEUP);
								else
									if (pStock->m_sQuote.SP1 < pStock->m_sQuote.zrsp)
										return getColor(PRICEDOWN);
									else
										return getColor(PRICENORMAL);
							}
						}

						if (c_strName == STR_JC || c_strName == STR_DM)
							return getColor(LISTNAMECOLOR);
						if (c_strName == STR_CJL)
							return getColor(VOLCOLOR);
						if (c_strName == STR_GROUP_STOCK_INCOME || c_strName == STR_GROUP_STOCK_INCOME_PER)
						{
							char acValue[32];
							unicodeToAscii(c_strValue,acValue,16);
							if (atof(acValue) > 0)
								return getColor(PRICEUP);
							if (atof(acValue) < 0)
								return getColor(PRICEDOWN);

						}
						if (c_strName == STR_DIAGNOSE_QUICK_BTN || c_strName == STR_CHANGE_STOCK_BTN)
							return RGB(0,0,255);//getColor(NEWSLISTHILIGHTCOLOR);
						
						return c_clDef;
}

void CSkinManager::LoadFontConfig()
{
	USES_CONVERSION;
	WCHAR acBuf[32];
#ifdef CCTV_TV
	GetPrivateProfileString(_T("FONT"),_T("QUOTELIST"),_T("-18"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nQuoteListFontSize = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("FONT"),_T("BUTTON"),_T("-22"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nButtonFontSize = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("FONT"),_T("MENU"),_T("-18"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nMenuFontSize = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("FONT"),_T("TEXT"),_T("-22"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nTextFontSize = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("FONT"),_T("GRAPH"),_T("-12"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nGraphFontSize = atoi(W2A(acBuf));
#else
	GetPrivateProfileString(_T("FONT"),_T("QUOTELIST"),_T("-12"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nQuoteListFontSize = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("FONT"),_T("BUTTON"),_T("-12"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nButtonFontSize = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("FONT"),_T("MENU"),_T("-12"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nMenuFontSize = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("FONT"),_T("TEXT"),_T("-12"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nTextFontSize = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("FONT"),_T("GRAPH"),_T("-12"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	m_nGraphFontSize = atoi(W2A(acBuf));
#endif
}

void CSkinManager::SaveFontConfig()
{	
	CString strText;
	strText.Format(_T("%d"),m_nQuoteListFontSize);
	WritePrivateProfileString(_T("FONT"),_T("QUOTELIST"),strText,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));

	strText.Format(_T("%d"),m_nButtonFontSize);
	WritePrivateProfileString(_T("FONT"),_T("BUTTON"),strText,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));

	strText.Format(_T("%d"),m_nMenuFontSize);
	WritePrivateProfileString(_T("FONT"),_T("MENU"),strText,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));

	strText.Format(_T("%d"),m_nTextFontSize);
	WritePrivateProfileString(_T("FONT"),_T("TEXT"),strText,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));

	strText.Format(_T("%d"),m_nGraphFontSize);
	WritePrivateProfileString(_T("FONT"),_T("GRAPH"),strText,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
}

int CSkinManager::GetFontHeight(CFont * c_pFont)
{
	CClientDC dc(NULL);
	CFont *pOld = dc.SelectObject(c_pFont);
	CSize sz = dc.GetTextExtent(_T("测试行高"));
	dc.SelectObject(pOld);
	return sz.cy;
}

int CSkinManager::GetFontWidth(CFont *c_pFont,CString c_strText)
{
	CClientDC dc(NULL);
	CFont *pOld = dc.SelectObject(c_pFont);
	CSize sz = dc.GetTextExtent(c_strText);
	dc.SelectObject(pOld);
	return sz.cx;
}