#ifndef RegistryUtil_h__
#define RegistryUtil_h__
#include <atlstr.h>

//************************************
// Method:    QuerySysRegKeyValueToString
// FullName:  QuerySysRegKeyValueToString
// Access:    public 
// Returns:   CString
// Description:��ע����ж�ȡ�ַ���
// Parameter: CString strKeyName     ע�������
// Parameter: CString strValueName  ��ֵ��
// Parameter: CString strDefValue      Ĭ��ֵ
//************************************
CString QuerySysRegKeyValueToString(CString strKeyName, CString strValueName,CString strDefValue = _T(""));

//************************************
// Method:    QuerySysRegKeyValueToDWORD
// FullName:  QuerySysRegKeyValueToDWORD
// Access:    public 
// Returns:   DWORD
// Description:��ע����ж�ȡ����
// Parameter: CString strKeyName	ע�������
// Parameter: CString strValueName ��ֵ��
// Parameter: DWORD dwDefValue   Ĭ��ֵ
//************************************
DWORD QuerySysRegKeyValueToDWORD(CString strKeyName, CString strValueName,DWORD dwDefValue = 0);

//************************************
// Method:    SetSysRegKeyValue
// FullName:  SetSysRegKeyValue
// Access:    public 
// Returns:   BOOL
// Description:���ַ���д�뵽ע����
// Parameter: CString strKeyName     ע�������
// Parameter: CString strValueName  ��ֵ��
// Parameter: CString strValue           Ҫд����ַ���
//************************************
BOOL SetSysRegKeyValue(CString strKeyName, CString strValueName,CString strValue);

//************************************
// Method:    SetSysRegKeyValue
// FullName:  SetSysRegKeyValue
// Access:    public 
// Returns:   BOOL
// Description:����ֵд�뵽ע�����
// Parameter: CString strKeyName	 ע�������
// Parameter: CString strValueName  ��ֵ��
// Parameter: DWORD dwDValue		  Ҫд�����ֵ
//************************************
BOOL SetSysRegKeyValue(CString strKeyName, CString strValueName,DWORD dwDValue);


#endif // RegistryUtil_h__
