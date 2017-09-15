#include "stdafx.h"
#include "ReadTXTData.h"

using namespace std;
const int CReadTXTData::getMaxRow(char* cwd){
	ifstream txtFile(cwd);
	if (!txtFile.is_open()){
		MessageBox(_T("δ��DXF�ļ����򻺴��ļ�ʧ�ܣ������´�DXF�ļ�(1)"));
	}
	string buffer;
	int number = 0;
	while (!txtFile.eof()){
		getline(txtFile, buffer);
		number++;

	}
	return number;
}

bool CReadTXTData::getTxtData(float **b, const int maxrow, const int maxcol, char*cwd){
	ifstream txtFile(cwd);
	if (!txtFile.is_open()){
		MessageBox(_T("δ��DXF�ļ����򻺴��ļ�ʧ�ܣ������´�DXF�ļ�(2)"));
	}
	string buffer;
	for (int i = 0; i < maxrow; i++){
		getline(txtFile, buffer);//һ�ζ���һ��


		istringstream is(buffer);//��buffer���������뵽is�������ո�ֹͣ
		for (int j = 0; j < maxcol; j++){
			is >> b[i][j];//�����ո�����������ζ��һ��ֻ���һ��string)
		}
	}
	return true;
}

