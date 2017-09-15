// ChildDlgB2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WJSdemo.h"
#include "ChildDlgB2.h"
#include "afxdialogex.h"
#include "WJSdemoDlg.h"


// CChildDlgB2 �Ի���

IMPLEMENT_DYNAMIC(CChildDlgB2, CDialogEx)

CChildDlgB2::CChildDlgB2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChildDlgB2::IDD, pParent)
	, m_speed1(0)
	, m_speed2(0)
{

}

CChildDlgB2::~CChildDlgB2()
{
}

void CChildDlgB2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITSPEED1, m_speed1);
	DDX_Text(pDX, IDC_EDITSPEED2, m_speed2);
//	DDX_Control(pDX, IDC_SLIDER1, m_sliderNonCuttingRate);
	//  DDX_Control(pDX, IDC_SLIDER_FEEDRATE, m_slidernoncuttingrate);
	DDX_Control(pDX, IDC_SLIDER_NONCUTTINGRATE, m_SliderNonCuttingRate);
	DDX_Control(pDX, IDC_SLIDER_FEEDRATE, m_SliderFeedRate);
}


BEGIN_MESSAGE_MAP(CChildDlgB2, CDialogEx)
	ON_BN_CLICKED(IDC_VISUALSIMULATION_BTN, &CChildDlgB2::OnBnClickedVisualsimulationBtn)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_NONCUTTINGRATE, &CChildDlgB2::OnNMCustomdrawSliderNoncuttingrate)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_FEEDRATE, &CChildDlgB2::OnNMCustomdrawSliderFeedrate)

	
	ON_BN_CLICKED(IDC_BTN_DYNAMICSIMULATION, &CChildDlgB2::OnBnClickedBtnDynamicsimulation)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CChildDlgB2::OnBnClickedBtnProcess)
END_MESSAGE_MAP()


// CChildDlgB2 ��Ϣ�������

BOOL CChildDlgB2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_SliderFeedRate.SetRange(1, 120);//����slider�ķ�Χ

	m_SliderFeedRate.SetTicFreq(5);//����slider�Ŀ̶ȼ������������Ϊ1����λһ���̶�

	m_SliderFeedRate.SetPos(100);//����slider��ֵ������ѳ�ʼֵ��Ϊ100

	m_SliderNonCuttingRate.SetRange(1, 120);//����slider�ķ�Χ

	m_SliderNonCuttingRate.SetTicFreq(5);//����slider�Ŀ̶ȼ������������Ϊ1����λһ���̶�

	m_SliderNonCuttingRate.SetPos(100);//����slider��ֵ������ѳ�ʼֵ��Ϊ100

	HBITMAP hBmp1 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_VISUALIZEDSIMULATION));
	((CButton *)GetDlgItem(IDC_VISUALSIMULATION_BTN))->SetBitmap(hBmp1);

	HBITMAP hBmp2 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_DYNAMICSIMULATION));
	((CButton *)GetDlgItem(IDC_BTN_DYNAMICSIMULATION))->SetBitmap(hBmp2);

	HBITMAP hBmp3 = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_PROCESS));
	((CButton *)GetDlgItem(IDC_BTN_PROCESS))->SetBitmap(hBmp3);

	SetWindowText(_T("�Զ�"));


	return TRUE;
}






void CChildDlgB2::OnNMCustomdrawSliderNoncuttingrate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int pos = m_SliderNonCuttingRate.GetPos();//��ȡslider�ĵ�ǰλ��

	CString str;//����һ���ַ�������

	str.Format(_T("%d"), pos);//��slider�ĵ�ǰλ��posתΪ�ַ��������str�С�

	SetDlgItemText(IDC_STATIC_NONCUTTINGRATE, str);//����IDΪIDC_STATIC_B_status���ı��������
	float* speed = new float;
	
	UpdateData(TRUE);
	*speed = (float)60000 / (pos * m_speed1 / 100);

	UpdateData(FALSE);	
	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	FromHandle(hWnd)->SendMessage(UPDATENONCUTTINGSTROCKRATE, (WPARAM)(speed), 0);
	delete speed;
	*pResult = 0;
}


