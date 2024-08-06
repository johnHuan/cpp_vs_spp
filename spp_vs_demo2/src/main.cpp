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

	SatOBSData satData;		// ����۲�������
	vector<SatResults> result;

	string strPath = "E:/Python/workspace1/SPP/data/GPS��������.txt";
	string targetPath = "E:/Python/workspace1/SPP/data/haha/SPP_result.txt";

	// ��ȡ�۲�����
	bool res = satObsDataRead(strPath, satData);
	
	// SPP����
	sppCalculate(satData, result);
	
	// �������
	calResultWrite(targetPath, satData, result);
	cout << res << endl;
	printf("\r\n%d\r\n", res);
	return 0;
}