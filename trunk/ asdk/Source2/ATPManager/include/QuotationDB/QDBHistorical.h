/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 历史行情类.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/

#pragma once


#include "../Include/tdb/HDBApiDefine.h"




/**
 通过此接口查询历史行情，历史行情数据需要宏汇DateBase服务支持（TDB）。
*/
class AFX_EXT_CLASS CQDBHistorical
{
public:
	CQDBHistorical(void);
	virtual ~CQDBHistorical(void);


	/**
		查询历史K线数据.
		@param	pReq			K线数据请求包.
		@param	dwMilliseconds  等候的最长时间.因为数据需要从TDB服务上获取，因此需要时间进行等待.
		@param  nItems			获取的记录数.
		@return                 返回K线数据记录，为 new  分配，使用完后，调用者负责用delete [] 删除内存.
								当超时，或者无数据时，返回NULL.
	*/
	static 	HDBDefine_KData* QueryKData(HDBDefine_RequestKData* pReq,DWORD dwMilliseconds,int& nItems);



	/**
		查询历史Tick数据.
		@param	pReq			Tick数据请求包.
		@param	dwMilliseconds  等候的最长时间.因为数据需要从TDB服务上获取，因此需要时间进行等待.
		@param  nItems			获取的记录数.
		@return                 返回Tick数据记录，为 new  分配，使用完后，调用者负责用delete [] 删除内存.
								当超时，或者无数据时，返回NULL.
	*/
	static HDBDefine_TickData* QueryTick(HDBDefine_RequestTickData* pReq,DWORD dwMilliseconds,int& nItems);





	/**
		查询历史逐笔成交数据.
		@param	pReq			Tick数据请求包 (要求 其 nType = 0).
		@param	dwMilliseconds  等候的最长时间.因为数据需要从TDB服务上获取，因此需要时间进行等待.
		@param  nItems			获取的记录数.
		@return                 返回逐笔成交数据记录，为 new  分配，使用完后，调用者负责用delete [] 删除内存.
								当超时，或者无数据时，返回NULL.
	*/
	static HDBDefine_Transaction* QueryTransaction(HDBDefine_RequestSaveData* pReq,DWORD dwMilliseconds,int& nItems);




	/**
		查询委托队列数据.
		@param	pReq			Tick数据请求包 (要求 其 nType = 1).
		@param	dwMilliseconds  等候的最长时间.因为数据需要从TDB服务上获取，因此需要时间进行等待.
		@param  nItems			获取的记录数.
		@return                 返回逐笔委托数据记录，为 new  分配，使用完后，调用者负责用delete [] 删除内存.
								当超时，或者无数据时，返回NULL.
	*/
	static HDBDefine_OrderQueue* QueryOrderQueue(HDBDefine_RequestSaveData* pReq,DWORD dwMilliseconds,int& nItems);


};
