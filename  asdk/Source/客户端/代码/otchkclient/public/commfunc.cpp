///-#include "commfunc.h"
#include "stdafx.h"
#include "winver.h"
#include <AFXINET.H>
#include <atlbase.h>
#include <tlhelp32.h> //声明快照函数文件

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "direct.h"
#include "string.h"
#include "io.h"
#include "../public/data.h"
#include <list>

using   namespace   std;

#include "Rpcdce.h" 
#pragma comment(lib,"Rpcrt4.lib") 
#include <Nb30.h>
#pragma comment(lib,"Netapi32.lib") 

#pragma comment(lib, "Version.lib")
#define WM_DOWNLOAD_LEN			WM_USER + 401
CString GetFileVersion(char*  FileName)
{   
	int   iVerInfoSize;
	char   *pBuf;
	CString   asVer(_T(""));
	CString strFileName;
	VS_FIXEDFILEINFO   *pVsInfo;
	unsigned   int   iFileInfoSize   =   sizeof(   VS_FIXEDFILEINFO   );
    
    strFileName = FileName;
	iVerInfoSize   =   GetFileVersionInfoSize(strFileName,NULL); 
    
	if(iVerInfoSize!= 0)
	{   
		pBuf   =   new   char[iVerInfoSize];
		if(GetFileVersionInfo(strFileName,0,   iVerInfoSize,   pBuf   )   )   
		{   
			if(VerQueryValue(pBuf,   _T("\\"),(void   **)&pVsInfo,&iFileInfoSize))   
			{   
				asVer.Format(_T("%d.%d.%d.%d"),HIWORD(pVsInfo->dwFileVersionMS),LOWORD(pVsInfo->dwFileVersionMS),HIWORD(pVsInfo->dwFileVersionLS),LOWORD(pVsInfo->dwFileVersionLS));
			}   
		}   
		delete   pBuf;   
	}   
	return   asVer;   
}  

CString GetCurrentAppDirectory()
{
	char szFile[MAX_PATH];
	char szPath[MAX_PATH];
	GetModuleFileNameA(NULL,szFile,MAX_PATH);
	size_t i;
	for(i=strlen(szFile)-1; i>0 && szFile[i]!='\\'; i--);
	szFile[i]='\0';
	strcpy(szPath,szFile);
	CString strRet;
	strRet = szPath;
	return strRet;
}

CString GetModifyTime(CString appname)
{
	WIN32_FIND_DATA ffd ;
	HANDLE hFind = FindFirstFile(appname,&ffd);
	SYSTEMTIME stUTC, stLocal;
	FileTimeToSystemTime(&(ffd.ftLastWriteTime), &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
	CString strTmp;
	strTmp.Format(_T("%d-%d-%d,%d:%d"), stLocal.wYear,stLocal.wMonth,stLocal.wDay,stLocal.wHour,stLocal.wMinute);
	//--	
	return strTmp;
}

char * ExtractDirFromFullPath(char * path)
{
 char *p = path;
 char *tag = p;
 while (*p)
 {
  if ( (*p) == '\\' )
   tag = p;
  ++p;
 }
 *tag = '\0';
 return path;
}


int DownLoadData(CString c_strDownUrl,CString c_strWriteFileName,HWND c_hwnd,int * c_pnCancel)
{
	CString strSentence, strWriteName;;
	CInternetSession sess;
	CHttpFile* fileGet;
	unsigned int	uiTotalLen = 0;
	sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);      // 5秒的连接超时
	sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 2000);           // 1秒的发送超时
	sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 1000 * 60);        // 60秒的接收超时
	sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 2000);     // 2秒的发送超时
	sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 1000 * 60);       // 60秒的接收超时
	sess.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);          // 1次重试
	
	try
	{
		fileGet=(CHttpFile*)sess.OpenURL(c_strDownUrl);
	}
	catch(CException* )
	{
		fileGet = 0;
		return -9;
		//throw;
	}    

	if(fileGet)
	{
		DWORD dwStatus;
		DWORD dwBuffLen = sizeof(dwStatus);
		BOOL bSuccess = fileGet->QueryInfo(HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwBuffLen);
		CString strEnter;
		strEnter = "\n";
		if( bSuccess && dwStatus>= 200&& dwStatus<300 ) 
		{ 
			CStdioFile fileWrite;
			char aczBuf[10240 + 1];
			int n;
			if(fileWrite.Open(c_strWriteFileName, CFile::modeWrite|CFile::modeCreate|CFile::typeBinary))
			{ 
				/*
				while(fileGet->ReadString(strSentence))
				{
				fileWrite.WriteString(strSentence);
				fileWrite.WriteString(strEnter);
				}*/
				while(true)
				{
					n = fileGet->Read(aczBuf,10240);
					if (n<=0)
						break;
					fileWrite.Write(aczBuf,n);
					uiTotalLen += n;
					if (c_hwnd > 0)
					{
						::SendMessage(c_hwnd,WM_DOWNLOAD_LEN,uiTotalLen,n);
						MSG   Message; 
						while (::PeekMessage(&Message,   NULL,   0,   0,   PM_REMOVE))     
						{ 
							::TranslateMessage(&Message); 
							::DispatchMessage(&Message); 
						}
					}
					if (*c_pnCancel == 1)
					{
						fileWrite.Close();
						fileGet->Close();
						delete fileGet;
						sess.Close();
						return -999;
					}
				}
				fileWrite.Close();
			}
			else
			{
				return -1;
			}
		}
		else 
		{
			strSentence.Format(_T("打开网页文件出错，错误码：%d"), dwStatus);
			fileGet->Close();
			delete fileGet;
			sess.Close();
			return -2;
		}
		fileGet->Close();
		delete fileGet;
	}
	else
	{
		sess.Close();
		return -3;
	}

	sess.Close();
	return 0;
}

