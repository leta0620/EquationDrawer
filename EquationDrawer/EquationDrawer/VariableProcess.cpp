#include "VariableProcess.h"

// ��J�ܼƦ���A�B�z�ܼ�
VariableProcess::VariableProcess()
{

}
VariableProcess::VariableProcess(string variableFormula)
{

}

// ����ܼƦW�r
string VariableProcess::GetVariableName()
{
	return this->variableName;
}
// ����ܼƼƭ�
double VariableProcess::GetVariableNum()
{
	return this->variableNum;
}