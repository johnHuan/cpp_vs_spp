#ifndef _CALCULATE_H_
#define _CALCULATE_H_
#pragma once
#include <math.h>
#include <string>
#include <vector>
#include <atlstr.h>
#include "DataFile.h"


typedef struct SatResults
{
	double X;
	double Y;
	double Z;
	double mx;
	double my;
	double mz;
	double PDOP;	
};

#endif

void sppCalculate(SatOBSData satObsData, vector<SatResults> &result);

bool calResultWrite(string targetPath, SatOBSData data, vector<SatResults> result);
