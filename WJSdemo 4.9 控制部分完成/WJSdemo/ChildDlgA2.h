#pragma once
#include "Resource.h"

// CChildDlgA2 对话框

class CChildDlgA2 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA2)

public:
	CChildDlgA2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChildDlgA2();

// 对话框数据
	enum { IDD = IDD_CHILDDLG_A2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
