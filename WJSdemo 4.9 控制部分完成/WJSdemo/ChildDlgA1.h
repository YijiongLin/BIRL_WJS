#pragma once
#include "afxcmn.h"
#include "ChildDlgA11.h"
#include "ChildDlgA12.h"
#include "ChildDlgA13.h"
#include "ChildDlgA14.h"
#include "Resource.h"

// CChildDlgA1 �Ի���

class CChildDlgA1 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA1)

public:
	CChildDlgA1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgA1();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_A1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_taba1;
	CChildDlgA11 m_ChildDlgA11;
	CChildDlgA12 m_ChildDlgA12;
	CChildDlgA13 m_ChildDlgA13;
	CChildDlgA14 m_ChildDlgA14;

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
