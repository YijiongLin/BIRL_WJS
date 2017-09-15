// ChildDlgA1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WJSdemo.h"
#include "ChildDlgA1.h"
#include "afxdialogex.h"
#include "WJSdemoDlg.h"


// CChildDlgA1 �Ի���

IMPLEMENT_DYNAMIC(CChildDlgA1, CDialogEx)

CChildDlgA1::CChildDlgA1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChildDlgA1::IDD, pParent)
{

}

CChildDlgA1::~CChildDlgA1()
{
}

void CChildDlgA1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_taba1);
}


BEGIN_MESSAGE_MAP(CChildDlgA1, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CChildDlgA1::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CChildDlgA1 ��Ϣ�������
BOOL CChildDlgA1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�


	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   
	SetWindowText(_T("λ��"));

	m_taba1.InsertItem(0, _T("����"));  // ����A���һ����ǩ�����桱  
	m_taba1.InsertItem(1, _T("����"));  // ����A��ڶ�����ǩ������   
	m_taba1.InsertItem(2, _T("��Ϣ"));  // ����A��ڶ�����ǩ����Ϣ��  
	m_taba1.InsertItem(3, _T("�趨"));  // ����A����ĸ���ǩ���趨��   

	m_ChildDlgA11.Create(IDD_CHILDDLG_A11, &m_taba1);    // ����A���һ����ǩҳ��m_ChildDlgA1Ϊ�Ի���������ͨ���ö�����Ե���Create������������ǩҳ����һ������Ϊ�Ի���ID���ڶ���ΪTab�ؼ��Ĺ���������
	m_ChildDlgA12.Create(IDD_CHILDDLG_A12, &m_taba1); // ����A��ڶ�����ǩҳ  
	m_ChildDlgA13.Create(IDD_CHILDDLG_A13, &m_taba1); // ����A���������ǩҳ  
	m_ChildDlgA14.Create(IDD_CHILDDLG_A14, &m_taba1); // ����A����ĸ���ǩҳ  


	m_taba1.GetClientRect(&tabRect); // ��ȡ��ǩ�ؼ��ͻ�����СRect��������tabRect�С�
	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	// ���ݵ����õ�tabRect����m_ChildDlgA1�ӶԻ��򣬲�����Ϊ��ʾ   
	m_ChildDlgA11.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// m_ChildDlgA2�ӶԻ�����Ϊ����   
	m_ChildDlgA12.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	//m_ChildDlgA3�ӶԻ�������Ϊ����   
	m_ChildDlgA13.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	//m_ChildDlgA4�ӶԻ�������Ϊ����   
	m_ChildDlgA14.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CChildDlgA1::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here   
	*pResult = 0;
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	m_taba1.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_taba1.GetCurSel())//����TabControl��ǩ�ؼ��ĵ�ǰѡ������ʾ��ǩҳ
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ��λ�á�������ʾm_ChildDlgA1�Ի�����������Ի���   
	case 0:
	{m_ChildDlgA11.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	m_ChildDlgA12.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_ChildDlgA13.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_ChildDlgA14.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	FromHandle(hWnd)->SendMessage(TABA1GLFLUSH, 0, 0);//

	break; }
	case 1:
		m_ChildDlgA11.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA12.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_ChildDlgA13.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA14.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 2:
		m_ChildDlgA11.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA12.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA13.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_ChildDlgA14.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 3:
		m_ChildDlgA11.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA12.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA13.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA14.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
}
