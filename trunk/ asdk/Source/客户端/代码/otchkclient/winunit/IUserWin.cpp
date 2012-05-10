#include "StdAfx.h"
#include "WinF10.h"
#include "IUserWin.h"

IUserWin::IUserWin(void)
{
}

IUserWin::~IUserWin(void)
{
}

void IUserWin::SetLayout(void)
{
}

void IUserWin::ResetSkin(void)
{
}

void IUserWin::FreshData(void)
{
}

void IUserWin::SetStockCode(CString c_strCode)
{
}

void IUserWin::CreateSelf(CWnd * c_pParent)
{
}

void IUserWin::GetTitle(CString &c_strIn)
{
	CWnd * pWnd = GetWnd();
	if (pWnd)
	{
		pWnd->GetWindowText(c_strIn);
	}
}

void IUserWin::GetViewTitle(CString &c_strIn)
{
	CWnd * pWnd = GetWnd();
	if (pWnd)
	{
		pWnd->GetWindowText(c_strIn);
	}
}

void IUserWin::SetTitle(CString c_strIn)
{
	CWnd * pWnd = GetWnd();
	if (pWnd)
	{
		pWnd->SetWindowText(c_strIn);
	}
}

bool IUserWin::IsTitle(CString c_strIn)
{
	CWnd * pWnd = GetWnd();
	if (pWnd)
	{
		CString strTitle;
		pWnd->GetWindowText(strTitle);
		if (strTitle == c_strIn)
			return true;
	}
	return false;
}

void IUserWin::RefreshWin()
{
	CWnd * pWnd;
	pWnd = GetWnd();
	if (pWnd)
		pWnd->Invalidate();
}

void IUserWin::DoCommand(int c_nCommand)
{
}