int DeleteTmpFile(char * c_aczPath)
{
	long hFile;
	char filespeca[256];
	char filename[256];
	time_t  l_cur_time ;	
	time(&l_cur_time) ;
	_finddata_t fileinfo;
	
	sprintf_s(filespeca,256,"%s\\*.*",c_aczPath);

	if ((hFile=_findfirst(filespeca,&fileinfo)) != -1)
	{
	do
	{
		if (fileinfo.attrib & _A_SUBDIR)
		{
		}
		else
		{
			sprintf(filename,"%s\\%s",c_aczPath,fileinfo.name);
			DeleteFileA(filename);			
		}

	} while (_findnext(hFile,&fileinfo) == 0);

	_findclose(hFile);
	}
	return 0;
}

int GetAllLocalAdapterMacAddr(std::list<vector<unsigned char>> & mac)

{

	NCB ncb;

	LANA_ENUM AdapterList;


	memset(&ncb, 0, sizeof(ncb));

	ncb.ncb_command = NCBENUM;

	ncb.ncb_buffer = (unsigned char *)&AdapterList;

	ncb.ncb_length = sizeof(AdapterList);

	Netbios(&ncb);


	mac.resize(0);


	for (int i = 0; i < AdapterList.length ; ++i )

	{

		struct ASTAT

		{

			ADAPTER_STATUS adapt;

			NAME_BUFFER    psz_name[30];

		} Adapter;



		// Reset the LAN adapter so that we can begin querying it

		NCB Ncb;

		memset( &Ncb, 0, sizeof (Ncb));

		Ncb.ncb_command  = NCBRESET;

		Ncb.ncb_lana_num = AdapterList.lana[i];



		if (Netbios(&Ncb) != NRC_GOODRET)

			continue;



		// Prepare to get the adapter status block

		memset(&Ncb, 0, sizeof(Ncb)) ;

		Ncb.ncb_command = NCBASTAT;

		Ncb.ncb_lana_num = AdapterList.lana[ i ];

		strcpy((char *)Ncb.ncb_callname, "*" );



		memset(&Adapter, 0, sizeof (Adapter));

		Ncb.ncb_buffer = (unsigned char *)&Adapter;

		Ncb.ncb_length = sizeof (Adapter);



		// Get the adapter's info and, if this works, return it in standard,

		// colon-delimited form. 

		if ( Netbios( &Ncb ) == 0 )

		{

			std::vector<unsigned char> v6;

			v6.resize(6);

			for (int i=0; i<6; i++)

				v6[i] = Adapter.adapt.adapter_address[i];

			if (v6[0] == 0)

			{

				std::list<std::vector<unsigned char> >::iterator i = mac.begin();

				for (; i!=mac.end(); i++) if (*i == v6)

					break;

				if (i==mac.end())

					mac.push_back(v6);

			}

		}

		else

			break;

	}

	return 0;

}

CString GetMac()
{
	long rt;  
	UUID ui;
	char mac[6][10]={0};
	CString temp;
	CString Mac(_T(""));

	std::list<vector<unsigned char>> vMac;
	GetAllLocalAdapterMacAddr(vMac);
	vector<unsigned char>::iterator iter;
	if (vMac.size() > 0)
	{

		//for(iter=(vMac.begin())->begin(); iter!=(vMac.begin())->end(); iter++)
		//{
		Mac.Format(_T("%.2X.%.2X.%.2X.%.2X.%.2X.%.2X"),(vMac.begin())->at(0),(vMac.begin())->at(1),(vMac.begin())->at(2),(vMac.begin())->at(3),(vMac.begin())->at(4),(vMac.begin())->at(5));
		//}
		return Mac;
	}

	rt = UuidCreateSequential(&ui);
	if (rt == RPC_S_OK)
	{
		/*
		itoa(ui.Data4[2],mac[0],16);
		itoa(ui.Data4[3],mac[1],16);
		itoa(ui.Data4[4],mac[2],16);
		itoa(ui.Data4[5],mac[3],16);
		itoa(ui.Data4[6],mac[4],16);
		itoa(ui.Data4[7],mac[5],16);*/
		Mac.Format(_T("%.2X.%.2X.%.2X.%.2X.%.2X.%.2X"),ui.Data4[2],ui.Data4[3],ui.Data4[4],ui.Data4[5],ui.Data4[6],ui.Data4[7]);
	}

	return Mac;
}


