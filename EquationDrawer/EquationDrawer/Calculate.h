#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

// �B�̹B�⦡���O
class Calculate
{
public:
	// ��J�B�⦡��A�B�z�B�⦡(�B�⦡���i��)
	Calculate();
	Calculate(string formula);
	Calculate(string formula, double singalNum);
	Calculate(string formula, double start, double end);

	// �����l�B�⦡
	string GetOriginFormula();
	// �����Ǧ�
	vector<string> GetPostOrderFormula();

	// ������~�N�X
	int GetCError();

	// ����B�⦡����(��@�Ʀr�I)
	vector<double> GetAnsList(double singalNum);
	// ����B�⦡����(�s��Ʀr��)
	vector<double> GetAnsList(double start, double end);

	// �p���{��
	void Calculation(string input);
	// ��B�B�z��J
	void SetInput(string input);
	// ���Ψ��ର���
	void CutInput();
	// �p��a�J�Ʀr�����G(��@��)
	void CalculateAns(double x);
	// �p��a�J�Ʀr�����G(�d���)
	void CalculateAns(double start, double end);


private:
	int cError;

	string originFormula;
	string processFormula;	// ������
	vector<string> postOrderFormula;

	vector<double> ansList;

	// �p��ƭ�(������)
	double CalculateAnsSingal(double x);
};

