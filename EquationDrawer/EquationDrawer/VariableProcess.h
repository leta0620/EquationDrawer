#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Calculate.h"
using namespace std;

// �ܼƳB�z���O
class VariableProcess
{
public:
	// ��J�ܼƦ���A�B�z�ܼ�
	VariableProcess();
	VariableProcess(string variableFormula);

	// ������~�N�X
	int GetVError();

	// ����ܼƦW�r
	string GetVariableName();
	// ����ܼƼƭ�
	double GetVariableNum();
	
private:
	int vError;

	string variableName;
	double variableNum;
};

