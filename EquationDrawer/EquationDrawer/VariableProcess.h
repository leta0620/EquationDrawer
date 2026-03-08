#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Calculate.h"
using namespace std;

// 變數處理類別
class VariableProcess
{
public:
	// 輸入變數式後，處理變數
	VariableProcess();
	VariableProcess(string variableFormula);

	// 獲取錯誤代碼
	int GetVError();

	// 獲取變數名字
	string GetVariableName();
	// 獲取變數數值
	double GetVariableNum();
	
private:
	int vError;

	string variableName;
	double variableNum;
};

