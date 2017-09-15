#pragma once
#include "GeomForCut.h"
#include "WJSOpenGL.h"
#include "Resource.h"

// CChildDlgA11 �Ի���

class CChildDlgA11 : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlgA11)

public:
	CChildDlgA11(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlgA11();
	afx_msg LRESULT recieveDXFProcDataFromMainDlg(WPARAM wparam, LPARAM lparam);//���һ���������ε�ͷ�ڵ���Ϣ
	static UINT StaticDrawThread(LPVOID lParam);//��ȡͷ�ڵ����ݲ���̬��ͼ��ȫ��Ԥ����
	static UINT DynamicDrawThread(LPVOID lParam);//��ȡͷ�ڵ����ݲ���̬��ͼ�����ӻ�ģ�⣩
	static UINT CNCDrawThread(LPVOID lParam);//��ȡͷ�ڵ����ݲ���̬��ͼ�����ӻ�ģ�⣩
	void BeginCNCDraw();
	
	int ReadDXFandDrawFunc();
	//void DynamicDrawFunc();

	CMapPtrToPtr m_StaticDrawThreadList, m_VisualDynamicDrawThreadList, m_CNCDrawThreadList;//���߳̾�����̶߳�����ӵ�m_StaticDrawThreadList�У�Ŀ���Ƿ�ֹ�߳�δ����ʱ����ֹ���̳����ڴ�й¶��
	afx_msg LRESULT TabA1glFlush(WPARAM wparam, LPARAM lparam);//�л�Tab��ʱ��ͨ��glFlsuh����ʾOpenGl
	afx_msg LRESULT ClearDXFData(WPARAM wparam, LPARAM lparam);//B1Dlg���͹��������DXF�������
	afx_msg LRESULT GetVisualSimulationMsg(WPARAM wparam, LPARAM lparam);//���ӻ����涯̬��ͼ��Ϣ����
	afx_msg LRESULT StopandRedrawStaticPaint(WPARAM wparam, LPARAM lparam);//ֹͣ���ӻ����涯̬��ͼ�� ��Ϣ����
	afx_msg LRESULT PauseandContinueVisualSimulation(WPARAM wparam, LPARAM lparam);//ֹͣ���ӻ����涯̬��ͼ�� ��Ϣ����
	afx_msg LRESULT UpdateFeedRateFunc(WPARAM wparam, LPARAM lparam);//ͨ������������Ϣ�����ı�����ٶ�
	afx_msg LRESULT UpdateNonCuttingRateFunc(WPARAM wparam, LPARAM lparam);//ͨ������������Ϣ�����ı���г��ٶ�
	afx_msg LRESULT CNCDraw(WPARAM wparam, LPARAM lparam);//ͨ������������Ϣ�����ı���г��ٶ�
	afx_msg LRESULT AutoModeRedrawStaticFunc(WPARAM W, LPARAM L);//ÿ�����������Զ�ģʽǰ������ջ�����ػ���̬ͼ

	
	bool m_endDynamicDraw;//�жϿ��ӻ�ģ���Ƿ����
	double m_drawspeed1, m_drawspeed2;//speed1���ڿ��г̣�speed2���ڽ���
	static bool m_redraw;
	CWinThread* pStaticDrawThread,*pVisualDynamicDrawThread,*pCNCDrawThread;
// �Ի�������
	enum { IDD = IDD_CHILDDLG_A11 };

	 //bool m_staticdraw=true;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:	
	BatchHEAD* m_A11_pBatchHead;//�����������Ի�����ú�һ���������ε����ݵ�ͷ�ڵ�
	bool m_A11_IfDataDisposed;//�ж������Ƿ������
	GeomCloseHEAD*A11_pTheFirstLevelCloseHead;
	int A11_BatchHEAD_ID;//��ʼ��ʱ�򣬻�û������
	int A11_NestResult_ID;//��ʼ������û��ͼֽ����
	int A11_GEOMCLOSE_ID;//��ʼ������û�з�ջ�
	GeomCloseHEAD* m_A11_pGeomclsHead;
	NestResultDataNode*m_A11_pNestrsltdtND;//ָ���ջ�˫�������ͷ���

	int A11_ReadKidCloseHeadData(GeomCloseHEAD*pTemp);
	int A11_ReadCloseHeadData(GeomCloseHEAD*Htemp);

	//�������Ҫ��ʵ�ְ�֮ǰ�ķ�ջ�֮�䴮�����и�ʹ�á�
	//ʵ�֣�����ջ�֮�����򣬶�Բ��������ͼ��Ҫ���⴦������Բ��Ҫת����ԭ����������ʽ
	//�������ͼԪ֮��Ĺ���ֱ��
	//Ū�������������洢��һ������dxf������
	GeomForCut m_A11_GeomForCut;

	bool m_A11_firstdraw;//����һ�ν����ȡ����ʱ��x0_tran��y0_tranӦ��Ϊ0.0����ÿ��һ��ͼƬʱ�򣬶�Ӧ��Ϊ0.0;(������ԭ����m_A11_NewDxf)
	bool m_A11_NewDxf;
	//һЩ����
	double x0, x1, y0, y1, Arccent_x, Arccent_y, r, temp, Angle_start, Angle_end, Angle_cut_start;
	double x0_tran, y0_tran, x1_tran, y1_tran;
	double Angle_add;//�����Ƕ�

	CWJSOpenGL OpenGLDraw;//ʵ����OpenGL�����ڻ�ͼ

	DXFProcData* GetDXFProcMsgFromMainDlg;//����סDlg�����DXFͼ�����Ϣ
	double DrawX0, DrawY0, DrawX1, DrawY1;

};
