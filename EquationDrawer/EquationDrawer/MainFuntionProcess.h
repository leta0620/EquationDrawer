#pragma once
<<<<<<< HEAD
#include "VariableProcess.h"
#include "Calculate.h"
=======
#include "Calculate.h"
#include "Pos.h"
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

struct OriginInput
{
	string input;
	int errorType = 0;
<<<<<<< HEAD
=======
	bool isFuntion = true;
};

struct VariableItem
{
	string name;
	double num;
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};

// ��ƳB�z���O
class FuntionProcess
{
public:
	// ��l�ơA��J�Ҧ����
	FuntionProcess();
	FuntionProcess(vector<string> iniInputList);
	FuntionProcess(vector<string> iniInputList, double start, double end);

<<<<<<< HEAD
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
=======
	// �B�z��J�A����O��{���٬O�ܼ�
	void InputProcess(vector<string> iniInputList);

	// ���w�d��i��p��
	void CalculateAllFuntion(double start, double end);


	// ������~�X�M��
	vector<int> GetErrorList();
	// ����nø�s���y�вM��
	vector<vector<Pos>> GetDrawList();
	// ����iø�s���M��A�������l��J�����X��
	vector<int> GetColorList();


private:
	vector<OriginInput> inputList;	// ��J�M��A�]�t���~�ȩM�O�_���禡���P�_
	vector<string> funtionList;	// �禡�M��
	vector<VariableItem> variableList;	// �ܼƲM��

	vector<vector<Pos>> drawList;	// ø�ϲM��A�̭��|��iø�s���y�вM��
	vector<int> colorList;			// �iø�s���M��A�������l��J�����X��
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};

