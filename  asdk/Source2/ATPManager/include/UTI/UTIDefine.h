/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ʵʱ������.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-4		��ΰ		 ����
-------------------------------------------------------------
*/


#pragma once

#ifndef __UTIDEFINE_H_
#define __UTIDEFINE_H_
#pragma pack(push,1)

//#include "TradeHead.h"
//#include "nsdprocapi.h"

#ifndef INFINITE
#define INFINITE 0xFFFFFFFF
#endif

#ifndef __NSDPROCAPI_H__

//�г�����
#define MARKET_SZ        0   //  ����
#define MARKET_SH        1   //  �Ϻ�
#define MARKET_STZ       2   //  ������
#define MARKET_HK		 6	 //  �۹�
#define MARKET_SP		 7	 //	 ��Ʒ�ڻ�
#define MARKET_CF		 10	 //	 ��ָ�ڻ�



#define LEN_ERROR		64		//��������
#define LEN_SESSION		64		//�Ự����
#define LEN_MARKETNAME	16		//�г�����
#define LEN_BROKER		16		//������
#define LEN_CUSTOM		16		//�ͻ���
#define LEN_ACCOUNT		16		//�ʽ��˺�
#define LEN_USERCODE	16		//�ɶ�����
#define LEN_USERNAME	24		//�ɶ�����	--���ļ���
#define LEN_USERADDR	96		//�ͻ���ַ
#define LEN_POSTCODE	8		//��������
#define LEN_TELN0		16		//�绰����
#define LEN_EMAIL		36		//EMAIL
#define LEN_IDNO		36		//֤������
#define LEN_PASSWORD	24		//�ɶ�����
#define LEN_STOCKCODE	8		//֤ȯ����
#define LEN_STOCKENCODE	16		//֤ȯ����
#define LEN_STOCKNAME	16		//֤ȯ����
#define LEN_MADENUMBER  16      //�ɽ����
#define LEN_ORDERNUMBER	28		//ί�����
#define LEN_CHANNELCODE	144		//��������

#define LEN_ORDERGROUP	12		//ί������
#define LEN_SEAT		8		//ϯλ��
#define LEN_FIRMIT		12		//�����̺�
#define LEN_ORGID		8		//Ӫҵ������
#define LEN_ORGNAME		32		//Ӫҵ������
#define LEN_BANKCODE	8		//���д���
#define LEN_BANKNAME	24		//��������
#define LEN_BANKACCOUNT 24		//�����ʺ�
#define LEN_INFOCODE	8		//��Ϣ���
#define LEN_POSTSTR		32		//��ѯ��λ��
#define LEN_REMARK		16		//��Ҫ˵��
#define LEN_RATION		32		//��Ŵ���
#define LEN_BOARD		8		//���

#define LEN_TACODE		8		//����˾
#define LEN_TANAME		24		//����˾����
#define LEN_OFCODE		8		//�������
#define LEN_OFENCODE	16		//��������
#define LEN_OFNAME		24		//�����������
#define LEN_TAACCOUNT	16		//�����˺�
#define LEN_TRANSACCOUNT	24  //�����˺�
#define LEN_EXTINST			16	//�ⲿ����
#define LEN_APPLYNUMBER		36	//������
#define LEN_PACTCODE		36	//Э�����
#define LEN_BRANCHID		16	//��֧��������
#define LEN_TITLE			64	//�������������
#define LEN_RISKNAME		32	//������������

#define LEN_COMBCODE	16		//��ϴ���
#define LEN_COMBNAME	24		//�������

#define LEN_FUTCODE	16		//�ڻ�Ʒ�ִ���
#define LEN_FUTNAME	23		//�ڻ�Ʒ������

#define LEN_IPOSTOCKNAME	64	//IPO��Ʊ����

#endif


/////////////////////////////////////////////////////////////////////////////////////
/// OpenTD ͨ��Э��
/////////////////////////////////////////////////////////////////////////////////////


enum UTI_TradeFunID
{
	/**
	�˺ŵ�½.
	*/
	ID_TRADE_XYGD	= 1,
	/**
	��ѯ�ɶ�������ױ���.
	*/
	ID_TRADE_GDCX	= 2,
	/**
	�˺��˳�.
	*/
	ID_TRADE_EXIT	= 3,

