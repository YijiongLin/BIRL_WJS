#pragma once
#include "Resource.h"

// CChildDlgA12 �Ի���

class CChildDlgA12 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA12)

public:
	CChildDlgA12(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgA12();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_A11 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