void CaclLineInRect(CPoint c_ptA,CPoint c_ptB,CRect c_rectDraw,CPoint &c_ptRetA,CPoint &c_ptRetB)
{
	float x1,y1,x2,y2;
	int dx,dy;
	dx = c_ptB.x - c_ptA.x;
	dy = c_ptB.y - c_ptA.y;

	x1 = c_ptA.x;
	x2 = c_ptB.x;
	y1 = c_ptA.y;
	y2 = c_ptB.y;
	if (dx == 0)
	{
		x1 = c_ptA.x;
		x2 = c_ptA.x;
		y1 = c_ptA.y<c_ptB.y?c_rectDraw.bottom:c_rectDraw.top;
		y2 = c_ptA.y<c_ptB.y?c_rectDraw.top:c_rectDraw.bottom;		
	}
	else
	if (dy == 0)
	{
		x2 = c_ptA.x<c_ptB.x?c_rectDraw.left:c_rectDraw.right;
		x1 = c_ptA.x<c_ptB.x?c_rectDraw.right:c_rectDraw.left;
		y1 = c_ptA.y;
		y2 = c_ptA.y;
	}
	else
	if (dx > 0 && dy < 0)
	{
		float d = dx;
		d /= dy;
		x1 = c_rectDraw.right;
		y1 = c_ptA.y + (x1-c_ptA.x) / d;
		if (y1 < c_rectDraw.top)
		{
			y1 = c_rectDraw.top;
			x1 = c_ptA.x + (y1-c_ptA.y) * d;
		}

		x2 = c_rectDraw.left;
		y2 = c_ptA.y + (x2 - c_ptA.x) / d;
		if (y2 > c_rectDraw.bottom)
		{
			y2 = c_rectDraw.bottom;
			x2 = c_ptA.x + (y2 - c_ptA.y) * d;
		}
	}
	else
	if (dx < 0 && dy < 0)
	{
		float d = dx;
		d /= dy;
		x1 = c_rectDraw.left;
		y1 = c_ptA.y + (x1-c_ptA.x) / d;
		if (y1 < c_rectDraw.top)
		{
			y1 = c_rectDraw.top;
			x1 = c_ptA.x + (y1-c_ptA.y) * d;
		}

		x2 = c_rectDraw.right;
		y2 = c_ptA.y + (x2 - c_ptA.x) / d;
		if (y2 > c_rectDraw.bottom)
		{
			y2 = c_rectDraw.bottom;
			x2 = c_ptA.x + (y2 - c_ptA.y) * d;
		}
	}
	else
	if (dx < 0 && dy > 0)
	{
		float d = dx;
		d /= dy;
		x1 = c_rectDraw.left;
		y1 = c_ptA.y + (x1-c_ptA.x) / d;
		if (y1 > c_rectDraw.bottom)
		{
			y1 = c_rectDraw.bottom;
			x1 = c_ptA.x + (y1-c_ptA.y) * d;
		}

		x2 = c_rectDraw.right;
		y2 = c_ptA.y + (x2 - c_ptA.x) / d;
		if (y2 < c_rectDraw.top)
		{
			y2 = c_rectDraw.top;
			x2 = c_ptA.x + (y2 - c_ptA.y) * d;
		}
	}
	else
	if (dx > 0 && dy > 0)
	{
		float d = dx;
		d /= dy;
		x1 = c_rectDraw.right;
		y1 = c_ptA.y + (x1-c_ptA.x) / d;
		if (y1 > c_rectDraw.bottom)
		{
			y1 = c_rectDraw.bottom;
			x1 = c_ptA.x + (y1-c_ptA.y) * d;
		}

		x2 = c_rectDraw.left;
		y2 = c_ptA.y + (x2 - c_ptA.x) / d;
		if (y2 < c_rectDraw.top)
		{
			y2 = c_rectDraw.top;
			x2 = c_ptA.x + (y2 - c_ptA.y) * d;
		}
	}
	c_ptRetA.x = x1;
	c_ptRetA.y = y1;
	c_ptRetB.x = x2;
	c_ptRetB.y = y2;

}

void CaclPointByMidLine(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC,CPoint &c_ptD)
{
	int dx = c_ptB.x - c_ptA.x;
	int dy = c_ptB.y - c_ptA.y;

	if (dx == 0)
	{
		c_ptD = c_ptC;
		c_ptD.x -=  2 *(c_ptC.x - c_ptA.x);
		return;
	}
	
	if (dy == 0)
	{
		c_ptD = c_ptC;
		c_ptD.y -= 2 *(c_ptD.y - c_ptA.y);
		return;
	}

	float d = dx;
	d /= dy;

	c_ptD.y = c_ptC.y;
	c_ptD.x = c_ptA.x + (c_ptD.y-c_ptA.y) * d;

	c_ptD.x -= c_ptC.x - c_ptD.x;
}

