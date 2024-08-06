#include "CalCulate.h"
#include "Matrix.h"
#include <fstream>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <string>
#include "utils.h"
#include <iostream>
#include <time.h>

void sppCalculate(SatOBSData satObsData, vector<SatResults> &result)
{
	SatResults satRes;
	const int N = satObsData.satData.size();
	for (int epoch = 0; epoch < N; epoch++)
	{		
		int satNum = satObsData.satData[epoch].m_satNum;
		// 记录日志
		cout << "+开始解算第 --" << satObsData.satData[epoch].m_GPSTime << " -- 个历元，卫星数有：" << satNum << "颗！";
		// 记录时间
		clock_t start, end;
		start = clock();		
		vector<double> R0(satNum);
		vector<double> l(satNum);
		vector<double> m(satNum);
		vector<double> n(satNum);
		
		for (int i = 0; i < satNum; i++)
		{
			double deltaX = satObsData.satData[epoch].m_X[i] - satObsData.approx.X;
			double deltaY = satObsData.satData[epoch].m_Y[i] - satObsData.approx.Y;
			double deltaZ = satObsData.satData[epoch].m_Z[i] - satObsData.approx.Z;
			R0[i] = sqrtl(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
			l[i] = deltaX / R0[i];
			m[i] = deltaY / R0[i];
			n[i] = deltaZ / R0[i];
		}
		vector<vector<double>> B(satNum);		
		for (int i = 0; i < satNum; i++)
		{
			B[i].resize(4);			// 转换成 N行(卫星数) × 4列
		}
		for (int i = 0; i < satNum; i++)
		{
			B[i][0] = l[i];
			B[i][1] = m[i];
			B[i][2] = n[i];
			B[i][3] = -1;
		}

		vector<vector<double>> L(1);
		for (int i = 0; i < 1; i++)
		{
			L[i].resize(satNum);		// 转化成 1行×N列
		}
		for (int i = 0; i < satNum; i++)	// 给第一行的所有列赋值
		{
			L[0][i] = satObsData.satData[epoch].m_CL[i] - R0[i] + satObsData.satData[epoch].m_Clock[i] - satObsData.satData[epoch].m_ZTD[i];
		}
		vector<double> m_CL(satNum);
		for (int i = 0; i < satNum; i++)
		{
			m_CL[i] = satObsData.satData[epoch].m_CL[i];
		}

		vector<double> p(satNum);
		vector<vector<double>> P(satNum);
		for (int i = 0; i < satNum; i++)
		{
			P[i].resize(satNum);
		}
		for (int i = 0; i < satNum; i++)
		{
			p[i] = sin(satObsData.satData[epoch].m_Elevation[i] * 3.1415926 / 180) / 0.04;
		}
		for (int i = 0; i < satNum; i++)
		{
			for (int j = 0; j < satNum; j++)
			{
				if (i == j)
					P[i][j] = p[i];
				else
					P[i][j] = 0;
			}
		}
		vector<vector<double>> LT(satNum, vector<double>(1));
		LT = operator_converse(L);

		vector<vector<double>> BT(4, vector<double>(satNum));
		BT = operator_converse(B);

		vector<vector<double>> BTP(4, vector<double>(satNum));
		BTP = operator_multiply(BT, P);

		vector<vector<double>> BTPB(4, vector<double>(4));
		BTPB = operator_multiply(BTP, B);

		
		vector<vector<double>> BTPBN(4, vector<double>(4));		 // BT P B的逆矩阵
		//协方差矩阵
		BTPBN = operator_inv(BTPB);

		vector<vector<double>> BTPBNBT(4, vector<double>(satNum));
		BTPBNBT = operator_multiply(BTPBN, BT);

		vector<vector<double>> BTPBNBTP(4, vector<double>(satNum));
		BTPBNBTP = operator_multiply(BTPBNBT, P);

		//偏移量
		vector<vector<double>> BTPBNBTPL(4, vector<double>(1));  // BTPB的逆乘以BTPL
		BTPBNBTPL = operator_multiply(BTPBNBTP, LT);

		vector<vector<double>> D(4, vector<double>(1));
		D = operator_number(BTPBNBTPL, -1.0);

		vector<vector<double>> V(satNum, vector<double>(1));

		V = operator_add(operator_multiply(B, D), LT);

		vector<vector<double>> VTP(1, vector<double>(satNum));
		VTP = operator_multiply(operator_converse(V), P);

		vector<vector<double>> VTPV(1, vector<double>(1));
		VTPV = operator_multiply(VTP, V);

		satRes.X = satObsData.approx.X + D[0][0];
		satRes.Y = satObsData.approx.Y + D[1][0];
		satRes.Z = satObsData.approx.Z + D[3][0];

		double m0 = sqrtl(VTPV[0][0] / (satNum - 4));

		satRes.mx = m0 * BTPBN[0][0];
		satRes.my = m0 * BTPBN[1][1];
		satRes.mz = m0 * BTPBN[2][2];

		satRes.PDOP = sqrtl(BTPBN[0][0] * BTPBN[0][0] + BTPBN[1][1] * BTPBN[1][1] + BTPBN[2][2] * BTPBN[2][2]);
		result.push_back(satRes);
		end = clock();
		cout << "\t\t。。。" << "解算完毕！！耗时：" << end - start <<"毫秒! PDOP="<<satRes.PDOP << endl;
	}
}


bool calResultWrite(string targetPath, SatOBSData data, vector<SatResults> result)
{
	ofstream ofs(targetPath);
	try
	{
		if (ofs.is_open())
		{			
			char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
			setlocale(LC_CTYPE, "chs");//设定中文
			ofs << "观测历元 \t 卫星数 \t	X/m \t σx/m \t Y/m \t σy/m \t Z/m	\t σz/m  \t PDOP" << endl;
			ofs << "===============================================================================================================" << endl;
			for (int i = 0; i < result.size(); i++)
			{
				ofs << to_string(data.satData[i].m_GPSTime);
				ofs << "\t";
				ofs << to_string(data.satData[i].m_satNum);
				ofs << "\t";
				ofs << to_string(result[i].X);
				ofs << "\t";
				ofs << to_string(result[i].mx);
				ofs << "\t";
				ofs << to_string(result[i].Y);
				ofs << "\t";
				ofs << to_string(result[i].my);
				ofs << "\t";
				ofs << to_string(result[i].Z);
				ofs << "\t";
				ofs << to_string(result[i].mz);
				ofs << "\t";
				ofs << to_string(result[i].PDOP);
				ofs << endl;
			}
			if (ofs.fail())
			{
				printf("文件写入失败！！");
			}
			setlocale(LC_CTYPE, old_locale);
			free(old_locale);
			ofs.flush();
			ofs.close();
		}
		else {
			cout << "文件打开失败" << endl;
		}
	}
	catch (const std::exception& errorMessage)
	{
		cerr << "错误！" << errorMessage.what() << endl;
	}
	return true;
}
