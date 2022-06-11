#include "MainFuntionProcess.h"

// 初始化
FuntionProcess::FuntionProcess()
{
	;
}
// 初始化，輸入所有函數
FuntionProcess::FuntionProcess(vector<string> iniInputList)
{
	InputProcess(iniInputList);
}

// 初始化，輸入所有函數，且有輸入計算的範圍
FuntionProcess::FuntionProcess(vector<string> iniInputList, double start, double end)
{
	InputProcess(iniInputList);
}



// 處理輸入
void FuntionProcess::InputProcess(vector<string> iniInputList)
{
	// 將輸入放進inputList
	this->inputList.resize(iniInputList.size());
	for (int iniInput = 0; iniInput < iniInputList.size(); iniInput++)
	{
		this->inputList[iniInput].input = iniInputList[iniInput];
		this->inputList[iniInput].errorType = 0;
	}

	// 對輸入的式子進行逐條處理
	for (int ini = 0; ini < iniInputList.size(); ini++)
	{
		// 若輸入式不為空
		if (!(iniInputList[ini].empty() || iniInputList[ini] == "\t"))
		{
			// 消除式子間的空白
			string iniFormula, tmp;
			istringstream ss(iniInputList[ini]);
			while (ss >> tmp)
			{
				iniFormula += tmp;
			}

			// 判斷是 方程式 還是 變數
			if (iniFormula.size() >= 2)
			{
				// 方程式
				if (iniFormula[0] == 'y' && iniFormula[1] == '=')
				{
					iniFormula.erase(0, 2);
					Calculate funtionCalculate(iniFormula);
					this->funtionList.push_back(funtionCalculate);
				}
				else
				{
					// 測試變數名稱是否合法
					bool errorVariableName = false;
					int test = 0;
					for (; test < iniFormula.size(); test++)
					{
						if (iniFormula[test] == '=')
						{
							break;
						}
						else if (!((iniFormula[test] >= 'a' && iniFormula[test] <= 'z') || (iniFormula[test] >= 'A' && iniFormula[test] <= 'Z') || (iniFormula[test] >= '0' && iniFormula[test] <= '9')))
						{
							// 變數名稱錯誤
							errorVariableName = true;
							break;
						}
					}

					// 變數
					if (errorVariableName == false)
					{
						// 建立變數類別
						VariableProcess variable(iniFormula);

					}
					// 錯誤
					else if (errorVariableName == true)
					{
						this->inputList[ini].errorType = 1;
						continue;
					}

				}
			}
		}
	}
}

// 將變數值放入函式
void FuntionProcess::PutInVariable()
{

}