void CaclArrow(CPoint c_ptA,CPoint c_ptB,CPoint &c_ptRetA,CPoint &c_ptRetB)
{
	int dx = c_ptB.x - c_ptA.x;
	int dy = c_ptB.y - c_ptA.y;

	double slopy , cosy , siny;
	double Par = 10.0;  //length of Arrow (>)
	slopy = atan2( double( c_ptA.y - c_ptB.y ),double( c_ptA.x - c_ptB.x ) );
	cosy = cos( slopy );
	siny = sin( slopy ); //need math.h for these functions
  
	//here is the tough part - actually drawing the arrows
	//a total of 6 lines drawn to make the arrow shape
	/*
	pdc->MoveTo( m_One);
	pdc->LineTo( m_One.x + int( - Par * cosy - ( Par / 2.0 * siny ) ),
		m_One.y + int( - Par * siny + ( Par / 2.0 * cosy ) ) );
	pdc->LineTo( m_One.x + int( - Par * cosy + ( Par / 2.0 * siny ) ),
		m_One.y - int( Par / 2.0 * cosy + Par * siny ) );
	pdc->LineTo( m_One );*/
	/*/-------------similarly the the other end-------------/*/
	//pdc->MoveTo( m_Two );
	c_ptRetA.x = c_ptB.x + int( Par * cosy - ( Par / 2.0 * siny ) );
	c_ptRetA.y = c_ptB.y + int( Par * siny + ( Par / 2.0 * cosy ) );

	//pdc->LineTo( m_Two.x + int( Par * cosy - ( Par / 2.0 * siny ) ),
	///	m_Two.y + int( Par * siny + ( Par / 2.0 * cosy ) ) );
	c_ptRetB.x = c_ptB.x + int( Par * cosy + Par / 2.0 * siny );
	c_ptRetB.y = c_ptB.y - int( Par / 2.0 * cosy - Par * siny );
	//pdc->LineTo( m_Two.x + int( Par * cosy + Par / 2.0 * siny ),
	//	m_Two.y - int( Par / 2.0 * cosy - Par * siny ) );
	//pdc->LineTo( m_Two );
}
bool IsNearLine(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC,int c_nDis,int c_nType)
{
	int X,Y;
	bool bRet = false;
	int dx = c_ptB.x - c_ptA.x;
	int dy = c_ptB.y - c_ptA.y;
	if (dx == 0)
	{
		X = c_ptC.x;
		Y = c_ptC.y;
		if (abs(X - c_ptA.x) <= c_nDis)
			bRet = true;
	}
	else
	if (dy == 0)
	{
		X = c_ptC.x;
		Y = c_ptC.y;
		if (abs(Y - c_ptA.y) <= c_nDis)
			bRet = true;
	}
	else
	{
		float d = dx;
		d /= dy;
		d = (c_ptC.y - c_ptA.y) * d + c_ptA.x;		
		X = d;
		Y = c_ptC.y;
		if (abs(d - c_ptC.x) < c_nDis * c_nDis)
			bRet = true;

	}

	int XHigh,XLow;
	int YHigh,YLow;
	XHigh = c_ptA.x>c_ptB.x?c_ptA.x:c_ptB.x;
	XLow = c_ptA.x>c_ptB.x?c_ptB.x:c_ptA.x;

	YHigh = c_ptA.y>c_ptB.y?c_ptA.y:c_ptB.y;
	YLow = c_ptA.y>c_ptB.y?c_ptB.y:c_ptA.y;

	if (c_nType == 1)//限制在线段内
	{
		if (bRet && X >= XLow - c_nDis && X <= XHigh + c_nDis && Y>=YLow - c_nDis && Y < YHigh + c_nDis)
			bRet = true;
		else
			bRet = false;
	}


	return bRet;
}

bool IsNearRect(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC,int c_nDis)
{
	int XHigh,XLow;
	int YHigh,YLow;
	XHigh = c_ptA.x>c_ptB.x?c_ptA.x:c_ptB.x;
	XLow = c_ptA.x>c_ptB.x?c_ptB.x:c_ptA.x;

	YHigh = c_ptA.y>c_ptB.y?c_ptA.y:c_ptB.y;
	YLow = c_ptA.y>c_ptB.y?c_ptB.y:c_ptA.y;
	
	bool bRet = false;

	bRet = IsNearLine(CPoint(XLow,YLow),CPoint(XHigh,YLow),c_ptC,c_nDis,1);
	if (bRet == false)
		bRet = IsNearLine(CPoint(XHigh,YLow),CPoint(XHigh,YHigh),c_ptC,c_nDis,1);
	if (bRet == false)
		bRet = IsNearLine(CPoint(XHigh,YHigh),CPoint(XLow,YHigh),c_ptC,c_nDis,1);
	if (bRet == false)
		bRet = IsNearLine(CPoint(XLow,YHigh),CPoint(XLow,YLow),c_ptC,c_nDis,1);

	return bRet;
}

