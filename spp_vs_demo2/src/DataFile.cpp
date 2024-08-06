#include <atlstr.h>
#include <fstream>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include "utils.h"
#include "DataFile.h"
#include "Calculate.h"
#include <iostream>
using namespace std;

/// <summary>
/// 读取卫星观测数据
/// </summary>
/// <param name="strpath">观测数据所在目录及路径</param>
/// <param name="data">观测数据类</param>
/// <returns>是否成功</returns>
bool satObsDataRead(string strpath, SatOBSData& satOBSData) {
	string approx = "APPROX_POSITION：";
	string sate_num = "Satellite Number:";
	string gps_time = "GPS time：";

	ifstream ifs;
	ifs.open(strpath, ios::in);

	string line;
	vector<string> str_list;
	size_t idx;
	getline(ifs, line);

	// APPROX_POSITION
	string_split(line, ",", str_list);	
	satOBSData.approx.X = stod(str_list[0].substr(approx.size()));
	satOBSData.approx.Y = stod(str_list[1]);
	idx = str_list[2].find("(m)");
	satOBSData.approx.Z = stod(str_list[2].substr(0, idx));

	// 第二行跳过
	getline(ifs, line);

	bool bInfo = false;
	tagSatData satData;
	while (!ifs.eof())
	{
		getline(ifs, line);
		if (line.size() == 0)
			continue;
		string_split(line, ",", str_list);
		if (str_list[0].substr(0, 9) == "Satellite")
		{
			if (bInfo)
			{
				satOBSData.satData.push_back(satData);				
				satData = tagSatData();
			}
			bInfo = true;
			idx = str_list[0].find(sate_num);
			satData.m_satNum = stoi(str_list[0].substr(idx+sate_num.size(), -1));

			idx = str_list[1].find(gps_time);
			satData.m_GPSTime = stoi(str_list[1].substr(idx + gps_time.size(), -1));
		}
		else {
			satData.m_PRN.push_back(str_list[0]);
			satData.m_X.push_back(stod(str_list[1]));
			satData.m_Y.push_back(stod(str_list[2]));
			satData.m_Z.push_back(stod(str_list[3]));
			satData.m_Clock.push_back(stof(str_list[4]));
			satData.m_Elevation.push_back(stof(str_list[5]));
			satData.m_CL.push_back(stod(str_list[6]));
			satData.m_ZTD.push_back(stof(str_list[7]));
		}		
	}
	if (bInfo)
		satOBSData.satData.push_back(satData);
	return bInfo;
}
