#pragma once
#include "Calculate.h"
#include "Pos.h"

struct OriginInput
{
	string input;
	int errorType = 0;
	bool isFuntion = true;
};

struct VariableItem
{
	string name;
	double num;
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

	// 給定範圍進行計算
	void CalculateAllFuntion(double start, double end);


	// 獲取錯誤碼清單
	vector<int> GetErrorList();
	// 獲取要繪製的座標清單
	vector<vector<Pos>> GetDrawList();
	// 獲取可繪製的清單，對應到原始輸入的哪幾行
	vector<int> GetColorList();


private:
	vector<OriginInput> inputList;	// 輸入清單，包含錯誤值和是否為函式的判斷
	vector<string> funtionList;	// 函式清單
	vector<VariableItem> variableList;	// 變數清單

	vector<vector<Pos>> drawList;	// 繪圖清單，裡面會放可繪製的座標清單
	vector<int> colorList;			// 可繪製的清單，對應到原始輸入的哪幾行
};

