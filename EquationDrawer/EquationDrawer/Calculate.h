#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
<<<<<<< HEAD
=======
#include "Pos.h"
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
using namespace std;

// 處裡運算式類別
class Calculate
{
public:
	// 輸入運算式後，處理運算式(運算式不可有)
	Calculate();
	Calculate(string formula);
<<<<<<< HEAD
	Calculate(string formula, double singalNum);
	Calculate(string formula, double start, double end);
=======
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

	// 獲取初始運算式
	string GetOriginFormula();
	// 獲取後序式
	vector<string> GetPostOrderFormula();

	// 獲取錯誤代碼
	int GetCError();

<<<<<<< HEAD
	// 獲取運算式答案(單一數字點)
	vector<double> GetAnsList(double singalNum);
	// 獲取運算式答案(連續數字串)
	vector<double> GetAnsList(double start, double end);

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


private:
	int cError;
=======
	// 獲取運算式答案(無帶入x)
	double GetAnsList();
	// 獲取運算式答案(單一數字點)
	vector<Pos> GetAnsList(double singalNum);
	// 獲取運算式答案(連續數字串)
	vector<Pos> GetAnsList(double start, double end);

	// 更改後序式
	void SetPostOrder(int Loc, string input);

private:
	int cError;
	bool runError;
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

	string originFormula;
	string processFormula;	// 內部用
	vector<string> postOrderFormula;

<<<<<<< HEAD
	vector<double> ansList;

	// 計算數值(內部用)
	double CalculateAnsSingal(double x);
=======
	vector<Pos> ansList;

	// 計算數值(內部用)
	double CalculateAnsSingal(double x);

	// 計算方程式
	void Calculation(string input);
	// 初步處理輸入，將不合格的輸入文字找出來
	void SetInput(string input);
	// 切割並轉為後序
	void CutInput();
	// 計算結果
	double CalculateAns();
	// 計算帶入數字的結果(單一值)
	void CalculateAns(double x);
	// 計算帶入數字的結果(範圍值)
	void CalculateAns(double start, double end);
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};

