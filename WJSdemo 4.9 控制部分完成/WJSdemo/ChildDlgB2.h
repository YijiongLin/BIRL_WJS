#pragma once
#include "Resource.h"
#include "afxcmn.h"
#include "ReadTXTData.h"

// CChildDlgB2 �Ի���
struct Speed{
	double m_noncutspeed;
	double m_cutspeed;
};
class CChildDlgB2 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgB2)

public:
	CChildDlgB2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgB2();

// �Ի�������
	enum { IDD = IDD_CHILDDLG_B2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedVisualsimulationBtn();
	//Speed1 �����ٶ�
	double m_speed1;
	//Speed2 ʵ���ٶ�
	double m_speed2;
//	CSliderCtrl m_sliderNonCuttingRate;
//	CSliderCtrl m_slidernoncuttingrate;
	afx_msg void OnNMCustomdrawSliderNoncuttingrate(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderNonCuttingRate;
	CSliderCtrl m_SliderFeedRate;
	afx_msg void OnNMCustomdrawSliderFeedrate(NMHDR *pNMHDR, LRESULT *pResult);
	CReadTXTData ReadTXTData;
	Speed CNCSpeed;
	afx_msg void OnBnClickedBtnDynamicsimulation();
	bool B2ReadTXTData(float **b, char* cwd);
	void StartErrorWarning();
	afx_msg void OnBnClickedBtnProcess();
};
