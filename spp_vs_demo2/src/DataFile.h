#ifndef _DATAFILE_H
#define _DATAFILE_H
#endif // !_DATAFILE_H
#include <string>
#include <vector>

using namespace std;
#pragma once

typedef struct tagDataHead		// 观测数据第一行
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
	vector<double> m_X, m_Y, m_Z;	// 卫星位置
	vector<float> m_Clock;			// 卫星钟改正数
	vector<float> m_Elevation;		// 卫星高度角
	vector<double> m_CL;			// 伪矩P
	vector<float> m_ZTD;			// 对流层延迟
};

class SatOBSData
{
public:
	tagDataHead approx;				// 数据头，概略坐标
	vector<tagSatData> satData;		// 观测数据体
};

/// <summary>
/// 读取卫星观测数据
/// </summary>
/// <param name="strpath">观测数据所在目录及路径</param>
/// <param name="data">观测数据类</param>
/// <returns>是否成功</returns>
bool satObsDataRead(string strpath, SatOBSData &data);