	/**
	����ί��(֤ȯ).
	*/
	ID_SEC_MMWT		= 100,
	/**
	����ί��(֤ȯ).
	*/
	ID_SEC_CXWT		= 101,
	/**
	���������(֤ȯ).
	*/
	ID_SEC_MAXVOL	= 102,
	/**
	�ʽ��ѯ(֤ȯ).
	*/
	ID_SEC_ZJCX		= 103,
	/**
	�ֲֲ�ѯ(֤ȯ).
	*/
	ID_SEC_CCCX		= 104,
	/**
	ί�в�ѯ(֤ȯ).
	*/
	ID_SEC_WTCX		= 105,
	/**
	�ɳ�����ѯ(֤ȯ).
	*/
	ID_SEC_KCDCX	= 106,
	/**
	�ɽ���ѯ(֤ȯ).
	*/
	ID_SEC_CJCX		= 107,
	/**
	�����ɽ���ѯ(֤ȯ).
	*/
	ID_SEC_SUMZLCJCX= 108,

	/**
	����ί��(�ڻ�).
	*/
	ID_FUT_MMWT		= 200,
	/**
	����ί��(�ڻ�).
	*/
	ID_FUT_CXWT		= 201,
	/**
	���������(�ڻ�).
	*/
	ID_FUT_MAXVOL	= 202,
	/**
	�ʽ��ѯ(�ڻ�).
	*/
	ID_FUT_ZJCX		= 203,
	/**
	�ֲֲ�ѯ(�ڻ�).
	*/
	ID_FUT_CCCX		= 204,
	/**
	ί�в�ѯ(�ڻ�).
	*/
	ID_FUT_WTCX		= 205,
	/**
	�ɳ�����ѯ(�ڻ�).
	*/
	ID_FUT_KCDCX	= 206,
	/**
	�ɽ���ѯ(�ڻ�).
	*/
	ID_FUT_CJCX		= 207,
	/**
	�����ɽ���ѯ(�ڻ�).
	*/
	ID_FUT_SUMZLCJCX= 208,
};

/**
�˻���Ϣ�����ڸ�������ָ��
*/
struct UTI_AccInfo
{
	/**
	����Ӫҵ��
	*/
	char chOrgID[LEN_ORGID];		
	/**
	�ͻ���
	*/
	char chCustomer[LEN_CUSTOM];		
	/**
	�ʽ��˺�
	*/
	char chAccountCode[LEN_ACCOUNT];	
	/**
	����������
	*/
	char chBroker[LEN_BROKER];			
	/**
	�й�����
	*/
	char chBankCode[LEN_BANKCODE];		
	/**
	�Ự�ر�Σ��Ժ��������������,Ҳ�ɵ�����չ������
	*/
	char chSession[LEN_SESSION];		
	/**
	�ͻ�����
	*/
	char chPassword[LEN_PASSWORD];		
};

/**
�ɶ���Ϣ���ױ�����Ϣ
*/
struct UTI_SecuInfo
{
	/**
	�г�����. 
	1 SZ A
	2 SZ B
	3 SH A
	4 SH B
    5 CF 
	6 SP SHFE
	7 SP ZCE
	8 SP DCE
	*/
	int	 nHolderType;
	/**
	����Ӫҵ��
	*/
	char chOrgID[LEN_ORGID];		
	/**
	�ͻ���
	*/
	char chCustomer[LEN_CUSTOM];		
	/**
	�ʽ��˺�
	*/
	char chAccountCode[LEN_ACCOUNT];	
	/**
	�ɶ�����
	*/
	char chUserCode[LEN_USERCODE];		
	/**
	ϯλ��
	*/
	char chSeat[LEN_SEAT];			
};

