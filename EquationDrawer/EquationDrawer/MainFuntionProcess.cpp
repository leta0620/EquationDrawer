#include "MainFuntionProcess.h"

// ��l��
FuntionProcess::FuntionProcess()
{
	;
}
// ��l�ơA��J�Ҧ����
FuntionProcess::FuntionProcess(vector<string> iniInputList)
{
	InputProcess(iniInputList);
}

// ��l�ơA��J�Ҧ���ơA�B����J�p�⪺�d��
FuntionProcess::FuntionProcess(vector<string> iniInputList, double start, double end)
{
	InputProcess(iniInputList);
	CalculateAllFuntion(start, end);
}



// �B�z��J
void FuntionProcess::InputProcess(vector<string> iniInputList)
{
	// �N��J��iinputList
	this->inputList.resize(iniInputList.size());
	for (int iniInput = 0; iniInput < iniInputList.size(); iniInput++)
	{
		this->inputList[iniInput].input = iniInputList[iniInput];
		this->inputList[iniInput].errorType = 0;
	}

	// ���J�����l�i��v���B�z
	for (int ini = 0; ini < iniInputList.size(); ini++)
	{
		// �Y��J��������
		if (!(iniInputList[ini].empty() || iniInputList[ini] == "\t"))
		{
			// �������l�����ť�
			string iniFormula, tmp;
			istringstream ss(iniInputList[ini]);
			while (ss >> tmp)
			{
				iniFormula += tmp;
			}

			// �P�_�O ��{�� �٬O �ܼ�
			if (iniFormula.size() >= 2)
			{
				// ��{��
				if (iniFormula[0] == 'y' && iniFormula[1] == '=')
				{
					// ����Ҧ�funtion�����ifuntionList
					iniFormula.erase(0, 2);
					this->inputList[ini].input = iniFormula;
					this->inputList[ini].isFuntion = true;
				}
				else
				{
					this->inputList[ini].isFuntion = false;

					// �����ܼƦW�٬O�_�X�k
					bool errorVariableName = false;
					bool hasEqual = false;
					string variableTmp;
					int test = 0;
					for (; test < iniFormula.size(); test++)
					{
						if (iniFormula[test] == '=')
						{
							hasEqual = true;
							break;
						}
						else if (!((iniFormula[test] >= 'a' && iniFormula[test] <= 'z') || (iniFormula[test] >= 'A' && iniFormula[test] <= 'Z') || (iniFormula[test] >= '0' && iniFormula[test] <= '9')))
						{
							// �ܼƦW�ٿ��~
							errorVariableName = true;
							this->inputList[ini].errorType = 13;
							break;
						}

						variableTmp += iniFormula[test];
					}

					// �ܼ�
					if (errorVariableName == false && hasEqual == true)
					{
						// �B�z�ܼ�
						iniFormula.erase(0, variableTmp.size());

						Calculate tmp(iniFormula);

					}
					// ���~
					else if (errorVariableName == true || hasEqual == false)
					{
						this->inputList[ini].errorType = 13;
						continue;
					}
				}
			}
		}
	}
}

// ���w�d��i��p��
void FuntionProcess::CalculateAllFuntion(double start, double end)
{
	for (int round = 0; round < this->inputList.size(); round++)
	{
		if (this->inputList[round].isFuntion)
		{
			Calculate tmp(this->inputList[round].input);

			this->inputList[round].input = tmp.GetCError();

			if (tmp.GetCError() == 0)
			{
				this->drawList.push_back(tmp.GetAnsList(start, end));
			}
		}
	}
}

// ������~�X�M��
vector<int> FuntionProcess::GetErrorList()
{
	vector<int> errorList;

	// �N���~�X���X��
	for (int i = 0; i < this->inputList.size(); i++)
	{
		errorList.push_back(inputList[i].errorType);
	}

	return errorList;
}

// ����nø�s���y�вM��
vector<vector<Pos>> FuntionProcess::GetDrawList()
{
	return this->drawList;
}