#pragma once
#define GET_DXFDATA WM_USER+1000//��A11��ȡһ���������ε�ͷ�ڵ㣬���ڻ�ͼ
#define PROCEEDDXFDATA WM_USER+1001//B1�����Ի����ʹ���DXF��Ϣ�����õ�·���滮�õ����������ͷ�ڵ�
#define TABA1GLFLUSH WM_USER+1002//��A1��A11����glFlush����
#define CLEARDXFDATA WM_USER+1003//���DXF���ݣ�������
#define VISUALSIMULATION WM_USER+1004//B2��A11���Ϳ��ӻ�ģ���ź�
#define PAUSEORCONTINUE WM_USER+1005//��Dlg��A11���ͼ�������ͣ��ť
#define STOPSIGNAL1 WM_USER+1006//��Dlg��A11����ֹͣ����,STOPSIGNAL1���ڿ��ӻ�ģ�⣬STOPSIGNAL2���ڶ�̬ģ�⣬STOPSIGNAL3����ʵ�ʼӹ�
#define UPDATEFEEDRATE WM_USER+1007//���½�������
#define UPDATENONCUTTINGSTROCKRATE WM_USER+1008//���¿��г̱���
#define GET_FILEPATH WM_USER+1009//��ȡ�ļ�·��
#define UPDATE_CNCPOSITION WM_USER+1010//��������������
#define CNCCONNECT WM_USER+1011//������Ϣ��B4����B3
#define CNCCONNECTRESULT WM_USER+1012//������Ϣ������B3����B4
#define SETDOSTATES WM_USER+1013//����IO�����ź�
#define GETDOSTATES WM_USER+1014//����DO�����ź�
#define UPDATE_BASE_ORIGIN WM_USER+1015//���¹���ԭ������
#define SEND_AUTO_START_MESSAGE WM_USER+1016//���Ͳ������ӹ��򿪵��ӹ���Ϣ
#define CNC_DRAW WM_USER+1017//���ͻ�����������������̬��ͼ�ĺ���
#define BEFORE_AUTORUN_REDRAW WM_USER+1018//ÿ�����������Զ�ģʽǰ������ջ�����ػ���̬ͼA11Dlg
#define UPDATE_VISUAL_POSITION WM_USER+1019//���¿��ӻ�ģ�������

// CWJSdemoDlg �Ի���
struct SpeedStruct{
	float speed1;//�����ٶ�
	float speed2;//ʵ���ٶ�
};
enum DO_Num{ 
	DO64=64, 
	DO65=65, 
	DO66=66, 
	DO67=67, 
	DO68=68, 
	DO69=69 };

struct DOStates{
	bool DO64;
	bool DO65;
	bool DO66;
	bool DO67;
	bool DO68;
	bool DO69;

};

typedef struct CoordinateStruct{
	float x;//X������
	float y;//Y������
	float z;//Z������
}CoordinateStruct;


struct StopSignal{
	bool m_visualsimulation;//ֹͣ���ӻ�����
	bool m_dynamicsimulation;//ֹͣ��̬����
	bool m_manufacturing;//ֹͣ�ӹ�
};

struct PauseSignal{
	bool m_visualsimulation;//ֹͣ���ӻ�����
	bool m_dynamicsimulation;//ֹͣ��̬����
	bool m_manufacturing;//ֹͣ�ӹ�
};

enum StartMode{
	m_non,
	m_VisualSimulation,//�������ģʽ
	m_AutoWithoutCut,
	m_AutoCutting,
	m_Manulmode
};


enum m_LeadLineType{ LL_NoType, LL_Line, LL_Arc };

struct RunModeInf{
	StartMode RunMode;
	bool StopRunning;
	bool ContinueRunning;
	
};

enum JogMode{
	sd,
	joginching,
	jogcontinue,
	jogstep,
	joghome

};
enum AxisNumber{

	AN_X, AN_Y, AN_Z

};
struct ManualMode{
	JogMode jogmode;
	bool jogPositive;
	double jogSpeed;
	double jogstepDistance;
	AxisNumber axisnum;
};
extern ManualMode CNCmanualmode;
//extern SpeedStruct* getCNCSpeed;
extern float speed1;
extern float speed2;
extern bool b_setBaseFrame;
extern bool b_CutColor;