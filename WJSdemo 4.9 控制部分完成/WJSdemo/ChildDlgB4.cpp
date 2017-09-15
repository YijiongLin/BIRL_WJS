// ChildDlgB4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WJSdemo.h"
#include "ChildDlgB4.h"
#include "afxdialogex.h"
#include "WJSdemoDlg.h"


// CChildDlgB4 �Ի���

IMPLEMENT_DYNAMIC(CChildDlgB4, CDialogEx)

CChildDlgB4::CChildDlgB4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChildDlgB4::IDD, pParent)
	//, m_ConnectAdressInput(NULL)
	, m_ConnectAdressInput(_T(""))
{

}

CChildDlgB4::~CChildDlgB4()
{
}

void CChildDlgB4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_connectlistbox);
	DDX_Text(pDX, IDC_EDIT_CONNECTADRESS, m_ConnectAdressInput);
}


BEGIN_MESSAGE_MAP(CChildDlgB4, CDialogEx)
	ON_BN_CLICKED(IDC_DISCONNECT, &CChildDlgB4::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_CONNECT, &CChildDlgB4::OnBnClickedConnect)
	ON_MESSAGE(CNCCONNECTRESULT, CChildDlgB4::CNCConnectResultFunc)
END_MESSAGE_MAP()


// CChildDlgB4 ��Ϣ�������

BOOL CChildDlgB4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HBITMAP hBmp1 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_CONNECT));
	((CButton *)GetDlgItem(IDC_CONNECT))->SetBitmap(hBmp1);

	HBITMAP hBmp2 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_SCAN));
	((CButton *)GetDlgItem(IDC_SCAN))->SetBitmap(hBmp2);

	HBITMAP hBmp3 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_DISCONNECT));
	((CButton *)GetDlgItem(IDC_DISCONNECT))->SetBitmap(hBmp3);

	SetWindowText(_T("����"));

	GetDlgItem(IDC_EDIT_LOCALIP)->SetWindowText(_T("192.168.3.1"));
	SetDlgItemText(IDC_EDIT_CONNECTSTATE, _T("�Ͽ�/δ����"));
	//m_connectlistbox.AddString(_T("192.168.3.12"));        // ���б���β����ַ��� 
	//m_connectlistbox.AddString(_T("192.168.3.24"));        // ���б���β����ַ���  
	//m_connectlistbox.AddString(_T("192.168.3.30"));        // ���б���β����ַ���   

	return TRUE;
}

void CChildDlgB4::OnBnClickedDisconnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CChildDlgB4::OnBnClickedConnect()
{
	SetDlgItemText(IDC_EDIT_CONNECTSTATE, _T("������"));
	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB2)->m_hWnd, NULL, NULL, _T("�ֶ�"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	UpdateData(TRUE);

	UpdateData(FALSE);
	int len = WideCharToMultiByte(CP_ACP, 0, m_ConnectAdressInput, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_ConnectAdress = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_ConnectAdressInput, -1, m_ConnectAdress, len, NULL, NULL);
	FromHandle(hWnd)->SendMessage(CNCCONNECT, (WPARAM)m_ConnectAdress, 0);//
}

LRESULT CChildDlgB4::CNCConnectResultFunc(WPARAM a, LPARAM b){

	int result = (int)a;
	if (result == 1){
		SetDlgItemText(IDC_EDIT_CONNECTSTATE, _T("����ʧ��"));

	}
	else{
		SetDlgItemText(IDC_EDIT_CONNECTSTATE, _T("���ӳɹ�"));
		SetDlgItemText(IDC_EDIT_CONNECTADRESS, _T("192.168.3.99"));

	}
	return 0;
}