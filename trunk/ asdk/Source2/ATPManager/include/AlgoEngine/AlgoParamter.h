/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨������
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-2		��ΰ		 ����
-------------------------------------------------------------
*/


#pragma once




/**
�㷨������
Ӧ�������Ա
@See m_nParamType
������ʵ�ʵ�����.
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
		����.
		*/
		AP_TYPE_INT,

		/** 
		������.
		*/
		AP_TYPE_DOUBLE,

		/**
		INT64.
		*/
		AP_TYPE_INT64,

		/**
		�ַ���.
		*/
		AP_TYPE_STRING,

		/**
		��ѡ�����������Ժ�����ѡ�����ʹ��.
		*/
		AP_TYPE_OPTIONAL
	};

	/**
	*   ��������	
	*/
	CString m_szParamName;


	/**
	* ������������Ϣ
	*/
	CString m_szParamDescription;

	/**
	��������
	@See AP_TYPE
	*/
	int	 m_nParamType;

	/**
	��������ֵ
	*/
	virtual int GetIntVal(){return 0;}

	/**
	����Int64ֵ
	*/
	virtual INT64 GetInt64Val(){return 0;}

	/**
	�����ַ���ֵ
	*/
	virtual CString GetStringVal(){return "";}
	
	/**
	�Ƿ���Ч
	@param strReason	��Ϊ�Ƿ�ʱ�����طǷ�ԭ��.
	@return				���ز����Ƿ�Ϸ�.
	*/
	virtual bool IsValid(CString& strReason){return true;}


	/**
	��ӿ�ѡ��
	@param	strOptional ��ѡ��
	@return ����ɹ������ؿ�ѡ���ֵ�����򣬷���-1.
	*/
	virtual int AddOptional(CString strOptional){return -1;}


public:
	/**
	������ֵ
	@param nVal ֵ
	*/
	virtual void SetValue(int nVal){}

	/**
	������ֵ
	@param iVal ֵ
	*/
	virtual void SetValue(INT64 iVal){}

	/**
	������ֵ
	@param dVal ֵ
	*/
	virtual void SetValue(double dVal){}

	/**
	������ֵ
	@param strVal ֵ
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