#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "Pos.h"
using namespace std;

// �B�̹B�⦡���O
class Calculate
{
public:
	// ��J�B�⦡��A�B�z�B�⦡(�B�⦡���i��)
	Calculate();
	Calculate(string formula);

	// �����l�B�⦡
	string GetOriginFormula();
	// �����Ǧ�
	vector<string> GetPostOrderFormula();

	// ������~�N�X
	int GetCError();

	// ����B�⦡����(��@�Ʀr�I)
	vector<Pos> GetAnsList(double singalNum);
	// ����B�⦡����(�s��Ʀr��)
	vector<Pos> GetAnsList(double start, double end);


private:
	int cError;

	string originFormula;
	string processFormula;	// ������
	vector<string> postOrderFormula;

	vector<Pos> ansList;

	// �p��ƭ�(������)
	double CalculateAnsSingal(double x);

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
};

