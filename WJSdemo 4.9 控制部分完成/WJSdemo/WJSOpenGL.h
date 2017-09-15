#pragma once
#include "afxdialogex.h"

class CWJSOpenGL :
	public CDialogEx
{
protected:
	HDC hDC;//��ͼ�ؼ���DC
	HGLRC m_hGLRC;//OpenGL��Ⱦ������RC
	int pixelformat;//ƥ����������ر��
	PIXELFORMATDESCRIPTOR pixelDesc;//���ر������
	CWnd* PaintWnd;
	//CoordinateStruct* WPC;//���ݹ���ϵ������

public:
	CWJSOpenGL();
	~CWJSOpenGL();
	void InitOpenGL(CWnd* getPictureCtrlItem);//��ʼ��OpenGL
	//PIXELFORMATDESCRIPTOR pixelDesc;//���ر������
	//int pixelformat;//ƥ����������ر��
	//CWnd* PaintWnd;//��ͼ�ؼ���ID
	//HDC hDC;//��ͼ�ؼ���DC
	//HGLRC m_hGLRC;//OpenGL��Ⱦ������RC
	int m_GLPixelIndex;//m_GLPixelIndex��Ϊ�����ر���������ѡ�����
	void Reshape( );//������ͼ�ؼ�����Ұ�ʹ�С��
	void DrawOpenGL();
	void drawString(const char* str); //��Ļ��ʾ����  
	void InitDraw();//��ʼ�����壬��������
	//void DynamicDraw();//��̬��ͼ
	void selectFont(int size, int charset, const char* face); //����ѡ�����������������С���ַ������������ƣ��ɲ��鿴��������
	const int getMaxRow(char* cwd1); //�˺�������ֵΪnumber��Ϊtxt�ļ��е�������
	bool getTxtData(float** b, const int maxrow, const int maxcol, char* cwd1); //��ȡ�ı��еĶ�ά����
	void StaticDrawArc(float b1, float b2, float b3, float b4, float b5);//��̬Բ����ͼ��������г̣�
	void StaticDrawDottedLine(float b1, float b2, float b3, float b4); //��ֱ̬�߻�ͼ������г̣�
	void StaticDrawLine(float b1, float b2, float b3, float b4); //��ֱ̬�߻�ͼ��������г̣�
	void StaticDrawArrow(float b1, float b2, float b3, float b4);//��̬��ͷ��ͼ������г̣�

	int DynamicDrawArc(float b1, float b2, float b3, float b4, float b5, double &speed);//��̬Բ����ͼ��������г̣�
	int DynamicDrawDottedLine(float b1, float b2, float b3, float b4, double &speed); //��ֱ̬�߻�ͼ������г̣�
	int DynamicDrawLine(float b1, float b2, float b3, float b4, double &speed); //��ֱ̬�߻�ͼ��������г̣�

	void ClearOpenGL();

	void SendWPC(int type,int i, float xb,float x,float y, float z,float b3,float b4);//�����ӻ�ģ����Ϣ���͵�MainDlg


};

