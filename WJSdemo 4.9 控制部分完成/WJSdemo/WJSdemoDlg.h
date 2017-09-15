
// WJSdemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ChildDlgA1.h"
#include "ChildDlgA2.h"
#include "ChildDlgA3.h"
#include "ChildDlgA4.h"
#include "ChildDlgB1.h"
#include "ChildDlgB2.h"
#include "ChildDlgB3.h"
#include "ChildDlgB4.h"
#include "GeomForCut.h"
#include "Resource.h"
#include "GlobalSetting.h"

////ȫ�ֱ�����ֹͣ�ź�
//extern struct StopSignal stopsignal;
//
////ȫ�ֱ�������ͣ������ź�
//extern struct PauseSignal pausesignal;
//
////����ģʽ
//extern StartMode WJAutoStartMode;
extern RunModeInf CNCRunModeInf;
//ȫ�ֱ���������̬��ͼ�ж���
extern bool m_staticdraw;
//StopSignal stopsignal;

//ȫ�ֱ����������и������߳���
extern double m_LeadingLineLength;

extern bool m_FirstLeadingLineLengthSetting;//�Ƿ��һ�δ����öԻ������ڱ����һ�����ú��������Ϣ��
extern m_LeadLineType LeadlineType;

//����ϵ��������
extern CoordinateStruct BaseframeData;
extern CoordinateStruct BaseframeOrigin;
//DO���ź�
extern DO_Num CNC_DO_Num;
extern DOStates CNC_DO_States;

class CWJSdemoDlg : public CDialogEx
{
// ����
public:
	CWJSdemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WJSDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_taba; //��һ��ѡ������������ڱ�ǩҳ����ʾ�Ի���
	CChildDlgA1 m_ChildDlgA1;
	CChildDlgA2 m_ChildDlgA2;
	CChildDlgA3 m_ChildDlgA3;
	CChildDlgA4 m_ChildDlgA4;
	CChildDlgB1 m_ChildDlgB1;
	CChildDlgB2 m_ChildDlgB2;
	CChildDlgB3 m_ChildDlgB3;
	CChildDlgB4 m_ChildDlgB4;

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_tabb;
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);

	//��DXFͼ�����������·���滮��һ����Ƕ�׷�ջ�ͼ��
	afx_msg LRESULT ProceedDXFData(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT GetCNCPositionData(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT GetVisualizedPositionData(WPARAM wparam, LPARAM lparam); //��Ϣ��������������A11���������Ϣ

	///////////////////////////////////////����Ϊ�����ջ��͹滮�и�·����Ҫ�ı����ͺ���/////////////////////////////////////////////////////////////
	int BatchHEAD_ID;//��������
	BatchHEAD* m_pBatchHead;//���仮Ϊȫ�ֱ�����ͳһ��������



	bool m_NewDxf;//����һ�ν����ȡ����ʱ��x0_tran��y0_tranӦ��Ϊ0.0����ÿ��һ��ͼƬʱ�򣬶�Ӧ��Ϊ0.0;
	int NestResult_ID;//�������ͼֽ
	int GEOMCLOSE_ID;//��ջ��ĸ���
	GeomCloseHEAD*m_pGeomclsHead;//ָ�����ͼԪ˫�������ͷ���
	GeomClose m_GeomClose;//��ΪҪ���õ�ͼԪ�Ĳ�����ʵ���������
	CString path;//����򿪵��ļ���
	NestResultDataNode*m_pNestrsltdtND;//ָ���ջ�˫�������ͷ��㣬���ڱ���һ���������ε�������Ϣ

	//�������Ҫ��ʵ�ְ�֮ǰ�ķ�ջ�֮�䴮�����и�ʹ�á�
	//ʵ�֣�����ջ�֮�����򣬶�Բ��������ͼ��Ҫ���⴦������Բ��Ҫת����ԭ����������ʽ
	//�������ͼԪ֮��Ĺ���ֱ��
	//Ū�������������洢��һ������dxf������
	GeomForCut m_GeomForCut;

	int SendDOMessage(DO_Num , bool);
	void switchkeyword(CString path);
	CString m_readgeomele;//�洢��ȡ����dxf������
	char* m_readgeomeleUnicode;//��ΪUnicode�£�CStringת��Ϊchar*
	int m_typegeomele = -1;//����ͼԪ���͵ı�־λ
	enum{ LINE, ARC, CIRCLE };//��������ͼԪ����ö�ٱ���
	int symbol;//������Ѱ��ѭ����ʱ�����������жϴ洢
	GLINE m_line;//ȫ�ֵ�m_line����
	GARC m_arc;//ȫ�ֵ�m_arc����
	GCIRCLE m_circle;//ȫ�ֵ�m_circle����
	GeomStandData m_geomstanddata;//ʵ����һ���洢���ݽṹ
	GEOMELE m_geomele;//��ΪҪ���õ�ͼԪ�Ĳ�����ʵ���������
	GeomEleNode*m_pGeomEleND;//����ͼԪ˫�������ͷ���
	//����Բ����Ӧ���������һ��·
	NestResultDataNode*m_pNestNode_forCircle;//����һ��ֻ���Բ���������ͼ���
	GeomCloseHEAD*m_pGeomclsHead_forCircle;//ָ�����ͼԪ˫�������ͷ���


	bool AdjustGeomCloseNode(NestResultDataNode*head);
	GeomEleNode*m_pDiffGeomclsDataNode;//��ͬ��ջ������ݽ��
	bool m_IfDataDisposed;//�����Ƿ��Ѿ��������

	GLINE AcceptDxfLineData(int symbol, CString m_readgeomele, CStdioFile &m_dxfofnestresult);//����DXF�ļ��еı�ʶ���룬���GLINE������
	GARC AcceptDxfArcData(int symbol, CString m_readgeomele, CStdioFile &m_dxfofnestresult);//����DXF�ļ��еı�ʶ���룬���GARC������
	GCIRCLE AcceptDxfCircleData(int symbol, CString m_readgeomele, CStdioFile &m_dxfofnestresult);//����DXF�ļ��еı�ʶ���룬���GCIRCLE������





	//CString strFilePath;
	bool m_savefile = true;//����һ�ν���ReadCloseHeadDataʱ���򿪱����ļ��Ի���֮��ÿ�β����ٴ򿪱����ļ��Ի���
	CString strFilePath;//���ڱ��桰txt����·����
	///////////////////////////////////////����Ϊ�����ջ��͹滮�и�·����Ҫ�ı����ͺ���/////////////////////////////////////////////////////////////


	DXFProcData* SendDXFProcMsgtoA11;
	afx_msg void OnBnClickedPauseorcontinue();
	afx_msg void OnBnClickedStop();
//	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedBtnGasvalve();
	afx_msg void OnBnClickedBtnWatervalve();
	afx_msg void OnBnClickedBtnWaterpump();
	afx_msg void OnBnClickedBtnSandvalve();
	afx_msg void OnBnClickedBtnMainpump();
	afx_msg LRESULT getDOStatesFunc(WPARAM w, LPARAM l);//����DO������Ϣ
	afx_msg LRESULT updateBaseOriginFunc(WPARAM w, LPARAM y);

};
