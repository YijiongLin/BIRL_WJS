#pragma once
#include "Resource.h"

// CChildDlgA14 �Ի���

class CChildDlgA14 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA14)

public:
	CChildDlgA14(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgA14();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_A14 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
