
// WJSdemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WJSdemo.h"
#include "WJSdemoDlg.h"
#include "afxdialogex.h"
#include "io.h" 
#include "fcntl.h"
#include"stdio.h"
#include"afxdlgs.h"//for open file
#include "iostream"
#include "fstream"
#include "string"
#include "sstream"
#include "ostream"
#include "ChildDlgB1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
using namespace std;

////��ʼģʽ����ͼ���ֶ����Զ����Զ�������
//StartMode WJAutoStartMode = m_VisualSimulation;
////ȫ�ֱ�����ֹͣ�ź�
//struct StopSignal stopsignal = {false,false,false};
////ȫ�ֱ�������ͣ������źš���ʱ�����������кͿ������е���ͣ�źźϲ�����Ϊ�����Ϊͬһ��
//struct PauseSignal pausesignal = { true, true, true };

//struct RunModeInf{
//	StartMode RunMode;
//	bool StopRunning;
//	bool ContinueRunning;
//
//};
struct RunModeInf CNCRunModeInf = { m_non, true, true };
//ȫ�ֱ���������̬��ͼ�ж���
bool m_staticdraw = true;
bool m_FirstLeadingLineLengthSetting = true;

//ȫ�ֱ����������и�����������
struct CoordinateStruct BaseframeData = {0,0,0};
struct CoordinateStruct BaseframeOrigin = { 0, 0, 0 };
struct CoordinateStruct CNC_Pos_Origin = { 0, 0, 0 };
struct CoordinateStruct CNC_Pos = { 0, 0, 0 };

//�и�����������
m_LeadLineType LeadlineType=LL_NoType;
//ȫ�ֱ����������и������߳���
double m_LeadingLineLength = 0;

//ȫ�֣�DO��Ϣ
struct DOStates CNC_DO_States = { false, false, false, false, false,false };
enum DO_Num CNC_DO_Num = { DO64 };


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWJSdemoDlg �Ի���



CWJSdemoDlg::CWJSdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWJSdemoDlg::IDD, pParent)//���캯��
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWJSdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_taba);
	DDX_Control(pDX, IDC_TAB2, m_tabb);
}

BEGIN_MESSAGE_MAP(CWJSdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CWJSdemoDlg::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CWJSdemoDlg::OnTcnSelchangeTab2)
	ON_MESSAGE(PROCEEDDXFDATA, CWJSdemoDlg::ProceedDXFData)
	ON_MESSAGE(UPDATE_CNCPOSITION, CWJSdemoDlg::GetCNCPositionData)

	ON_BN_CLICKED(IDC_PAUSEORCONTINUE, &CWJSdemoDlg::OnBnClickedPauseorcontinue)
	ON_BN_CLICKED(IDC_STOP, &CWJSdemoDlg::OnBnClickedStop)
//	ON_BN_CLICKED(IDC_RADIO2, &CWJSdemoDlg::OnBnClickedRadio2)
ON_BN_CLICKED(IDC_BTN_GASVALVE, &CWJSdemoDlg::OnBnClickedBtnGasvalve)
ON_BN_CLICKED(IDC_BTN_WATERVALVE, &CWJSdemoDlg::OnBnClickedBtnWatervalve)
ON_BN_CLICKED(IDC_BTN_WATERPUMP, &CWJSdemoDlg::OnBnClickedBtnWaterpump)
ON_BN_CLICKED(IDC_BTN_SANDVALVE, &CWJSdemoDlg::OnBnClickedBtnSandvalve)
ON_BN_CLICKED(IDC_BTN_MAINPUMP, &CWJSdemoDlg::OnBnClickedBtnMainpump)
ON_MESSAGE(GETDOSTATES, CWJSdemoDlg::getDOStatesFunc)//��ȡDO����Ϣ
ON_MESSAGE(UPDATE_BASE_ORIGIN, CWJSdemoDlg::updateBaseOriginFunc)
END_MESSAGE_MAP()


// CWJSdemoDlg ��Ϣ�������

BOOL CWJSdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	

	SetWindowText(_T("����ѹˮ�����и����ܿ������"));
	CRect tabaRect, tabbRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   

	m_taba.InsertItem(0, _T("λ��"));  // ����A���һ����ǩ��λ�á�  
	m_taba.InsertItem(1, _T("����"));  // ����A��ڶ�����ǩ������   
	m_taba.InsertItem(2, _T("����"));  // ����A��ڶ�����ǩ��������  
	m_taba.InsertItem(3, _T("���"));  // ����A����ĸ���ǩ����ϡ� 

	m_tabb.InsertItem(0, _T("�ļ�����"));  // ����B���һ����ǩ��λ�á�  
	m_tabb.InsertItem(1, _T("�Զ�"));  // ����B��ڶ�����ǩ������   
	m_tabb.InsertItem(2, _T("�ֶ�"));  // ����B��ڶ�����ǩ��������  
	m_tabb.InsertItem(3, _T("����"));  // ����B��ڶ�����ǩ��������  

	m_ChildDlgA1.Create(IDD_CHILDDLG_A1, &m_taba);    // ����A���һ����ǩҳ��m_ChildDlgA1Ϊ�Ի���������ͨ���ö�����Ե���Create������������ǩҳ����һ������Ϊ�Ի���ID���ڶ���ΪTab�ؼ��Ĺ���������
	m_ChildDlgA2.Create(IDD_CHILDDLG_A2, &m_taba); // ����A��ڶ�����ǩҳ  
	m_ChildDlgA3.Create(IDD_CHILDDLG_A3, &m_taba); // ����A���������ǩҳ  
	m_ChildDlgA4.Create(IDD_CHILDDLG_A4, &m_taba); // ����A����ĸ���ǩҳ  
	m_ChildDlgB1.Create(IDD_CHILDDLG_B1, &m_tabb);    // ����B���һ����ǩҳ��m_ChildDlgB1Ϊ�Ի���������ͨ���ö�����Ե���Create������������ǩҳ����һ������Ϊ�Ի���ID���ڶ���ΪTab�ؼ��Ĺ���������
	m_ChildDlgB2.Create(IDD_CHILDDLG_B2, &m_tabb); // ����B��ڶ�����ǩҳ  
	m_ChildDlgB3.Create(IDD_CHILDDLG_B3, &m_tabb); // ����B���������ǩҳ  
	m_ChildDlgB4.Create(IDD_CHILDDLG_B4, &m_tabb); // ����B���������ǩҳ  


	m_taba.GetClientRect(&tabaRect); // ��ȡ��ǩ�ؼ��ͻ�����СRect��������tabRect�С�
	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	tabaRect.left += 1;
	tabaRect.right -= 1;
	tabaRect.top += 25;
	tabaRect.bottom -= 1;
	// ���ݵ����õ� tabaRect����m_ChildDlgA1�ӶԻ��򣬲�����Ϊ��ʾ   
	m_ChildDlgA1.SetWindowPos(NULL, tabaRect.left, tabaRect.top, tabaRect.Width(), tabaRect.Height(), SWP_SHOWWINDOW);
	// m_ChildDlgA2�ӶԻ�����Ϊ����   
	m_ChildDlgA2.SetWindowPos(NULL,  tabaRect.left,  tabaRect.top,  tabaRect.Width(),  tabaRect.Height(), SWP_HIDEWINDOW);
	//m_ChildDlgA3�ӶԻ�������Ϊ����   
	m_ChildDlgA3.SetWindowPos(NULL,  tabaRect.left,  tabaRect.top,  tabaRect.Width(),  tabaRect.Height(), SWP_HIDEWINDOW);
	//m_ChildDlgA4�ӶԻ�������Ϊ����   
	m_ChildDlgA4.SetWindowPos(NULL, tabaRect.left, tabaRect.top, tabaRect.Width(), tabaRect.Height(), SWP_HIDEWINDOW);

	m_tabb.GetClientRect(&tabbRect);
	 tabbRect.left += 1;
	 tabbRect.right -= 1;
	 tabbRect.top += 25;
	 tabbRect.bottom -= 1;
	m_ChildDlgB1.SetWindowPos(NULL,  tabbRect.left,  tabbRect.top,  tabbRect.Width(),  tabbRect.Height(), SWP_SHOWWINDOW);
	// m_ChildDlgA2�ӶԻ�����Ϊ����   
	m_ChildDlgB2.SetWindowPos(NULL,  tabbRect.left,  tabbRect.top,  tabbRect.Width(),  tabbRect.Height(), SWP_HIDEWINDOW);
	//m_ChildDlgA3�ӶԻ�������Ϊ����   
	m_ChildDlgB3.SetWindowPos(NULL,  tabbRect.left,  tabbRect.top,  tabbRect.Width(),  tabbRect.Height(), SWP_HIDEWINDOW);
	//m_ChildDlgA3�ӶԻ�������Ϊ����   
	m_ChildDlgB4.SetWindowPos(NULL,  tabbRect.left,  tabbRect.top,  tabbRect.Width(),  tabbRect.Height(), SWP_HIDEWINDOW);
	///////////���¶�DXF������̵���Ӧ��������ʼ��///////////////////
	BatchHEAD_ID = 0;//��ʼ��ʱ�򣬻�û������
	NestResult_ID = 0;//��ʼ������û��ͼֽ����
	GEOMCLOSE_ID = 0;//��ʼ������û�з�ջ�
	m_pBatchHead = NULL;//δָ���κεط�
	m_pNestrsltdtND = NULL;//ÿһ���и�ƽ��ͼ��800*800������Ϣ�����������з�ջ�
	m_pGeomclsHead = NULL;
	m_IfDataDisposed = false;
	m_NewDxf = true;//��ͼֽ

	HBITMAP hBmp1 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_STOP));
	((CButton *)GetDlgItem(IDC_STOP))->SetBitmap(hBmp1);

	HBITMAP hBmp2 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_PAUSE));
	((CButton *)GetDlgItem(IDC_PAUSEORCONTINUE))->SetBitmap(hBmp2);

	HBITMAP hBmp3 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_WATERPUMP));
	((CButton *)GetDlgItem(IDC_BTN_WATERPUMP))->SetBitmap(hBmp3);

	HBITMAP hBmp4 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_SANDVALVE));
	((CButton *)GetDlgItem(IDC_BTN_SANDVALVE))->SetBitmap(hBmp4);

	HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_MAINPUMP));
	((CButton *)GetDlgItem(IDC_BTN_MAINPUMP))->SetBitmap(hBmp5);

	HBITMAP hBmp6 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_GASVALVE));
	((CButton *)GetDlgItem(IDC_BTN_GASVALVE))->SetBitmap(hBmp6);

	HBITMAP hBmp7 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_WATERVALVE));
	((CButton *)GetDlgItem(IDC_BTN_WATERVALVE))->SetBitmap(hBmp7);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWJSdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWJSdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWJSdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWJSdemoDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here   
	*pResult = 0;
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	m_taba.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_taba.GetCurSel())//����TabControl��ǩ�ؼ��ĵ�ǰѡ������ʾ��ǩҳ
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ��λ�á�������ʾm_ChildDlgA1�Ի�����������Ի���   
	case 0:
	{m_ChildDlgA1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_ChildDlgA2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		FromHandle(hWnd)->SendMessage(TABA1GLFLUSH,0, 0);//
	}
		break;
	case 1:
		m_ChildDlgA1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_ChildDlgA3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 2:
		m_ChildDlgA1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_ChildDlgA4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 3:
		m_ChildDlgA1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgA4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
}


void CWJSdemoDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here   
	*pResult = 0;
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	m_tabb.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_tabb.GetCurSel())//����TabControl��ǩ�ؼ��ĵ�ǰѡ������ʾ��ǩҳ
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ��λ�á�������ʾm_ChildDlgB1�Ի�����������Ի���   
	case 0:
		m_ChildDlgB1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_ChildDlgB2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;
	case 1:
		m_ChildDlgB1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_ChildDlgB3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;
	case 2:
		m_ChildDlgB1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_ChildDlgB4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 3:
		m_ChildDlgB1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_ChildDlgB4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

		break;
	default:
		break;
	}
}