bool IsInRect(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC)
{
	int XHigh,XLow;
	int YHigh,YLow;
	XHigh = c_ptA.x>c_ptB.x?c_ptA.x:c_ptB.x;
	XLow = c_ptA.x>c_ptB.x?c_ptB.x:c_ptA.x;

	YHigh = c_ptA.y>c_ptB.y?c_ptA.y:c_ptB.y;
	YLow = c_ptA.y>c_ptB.y?c_ptB.y:c_ptA.y;
		
	if (c_ptC.x >= XLow && c_ptC.x <= XHigh && c_ptC.y >= YLow && c_ptC.y <= YHigh)
		return true;
	else
		return false;
}

bool IsNearArc(CPoint c_ptA,CPoint c_ptB,CPoint  c_ptC,int c_nDis)
{
	int d1 = sqrt(float((c_ptB.x - c_ptA.x) * (c_ptB.x - c_ptA.x) + (c_ptB.y - c_ptA.y) * (c_ptB.y - c_ptA.y)));
	int d2 = sqrt(float((c_ptC.x - c_ptA.x) * (c_ptC.x - c_ptA.x) + (c_ptC.y - c_ptA.y) * (c_ptC.y - c_ptA.y)));

	if (abs(d2 - d1) < c_nDis * c_nDis)
		return true;

	return false;
}

bool IsNearRound(CPoint c_ptA,CPoint c_ptB,CPoint  c_ptC,int c_nDis)
{
	int d1 = sqrt(float((c_ptB.x - c_ptA.x) * (c_ptB.x - c_ptA.x) + (c_ptB.y - c_ptA.y) * (c_ptB.y - c_ptA.y)));
	int d2 = sqrt(float((c_ptC.x - c_ptA.x) * (c_ptC.x - c_ptA.x) + (c_ptC.y - c_ptA.y) * (c_ptC.y - c_ptA.y)));

	if (abs(d2 - d1) < c_nDis * c_nDis)
		return true;

	return false;
}

void CaclParallel(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC,CPoint &c_ptD,double c_dPercent,CPoint &c_ptE,CPoint &c_ptF)
{
	double Ax,Ay,Bx,By,Cx,Cy,Dx,Dy,Ex,Ey,Fx,Fy;
	double persent=c_dPercent;
	double k;//平行线的斜率
	double bAB;//AB所在直线的截距
	double bCD;//CD所在直线的截距
	double bEF;//EF所在直线的截距
	Ax=c_ptA.x;
	Ay=c_ptA.y;
	Bx=c_ptB.x;
	By=c_ptB.y;
	Cx=c_ptC.x;
	Cy=c_ptC.y;
	if(c_ptA==c_ptB)//两点重合
	{
		return;
	}
	else if(c_ptA.x==c_ptB.x)//平行于Y轴
	{
		Dx=Cx;
		Dy=Cy+10;
		Ex=c_dPercent*(Cx-Ax)+Ax;
		Ey=(Ay+By)/2;
		Fx=Ex;
		Fy=Ey+10;
	}
	else if(c_ptA.y==c_ptB.y)//平行于X轴
	{
		Dy=Cy;
		Dx=Cx+10;
		Ey=c_dPercent*(Cy-Ay)+Ay;
		Ex=(Ax+Bx)/2;
		Fy=Ey;
		Fx=Ex+10;
	}
	else
	{
		k=(By-Ay)/(Bx-Ax);
		bAB=Ay-k*Ax;
		bCD=Cy-k*Cx;
		Dx=Cx+1000;
		Dy=k*Dx+bCD;
		bEF=persent*(bCD-bAB)+bAB;
		Ex=Cx;
		Ey=k*Ex+bEF;
		Fx=Ex+1000;
		Fy=k*Fx+bEF;
	}
		c_ptD.x=Dx;
		c_ptD.y=Dy;
		c_ptE.x=Ex;
		c_ptE.y=Ey;
		c_ptF.x=Fx;
		c_ptF.y=Fy;
}

int toUnicode(char * c_pSrc,int c_nSrcLen,char * c_pDest,int c_nMaxLen)
{
	if (c_nSrcLen * 2 >= c_nMaxLen)
		return -1;
	return MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,c_pSrc,c_nSrcLen,(LPWSTR)(c_pDest),c_nSrcLen * 2);
}

CString toUnicodeString(char * c_pSrc,int c_nSrcLen)
{
	
	WCHAR *pTmp = new WCHAR[c_nSrcLen + 1];
	memset(pTmp,0,c_nSrcLen * 2 + 1);
	MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,c_pSrc,c_nSrcLen,pTmp,c_nSrcLen);
	pTmp[c_nSrcLen] = 0;
	CString strRet(_T(""));
	strRet = pTmp;
	delete [] pTmp;	
	return strRet;
}

int toUtf8(char * c_pSrc,char * c_pDes,int c_nDataLen)
{
	memset(c_pDes,0,c_nDataLen * 3);
	//ANSI to UNICODE
	char * pTmp = new char[c_nDataLen * 2 + 2];
	memset(pTmp,0,c_nDataLen * 2 + 2);
	MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,c_pSrc,	strlen(c_pSrc),(LPWSTR)(pTmp),c_nDataLen);
						
	//UNICODE to UTF8
	int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, (LPWSTR)(pTmp), wcslen((LPWSTR)(pTmp)), NULL, 0, NULL, NULL);
	::WideCharToMultiByte(CP_UTF8, NULL, (LPWSTR)(pTmp), wcslen((LPWSTR)(pTmp)), c_pDes, u8Len, NULL, NULL);
	//最后加上'\0'
	c_pDes[u8Len] = '\0';
	delete [] pTmp;
	return strlen(c_pDes);
}

