#pragma once
#include "..\public\gridlist.h"

class CTrdGrid :
	public CGridList
{
public:
	CTrdGrid(void);
	~CTrdGrid(void);

public:
	void OnMDataItemLDbClick(int rowID,int columnID);
	void OnPaintDataItem(CDC & cMemDc,const CRect& rcDrawOnRect,int rowID,int columnID);	
};
