// ChildDlgB1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WJSdemo.h"
#include "ChildDlgB1.h"
#include "afxdialogex.h"
#include "WJSdemoDlg.h"
#include "Configuration.h"


// CChildDlgB1 �Ի���

IMPLEMENT_DYNAMIC(CChildDlgB1, CDialogEx)

CChildDlgB1::CChildDlgB1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChildDlgB1::IDD, pParent)
	//, m_leadline_length(0)
{

}

CChildDlgB1::~CChildDlgB1()
{
}

void CChildDlgB1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_EdiitFilePath);
	//  DDX_Text(pDX, IDC_LEADLINE_LENGTH, m_leadline_length);
}


BEGIN_MESSAGE_MAP(CChildDlgB1, CDialogEx)
	ON_BN_CLICKED(IDC_OPENFILE_STATICDRAW, &CChildDlgB1::OnBnClickedOpenfileStaticdraw)
	ON_BN_CLICKED(IDC_CLEARDXFDATA, &CChildDlgB1::OnBnClickedCleardxfdata)
	ON_MESSAGE(GET_FILEPATH, &CChildDlgB1::GetFilePathAndShow)

	ON_BN_CLICKED(IDC_BT_CONFIGURATION, &CChildDlgB1::OnBnClickedBtConfiguration)
	ON_BN_CLICKED(IDC_BTN_CONTOUREXTRACTION, &CChildDlgB1::OnBnClickedBtnContourextraction)
END_MESSAGE_MAP()


// CChildDlgB1 ��Ϣ�������
BOOL CChildDlgB1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HBITMAP hBmp1 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_OPENDXF));
	((CButton *)GetDlgItem(IDC_OPENFILE_STATICDRAW))->SetBitmap(hBmp1);

	HBITMAP hBmp2 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_CLEAR));
	((CButton *)GetDlgItem(IDC_CLEARDXFDATA))->SetBitmap(hBmp2);

	HBITMAP hBmp3 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_STOCKLAYOUT));
	((CButton *)GetDlgItem(IDC_BTN_STOCKLAYOUT))->SetBitmap(hBmp3);

	HBITMAP hBmp4 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_CONTOUREXTRACTION));
	((CButton *)GetDlgItem(IDC_BTN_CONTOUREXTRACTION))->SetBitmap(hBmp4);

	SetWindowText(_T("�ļ�����"));

	return TRUE;
}

void CChildDlgB1::OnBnClickedOpenfileStaticdraw()
{
	//CWnd* pWnd = GetDlgItem(IDD_NESTDXFDATAFORCUT_DIALOG);
	//HWND hWnd = pWnd->GetSafeHwnd();
	if (CNCRunModeInf.StopRunning == true){
	DeleteFile(_T("123Ƕ�׷�ջ�.txt"));

	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	//HWND hWnd = ::FindWindowEx(m_hWnd, NULL, NULL, _T("���̻߳�ͼ/����ͷ�ڵ�"));//���һ��ΪNULL���ԣ���Ϊ�����ڵ�Dlg�ı��⣬this->GetParent()->m_hWndΪ�����ֱ�
	//hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	//hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	FromHandle(hWnd)->SendMessage(PROCEEDDXFDATA, 0, 0);
	}
	else 	MessageBox(_T("����ֹͣĿǰ���е�ģʽ"));

}


void CChildDlgB1::OnBnClickedCleardxfdata()
{
	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	FromHandle(hWnd)->SendMessage(CLEARDXFDATA, 0, 0);
}

LRESULT CChildDlgB1::GetFilePathAndShow(WPARAM wparam, LPARAM lparam)  //��Ϣ����������������Dlg�򿪵�DXF·������ʾ
{
	char *pChar = (char*)wparam;
	int charLen = strlen(pChar); //����pChar��ָ����ַ�����С�����ֽ�Ϊ��λ��һ������ռ�����ֽ�  
	int len = MultiByteToWideChar(CP_ACP, 0, pChar, charLen, NULL, 0); //������ֽ��ַ��Ĵ�С�����ַ�����  
	wchar_t *pWChar = new wchar_t[len + 1]; //Ϊ���ֽ��ַ�������ռ䣬  
	MultiByteToWideChar(CP_ACP, 0, pChar, charLen, pWChar, len); //���ֽڱ���ת���ɿ��ֽڱ���  
	pWChar[len] = '\0';

	//��wchar_t����ת��ΪCString  
	CString str;
	str.Append(pWChar);

	delete[] pChar;
	delete[] pWChar;
	SetDlgItemText(IDC_EDIT_FILEPATH, str);
	return 0;
}

//void CChildDlgB1::OnBnClickedButton1()
//{
//	UpdateData(TRUE);
//	m_LeadingLineLength = m_leadline_length;
//	UpdateData(FALSE);
//	if (m_LeadingLineLength == 0){
//		MessageBox(_T("�������������и������߳���"));
//	}
//	else{
//
//	}
//
//}


void CChildDlgB1::OnBnClickedBtConfiguration()
{
	CConfiguration ConfigDlg;
	ConfigDlg.DoModal();
}


void CChildDlgB1::OnBnClickedBtnContourextraction()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
