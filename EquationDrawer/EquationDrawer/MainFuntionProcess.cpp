#include "MainFuntionProcess.h"

//-----------FuntionProcess-----------//

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

					// �T�{�ܼƬO�_�s�b
					for (int checkV = 0; checkV < this->variableList.size(); checkV++)
					{
						if (this->variableList[checkV].name == variableTmp)
						{
							this->inputList[ini].errorType = 14;
							break;
						}
					}

					// �ܼ�
					if (errorVariableName == false && hasEqual == true && this->inputList[ini].errorType == 0)
					{
						// �B�z�ܼ�
						iniFormula.erase(0, variableTmp.size() + 1);

						Calculate tmp(iniFormula);

						// �N��Ǧ������ܼƱa�J�ƭ�
						for (int i = 0; i < this->variableList.size(); i++)
						{
							for (int j = 0; j < tmp.GetPostOrderFormula().size(); j++)
							{
								if (this->variableList[i].name == tmp.GetPostOrderFormula()[j])
								{
									tmp.SetPostOrder(j, to_string(this->variableList[i].num));
								}
							}
						}

						double variableNum = tmp.GetAnsList();

						this->inputList[ini].errorType = tmp.GetCError();

						// �K�[�s�ܼ�
						if (tmp.GetCError() == 0)
						{
							VariableItem newVariable;

							newVariable.name = variableTmp;
							newVariable.num = variableNum;

							this->variableList.push_back(newVariable);
						}

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

			// �N��Ǧ������ܼƱa�J�ƭ�
			for (int i = 0; i < this->variableList.size(); i++)
			{
				for (int j = 0; j < tmp.GetPostOrderFormula().size(); j++)
				{
					if (this->variableList[i].name == tmp.GetPostOrderFormula()[j])
					{
						tmp.SetPostOrder(j, to_string(this->variableList[i].num));
					}
				}
			}

			this->inputList[round].errorType = tmp.GetCError();

			// �ˬd�O�_���H�k�ܼ�
			for (int checkV = 0; checkV < tmp.GetPostOrderFormula().size(); checkV++)
			{
				string checkStr = tmp.GetPostOrderFormula()[checkV];
				if (!(checkStr[0] >= '0' && checkStr[0] <= '9'))
				{
					if (!(checkStr[0] == 'x' || checkStr[0] == '+' || checkStr[0] == '-' || checkStr[0] == '*' || checkStr[0] == '/' || checkStr[0] == '@'))
					{
						this->inputList[round].errorType = 13;
						break;
					}
				}
			}

			if (this->inputList[round].errorType == 0)
			{
				this->drawList.push_back(tmp.GetAnsList(start, end));
				this->colorList.push_back(round);
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

// ����iø�s���M��A�������l��J�����X��
vector<int> FuntionProcess::GetColorList()
{
	return this->colorList;
}