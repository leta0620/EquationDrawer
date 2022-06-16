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
};

