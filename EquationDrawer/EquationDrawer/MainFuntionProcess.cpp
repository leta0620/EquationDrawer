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
					iniFormula.erase(0, 2);
					Calculate funtionCalculate(iniFormula);
					this->funtionList.push_back(funtionCalculate);
				}
				else
				{
					// �����ܼƦW�٬O�_�X�k
					bool errorVariableName = false;
					int test = 0;
					for (; test < iniFormula.size(); test++)
					{
						if (iniFormula[test] == '=')
						{
							break;
						}
						else if (!((iniFormula[test] >= 'a' && iniFormula[test] <= 'z') || (iniFormula[test] >= 'A' && iniFormula[test] <= 'Z') || (iniFormula[test] >= '0' && iniFormula[test] <= '9')))
						{
							// �ܼƦW�ٿ��~
							errorVariableName = true;
							break;
						}
					}

					// �ܼ�
					if (errorVariableName == false)
					{
						// �إ��ܼ����O
						VariableProcess variable(iniFormula);

					}
					// ���~
					else if (errorVariableName == true)
					{
						this->inputList[ini].errorType = 1;
						continue;
					}

				}
			}
		}
	}
}

// �N�ܼƭȩ�J�禡
void FuntionProcess::PutInVariable()
{

}