#pragma once
#include "Resource.h"

// CChildDlgA2 �Ի���

class CChildDlgA2 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA2)

public:
	CChildDlgA2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgA2();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_A2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
