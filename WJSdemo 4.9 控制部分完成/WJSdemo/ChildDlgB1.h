#pragma once
#include "Resource.h"
#include "afxwin.h"

// CChildDlgB1 �Ի���

class CChildDlgB1 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgB1)

public:
	CChildDlgB1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgB1();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_B1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenfileStaticdraw();
	afx_msg void OnBnClickedCleardxfdata();
	CEdit m_EdiitFilePath;

	//��ȡDlg�д�DXF�ļ���·������ʾ�ڱ༭��
	afx_msg LRESULT GetFilePathAndShow(WPARAM wparam, LPARAM lparam);

	//����������߳���
//	double m_leadline_length;
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtConfiguration();
	afx_msg void OnBnClickedBtnContourextraction();
};
