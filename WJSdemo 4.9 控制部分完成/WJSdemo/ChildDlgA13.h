#pragma once
#include "Resource.h"

// CChildDlgA13 �Ի���

class CChildDlgA13 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA13)

public:
	CChildDlgA13(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgA13();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_A13 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