LRESULT CWJSdemoDlg::ProceedDXFData(WPARAM wparam, LPARAM lparam)  //��Ϣ��������DXF���д����õ�BatchHead��������
{
	BatchHEAD_ID++;//������������ô��Ʒ���ξ���һ��
	m_pBatchHead = m_GeomForCut.CreatBatchHEAD(BatchHEAD_ID);//�������ν��г�ʼ������


	//��ͼֽ����ͼֽ���
	m_NewDxf = true;//��ͼֽ
	NestResult_ID++;//�������ͼֽ���
	m_pNestrsltdtND = m_GeomForCut.CreatNestResultNode(NestResult_ID);//�ڳ�ʼ��ʱ���¼���Ǵ򿪵ĵڼ���ͼֽ
	m_pBatchHead = m_GeomForCut.AddNestRsltDtNode(m_pBatchHead, m_pNestrsltdtND);//�������ɵĽ�������������ָ���ͼֽ˫��������
	//����һ��ֻ���Բ���������ͼ���
	m_pNestNode_forCircle = m_GeomForCut.CreatNestResultNode(NestResult_ID);//������һ��ͼֽ��ID����Ϊ����ֻ���Ȼ�һ����������Բ��ID����Ҫ�ı�
	//��ֻ���Բ���������ͼ���ҵ��������ν����
	m_pBatchHead = m_GeomForCut.AddNestRsltDtNode(m_pBatchHead, m_pNestNode_forCircle);//�µ�ͼֽ˫�����������ͬһ��������Fͷ�����

	//������¼ͼԪ����Fͷ���
	GEOMCLOSE_ID++;
	m_pGeomclsHead = m_GeomClose.CreatGeomCloseHEAD(GEOMCLOSE_ID);
	//�ѷ�ջ����ҵ��������ͼ����ϣ�����ͬһ����ͼ�е�����ͼԪ����һ������
	m_pNestrsltdtND = m_GeomForCut.AddGeomCloseHeadNode(m_pNestrsltdtND, m_pGeomclsHead);//����ָ���ջ���������dxf���ͼ��㣬�ͷ�ջ���㣬�ѷ�ջ����ҵ�����dxf���ͼ�ϣ������Ѿ�����������ṹ

	//
	OPENFILENAME ofn = { 0 };//��Ϊ���ļ����ض����
	//bOpenFileDialog
	//	TRUE����ʾ���ļ��Ի���FALSE����ʾ�����ļ��Ի���
	//	lpszDefExt
	//	ָ��Ĭ�ϵ��ļ���չ����
	//	lpszFileName
	//	ָ��Ĭ�ϵ��ļ�����
	//	dwFlags
	//	ָ��һЩ�ض����
	//	lpszFilter
	//	������Ҫ��һ����������ָ���ɹ�ѡ����ļ����ͺ���Ӧ����չ����
	//	pParentWnd
	//	Ϊ������ָ�롣
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
	CFileDialog m_dlg(TRUE, NULL, NULL, ofn.Flags, TEXT("DXF(*.*)|*.*|"), NULL);
	//�Ժ������һ��������DXF�ļ��������Զ��ӹ�

	/*CFileDialog m_dlg(true);
	m_dlg.m_ofn.nMaxFile = 511;
	m_dlg.m_ofn.lpstrFilter = "DXF Files(*.dxf)\0*.dxf\0All Files(*.*)\0*.*\0\0";
	m_dlg.m_ofn.lpstrTitle = "Open DXF Files";
	CString m_filename;
	*/

	if (m_dlg.DoModal() == IDOK)
	{
		path = m_dlg.GetPathName();
		switchkeyword(path);
		//�����Ѿ����������DXF���������ȫ����ȡ�ˣ�������Ҫ�����ݽ��У���ջ��ֿ��ҵ���ͬ�ķ�ջ�ͷ�����
		AdjustGeomCloseNode(m_pNestrsltdtND);
		//������õ�DXF���ݴ��ݵ�A11 Dlg�н��ж�ȡ�ͻ�ͼ
		DXFProcData* SendDXFProcMsgtoA111 = (DXFProcData *)malloc(sizeof(DXFProcData));

		SendDXFProcMsgtoA111->BatchHEAD_ID = BatchHEAD_ID;
		SendDXFProcMsgtoA111->GEOMCLOSE_ID = GEOMCLOSE_ID;
		SendDXFProcMsgtoA111->NestResult_ID = NestResult_ID;
		SendDXFProcMsgtoA111->m_IfDataDisposed = m_IfDataDisposed;
		SendDXFProcMsgtoA111->m_NewDxf = m_NewDxf;
		SendDXFProcMsgtoA111->m_pBatchHead = m_pBatchHead;
		SendDXFProcMsgtoA111->m_pNestrsltdtND = m_pNestrsltdtND;
		SendDXFProcMsgtoA111->m_pGeomclsHead = m_pGeomclsHead;

		HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		FromHandle(hWnd)->SendMessage(GET_DXFDATA, (WPARAM)(SendDXFProcMsgtoA111), 0);//
		free(SendDXFProcMsgtoA111);


		int len = WideCharToMultiByte(CP_ACP, 0, m_dlg.GetPathName(), -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
		char* cwd = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, m_dlg.GetPathName(), -1, cwd, len, NULL, NULL);

		HWND hWnd2 = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
		hWnd2 = ::FindWindowEx(FromHandle(hWnd2)->GetDlgItem(IDC_TAB2)->m_hWnd, NULL, NULL, _T("�ļ�����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		FromHandle(hWnd2)->SendMessage(GET_FILEPATH, (WPARAM)(cwd), 0);//


		return 0;
	}

	else{
		return -1;
	}

}



//���մ򿪵��ļ���·��ȥ����LINE ARC CIRCLE
void CWJSdemoDlg::switchkeyword(CString path)
{
	//bool a=false;
	CStdioFile m_dxfofnestresult(path, CFile::modeRead);//�����ļ�·����ֻ��
	//a=m_dxfofnestresult.ReadString(m_readgeomele);//ÿ�ζ�һ�У���ȡһ��֮��ָ����һ�У��Ż�bool
	while (m_dxfofnestresult.ReadString(m_readgeomele))//������ǿ��ļ���//m_readgeomele�洢��ȡ����dxf�����ݣ�
		//while (a)
	{
		//�����LINE ARC CIRCLE�������ؼ���֮���һ��
		//a = m_dxfofnestresult.ReadString(m_readgeomele);
		int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
		m_readgeomeleUnicode = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
		while ((strcmp(m_readgeomeleUnicode, "LINE") == 0) || (strcmp(m_readgeomeleUnicode, "ARC") == 0) || (strcmp(m_readgeomeleUnicode, "CIRCLE") == 0))
		{
			if (strcmp(m_readgeomeleUnicode, "LINE") == 0) m_typegeomele = 0;
			if (strcmp(m_readgeomeleUnicode, "ARC") == 0) m_typegeomele = 1;
			if (strcmp(m_readgeomeleUnicode, "CIRCLE") == 0) m_typegeomele = 2;
			switch (m_typegeomele)
			{
			case LINE://�鵽�Ĺؼ���ΪLINE��ʱ������ֻ�Ƕ�����LINE����Ҫ������
			{m_dxfofnestresult.ReadString(m_readgeomele);//������ﲻ����һ�У���ô����LINE����ô�ͽ���ȥ�����while����һֱ����LINE,��������һ��while�γ���ѭ����
			int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
			m_readgeomeleUnicode = new char[len + 1];
			WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
			//ÿ����һ��LINE֮�������������һ��LINE��ARC,CIRCLE�����������������LINEѭ��
			//����������ֻ�в���LINE ,ARC,CIRCLE��ENDSEC���ܽ��룬����������LINE ,ARC,CIRCLE��ENDSEC���ܳ�������LINE ,ARC,CIRCLE��ENDSEC���ų�����
			while ((strcmp(m_readgeomeleUnicode, "LINE") != 0) && (strcmp(m_readgeomeleUnicode, "ARC") != 0) && (strcmp(m_readgeomeleUnicode, "CIRCLE") != 0) && (strcmp(m_readgeomeleUnicode, "ENDSEC") != 0))//���ǼӶ���һ��(strcmp(m_readgeomele, "ENDSEC") != 0)���while��������ȥ��
			{
				m_dxfofnestresult.ReadString(m_readgeomele);//��DXF������ַ�����Ϣ����m_readgeomele
				int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
				m_readgeomeleUnicode = new char[len + 1];
				WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
				symbol = atoi(m_readgeomeleUnicode);//��m_readgeomele������ַ���תΪ������ֵsymbol
				m_line = AcceptDxfLineData(symbol, m_readgeomele, m_dxfofnestresult);//����symbol�����ԴͼԪ����ֹ���꣬
			}//�뿪�����ʱ���Ѿ�ѭ����һ��LINE��
			//���ȴ�ǵ����������ʱ��m_lineΪ0�ˣ�֮ǰ��ֵȫ��û�б�������������һ�δα����ǣ�Ҫ����취���м�Ĳ�������������
			m_geomstanddata = m_geomele.ReadLineData(m_line);//����ԴͼԪ����ֹ���꣬���һ����׼��ͼԪ�����ݸ�ʽ
			//������¼����ͼԪ��˫������,�ѻ�õ����ݱ�������
			m_pGeomEleND = m_GeomClose.CreatGeomEleNode(m_geomstanddata);//���������õ����ݣ�����һ����㱣������
			m_pGeomclsHead = m_GeomClose.InsertGeomEleNode(m_pGeomclsHead, m_pGeomEleND, m_geomstanddata);//�Ѵ����Ļ���ͼԪ���ҵ���m_pGeomclsHeadָ���˫�������С�
			break;//����cade LINE���¼�
			}
			case ARC:
			{m_dxfofnestresult.ReadString(m_readgeomele);
			int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
			m_readgeomeleUnicode = new char[len + 1];
			WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
			while ((strcmp(m_readgeomeleUnicode, "LINE") != 0) && (strcmp(m_readgeomeleUnicode, "ARC") != 0) && (strcmp(m_readgeomeleUnicode, "CIRCLE") != 0) && (strcmp(m_readgeomeleUnicode, "ENDSEC") != 0))//���ǼӶ���һ��(strcmp(m_readgeomele, "ENDSEC") != 0)���while��������ȥ��
			{
				m_dxfofnestresult.ReadString(m_readgeomele);//��DXF������ַ�����Ϣ����m_readgeomele
				int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
				m_readgeomeleUnicode = new char[len + 1];
				WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
				symbol = atoi(m_readgeomeleUnicode);//��m_readgeomele������ַ���תΪ������ֵsymbol
				m_arc = AcceptDxfArcData(symbol, m_readgeomele, m_dxfofnestresult);//����symbol�����ԴͼԪ����ֹ���꣬
			}//�뿪�����ʱ���Ѿ�ѭ����һ��LINE��
			//���ȴ�ǵ����������ʱ��m_lineΪ0�ˣ�֮ǰ��ֵȫ��û�б�������������һ�δα����ǣ�Ҫ����취���м�Ĳ�������������
			m_geomstanddata = m_geomele.ReadArcData(m_arc);//����ԴͼԪ����ֹ���꣬���һ����׼��ͼԪ�����ݸ�ʽ
			//������¼����ͼԪ��˫������,�ѻ�õ����ݱ�������
			m_pGeomEleND = m_GeomClose.CreatGeomEleNode(m_geomstanddata);//���������õ����ݣ�����һ����㱣������
			m_pGeomclsHead = m_GeomClose.InsertGeomEleNode(m_pGeomclsHead, m_pGeomEleND, m_geomstanddata);//�Ѵ����Ļ���ͼԪ���ҵ���m_pGeomclsHeadָ���˫�������С�
			break; }
			case CIRCLE:
			{m_dxfofnestresult.ReadString(m_readgeomele);
			int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
			m_readgeomeleUnicode = new char[len + 1];
			WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
			while ((strcmp(m_readgeomeleUnicode, "LINE") != 0) && (strcmp(m_readgeomeleUnicode, "ARC") != 0) && (strcmp(m_readgeomeleUnicode, "CIRCLE") != 0) && (strcmp(m_readgeomeleUnicode, "ENDSEC") != 0))
			{
				m_dxfofnestresult.ReadString(m_readgeomele);//�Ӳ������д���ȡ���ڶ�ȡ�����ݽṹģʽ��Ҫ���ܲ��ܼ�
				int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
				m_readgeomeleUnicode = new char[len + 1];
				WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
				symbol = atoi(m_readgeomeleUnicode);
				m_circle = AcceptDxfCircleData(symbol, m_readgeomele, m_dxfofnestresult);
			}
			m_geomstanddata = m_geomele.ReadCircleData(m_circle);
			//������¼����ͼԪ��˫������,�ѻ�õ����ݱ�������
			//Բ������������Ϊ���������һ����ջ�,�������ҵ���һ���������ͼ�У���ȡ������֮���ٹһ���
			GEOMCLOSE_ID++;//�Լ��Ϳ�������һ����ջ�
			//////////////////////////////////////////////////////////////////////////////////
			////����һ���������ͼ���
			//m_pNestNode_forCircle = m_GeomForCut.CreatNestResultNode(NestResult_ID);//������һ��ͼֽ��ID����Ϊ����ֻ���Ȼ�һ����������Բ��ID����Ҫ�ı�
			////��ͼ���ҵ��������ν����
			//m_pBatchHead = m_GeomForCut.AddNestRsltDtNode(m_pBatchHead, m_pNestNode_forCircle);//�µ�ͼֽ˫�����������ͬһ��������Fͷ�����
			////����һ����ջ����
			////////////////////////////////////////////////////////////////////////////////////
			m_pGeomclsHead_forCircle = m_GeomClose.CreatGeomCloseHEAD(GEOMCLOSE_ID);
			//�ѷ�ջ����ҵ��������ͼ�����
			m_pNestNode_forCircle = m_GeomForCut.AddGeomCloseHeadNode(m_pNestNode_forCircle, m_pGeomclsHead_forCircle);//����ָ���ջ���������dxf���ͼ��㣬�ͷ�ջ���㣬�ѷ�ջ����ҵ�����dxf���ͼ�ϣ������Ѿ�����������ṹ
			//����һ�����ݽ��
			m_pGeomEleND = m_GeomClose.CreatGeomEleNode(m_geomstanddata);//���������õ����ݣ�����һ����㱣������
			//�����ݽ��ҵ���ջ������
			m_pGeomclsHead_forCircle = m_GeomClose.InsertGeomEleNode(m_pGeomclsHead_forCircle, m_pGeomEleND, m_geomstanddata);//�Ѵ����Ļ���ͼԪ���ҵ���m_pGeomclsHeadָ���˫�������С�
			break; }
			default:break;//����switch (m_typegeomele)�¼�
			}
			//����Ҳ��Ӧ��break������������Ҳ�������ˡ�while�ǻ���ѭ���ģ�ÿһ�ζ���ȥ�ж��£������ֵ��
			//break;//������һ���ؼ���֮�����һ���ˣ��������ڶ���while���ж������ؼ��ֵ��Ǹ�while�ӵ�һ��while����ȥ��ʼ�ڶ��ֵ�ѭ����Ҳ������m_dxfofnestresult.ReadString(m_readgeomele);�����ڲ�ѭ������������Զ������ѭ���ˡ�
		}
		//break;//��Ӧ������������ֻ��һ�ξͽ�����
	}//û��������һ��ѭ������䣬����һֱ����ѭ��ָ���ļ�ĩβ��
}



bool CWJSdemoDlg::AdjustGeomCloseNode(NestResultDataNode*head)
{
	//�����Ѿ����������DXF���������ȫ����ȡ�ˣ�������Ҫ�����ݽ��У���ջ��ֿ��ҵ���ͬ�ķ�ջ�ͷ�����
	int m_GeomCloseID;//�����˵ķ�ջ��ĸ���
	GeomEleNode*temp;
	GeomCloseHEAD *m_FindTheEndClosed, *m_CircleFirstClosed = NULL;//���*Htemp,
	int m_MaxNumOfGeomClose, m_MAXNumOfGeomClose;//�����ջ�����



	temp = head->FirstGeomClose->FirstGeomele;//��ԭʼ����ĵ�һ�����ݽ��
	while (temp->nextGeomeleNode)//�ҵ���ԭʼ��������һ�����ݽ��
		temp = temp->nextGeomeleNode;
	m_MaxNumOfGeomClose = temp->m_NumGeomCloseID;//�����ջ�����������Բ֮�����ķ�ջ�����
	GeomCloseHEAD*m_NoIntactGeomCloseHead = NULL;
	for (m_GeomCloseID = 1; m_GeomCloseID <= m_MaxNumOfGeomClose; m_GeomCloseID++)//��֤ȫ������Ѿ�������һ�飬�Ҹ�������������
	{
		m_pDiffGeomclsDataNode = m_GeomForCut.FindDiffGeomCloseNode(m_pNestrsltdtND);
		m_GeomForCut.InsertGeomCloseHEAD(m_pNestrsltdtND, m_pDiffGeomclsDataNode);//��һ��˫�������ϵĲ�ͬ��ջ��ҵ������룩����ͬ��˫��������ȥ
	}
	//���Ѿ��ֿ���ͬ��ջ������ݽ��������ջ�������
	for (m_GeomCloseID = 1; m_GeomCloseID <= m_MaxNumOfGeomClose; m_GeomCloseID++)//��֤ȫ������Ѿ�������һ�飬�Ҹ�������������
	{
		m_NoIntactGeomCloseHead = m_GeomForCut.JudgeGeomCloseIntact(m_pNestrsltdtND);//�жϷ�ջ��Ƿ�����
		m_pNestrsltdtND = m_GeomForCut.Find_Change_GeomCloseHEAD(m_pNestrsltdtND, m_NoIntactGeomCloseHead);//���벻�����ķ�ջ���㣬Ѱ����Եķ�ջ���㣬���ڲ�������
	}
	//�ٽ���ջ�����һ�飬����ͬ�ķֳ�ȥ
	for (m_GeomCloseID = 1; m_GeomCloseID <= m_MaxNumOfGeomClose; m_GeomCloseID++)//��֤ȫ������Ѿ�������һ�飬�Ҹ�������������
	{
		m_pDiffGeomclsDataNode = m_GeomForCut.FindDiffGeomCloseNode(m_pNestrsltdtND);
		m_GeomForCut.InsertGeomCloseHEAD(m_pNestrsltdtND, m_pDiffGeomclsDataNode);
	}
	//���Ѿ��ֿ���ͬ��ջ������ݽ��������ջ�������
	//����Ӧ�����Ѿ���֤�˷�ջ����ڲ�ͬ�ķ�ջ�Fͷ���ָ���˫�������ϣ�����ÿһ����ջ�����ڵ����ݽ�㶼��������
	//���»��з�ջ�֮����������⣬��ջ�֮��Ĺ��������⣬Բ���عҵ����⡣
	//��ջ��ڵ����ݽ�㴦������
	//Ҫ��Բ���뵽����ͼ����
	if ((m_pNestrsltdtND->nextNestResultDataNode->FirstGeomClose))//�����Բ������ͼ
	{
		m_CircleFirstClosed = m_pNestrsltdtND->nextNestResultDataNode->FirstGeomClose;//ȫ����Բ���Ǹ���ջ�˫������ĵ�һ����ջ�ͷ���
		m_FindTheEndClosed = m_pNestrsltdtND->FirstGeomClose;

		while (m_FindTheEndClosed->nextGeomcloseNode)//�ҵ����һ��ֱ��Բ����ɵķ�ջ�
		{
			m_FindTheEndClosed = m_FindTheEndClosed->nextGeomcloseNode;
		}
		m_FindTheEndClosed->nextGeomcloseNode = m_CircleFirstClosed;
		m_CircleFirstClosed->prevGeomcloseNode = m_FindTheEndClosed;
		while (m_CircleFirstClosed->nextGeomcloseNode)//�ҵ�Բ��ջ������һ����ջ�
		{
			m_CircleFirstClosed = m_CircleFirstClosed->nextGeomcloseNode;

		}
		m_MAXNumOfGeomClose = m_MaxNumOfGeomClose + m_CircleFirstClosed->GEOMCLOSE_ID;
		m_FindTheEndClosed->GEOMCLOSE_ID = m_MAXNumOfGeomClose;//�����Ϳ��԰����еķ�ջ����������һ��Բ��ջ�������
		//�԰�����Բ���ٴ���һ��
		for (m_GeomCloseID = 1; m_GeomCloseID <= m_MAXNumOfGeomClose; m_GeomCloseID++)//��֤ȫ������Ѿ�������һ�飬�Ҹ�������������
		{
			m_pDiffGeomclsDataNode = m_GeomForCut.FindDiffGeomCloseNode(m_pNestrsltdtND);
			m_GeomForCut.InsertGeomCloseHEAD(m_pNestrsltdtND, m_pDiffGeomclsDataNode);
		}
		m_pNestrsltdtND->nextNestResultDataNode->FirstGeomClose = NULL;//��ȻԲ�Ѿ����������ͷ�����˳����ˣ���ô�͸����������Ϊ��
	}
	//���������������滮�׶Σ����ԣ���������и������߶���������ż�
	head = m_GeomForCut.ChangeSencondCH2FH(head);//������Ҫ�ѵ�һ���ĵ�ȥ������ͬʱӦ����Ҫ�ѵ�һ���ĵ����ݱ�������ġ�
	//�����Լ������еķ�ջ�������ˡ�
	//TSP�������Ĵ��룬��������
	//m_GeomForCut.ChangeEleNodeOfGeomClosed_origin(m_pNestrsltdtND);//��ϧ�����û�����κ�Ч����ԭ��֮һ�����Ƿ�ջ������û�з����������Ǵ�����㷨�����⡣
	//m_GeomForCut.ChangClosedNodeOfNRDXF(m_pNestrsltdtND);
	//m_GeomForCut.ChangeEleNodeOfGeomClosed_order(m_pNestrsltdtND);

	//m_GeomForCut.ChangeEleNode_Avoid_Impact(m_pNestrsltdtND);
	////////////////��һ�ִ���ʽ//////////////////////////////////
	////��̰���㷨�����еķ�ջ���������ʼ˳��
	m_GeomForCut.BaseTS_GR_ForCutPathPlan(head);//����û��Ƕ�׵�ƽ���и�ͼ�Σ�dtsp�����������

	//������Ƕ�׵ķ�ջ�����������������������ACO�Ǹ���
	//���ֳ���ͬ�ķ�ջ����
	m_GeomForCut.Find_AdjustNestCloseHead(head);//Ƕ�׷�ջ���Ƕ��ʶ�����������д���
	//////����Ⱥ�㷨�Ե�һ���ջ�����·���滮���Ż�
	//////////m_GeomForCut.Base_ACO_ForFirstCHead(head);//δ�ɹ�������������һƪEI�Ĺ���
	m_GeomForCut.BaseTS_GR_ForCutPathPlan(head);
	//  ////����̰���㷨������ĵ�һ���ջ�������ÿ����ջ�Ⱥ������ӷ�ջ�˳�򣬲�������Ӧ�ĸ���ջ���׵�
	m_GeomForCut.BaseTS_GR_ForKidCHead(head);
	//
	//����и�������
	//��д���ջ�����ż��
	m_GeomForCut.JudgeClosedHead_Odd_even(head);
	//�ڷ�ջ���ż�Ե�ȷ�����ջ���ż�Ժ�д���и�������
	m_GeomForCut.Add_CutGuideLine(head);
	//д���и� ������֮��Ҫ�����и������ߵ��ж�
	m_GeomForCut.CheckCutGuideLINE(head);
	//head = m_GeomForCut.ChangeSencondCH2FH(head);//������Ҫ�ѵ�һ���ĵ�ȥ������ͬʱӦ����Ҫ�ѵ�һ���ĵ����ݱ�������ġ�

	m_IfDataDisposed = true;
	return m_IfDataDisposed;
}

//����dxf����ķ��ţ����dxf����ֱ�ߵ���ֹ��
GLINE CWJSdemoDlg::AcceptDxfLineData(int symbol, CString m_readgeomele, CStdioFile &m_dxfofnestresult)//ǰ�������CNestDxfDataForCutDlg��ʹ������һЩm_line���Ա�ʹ��
{
	//GLINE m_line = {0.0,0.0,0.0,0.0};//ÿһ�ν�������ʼ��һ�Σ���ʼ����Ӧ��������

	switch (symbol)//ֻ����һ��
	{
	case 10://��ʼ��x
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_line.x0 = atof(m_readgeomeleUnicode);
	break; }
	case 20://��ʼ��y
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_line.y0 = atof(m_readgeomeleUnicode);
	break; }
	case 11://��ֹ��x
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_line.x1 = atof(m_readgeomeleUnicode);
	break; }
	case 21://��ֹ��y
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_line.y1 = atof(m_readgeomeleUnicode);
	break; }
	default://����������������
		break;
	}
	return m_line;
}
GARC CWJSdemoDlg::AcceptDxfArcData(int symbol, CString m_readgeomele, CStdioFile &m_dxfofnestresult)
{

	switch (symbol)
	{
	case 10://Բ��x
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_arc.Arccent_x = atof(m_readgeomeleUnicode);
	break; }
	case 20://Բ��y
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_arc.Arccent_y = atof(m_readgeomeleUnicode);
	break; }
	case 40://�뾶r
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_arc.m_Arc_r = atof(m_readgeomeleUnicode);
	break; }
	case 50://��ʼ��
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_arc.m_ArcAngle_start = atof(m_readgeomeleUnicode);
	break; }
	case 51://��ֹ��
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_arc.m_ArcAngle_end = atof(m_readgeomeleUnicode);
	break; }
	default:
		break;
	}
	return m_arc;
}
GCIRCLE CWJSdemoDlg::AcceptDxfCircleData(int symbol, CString m_readgeomele, CStdioFile &m_dxfofnestresult)
{
	switch (symbol)
	{
	case 10://Բ��x
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_circle.m_Circent_x = atof(m_readgeomeleUnicode);
	break; }
	case 20://Բ��y
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_circle.m_Circent_y = atof(m_readgeomeleUnicode);
	break; }
	case 40://�뾶r
	{m_dxfofnestresult.ReadString(m_readgeomele);
	int len = WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, NULL, 0, NULL, NULL);// Unicode����ģʽ CString-->char *
	m_readgeomeleUnicode = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_readgeomele, -1, m_readgeomeleUnicode, len, NULL, NULL);
	m_circle.m_Circle_r = atof(m_readgeomeleUnicode);
	break; }
	default:
		break;
	}
	return m_circle;
}


