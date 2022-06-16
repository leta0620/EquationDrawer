#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "Pos.h"
using namespace std;

// 處裡運算式類別
class Calculate
{
public:
	// 輸入運算式後，處理運算式(運算式不可有)
	Calculate();
	Calculate(string formula);

	// 獲取初始運算式
	string GetOriginFormula();
	// 獲取後序式
	vector<string> GetPostOrderFormula();

	// 獲取錯誤代碼
	int GetCError();

	// 獲取運算式答案(單一數字點)
	vector<Pos> GetAnsList(double singalNum);
	// 獲取運算式答案(連續數字串)
	vector<Pos> GetAnsList(double start, double end);


private:
	int cError;

	string originFormula;
	string processFormula;	// 內部用
	vector<string> postOrderFormula;

	vector<Pos> ansList;

	// 計算數值(內部用)
	double CalculateAnsSingal(double x);

	// 計算方程式
	void Calculation(string input);
	// 初步處理輸入
	void SetInput(string input);
	// 切割並轉為後序
	void CutInput();
	// 計算帶入數字的結果(單一值)
	void CalculateAns(double x);
	// 計算帶入數字的結果(範圍值)
	void CalculateAns(double start, double end);
};

