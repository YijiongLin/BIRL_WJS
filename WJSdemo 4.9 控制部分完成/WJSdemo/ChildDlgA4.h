#pragma once
#include "Resource.h"

// CChildDlgA4 �Ի���

class CChildDlgA4 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA4)

public:
	CChildDlgA4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgA4();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_A4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