/**
��ѯ��Ϣ
*/
struct UTI_QueryInfo
{
	/**
	��ѯģʽ,
	<table border="1">
	<tr><td>0</td><td>��ѯ����</td></tr>
	<tr><td>1</td><td>ָ���ɶ�������ױ���</td></tr>
	<tr><td>2</td><td>ָ��֤ȯ������Լ����</td></tr>
	<tr><td>3</td><td>ָ����ͬ��</td></tr>
	<tr><td>4</td><td>ָ������</td></tr>
	</table>
	*/
	int nQryType;				
	/**
	�ɶ�������ױ���
	*/
	char chUserCode[LEN_USERCODE];		
	/**
	�г�����. 
	1 SZ A
	2 SZ B
	3 SH A
	4 SH B
    5 CF 
	6 SP SHFE
	7 SP ZCE
	8 SP DCE
	*/
	int	 nHolderType;
	/**
	֤ȯ������Ǻ�Լ����
	*/
	char chStockCode[LEN_STOCKCODE];	
	/**
	��ͬ��
	*/
	char chOrderNumber[LEN_ORDERNUMBER];

	/**
	��ѯ����0-��ǰ��1-���
	*/
	int	 nQryFlag;						
	/**
	��������
	*/
	int	 nCount;						
	/**
	* ��λ��.
	*/
	char chPostStr[LEN_POSTSTR];
};

/**
����ָ�������ͷ
*/
struct UTI_Trade_ReqHead
{
	/**
	��ͷ����
	*/
	int  				nHeadSize;

	/**
	16�ֽ� ���ܺ�
	*/
	UTI_TradeFunID  	sFunID;	

	/**
	��¼��
	*/
	int  				nItems;	

	/**
	��¼��С
	*/
	int  				nItemSize;

	/**
	��˳�к�
	*/
	int  				nPackOrder;

	/**
	��������YYYYMMDD
	*/
	int  				nReqDate;

	/**
	����ʱ��HHMMSS
	*/
	int  				nReqTime;

	/**
	IP��ַ ��16���Ʊ�ʾ  ����+����+����
	*/
	char				chIPV4[12];	

	/**
	������ַ
	*/
	char				chMacAddr[13];	

	/**
	�˻���Ϣ
	*/
	UTI_AccInfo			accInfo;

};

/**
����ָ��Ӧ���ͷ
*/
struct UTI_Trade_AnsHead
{
	/**
	16�ֽ� ���ܺ�
	*/
	UTI_TradeFunID  	sFunID;		
	/**
	��˳�к�
	*/
	int  				nPackOrder;
	/**
	Ӧ���ʾ��0��ʾ�ɹ�������ʧ��
	*/
	int					nAnsStatus;
	/**
	������Ϣ
	*/
	char				chErrMsg[64];		
	/**
	���ؽ��������
	*/
	int					nResultQrys;		
	/**
	���ؽ����
	*/
	int					nItems[5];
	/**
	���ؽ����С
	*/
	int					nItemSize[5];
};


//���ݰ�ʶ��ͷ
struct UTI_MsgHead
{
	/**
	16�ֽ� ��ʶ��         0x5348
	*/
	unsigned short  	sFlags;		

	/**
	16�ֽ� ��������
	*/
	unsigned short  	sDataType;		          

	/**
	32�ֽ� ���ݳ��ȣ�������ʶ��ͷ��
	*/
	int					nDataLen;	

	/**
	32�ֽ� ʱ�������ȷ������,��ʽHHMMSSmmm��
	*/
	int					nTime;		

	/**
	32�ֽ� ��ˮ�ţ�����������̫��ʱ��Ч��ÿ������˳����룩
	*/
	int     			nOrder;
};

/**
��½
*/
typedef struct UTI_LoginRequest
{
	/**
	Ӫҵ������
	*/
	char chOrgID[8];	
	/**
	�ͻ���
	*/
	char chUserID[16];	

	/**
	�û�����
	*/
	char chPassword[32];	

	/**
	����
	*/
	char chID[8];			

	/**
	����
	*/
	char chMD5[32];			
}UTI_SEC_LoginRequest,UTI_FUT_LoginRequest;


/**
��½Ӧ��
*/
typedef struct UTI_LoginAnswer
{
	/**
	0=��½�ɹ�������ʧ��
	*/ 	
	int  nAnswer;	
	/**
	ʧ����Ϣ
	*/
	char chInfo[64];			//��Ϣ
}UTI_SEC_LoginAnswer,UTI_FUT_LoginAnswer;



#pragma pack(pop)
#endif //__UTIDEFINE_H_
