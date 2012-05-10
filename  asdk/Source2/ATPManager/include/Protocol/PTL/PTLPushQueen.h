/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨����ƽ̨ ����ģ���.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			 ����         �޸�˵��
2010-11-29	 ��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once
#ifndef _PTLPUSHQUEEN_H_
#define _PTLPUSHQUEEN_H_

#include "TDPushProtocol.h"
#include "..\\TDSECProtocol.h"
#include "..\\TDFutProtocol.h"





#include "atlcore.h"
#include <map>
#include <algorithm>
using namespace std;


#pragma pack(push,1)

struct PARTCOMPRESS_HEAD
{
	UINT_PTR  nId;
	ATP_MSG_PUSH_ITEM_METHOD nMethod;
};

#pragma pack(pop)

//ѹ������
#include "..\\..\\hhpfdk\HHNetCompressHelper.h"
#include "..\\..\\hhpfdk\HHNetCompareCompressHelper.h"

/**
* ѹ���ֲ���Ϣ��ָ�����ڴ���
* @param pPosition  �ֲ���Ϣ��
* @param pData      ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Sec_HoldPosition* pPosition,
						char* pData,
						int nLength);


/**
* ��ָ�����ڴ��н�ѹ���ֲ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pPosition  �ֲ���Ϣ��
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Sec_HoldPosition* pPosition);



/**
* �Ա�ѹ���ֲ���Ϣ��ָ�����ڴ���
* @param pNew		�µĳֲ���Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵĳֲ���Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_HoldPosition* New,
							  const ATP_Msg_Sec_HoldPosition* Old,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Sec_HoldPosition* pPosition);


////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* ѹ��ί�м�¼��Ϣ��ָ�����ڴ���
* @param pOrderRecord  ί�м�¼
* @param pData      ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord,
						char* pData,
						int nLength);


/**
* ��ָ�����ڴ��н�ѹ���ֲ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pOrderRecord  ί�м�¼��
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord);



/**
* �Ա�ѹ���ֲ���Ϣ��ָ�����ڴ���
* @param pNew		�µ�ί����Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵ�ί����Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_QueryOrderRecords_Answer* pNew,
							  const ATP_Msg_Sec_QueryOrderRecords_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord);

////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* ѹ���ɽ���¼��Ϣ��ָ�����ڴ���
* @param pMatch  �ɽ���¼
* @param pData   ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Sec_QueryMatch_Answer* pMatch,
						char* pData,
						int nLength);


/**
* ��ָ�����ڴ��н�ѹ���ɽ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pMatch  �ɽ���¼
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Sec_QueryMatch_Answer* pMatch);



/**
* �Ա�ѹ���ɽ���Ϣ��ָ�����ڴ���
* @param pNew		�µ�ί����Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵ�ί����Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_QueryMatch_Answer* pNew,
							  const ATP_Msg_Sec_QueryMatch_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Sec_QueryMatch_Answer* pMatch);


//�ʲ�
///////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* ѹ���ʲ���¼��Ϣ��ָ�����ڴ���
* @param pAssets �ʲ���¼
* @param pData   ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Sec_QueryAssets_Answer* pAssets,
						char* pData,
						int nLength);


/**
* ��ָ�����ڴ��н�ѹ���ʲ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pAssets  �ʲ���¼
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Sec_QueryAssets_Answer* pAssets);



/**
* �Ա�ѹ���ʲ���ָ�����ڴ���
* @param pNew		�µ��ʲ���Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵ��ʲ���Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_QueryAssets_Answer* pNew,
							  const ATP_Msg_Sec_QueryAssets_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Sec_QueryAssets_Answer* pStatus);

//////////////////////////////////////////////////////////////////////////
/**
* ѹ���µ���Ϣ��ָ�����ڴ���
* @param pPosition  �ֲ���Ϣ��
* @param pData      ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Sec_MakeOrder* pMakeOrder,
	char* pData,
	int nLength);


/**
* ��ָ�����ڴ��н�ѹ�µ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pPosition  �ֲ���Ϣ��
*/
extern int ptl_decmpress(char* pData,
	int nLength,
	ATP_Msg_Sec_MakeOrder* pMakeOrder);