void CChildDlgB2::OnNMCustomdrawSliderFeedrate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int pos =m_SliderFeedRate.GetPos();//��ȡslider�ĵ�ǰλ��

	CString str;//����һ���ַ�������

	str.Format(_T("%d"), pos);//��slider�ĵ�ǰλ��posתΪ�ַ��������str�С�

	SetDlgItemText(IDC_STATIC_FEEDRATE, str);//����IDΪIDC_STATIC_B_status���ı��������
	float* speed = new float;

	UpdateData(TRUE);
	*speed = (float)60000 / (pos * m_speed2 / 100);

	UpdateData(FALSE);
	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	FromHandle(hWnd)->SendMessage(UPDATEFEEDRATE, (WPARAM)(speed), 0);
	delete speed;
	*pResult = 0;
}


void CChildDlgB2::OnBnClickedVisualsimulationBtn()
{
	//////////////////���ж��Ƿ����У�����������ܽ������棬��ʾ��ֹͣ��ȴ�����
	//////////////////����ȷ���Ի���ȷ����ִ������

	if (CNCRunModeInf.StopRunning == true){
		DeleteFile(_T("123Ƕ�׷�ջ�.txt"));

		CNCRunModeInf = { m_VisualSimulation, false, true };

		SpeedStruct* sendspeed = (SpeedStruct *)malloc(sizeof(SpeedStruct));
		UpdateData(TRUE);
		sendspeed->speed1 = (float)60000 / m_speed1;
		sendspeed->speed2 = (float)60000 / m_speed2;
		UpdateData(FALSE);
		//CNCRunModeInf.StopRunning = false;//���û����һ�У�����û���������ӻ�����ǰ�����������ε��ֹͣ��ť��Ҳ���������ο��ӻ�����ſ�
		//�Խ��ж�̬��ͼ����Ϊδ���붯̬��ͼ��ֹͣ��stopsignal.m_visualsimulation��ֵ�����Ϊfalse��
		HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		FromHandle(hWnd)->SendMessage(VISUALSIMULATION, (WPARAM)(sendspeed), 0);
		free(sendspeed);
	}
	else StartErrorWarning();
}



void CChildDlgB2::OnBnClickedBtnDynamicsimulation()
{
	//////////////////���ж��Ƿ����У�����������ܽ������棬��ʾ��ֹͣ��ȴ�����
	//////////////////����ȷ���Ի���ȷ����ִ������

	if (CNCRunModeInf.StopRunning == true){
		DeleteFile(_T("123Ƕ�׷�ջ�.txt"));
	CNCRunModeInf = { m_AutoWithoutCut, false, true };
	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	FromHandle(hWnd)->SendMessage(BEFORE_AUTORUN_REDRAW, 0,0);
	//UpdateData(TRUE);//����ԭʼ�ٶ�Ϊ5000�������ٶ�3000�������ٶ�800
	//speed1 = m_speed1 / (0.5 * 60 * 1000);// m_feedspeed/(setspeed * 1000mm * 60 sec)= m_v1 
	//speed2 = m_speed2 / (0.5 * 60 * 1000);
	//UpdateData(FALSE);
	CString str1,str2;
	GetDlgItemText(IDC_EDITSPEED1, str1);//���ַ�ʽ��ֹ�ڶ��̣߳�������PrestranslateMessage��״���£��ı�����������ݶ�ʧ����Ϊ0��Updatedata������
	GetDlgItemText(IDC_EDITSPEED2, str2);
	speed1 = _ttof(str1) / (0.5 * 60 * 1000);
	speed2 = _ttof(str2) / (0.5 * 60 * 1000);


	if ((speed1 == 0) or(speed2 == 0)){
		MessageBox(_T("�������ٶ�"));
		CNCRunModeInf.StopRunning = true;
		return;
	}
	if (speed1 > 0.166 or speed2 > 0.166){
		MessageBox(_T("�ٶȲ��ܴ���5000mm/min"));
		CNCRunModeInf.StopRunning = true;
		return;
	}
	else{

		HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB2)->m_hWnd, NULL, NULL, _T("�ֶ�"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		FromHandle(hWnd)->SendMessage(SEND_AUTO_START_MESSAGE, 0, 0);
	}
	}
	else StartErrorWarning();
}



