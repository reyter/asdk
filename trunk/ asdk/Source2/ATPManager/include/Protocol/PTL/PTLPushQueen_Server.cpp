#include "stdafx.h"
#include "PTLPushQueen_Server.h"


bool IsTheSameItem(const ATP_Msg_CurrentAlgoStatus& left,const ATP_Msg_CurrentAlgoStatus& right)
{
	return left.nIdentity == right.nIdentity;
}

bool operator == (const ATP_Msg_CurrentAlgoStatus& left,const ATP_Msg_CurrentAlgoStatus& right)
{
	return !memcmp(&left,&right,sizeof(left));
}


bool IsTheSameItem(const UTI_SEC_OrderRecord& left,const UTI_SEC_OrderRecord& right)
{
	return  (left.nOrderDate == right.nOrderDate ) && (left.nOrderTime == right.nOrderTime) &&  (!strcmp(left.chOrderNumber ,right.chOrderNumber)) && (!strcmp(left.chPostStr,right.chPostStr));
}
bool IsTheSameItem(const UTI_SEC_Position& left,const UTI_SEC_Position& right)
{
	return (!strcmp(left.szMarket,right.szMarket)) && (!strcmp(left.szCode,right.szCode));
}
bool IsTheSameItem(const UTI_SEC_Match& left,const UTI_SEC_Match& right)
{
	return !strcmp(left.chMadeNumber,right.chMadeNumber) && !strcmp(left.chPostStr,right.chPostStr);
}
bool IsTheSameItem(const UTI_SEC_Assets& left,const UTI_SEC_Assets& right)
{
	return left.chMoneyType==right.chMoneyType;
}




bool IsTheSameItem(const UTI_FUT_OrderRecord& left,const UTI_FUT_OrderRecord& right)
{
	return (left.nOrderDate == right.nOrderDate ) && (left.nOrderTime == right.nOrderTime) && (!strcmp(left.chOrderNumber ,right.chOrderNumber));
}
bool IsTheSameItem(const UTI_FUT_Position& left,const UTI_FUT_Position& right)
{
	return  (left.cBSSide == right.cBSSide) && (!strcmp(left.szMarket,right.szMarket)) && (!strcmp(left.szCode,right.szCode));
}
bool IsTheSameItem(const UTI_FUT_Match& left,const UTI_FUT_Match& right)
{
	return !strcmp(left.chMadeNumber,right.chMadeNumber) && !strcmp(left.chPostStr,right.chPostStr);
}
bool IsTheSameItem(const UTI_FUT_Assets& left,const UTI_FUT_Assets& right)
{
	return left.chMoneyType==right.chMoneyType;
}


bool operator == (const UTI_SEC_OrderRecord& left,const UTI_SEC_OrderRecord& right)
{
	return !memcmp(&left,&right,sizeof(left));
}
bool operator == (const UTI_SEC_Position& left,const UTI_SEC_Position& right)
{
	return !memcmp(&left,&right,sizeof(left));
}
bool operator == (const UTI_SEC_Match& left,const UTI_SEC_Match& right)
{
	return !memcmp(&left,&right,sizeof(left));
}
bool operator == (const UTI_SEC_Assets& left,const UTI_SEC_Assets& right)
{
	return !memcmp(&left,&right,sizeof(left));
}



bool operator == (const UTI_FUT_OrderRecord& left,const UTI_FUT_OrderRecord& right)
{
	return !memcmp(&left,&right,sizeof(left));
}
bool operator == (const UTI_FUT_Position& left,const UTI_FUT_Position& right)
{
	return !memcmp(&left,&right,sizeof(left));
}
bool operator == (const UTI_FUT_Match& left,const UTI_FUT_Match& right)
{
	return !memcmp(&left,&right,sizeof(left));
}
bool operator == (const UTI_FUT_Assets& left,const UTI_FUT_Assets& right)
{
	return !memcmp(&left,&right,sizeof(left));
}