/**
* �Ա�ѹ���µ���Ϣ��ָ�����ڴ���
* @param pNew		�µĳֲ���Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵĳֲ���Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_MakeOrder* New,
	const ATP_Msg_Sec_MakeOrder* Old,
	char* pData,
	int nLength);

//************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////

//�ڻ�����

/**
* ѹ���ֲ���Ϣ��ָ�����ڴ���
* @param pPosition  �ֲ���Ϣ��
* @param pData      ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Fut_HoldPosition* pPosition,
						char* pData,
						int nLength);


/**
* ��ָ�����ڴ��н�ѹ���ֲ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pPosition  �ֲ���Ϣ��
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_HoldPosition* pPosition);



/**
* �Ա�ѹ���ֲ���Ϣ��ָ�����ڴ���
* @param pNew		�µĳֲ���Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵĳֲ���Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_HoldPosition* New,
							  const ATP_Msg_Fut_HoldPosition* Old,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Fut_HoldPosition* pPosition);


////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* ѹ��ί�м�¼��Ϣ��ָ�����ڴ���
* @param pOrderRecord  ί�м�¼
* @param pData      ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord,
						char* pData,
						int nLength);


/**
* ��ָ�����ڴ��н�ѹ���ֲ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pOrderRecord  ί�м�¼��
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord);



/**
* �Ա�ѹ���ֲ���Ϣ��ָ�����ڴ���
* @param pNew		�µ�ί����Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵ�ί����Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_QueryOrderRecords_Answer* pNew,
							  const ATP_Msg_Fut_QueryOrderRecords_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord);

////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* ѹ���ɽ���¼��Ϣ��ָ�����ڴ���
* @param pMatch  �ɽ���¼
* @param pData   ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Fut_QueryMatch_Answer* pMatch,
						char* pData,
						int nLength);


/**
* ��ָ�����ڴ��н�ѹ���ɽ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pMatch  �ɽ���¼
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_QueryMatch_Answer* pMatch);



/**
* �Ա�ѹ���ɽ���Ϣ��ָ�����ڴ���
* @param pNew		�µ�ί����Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵ�ί����Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_QueryMatch_Answer* pNew,
							  const ATP_Msg_Fut_QueryMatch_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Fut_QueryMatch_Answer* pMatch);


//�ʲ�
///////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* ѹ���ʲ���¼��Ϣ��ָ�����ڴ���
* @param pAssets �ʲ���¼
* @param pData   ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Fut_QueryAssets_Answer* pAssets,
						char* pData,
						int nLength);


/**
* ��ָ�����ڴ��н�ѹ���ʲ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pAssets  �ʲ���¼
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_QueryAssets_Answer* pAssets);



/**
* �Ա�ѹ���㷨״̬��Ϣ��ָ�����ڴ���
* @param pNew		�µ��ʲ���Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵ��ʲ���Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_QueryAssets_Answer* pNew,
							  const ATP_Msg_Fut_QueryAssets_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Fut_QueryAssets_Answer* pStatus);

//////////////////////////////////////////////////////////////////////////
/**
* ѹ���µ���Ϣ��ָ�����ڴ���
* @param pPosition  �ֲ���Ϣ��
* @param pData      ָд���ڴ�
* @param nLength �ڴ泤��
*/
extern int ptl_compress(const ATP_Msg_Fut_MakeOrder* pMakeOrder,
	char* pData,
	int nLength);


/**
* ��ָ�����ڴ��н�ѹ�µ���Ϣ
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
* @param pPosition  �ֲ���Ϣ��
*/
extern int ptl_decmpress(char* pData,
	int nLength,
	ATP_Msg_Fut_MakeOrder* pMakeOrder);



/**
* �Ա�ѹ���µ���Ϣ��ָ�����ڴ���
* @param pNew		�µĳֲ���Ϣ,���ΪNULL,���ʾҪɾ���ɳֲ���Ϣ.��
* @param pOld		�ɵĳֲ���Ϣ,���ΪNULL,��ʾҪ�����ֲ���Ϣ.
* @param pData      ָд���ڴ�
* @param nBufferLen �ڴ泤��
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_MakeOrder* New,
	const ATP_Msg_Fut_MakeOrder* Old,
	char* pData,
	int nLength);

//////////////////////////////////////////////////////////////////////////


extern int ptl_compress(const ATP_Msg_CurrentAlgoStatus* pStatus,
						char* pData,
						int nLength);


extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_CurrentAlgoStatus* pStatus);

extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_CurrentAlgoStatus* pStatus);


extern int ptl_comparecmpress(const ATP_Msg_CurrentAlgoStatus* pNew,
					   const ATP_Msg_CurrentAlgoStatus* pOld,
					   char* pData,
					   int nLength);

//////////////////////////////////////////////////////////////////////////
//������־ѹ��
extern int ptl_compress(const ATP_Msg_AlgoLog* pLog,
						char* pData,
						int nLength);


extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_AlgoLog* pLog);

//////////////////////////////////////////////////////////////////////////
//��־���
extern int ptl_compress(const ATP_Msg_Algo_LogCategory* pCate,
						char* pData,
						int nLength);


extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Algo_LogCategory* pCate);

#endif //_PTLPUSHQUEEN_H_
