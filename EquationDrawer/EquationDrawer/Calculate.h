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

// �B�̹B�⦡���O
class Calculate
{
public:
	// ��J�B�⦡��A�B�z�B�⦡(�B�⦡���i��)
	Calculate();
	Calculate(string formula);
<<<<<<< HEAD
	Calculate(string formula, double singalNum);
	Calculate(string formula, double start, double end);
=======
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

	// �����l�B�⦡
	string GetOriginFormula();
	// �����Ǧ�
	vector<string> GetPostOrderFormula();

	// ������~�N�X
	int GetCError();

<<<<<<< HEAD
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
=======
	// ����B�⦡����(�L�a�Jx)
	double GetAnsList();
	// ����B�⦡����(��@�Ʀr�I)
	vector<Pos> GetAnsList(double singalNum);
	// ����B�⦡����(�s��Ʀr��)
	vector<Pos> GetAnsList(double start, double end);

	// ����Ǧ�
	void SetPostOrder(int Loc, string input);

private:
	int cError;
	bool runError;
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

	string originFormula;
	string processFormula;	// ������
	vector<string> postOrderFormula;

<<<<<<< HEAD
	vector<double> ansList;

	// �p��ƭ�(������)
	double CalculateAnsSingal(double x);
=======
	vector<Pos> ansList;

	// �p��ƭ�(������)
	double CalculateAnsSingal(double x);

	// �p���{��
	void Calculation(string input);
	// ��B�B�z��J�A�N���X�檺��J��r��X��
	void SetInput(string input);
	// ���Ψ��ର���
	void CutInput();
	// �p�⵲�G
	double CalculateAns();
	// �p��a�J�Ʀr�����G(��@��)
	void CalculateAns(double x);
	// �p��a�J�Ʀr�����G(�d���)
	void CalculateAns(double start, double end);
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};

