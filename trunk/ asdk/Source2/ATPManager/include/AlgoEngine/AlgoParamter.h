/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法参数类
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-2		李伟		 创建
-------------------------------------------------------------
*/


#pragma once




/**
算法参数类
应根据其成员
@See m_nParamType
来决定实际的类型.
*/
class AFX_EXT_CLASS CAlgoParamter
{
public:
	CAlgoParamter(void);
	virtual ~CAlgoParamter(void);

	CAlgoParamter& operator==(CAlgoParamter& apRight);

	enum AP_TYPE
	{
		/**
		整型.
		*/
		AP_TYPE_INT,

		/** 
		浮点数.
		*/
		AP_TYPE_DOUBLE,

		/**
		INT64.
		*/
		AP_TYPE_INT64,

		/**
		字符串.
		*/
		AP_TYPE_STRING,

		/**
		可选项，仅该先项可以和上面选项组合使用.
		*/
		AP_TYPE_OPTIONAL
	};

	/**
	*   参数名称	
	*/
	CString m_szParamName;


	/**
	* 参数的描述信息
	*/
	CString m_szParamDescription;

	/**
	参数类型
	@See AP_TYPE
	*/
	int	 m_nParamType;

	/**
	返回整型值
	*/
	virtual int GetIntVal(){return 0;}

	/**
	返回Int64值
	*/
	virtual INT64 GetInt64Val(){return 0;}

	/**
	返回字符串值
	*/
	virtual CString GetStringVal(){return "";}
	
	/**
	是否有效
	@param strReason	当为非法时，返回非法原因.
	@return				返回参数是否合法.
	*/
	virtual bool IsValid(CString& strReason){return true;}


	/**
	添加可选项
	@param	strOptional 可选项
	@return 如果成功，返回可选项的值，否则，返因-1.
	*/
	virtual int AddOptional(CString strOptional){return -1;}


public:
	/**
	设置其值
	@param nVal 值
	*/
	virtual void SetValue(int nVal){}

	/**
	设置其值
	@param iVal 值
	*/
	virtual void SetValue(INT64 iVal){}

	/**
	设置其值
	@param dVal 值
	*/
	virtual void SetValue(double dVal){}

	/**
	设置其值
	@param strVal 值
	*/
	virtual void SetValue(CString strVal){}
};



class AFX_EXT_CLASS CAlgoParamter_Int
	:public CAlgoParamter
{
public:

	CAlgoParamter_Int& operator==(CAlgoParamter_Int& apRight);

	virtual int GetIntVal(){return m_nVal;}

public:
	int  m_nVal;
};


class AFX_EXT_CLASS CAlgoParamter_Int64
	:public CAlgoParamter
{
public:

	CAlgoParamter_Int64& operator==(CAlgoParamter_Int64& apRight);

	virtual INT64 GetInt64Val(){return m_i64Val;}

public:
	INT64  m_i64Val;
};


class AFX_EXT_CLASS CAlgoParamter_Double
	:public CAlgoParamter
{
public:

	CAlgoParamter_Double& operator==(CAlgoParamter_Double& apRight);

	virtual double GetDoubleVal(){return m_dVal;}

public:
	double  m_dVal;
};


class AFX_EXT_CLASS CAlgoParamter_Optional
	:public CAlgoParamter,public vector<CString>
{
public:
	CString GetString(int nIndex)
	{
		if(nIndex>=0 && nIndex<size())
			return (*this)[nIndex];
		else 
			return "";
	}

	virtual int GetIntVal()
	{
		return m_nSelect;
	}

	virtual CString GetStringVal()
	{
		return GetString(GetIntVal());
	}

	virtual void SetValue(int nVal)
	{
		m_nSelect = nVal;
	}
protected:
	int m_nSelect;
};