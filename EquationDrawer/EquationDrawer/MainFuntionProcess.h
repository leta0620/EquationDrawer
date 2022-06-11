#pragma once
#include "VariableProcess.h"
#include "Calculate.h"

struct OriginInput
{
	string input;
	int errorType = 0;
};

// ��ƳB�z���O
class FuntionProcess
{
public:
	// ��l�ơA��J�Ҧ����
	FuntionProcess();
	FuntionProcess(vector<string> iniInputList);
	FuntionProcess(vector<string> iniInputList, double start, double end);

	// �B�z��J
	void InputProcess(vector<string> iniInputList);

	//// ������~�X
	//int GetErrorType();
	// ������~�N�X�M�ԲӸ��
	string GetErrorTypeAndInformation();

	// ��o��l��J�M��
	vector<OriginInput> GetInputList;
	// ����ܼƲM��
	vector<VariableProcess> GetVariableList;
	// �����{���M��
	vector<Calculate> GetFuntionList;
	// �N�ܼƭȩ�J�禡
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

