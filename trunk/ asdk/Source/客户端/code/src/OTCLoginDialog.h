#pragma once
#include "OTCBaseObject.h"
#include "afxwin.h"


#define  USERNAME_MAXLENGTH  16 //�û�������󳤶�Ϊ16λ

// COTCLoginDialog �Ի���

class COTCLoginDialog : public CDialog,COTCBaseObject
{
	DECLARE_DYNAMIC(COTCLoginDialog)

public:
	COTCLoginDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COTCLoginDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

protected:
	//���ض������
	virtual void LoadMultiLanguage(void);

public:
	afx_msg void OnBnClickedButtonAppsetting();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLoginCancel();

	//������֤ʱ�����û����õ�¼����Ŀؼ�
	void EnableLoginCtrl(BOOL bEnable);

private:
	// �����ַ�б�
	CComboBox m_CombServerList;
	//�ͻ���
	CEdit m_editAccount;
	//��¼����
	CEdit m_editPassword;

public:
	CButton m_checkSaveAccount;
	CButton m_checkSavePassword;
	afx_msg void OnBnClickedCheckSaveAccount();
	afx_msg void OnBnClickedCheckSavePassword();
};