void CWJSdemoDlg::OnBnClickedPauseorcontinue()
{
	if (m_staticdraw != true){//������ж�̬��ͼ�����������
		if (CNCRunModeInf.RunMode == m_VisualSimulation){//��һ�֣����ӻ�
			if (CNCRunModeInf.ContinueRunning == true){

				HBITMAP hBmpContinue = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_CONTINUE));
				((CButton *)GetDlgItem(IDC_PAUSEORCONTINUE))->SetBitmap(hBmpContinue);
			}
			else{
				HBITMAP hBmpPause = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_PAUSE));
				((CButton *)GetDlgItem(IDC_PAUSEORCONTINUE))->SetBitmap(hBmpPause);
			}

			HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
			hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
			hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
			FromHandle(hWnd)->SendMessage(PAUSEORCONTINUE, 0, 0);//����ֹͣ��Ϣ�������ػ澲̬ͼ����ն�̬ͼ
		}

		else if (CNCRunModeInf.RunMode == m_AutoWithoutCut){
			if (CNCRunModeInf.ContinueRunning == true){

				HBITMAP hBmpContinue = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_CONTINUE));
				((CButton *)GetDlgItem(IDC_PAUSEORCONTINUE))->SetBitmap(hBmpContinue);
			}
			else{
				HBITMAP hBmpPause = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_PAUSE));
				((CButton *)GetDlgItem(IDC_PAUSEORCONTINUE))->SetBitmap(hBmpPause);
			}

			HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
			hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB2)->m_hWnd, NULL, NULL, _T("�ֶ�"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
			FromHandle(hWnd)->SendMessage(PAUSEORCONTINUE, 0, 0);//����ֹͣ��Ϣ�������ػ澲̬ͼ����ն�̬ͼ
		}
		else if (CNCRunModeInf.RunMode == m_AutoCutting){
			if (CNCRunModeInf.ContinueRunning == true){

				HBITMAP hBmpContinue = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_CONTINUE));
				((CButton *)GetDlgItem(IDC_PAUSEORCONTINUE))->SetBitmap(hBmpContinue);
			}
			else{
				HBITMAP hBmpPause = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_PAUSE));
				((CButton *)GetDlgItem(IDC_PAUSEORCONTINUE))->SetBitmap(hBmpPause);
			}

			HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
			hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB2)->m_hWnd, NULL, NULL, _T("�ֶ�"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
			FromHandle(hWnd)->SendMessage(PAUSEORCONTINUE,0, 0);//����ֹͣ��Ϣ�������ػ澲̬ͼ����ն�̬ͼ
		}
	}
	else{
		HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		FromHandle(hWnd)->SendMessage(PAUSEORCONTINUE, 0, 0);//����ֹͣ��Ϣ�������ػ澲̬ͼ����ն�̬ͼ
	}
}