int unicodeToAscii(CString c_strUnicode,char * c_pRet,int c_nMaxLen)
{
	int nLen = WideCharToMultiByte(CP_ACP,0,c_strUnicode,-1,0,0,0,0);
	if (nLen > c_nMaxLen)
		return 0;
	int nRet = WideCharToMultiByte(CP_ACP,0,c_strUnicode,c_strUnicode.GetLength(),c_pRet,c_strUnicode.GetLength()*2,0,0);
	c_pRet[nLen] = 0;
	if (nRet > 0)
	c_pRet[nRet] = 0;
	return nLen;
}

int unicodeToAscii(WCHAR * c_wcUnicode,int c_nUnicodeLen,char * c_pRet,int c_nMaxLen)
{
	int nLen = WideCharToMultiByte(CP_ACP,0,c_wcUnicode,c_nUnicodeLen,0,0,0,0);
	if (nLen > c_nMaxLen)
		return 0;
	int nRet = WideCharToMultiByte(CP_ACP,0,c_wcUnicode,c_nUnicodeLen,c_pRet,c_nUnicodeLen*2,0,0);
	c_pRet[nLen] = 0;
	if (nRet > 0)
	c_pRet[nRet] = 0;
	return nLen;
}

int untf8ToAscii(char * c_pSrc,int c_nSrcLen,char * c_pDes,int c_nDataLen)
{
	int nValidLen;
	nValidLen = strlen(c_pSrc);
	if (nValidLen > c_nSrcLen)
		nValidLen = c_nSrcLen;
	//先UTF8 to UNICODE
	int uncodeLen = MultiByteToWideChar(CP_UTF8, NULL, c_pSrc,nValidLen, NULL, 0);
	wchar_t* wszString = new wchar_t[uncodeLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, c_pSrc, nValidLen, wszString, uncodeLen);
	//最后加上'\0'
	wszString[uncodeLen] = '\0';

	//UNICODE to ANSI
	WideCharToMultiByte(CP_ACP,0,wszString,-1,c_pDes,c_nDataLen,NULL,NULL);
	delete [] wszString;
	return nValidLen;	
}

CString untf8ToString(char * c_pSrc,int c_nSrcLen)
{
	int nValidLen;
	nValidLen = strlen(c_pSrc);
	if (nValidLen > c_nSrcLen)
		nValidLen = c_nSrcLen;
	//先UTF8 to UNICODE
	int uncodeLen = MultiByteToWideChar(CP_UTF8, NULL, c_pSrc,nValidLen, NULL, 0);
	wchar_t* wszString = new wchar_t[uncodeLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, c_pSrc, nValidLen, wszString, uncodeLen);
	//最后加上'\0'
	wszString[uncodeLen] = '\0';
	return wszString;
}

