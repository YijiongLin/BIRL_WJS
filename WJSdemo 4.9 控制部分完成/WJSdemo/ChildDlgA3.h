#pragma once
#include "Resource.h"

// CChildDlgA3 �Ի���

class CChildDlgA3 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA3)

public:
	CChildDlgA3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgA3();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_A3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