void CWJSdemoDlg::OnBnClickedStop()
{
	if (CNCRunModeInf.RunMode == m_VisualSimulation){
	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	FromHandle(hWnd)->SendMessage(STOPSIGNAL1, 0, 0);//����ֹͣ��Ϣ�������ػ澲̬ͼ����ն�̬ͼ
	}

	else {
		HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		FromHandle(hWnd)->SendMessage(STOPSIGNAL1, 0, 0);//����ֹͣ��Ϣ�������ػ澲̬ͼ����ն�̬ͼ
	}


	//stopsignal.m_manufacturing
}

LRESULT CWJSdemoDlg::GetCNCPositionData(WPARAM wparam, LPARAM lparam)  //��Ϣ��������������A11���������Ϣ
{

		EPos * receiveCNC_Pos = (EPos*)wparam;

	CString CX, CY, CZ, SBZ, SBX, SBY;//����C�ַ����ͱ���CX,CY

	CX.Format(_T("%5.1f"), receiveCNC_Pos->x);//����CString��Format�ķ��������ܵ���������Ϣ����CX
	CEdit* edit2 = (CEdit*)GetDlgItem(IDC_EDIT_MCX);//��ñ༭��1�ľ����ǿ��ת��ΪCEdit����
	edit2->SetWindowText(CX);//����CEdit�е�SetWindowText�������ñ༭���е�����

	CY.Format(_T("%5.1f"), receiveCNC_Pos->y);
	CEdit* edit3 = (CEdit*)GetDlgItem(IDC_EDIT_MCY);
	edit3->SetWindowText(CY);

	CZ.Format(_T("%5.1f"), receiveCNC_Pos->z);
	CEdit* edit6 = (CEdit*)GetDlgItem(IDC_EDIT_MCZ);
	edit6->SetWindowText(CZ);

	BaseframeData.x = receiveCNC_Pos->x - BaseframeOrigin.x;
	BaseframeData.y = receiveCNC_Pos->y - BaseframeOrigin.y;
	BaseframeData.z = receiveCNC_Pos->z - BaseframeOrigin.z;

	SBX.Format(_T("%5.1f"), BaseframeData.x);//����CString��Format�ķ��������ܵ���������Ϣ����CX
	CEdit* edit4 = (CEdit*)GetDlgItem(IDC_EDIT_WPCX);//��ñ༭��1�ľ����ǿ��ת��ΪCEdit����
	edit4->SetWindowText(SBX);//����CEdit�е�SetWindowText�������ñ༭���е�����

	SBY.Format(_T("%5.1f"), BaseframeData.y);
	CEdit* edit5 = (CEdit*)GetDlgItem(IDC_EDIT_WPCY);
	edit5->SetWindowText(SBY);

	SBZ.Format(_T("%5.1f"), BaseframeData.z);
	CEdit* edit7 = (CEdit*)GetDlgItem(IDC_EDIT_WPCZ);
	edit7->SetWindowText(SBZ);

	//HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	//hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	//hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	//FromHandle(hWnd)->SendMessage(CNC_DRAW, 0, 0);//����ֹͣ��Ϣ�������ػ澲̬ͼ����ն�̬ͼ
	return 0;
	
}

