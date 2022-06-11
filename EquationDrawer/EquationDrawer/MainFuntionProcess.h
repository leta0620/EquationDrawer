#pragma once
#include "VariableProcess.h"
#include "Calculate.h"

struct OriginInput
{
	string input;
	int errorType = 0;
};

// 函數處理類別
class FuntionProcess
{
public:
	// 初始化，輸入所有函數
	FuntionProcess();
	FuntionProcess(vector<string> iniInputList);
	FuntionProcess(vector<string> iniInputList, double start, double end);

	// 處理輸入
	void InputProcess(vector<string> iniInputList);

	//// 獲取錯誤碼
	//int GetErrorType();
	// 獲取錯誤代碼和詳細資料
	string GetErrorTypeAndInformation();

	// 獲得原始輸入清單
	vector<OriginInput> GetInputList;
	// 獲取變數清單
	vector<VariableProcess> GetVariableList;
	// 獲取方程式清單
	vector<Calculate> GetFuntionList;
	// 將變數值放入函式
	void PutInVariable();

private:
	vector<OriginInput> inputList;
	vector<VariableProcess> variableList;
	vector<Calculate> funtionList;

	/*
	a = 3
	b = 3a + 5
	y = ax
	y = 3x - b
	*/
};

