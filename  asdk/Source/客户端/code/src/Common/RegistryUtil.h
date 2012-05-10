#ifndef RegistryUtil_h__
#define RegistryUtil_h__
#include <atlstr.h>

//************************************
// Method:    QuerySysRegKeyValueToString
// FullName:  QuerySysRegKeyValueToString
// Access:    public 
// Returns:   CString
// Description:从注册表中读取字符串
// Parameter: CString strKeyName     注册表项名
// Parameter: CString strValueName  键值名
// Parameter: CString strDefValue      默认值
//************************************
CString QuerySysRegKeyValueToString(CString strKeyName, CString strValueName,CString strDefValue = _T(""));

//************************************
// Method:    QuerySysRegKeyValueToDWORD
// FullName:  QuerySysRegKeyValueToDWORD
// Access:    public 
// Returns:   DWORD
// Description:从注册表中读取数字
// Parameter: CString strKeyName	注册表项名
// Parameter: CString strValueName 键值名
// Parameter: DWORD dwDefValue   默认值
//************************************
DWORD QuerySysRegKeyValueToDWORD(CString strKeyName, CString strValueName,DWORD dwDefValue = 0);

//************************************
// Method:    SetSysRegKeyValue
// FullName:  SetSysRegKeyValue
// Access:    public 
// Returns:   BOOL
// Description:将字符串写入到注册中
// Parameter: CString strKeyName     注册表项名
// Parameter: CString strValueName  键值名
// Parameter: CString strValue           要写入的字符串
//************************************
BOOL SetSysRegKeyValue(CString strKeyName, CString strValueName,CString strValue);

//************************************
// Method:    SetSysRegKeyValue
// FullName:  SetSysRegKeyValue
// Access:    public 
// Returns:   BOOL
// Description:将数值写入到注册表中
// Parameter: CString strKeyName	 注册表项名
// Parameter: CString strValueName  键值名
// Parameter: DWORD dwDValue		  要写入的数值
//************************************
BOOL SetSysRegKeyValue(CString strKeyName, CString strValueName,DWORD dwDValue);


#endif // RegistryUtil_h__