int HttpTradeData(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRetData)
{
	CString strSentence, strWriteName;;
	CInternetSession sess(NULL,1,INTERNET_OPEN_TYPE_PRECONFIG);
	CHttpFile* fileGet;
/*
INTERNET_PROXY_INFO proxyinfo;

proxyinfo.dwAccessType = INTERNET_OPEN_TYPE_PROXY;

proxyinfo.lpszProxy ="211.104.243.73:8080";

proxyinfo.lpszProxyBypass = NULL;

session.SetOption(INTERNET_OPTION_PROXY,(LPVOID)&proxyinfo,

sizeof(INTERNET_PROXY_INFO));

*/
	unsigned int	uiTotalLen = 0;
	sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 5);      // 5秒的连接超时
	//sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 2000);           // 1秒的发送超时
	
	//sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 1000 * 3);        // 60秒的接收超时
	//sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 3000);     // 2秒的发送超时
	//sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 1000 * 3);       // 60秒的接收超时
	sess.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 0);          // 1次重试
	sess.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);          // 1次重试
	CHttpConnection * pConn;
	CString strServer;
	strServer = toUnicodeString(c_pHost,strlen(c_pHost));
	try
	{		
		pConn=sess.GetHttpConnection(strServer,(INTERNET_PORT)c_nPort);
		fileGet=pConn->OpenRequest(CHttpConnection::HTTP_VERB_GET,_T("/simu_trade.do"),0,1,0,0,INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE);

		char acHttp[1024];
		//sprintf(acHttp,"Host: %s:%d \r\n  Content-Length: %d\r\n content-type: audio/mp3;\r\ncontent-source : invest\r\n\r\n",c_pHost,c_nPort,c_nSendLen);
		sprintf(acHttp,"Host: %s:%d \r\ncontent-type: audio/mp3;\r\ncontent-source : invest\r\n\r\n",c_pHost,c_nPort);
		CString strHttp;
		strHttp = toUnicodeString(acHttp,strlen(acHttp));		

		INTERNET_BUFFERS BufferIn;
		memset(&BufferIn, 0, sizeof(BufferIn));
		BufferIn.dwStructSize    = sizeof( INTERNET_BUFFERS ); // Must be set or error will occur
		BufferIn.Next            = NULL; 
		BufferIn.lpcszHeader     = strHttp.GetBuffer();
		BufferIn.dwHeadersLength = strHttp.GetLength();
		BufferIn.dwHeadersTotal  = 0;
		BufferIn.lpvBuffer       = c_pSendData;                
		BufferIn.dwBufferLength  = c_nSendLen;
		BufferIn.dwBufferTotal   = c_nSendLen; // This is the only member used other than dwStructSize
		BufferIn.dwOffsetLow     = 0;
		BufferIn.dwOffsetHigh    = 0;
		/*
		fileGet->AddRequestHeaders(strHttp);		
		fileGet->SendRequest();
		
		BOOL bRequestOK = fileGet->SendRequestEx(c_nSendLen, HSR_SYNC | HSR_INITIATE);
		if(!bRequestOK)
		{                                          
			fileGet->Close();
			delete fileGet;
			pConn->Close();
			delete pConn;
			sess.Close();
			return -8;
		}  
		fileGet->Write(c_pSendData,c_nSendLen);*/
		
		if (!fileGet->SendRequestEx(&BufferIn,NULL,0,1))//HSR_ASYNC|HSR_INITIATE,1))
		{
			fileGet->Close();
			delete fileGet;
			pConn->Close();
			delete pConn;
			sess.Close();
			return  -10;
		}
		fileGet->EndRequest();//HSR_SYNC);	
/*
		fileGet->Close();
		delete fileGet;
		pConn->Close();
		delete pConn;
		sess.Close();
		
		return -9;*/

	}
	catch(CException* m_pException)
	{
		fileGet->Close();
		delete fileGet;
		//m_pException->Delete();
		pConn->Close();
		delete pConn;
		sess.Close();		
		throw;
		return -9;
	}    

	if(fileGet)
	{
		DWORD dwStatus;
		DWORD dwBuffLen = sizeof(dwStatus);
		BOOL bSuccess = fileGet->QueryInfo(HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwBuffLen);			
		if( bSuccess && dwStatus>= 200&& dwStatus<300 ) 
		{ 		
			DWORD dwLen;
			BOOL bLen = fileGet->QueryInfo(HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER,&dwLen,&dwBuffLen);
			int n;
			if(bLen)
			{ 
				while(uiTotalLen<dwLen)
				{
					n = fileGet->Read(c_pRetData + uiTotalLen,10240);
					if (n<=0)
						break;
					uiTotalLen += n;
				}				
			}
			else
			{
				return -1;
			}
		}
		else 
		{
			strSentence.Format(_T("打开网页文件出错，错误码：%d"), dwStatus);
			fileGet->Close();	
			delete fileGet;
			pConn->Close();
			delete pConn;
			sess.Close();			
			return -2;
		}
	}
	else
	{
		fileGet->Close();
		delete fileGet;
		pConn->Close();
		delete pConn;
		sess.Close();		
		return -3;
	}
	
	fileGet->Close();
	delete fileGet;	
	pConn->Close();	
	delete pConn;
	sess.Close();

	return uiTotalLen;
}


bool IsSameWeek(unsigned int uiNow, unsigned int uiPrev)
{//比较今日和所给定日期是否在同一周内
	tm	stPrevTime,stNowTime;

	///给定的日期.
	memset(&stPrevTime,0,sizeof(tm));
	stPrevTime.tm_year=uiPrev/10000-1900;
	stPrevTime.tm_mon=uiPrev%10000/100-1;
	stPrevTime.tm_mday=uiPrev%100;
	time_t stPrev=mktime(&stPrevTime);

	///今天.
	memset(&stNowTime,0,sizeof(tm));
	stNowTime.tm_year=uiNow/10000-1900;
	stNowTime.tm_mon=uiNow%10000/100-1;
	stNowTime.tm_mday=uiNow%100;
	time_t stNow=mktime(&stNowTime);

	if(stNow>stPrev && difftime(stNow,stPrev)>=7*24*3600)
		return	false;
	else if(stPrev>stNow && difftime(stPrev,stNow)>=7*24*3600)
		return	false;
	if(stNowTime.tm_wday<stPrevTime.tm_wday && stNow>stPrev)
		return	false;
	else if(stNowTime.tm_wday>stPrevTime.tm_wday && stNow<stPrev)
		return	false;
	return	true;
}

bool IsSameMonth(unsigned int uiNow, unsigned int uiPrev)
{//比较今日和所给定日期是否在同一月内
	unsigned char ucNowMonth=uiNow%10000/100;
	unsigned char ucPrevMonth=uiPrev%10000/100;
	if(uiNow/10000 != uiPrev/10000)
		return false;
	if(ucNowMonth!=ucPrevMonth)
		return false;
	return	true;
}

