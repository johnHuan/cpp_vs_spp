#ifndef _DATAFILE_H
#define _DATAFILE_H
#endif // !_DATAFILE_H
#include <string>
#include <vector>

using namespace std;
#pragma once

typedef struct tagDataHead		// �۲����ݵ�һ��
{
	//unsigned char SatPrn;
	long double X;
	long double Y;
	long double Z;	
	tagDataHead() {
		X = 0.0;
		Y = 0.0;
		Z = 0.0;
	}
};

typedef struct tagSatData
{
	int m_satNum;					// satellite number
	int m_GPSTime;					// GPSTime
	
	vector<string> m_PRN;			// C10-C32;
	vector<double> m_X, m_Y, m_Z;	// ����λ��
	vector<float> m_Clock;			// �����Ӹ�����
	vector<float> m_Elevation;		// ���Ǹ߶Ƚ�
	vector<double> m_CL;			// α��P
	vector<float> m_ZTD;			// �������ӳ�
};

class SatOBSData
{
public:
	tagDataHead approx;				// ����ͷ����������
	vector<tagSatData> satData;		// �۲�������
};

/// <summary>
/// ��ȡ���ǹ۲�����
/// </summary>
/// <param name="strpath">�۲���������Ŀ¼��·��</param>
/// <param name="data">�۲�������</param>
/// <returns>�Ƿ�ɹ�</returns>
bool satObsDataRead(string strpath, SatOBSData &data);