void CChildDlgB2::OnBnClickedBtnProcess()
{
	//////////////////���ж��Ƿ����У�����������ܽ������棬��ʾ��ֹͣ��ȴ�����
	//////////////////����ȷ���Ի���ȷ����ִ������
	//stopsignal = { false, false, false };
	//ȫ�ֱ�������ͣ������źš���ʱ�����������кͿ������е���ͣ�źźϲ�����Ϊ�����Ϊͬһ��
	//pausesignal = { true, true, true };
	if (CNCRunModeInf.StopRunning == true){
		DeleteFile(_T("123Ƕ�׷�ջ�.txt"));
	CNCRunModeInf = { m_AutoCutting, false, true };
	HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("λ��"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB1)->m_hWnd, NULL, NULL, _T("����"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
	FromHandle(hWnd)->SendMessage(BEFORE_AUTORUN_REDRAW, 0, 0);
	//UpdateData(TRUE);//����ԭʼ�ٶ�Ϊ5000�������ٶ�3000�������ٶ�800
	//speed1 = m_speed1 / (0.5 * 60 * 1000);// m_feedspeed/(setspeed * 1000mm * 60 sec)= m_v1 
	//speed2 = m_speed2 / (0.5 * 60 * 1000);
	//UpdateData(FALSE);
	CString str1, str2;
	GetDlgItemText(IDC_EDITSPEED1, str1);//���ַ�ʽ��ֹ�ڶ��̣߳�������PrestranslateMessage��״���£��ı�����������ݶ�ʧ����Ϊ0��Updatedata������
	GetDlgItemText(IDC_EDITSPEED2, str2);
	speed1 = _ttof(str1) / (0.5 * 60 * 1000);
	speed2 = _ttof(str2) / (0.5 * 60 * 1000);


	if ((speed1 == 0) or(speed2 == 0)){
		MessageBox(_T("�������ٶ�"));
		CNCRunModeInf.StopRunning = true;
		return;
	}
	if (speed1 > 0.166 or speed2 > 0.166){
		MessageBox(_T("�ٶȲ��ܴ���5000mm/min"));
		CNCRunModeInf.StopRunning = true;
		return;
	}
	else{

		HWND hWnd = ::FindWindow(NULL, _T("����ѹˮ�����и����ܿ������"));//��ø������ֱ�
		hWnd = ::FindWindowEx(FromHandle(hWnd)->GetDlgItem(IDC_TAB2)->m_hWnd, NULL, NULL, _T("�ֶ�"));//���ڸ������ֱ��»��Tab�ؼ����ٻ���Ӵ���
		FromHandle(hWnd)->SendMessage(SEND_AUTO_START_MESSAGE, 0, 0);
	}
	}
	else StartErrorWarning();
}

void CChildDlgB2::StartErrorWarning(){
	switch (CNCRunModeInf.RunMode){
	case m_VisualSimulation:
		MessageBox(_T("���ڽ��п��ӻ�ģ���������ֹͣ����������ִ�������Զ�������"));
		break;
	case m_AutoCutting:
		MessageBox(_T("���ڽ���ʵ�ʼӹ���������ֹͣ����������ִ�������Զ�������"));
		break;
	case m_AutoWithoutCut:
		MessageBox(_T("���ڽ��ж�̬ģ���������ֹͣ����������ִ�������Զ�������"));
		break;
	default:
		break;

	}
}