//是否存在进程
int IsProccessExists(CString c_strApp)
{
	PROCESSENTRY32 pe32;
	//在使用这个结构之前，先设置它的大小
	pe32.dwSize = sizeof(pe32);
	//给系统内的所有进程拍一个快照
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	//Includes the process list in the snapshot
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot 调用失败! \n");
		return -1;
	}
	
	//遍历进程快照，轮流显示每个进程信息
	BOOL bMore = ::Process32First(hProcessSnap,&pe32);
	while (bMore)
	{
		if (c_strApp.CompareNoCase(pe32.szExeFile) == 0)		
		{
			::CloseHandle(hProcessSnap);
			return 1;
		}
		//printf(" 进程名称为:%s\n",pe32.szExeFile);
		//printf(" 进程ID为:%u \n\n",pe32.th32ProcessID);
		//遍历下一个
		bMore = ::Process32Next(hProcessSnap,&pe32);
	}
	//清除snapshot对象
	::CloseHandle(hProcessSnap);
	return 0;
}

int LogFile(char * c_pFile,char * c_pData,int c_nLen)
{
	FILE *f;
	f = fopen(c_pFile,"ab");
	if (f)
	{
		time_t now;
		time(&now);
		struct tm *lt = localtime(&now);
		char acDate[32];
		sprintf(acDate,"%4d%.2d%.2d %.2d:%.2d:%.2d  ",lt->tm_year,lt->tm_mon,lt->tm_mday,lt->tm_hour,lt->tm_min,lt->tm_sec);
		fseek(f,0,SEEK_END);
		fwrite(acDate,1,strlen(acDate),f);
		int nRet = fwrite(c_pData,1,c_nLen,f);
		fclose(f);
		return nRet;
	}
	return -1;
}

//对齐，按照c_pKBase进行对齐,c_pK空间留有足够空间
int AlignKData(KLINE * c_pKBase,int c_nBaseCount,KLINE * c_pK,int c_nKCount)
{
	KLINE * pKTmp = (KLINE *)malloc(sizeof(KLINE) * c_nBaseCount);
	int nBase = 0;
	int nDes = 0;
	int nBaseDay = 0;
	while(nBase < c_nBaseCount)
	{
		nBaseDay = c_pKBase[nBase].day;
		while(nDes < c_nKCount)
		{
			if (c_pK[nDes].day == nBaseDay)//一致
			{
				pKTmp[nBase].day = c_pK[nDes].day;
				pKTmp[nBase].open = c_pK[nDes].open;
				pKTmp[nBase].high = c_pK[nDes].high;
				pKTmp[nBase].low = c_pK[nDes].low;
				pKTmp[nBase].close = c_pK[nDes].close;
				pKTmp[nBase].amount = c_pK[nDes].amount;
				pKTmp[nBase].volume = c_pK[nDes].volume;
				nDes++;
				nBase++;
				break;
			}
			else
			if (c_pK[nDes].day > nBaseDay)//
			{
				if (nDes > 0)
				{
					pKTmp[nBase].day = nBaseDay;//延用上一个值
					pKTmp[nBase].open = pKTmp[nBase-1].open;
					pKTmp[nBase].high = pKTmp[nBase-1].high;
					pKTmp[nBase].low = pKTmp[nBase-1].low;
					pKTmp[nBase].close = pKTmp[nBase-1].close;
					pKTmp[nBase].amount = pKTmp[nBase-1].amount;
					pKTmp[nBase].volume = pKTmp[nBase-1].volume;
					nBase++;
					break;
				}
				else//第一个
				{
					pKTmp[nBase].day = nBaseDay;//不可比较
					pKTmp[nBase].open = 0;
					pKTmp[nBase].high = 0;
					pKTmp[nBase].low = 0;
					pKTmp[nBase].close = 0;
					pKTmp[nBase].amount = 0;
					pKTmp[nBase].volume = 0;
					nBase++;
					break;
				}
			}
			else
			if (c_pK[nDes].day < nBaseDay)//放弃此数据
			{
				nDes++;
				break;
			}
		}
	}
	memcpy(c_pK,pKTmp,sizeof(KLINE)*c_nBaseCount);
	free(pKTmp);
	return c_nBaseCount;
}
/*
系统买入机械规则：
⒈收盘价比五日均价低4%，确保信号发生在跌势；
⒉开盘价低于昨日最低价1%；
⒊收盘反弹至昨日最低价以上。
*/

bool IsJumpDownBuy(KLINE * c_pBlock,int c_nPos)
{
	if (c_nPos < 10)
		return false;
	int nSum = c_pBlock[c_nPos].close + c_pBlock[c_nPos-1].close + c_pBlock[c_nPos-2].close + c_pBlock[c_nPos-3].close + c_pBlock[c_nPos-4].close;
	nSum *= 96;
	nSum /= 5*100;
	if(c_pBlock[c_nPos].close <= nSum && c_pBlock[c_nPos].close < c_pBlock[c_nPos-1].close * 99/100 && c_pBlock[c_nPos].close > c_pBlock[c_nPos].low)
	{
		return true;
	}
	return false;
}