LRESULT CWJSdemoDlg::GetVisualizedPositionData(WPARAM wparam, LPARAM lparam)  //��Ϣ��������������A11���������Ϣ
{
	CoordinateStruct* receiveWPC = (CoordinateStruct*)wparam;

	CString CX, CY;//����C�ַ����ͱ���CX,CY
	CX.Format(_T("%5.2f"), receiveWPC->x);//����CString��Format�ķ��������ܵ���������Ϣ����CX
	CEdit* edit2 = (CEdit*)GetDlgItem(IDC_EDIT_WPCX);//��ñ༭��1�ľ����ǿ��ת��ΪCEdit����
	edit2->SetWindowText(CX);//����CEdit�е�SetWindowText�������ñ༭���е�����
	CY.Format(_T("%5.2f"), receiveWPC->y);
	CEdit* edit3 = (CEdit*)GetDlgItem(IDC_EDIT_WPCY);
	edit3->SetWindowText(CY);
	//free(receiveWPC);
	return 0;
}
void CWJSdemoDlg::OnBnClickedBtnMainpump()//�����
{
	if (CNC_DO_States.DO69 == false)
		CNC_DO_States.DO69 = true;
	else 
		CNC_DO_States.DO69 = false;

	SendDOMessage(DO69, CNC_DO_States.DO69);


}


