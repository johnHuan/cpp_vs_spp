#include <fstream>
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "DataFile.h"
#include "Calculate.h"
#include "utils.h"
#include <iostream>
using namespace std;

int main() {

	SatOBSData satData;		// 定义观测数据类
	vector<SatResults> result;

	string strPath = "E:/Python/workspace1/SPP/data/GPS卫星数据.txt";
	string targetPath = "E:/Python/workspace1/SPP/data/haha/SPP_result.txt";

	// 读取观测数据
	bool res = satObsDataRead(strPath, satData);
	
	// SPP解算
	sppCalculate(satData, result);
	
	// 结果保存
	calResultWrite(targetPath, satData, result);
	cout << res << endl;
	printf("\r\n%d\r\n", res);
	return 0;
}