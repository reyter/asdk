#include "stdafx.h"
#include "CATPNetCApi.h"
#include "ATPNetCProcessor.h"
#include "ATPManagerNetDefine.h"
#include "ATPManagerDataBaseDefine.h"

/*
#ifdef __cplusplus
extern "C"
{
#endif
	CATPNetCProcessor *g_pATPManagerNet = NULL;

	ATPNETCAPI(CATPNetCProcessor*)	Connect(char *pIP,int nPort)
	{
// 		try
// 		{
// 			CHHNetFrameProcessor::RegistClientNetFrameProcessor(1,50,"�ͻ��˳���",RUNTIME_CLASS(CATPNetCProcessor));
// 			g_pATPManagerNet	= (CATPNetCProcessor*)
// 				CHHNetFrameProcessor::CreateClientNetFrameProcessor(
// 				nPort,
// 				pIP,
// 				"�ͻ��˳���",
// 				1,
// 				50,
// 				RUNTIME_CLASS(CATPNetCProcessor),TRUE);
// 		}
// 		catch (...)
// 		{
// 			
// 		}
// 		return g_pATPManagerNet;
		
	}

	ATPNETCAPI(int)	Login(char *pAccount, char *pPwd)//����
	{
		//���ݰ�ͷ
// 		struATPManageTeleHead _tagHead = {0};
// 		_tagHead.nMagic = 0x7e;
// 		_tagHead.nMsgHeadLen = 0;
// 		_tagHead.nDataLen = 0;
// 		
// 		//��Ϣ��ͷ
// 		struATPManageMsgHead _tagMsgHead = {0};
// 		_tagMsgHead.nMsgType = ID_ATPMANAGE_LOGIN;
// 		_tagMsgHead.nFlag = 1;
// 
// 		CString strDN	= g_pATPManagerNet->GetThisDN();
// 		return g_pATPManagerNet->Send(strDN,"Hello,World!",strlen("Hello,World!"));
	}

#ifdef __cplusplus
}
#endif

*/