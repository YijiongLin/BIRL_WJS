#pragma once
#include "afxwin.h"


// CConfiguration �Ի���
class CConfiguration : public CDialogEx
{
	DECLARE_DYNAMIC(CConfiguration)

public:
	CConfiguration(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfiguration();

// �Ի�������
	enum { IDD = IDD_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	double m_LeadLineLength_input;
	afx_msg void OnBnClickedSetConfiguration();
	CButton m_LeadLineSetting;
	virtual BOOL OnInitDialog();
	static  UINT SetWaterJetConfigThread(LPVOID lParam);//�������ö��߳�
	void SetWaterJetConfig();
};