void CWJSdemoDlg::OnBnClickedBtnWaterpump()//ˮ��
{
	if (CNC_DO_States.DO65 == false)
		CNC_DO_States.DO65 = true;
	else
		CNC_DO_States.DO65 = false;

	SendDOMessage(DO65, CNC_DO_States.DO65);
}



void CWJSdemoDlg::OnBnClickedBtnWatervalve()//ˮ��
{
	if (CNC_DO_States.DO68 == false)
		CNC_DO_States.DO68 = true;
	else
		CNC_DO_States.DO68 = false;

	SendDOMessage(DO68, CNC_DO_States.DO68);
}


void CWJSdemoDlg::OnBnClickedBtnSandvalve()//ɰ��
{
	if (CNC_DO_States.DO67 == false)
		CNC_DO_States.DO67 = true;
	else
		CNC_DO_States.DO67 = false;

	SendDOMessage(DO67, CNC_DO_States.DO67);
}


void CWJSdemoDlg::OnBnClickedBtnGasvalve()//��ѹ����
{
	if (CNC_DO_States.DO66 == false)
		CNC_DO_States.DO66 = true;
	else
		CNC_DO_States.DO66 = false;

	SendDOMessage(DO66, CNC_DO_States.DO66);
}
int CWJSdemoDlg::SendDOMessage(DO_Num Do_num, bool Do_states){

	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB2)->m_hWnd, NULL, NULL, _T("�ֶ�"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	switch (Do_num){
	case DO69:{
				  FromHandle(hWnd)->SendMessage(SETDOSTATES, Do_num, CNC_DO_States.DO69);
				  break;
	}
	case DO65:{
				  FromHandle(hWnd)->SendMessage(SETDOSTATES, Do_num, CNC_DO_States.DO65);
				  break;
	}
	case DO66:{
				  FromHandle(hWnd)->SendMessage(SETDOSTATES, Do_num, CNC_DO_States.DO66);
				  break;
	}
	case DO67:{
				  FromHandle(hWnd)->SendMessage(SETDOSTATES, Do_num, CNC_DO_States.DO67);
				  break;
	}
	case DO68:{
				  FromHandle(hWnd)->SendMessage(SETDOSTATES, Do_num, CNC_DO_States.DO68);
				  break;
	}
	default:
		break;

	}
	return 0;
}
LRESULT CWJSdemoDlg::getDOStatesFunc(WPARAM w,LPARAM y){
	int DOChannel = (int)w;
	int GetCNC_DO = (int)y;

	switch (w){
	case 69:
	{if (GetCNC_DO == 1){
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_MAINPUMP_GREEN));
			((CButton *)GetDlgItem(IDC_BTN_MAINPUMP))->SetBitmap(hBmp5);
		}
		else{
			HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_MAINPUMP));
			((CButton *)GetDlgItem(IDC_BTN_MAINPUMP))->SetBitmap(hBmp5);
		}

		break;
	}
	case 65:
	{if (GetCNC_DO == 1){
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_WATERPUMP_GREEN));
		((CButton *)GetDlgItem(IDC_BTN_WATERPUMP))->SetBitmap(hBmp5);
	}
	else{
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_WATERPUMP));
		((CButton *)GetDlgItem(IDC_BTN_WATERPUMP))->SetBitmap(hBmp5);
	}

	break;
	}	
	case 66:
	{if (GetCNC_DO == 1){
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_GASVALVE_GREEN));
		((CButton *)GetDlgItem(IDC_BTN_GASVALVE))->SetBitmap(hBmp5);
	}
	else{
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_GASVALVE));
		((CButton *)GetDlgItem(IDC_BTN_GASVALVE))->SetBitmap(hBmp5);
	}

	break;
	}	
	case 67 :
	{if (GetCNC_DO == 1){
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_SANDVALVE_GREEN));
		((CButton *)GetDlgItem(IDC_BTN_SANDVALVE))->SetBitmap(hBmp5);
	}
	else{
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_SANDVALVE));
		((CButton *)GetDlgItem(IDC_BTN_SANDVALVE))->SetBitmap(hBmp5);
	}

	break;
	}	
	
	case 68:
	{if (GetCNC_DO == 1){
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_WATERVALVE_GREEN));
		((CButton *)GetDlgItem(IDC_BTN_WATERVALVE))->SetBitmap(hBmp5);
	}
	else{
		HBITMAP hBmp5 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_WATERVALVE));
		((CButton *)GetDlgItem(IDC_BTN_WATERVALVE))->SetBitmap(hBmp5);
	}

	break;
	}
	default:
		break;
	}
	return 0;
}

LRESULT CWJSdemoDlg::updateBaseOriginFunc(WPARAM w, LPARAM y){
	CString BOX,BOY,BOZ;//����C�ַ����ͱ���CX,CY

	BOX.Format(_T("%5.1f"), BaseframeOrigin.x);//����CString��Format�ķ��������ܵ���������Ϣ����CX
	CEdit* edit2 = (CEdit*)GetDlgItem(IDC_EDIT_WPOX);//��ñ༭��1�ľ����ǿ��ת��ΪCEdit����
	edit2->SetWindowText(BOX);//����CEdit�е�SetWindowText�������ñ༭���е�����

	BOY.Format(_T("%5.1f"), BaseframeOrigin.y);
	CEdit* edit3 = (CEdit*)GetDlgItem(IDC_EDIT_WPOY);
	edit3->SetWindowText(BOY);

	BOZ.Format(_T("%5.1f"), BaseframeOrigin.z);
	CEdit* edit6 = (CEdit*)GetDlgItem(IDC_EDIT_WPOZ);
	edit6->SetWindowText(BOZ);

	return 0;
}
