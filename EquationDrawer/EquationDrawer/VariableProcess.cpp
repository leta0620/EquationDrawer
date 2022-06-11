#include "VariableProcess.h"

// 輸入變數式後，處理變數
VariableProcess::VariableProcess()
{

}
VariableProcess::VariableProcess(string variableFormula)
{

}

// 獲取變數名字
string VariableProcess::GetVariableName()
{
	return this->variableName;
}
// 獲取變數數值
double VariableProcess::GetVariableNum()
{
	return this->variableNum;
}