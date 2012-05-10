/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ��ʷ������.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-1		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once


#include "../Include/tdb/HDBApiDefine.h"




/**
 ͨ���˽ӿڲ�ѯ��ʷ���飬��ʷ����������Ҫ���DateBase����֧�֣�TDB����
*/
class AFX_EXT_CLASS CQDBHistorical
{
public:
	CQDBHistorical(void);
	virtual ~CQDBHistorical(void);


	/**
		��ѯ��ʷK������.
		@param	pReq			K�����������.
		@param	dwMilliseconds  �Ⱥ���ʱ��.��Ϊ������Ҫ��TDB�����ϻ�ȡ�������Ҫʱ����еȴ�.
		@param  nItems			��ȡ�ļ�¼��.
		@return                 ����K�����ݼ�¼��Ϊ new  ���䣬ʹ����󣬵����߸�����delete [] ɾ���ڴ�.
								����ʱ������������ʱ������NULL.
	*/
	static 	HDBDefine_KData* QueryKData(HDBDefine_RequestKData* pReq,DWORD dwMilliseconds,int& nItems);



	/**
		��ѯ��ʷTick����.
		@param	pReq			Tick���������.
		@param	dwMilliseconds  �Ⱥ���ʱ��.��Ϊ������Ҫ��TDB�����ϻ�ȡ�������Ҫʱ����еȴ�.
		@param  nItems			��ȡ�ļ�¼��.
		@return                 ����Tick���ݼ�¼��Ϊ new  ���䣬ʹ����󣬵����߸�����delete [] ɾ���ڴ�.
								����ʱ������������ʱ������NULL.
	*/
	static HDBDefine_TickData* QueryTick(HDBDefine_RequestTickData* pReq,DWORD dwMilliseconds,int& nItems);





	/**
		��ѯ��ʷ��ʳɽ�����.
		@param	pReq			Tick��������� (Ҫ�� �� nType = 0).
		@param	dwMilliseconds  �Ⱥ���ʱ��.��Ϊ������Ҫ��TDB�����ϻ�ȡ�������Ҫʱ����еȴ�.
		@param  nItems			��ȡ�ļ�¼��.
		@return                 ������ʳɽ����ݼ�¼��Ϊ new  ���䣬ʹ����󣬵����߸�����delete [] ɾ���ڴ�.
								����ʱ������������ʱ������NULL.
	*/
	static HDBDefine_Transaction* QueryTransaction(HDBDefine_RequestSaveData* pReq,DWORD dwMilliseconds,int& nItems);




	/**
		��ѯί�ж�������.
		@param	pReq			Tick��������� (Ҫ�� �� nType = 1).
		@param	dwMilliseconds  �Ⱥ���ʱ��.��Ϊ������Ҫ��TDB�����ϻ�ȡ�������Ҫʱ����еȴ�.
		@param  nItems			��ȡ�ļ�¼��.
		@return                 �������ί�����ݼ�¼��Ϊ new  ���䣬ʹ����󣬵����߸�����delete [] ɾ���ڴ�.
								����ʱ������������ʱ������NULL.
	*/
	static HDBDefine_OrderQueue* QueryOrderQueue(HDBDefine_RequestSaveData* pReq,DWORD dwMilliseconds,int& nItems);


};
