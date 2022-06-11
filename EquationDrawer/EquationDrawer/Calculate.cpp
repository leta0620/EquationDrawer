#include "Calculate.h"

//--------�Ƶ{��--------//

// �^�ǹB����u����
int OperatorPriority(char in)
{
	switch (in)
	{
	case'@':	// �t���u���סG4
		return 4;
	case'!':	// ���h�u���סG3
		return 3;
	case'^':	// �����u���סG2
		return 2;
	case'*':	// �����u���סG1
		return 1;
	case'/':	// �����u���סG1
		return 1;
	case'+':	// �[���u���סG0
		return 0;
	case'-':	// ��u���סG0
		return 0;
	default:
		return -1;
	}
}

//--------Calculate���O--------//

// ��J�B�⦡��A�i��B�z
Calculate::Calculate()
{
	this->cError = 0;
	this->ansList.clear();
	this->originFormula = "";
	this->processFormula = "";
}
Calculate::Calculate(string formula)
{
	this->cError = 0;
	this->ansList.clear();
	this->originFormula = "";
	this->processFormula = "";

	Calculation(formula);
}
Calculate::Calculate(string formula, double singalNum)
{
	this->cError = 0;
	this->ansList.clear();
	this->originFormula = "";
	this->processFormula = "";

	Calculation(formula);
	this->CalculateAns(singalNum);
}
Calculate::Calculate(string formula, double start, double end)
{
	this->cError = 0;
	this->ansList.clear();
	this->originFormula = "";
	this->processFormula = "";

	Calculation(formula);
	this->CalculateAns(start, end);
}



string Calculate::GetOriginFormula()
{
	return this->originFormula;
}
vector<string> Calculate::GetPostOrderFormula()
{
	return this->postOrderFormula;
}

// ����B�⦡����(��@�Ʀr�I)
vector<double> Calculate::GetAnsList(double singalNum)
{
	vector<double> tmp;
	return tmp;
}
// ����B�⦡����(�s��Ʀr��)
vector<double> Calculate::GetAnsList(double start, double end)
{
	vector<double> tmp;
	return tmp;
}

// �p���{��
void Calculate::Calculation(string input)
{
	SetInput(input);
	if (this->cError != 0)
	{
		return;
	}
	CutInput();
}

// ��J�ƾǦ�
void Calculate::SetInput(string input)
{
	if (input.size() > 0)
	{
		if (!(input[0] == '-' || input[0] == '(' || (input[0] >= 'A' && input[0] <= 'Z') || (input[0] >= 'a' && input[0] <= 'z') || (input[0] >= '0' && input[0] <= '9')))
		{
			this->cError = 1;
			return;
		}
	}

	for (int i = 0; i < input.size(); i++)
	{
		if (!((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '.' || input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '!' || input[i] == '.' || input[i] == '^' || input[i] == '(' || input[i] == ')'))
		{
			this->cError = 1;
			break;
		}
	}

	this->originFormula = input;
}

// �P�_��J�r��B���ǡB�p�⧹��ians(�`�N�ܼơH)(�|���p�ƿ�J)
void Calculate::CutInput()
{
	// �N�t���ܦ�'@'
	this->processFormula = this->originFormula;
	for (int transNeg = 0; transNeg < this->processFormula.size(); transNeg++)
	{
		if (transNeg < this->processFormula.size() - 1)
		{
			// �Y��J���Ĥ@�Ӧr�����t 
			if ((transNeg == 0 && this->processFormula[transNeg] == '-'))
			{
				this->processFormula[transNeg] = '@';
			}
			// �Y��J�r�������N�Ÿ� �� �t�� �A�ҡG(5+-4) or (5+(-6))
			else if (((this->processFormula[transNeg] < '0' || this->processFormula[transNeg] == '^') && this->processFormula[transNeg] != ')' && this->processFormula[transNeg] != '!' && this->processFormula[transNeg + 1] == '-'))
			{
				this->processFormula[transNeg + 1] = '@';
			}
		}
	}

	// �ˬd�p���I
	for (int dotErrorTest = 0; dotErrorTest < this->processFormula.size(); dotErrorTest++)
	{
		// �Ÿ�.23 or 0.-1 or 0.+1
		if (this->processFormula[dotErrorTest] == '.')
		{
			if (dotErrorTest < this->processFormula.size() - 1)
			{
				if (!(this->processFormula[dotErrorTest + 1] >= '0' && this->processFormula[dotErrorTest + 1] <= '9'))
				{
					this->cError = 2;
					return;
				}
				if (this->processFormula[dotErrorTest - 1] == '!')
				{
					this->cError = 2;
					return;
				}
			}
			else
			{
				this->cError = 2;
				return;
			}
		}
	}

	// ��r��i����γB��
	vector<string> cutString;
	string tmp;
	int loc = 0;

	while (loc < this->processFormula.size())
	{
		if (this->processFormula[loc] >= '0' && this->processFormula[loc] <= '9')
		{
			bool hasDot = false;

			// ����
			for (; (this->processFormula[loc] >= '0' && this->processFormula[loc] <= '9') || this->processFormula[loc] == '.'; loc++)
			{
				if (hasDot && this->processFormula[loc] == '.')
				{
					this->cError = 2;
					return;
				}

				if (this->processFormula[loc] == '.')
				{
					hasDot = true;
				}

				tmp += this->processFormula[loc];
			}

			// ��J�� 56ABC �����A���Ʀr�A��r�����~��J
			if ((this->processFormula[loc] >= 'A' && this->processFormula[loc] <= 'Z') || (this->processFormula[loc] >= 'a' && this->processFormula[loc] <= 'z'))
			{
				this->cError = 3;
				return;
			}

			cutString.push_back(tmp);
			tmp.clear();
		}
		else if ((this->processFormula[loc] >= 'A' && this->processFormula[loc] <= 'Z') || (this->processFormula[loc] >= 'a' && this->processFormula[loc] <= 'z'))
		{
			// �ܼƦW
			for (; (this->processFormula[loc] >= 'A' && this->processFormula[loc] <= 'Z') || (this->processFormula[loc] >= 'a' && this->processFormula[loc] <= 'z') || (this->processFormula[loc] >= '0' && this->processFormula[loc] <= '9'); loc++)
			{
				tmp += this->processFormula[loc];
			}

			cutString.push_back(tmp);
			tmp.clear();
		}
		else if (this->processFormula[loc] == '@')
		{
			// �t��
			tmp += this->processFormula[loc];
			loc++;

			if (loc < this->processFormula.size())
			{
				if (!(this->processFormula[loc] >= '0' && this->processFormula[loc] <= '9'))
				{
					cutString.push_back(tmp);
					tmp.clear();
				}
				else if (this->processFormula[loc] >= '0' && this->processFormula[loc] <= '9')
				{
					bool hasDot = false;

					// �Ʀr
					for (; (this->processFormula[loc] >= '0' && this->processFormula[loc] <= '9') || this->processFormula[loc] == '.'; loc++)
					{
						if (hasDot && this->processFormula[loc] == '.')
						{
							this->cError = 2;
							return;
						}

						if (this->processFormula[loc] == '.')
						{
							hasDot = true;
						}

						tmp += this->processFormula[loc];
					}

					// ��J�� 56ABC �����A���Ʀr�A��r�����~��J
					if ((this->processFormula[loc] >= 'A' && this->processFormula[loc] <= 'Z') || (this->processFormula[loc] >= 'a' && this->processFormula[loc] <= 'z'))
					{
						this->cError = 3;
						return;
					}

					cutString.push_back(tmp);
					tmp.clear();
				}
			}
			else
			{
				cutString.push_back(tmp);
				tmp.clear();
			}
		}
		else if (this->processFormula[loc] < '0' || this->processFormula[loc] == '^')
		{
			// ��L�B��Ÿ�
			tmp += this->processFormula[loc];
			cutString.push_back(tmp);
			loc++;
			tmp.clear();
		}
		else
		{
			// ��L�r���A��error�A�òפ�B��
			this->cError = 1;
			return;
		}
	}

	// �ˬd���ε��G
	int frontBrackets = 0, backBrackets = 0;
	for (int errorTest = 0; errorTest < cutString.size(); errorTest++)
	{
		// �P�_�e��A���ƶq�O�_�ۦP
		if (cutString[errorTest] == "(")
		{
			frontBrackets++;
		}
		else if (cutString[errorTest] == ")")
		{
			backBrackets++;
		}

		// �P�_�O�_��0000
		bool allZero = true;
		for (int testZero = 0; testZero < cutString[errorTest].size(); testZero++)
		{
			if (cutString[errorTest][testZero] != '0')
			{
				allZero = false;
			}
		}
		if (allZero)
		{
			cutString[errorTest] = "0";
		}

		if (errorTest >= 2)
		{
			// ...!46...
			if (cutString[errorTest] == "!" && !((cutString[errorTest - 1][cutString[errorTest - 1].size() - 1] >= '0' && cutString[errorTest - 1][cutString[errorTest - 1].size() - 1] <= '9') || (cutString[errorTest - 1] == ")")))
			{
				this->cError = 4;
				return;
			}

			// 5^^4
			if (cutString[errorTest] == "^" && cutString[errorTest - 1] >= "^")
			{
				this->cError = 5;
				return;
			}
		}
	}
	// �e�A����A���ƶq���P�A����
	if (frontBrackets != backBrackets)
	{
		this->cError = 10;
		return;
	}

	// ����
	vector<string> postfix;
	vector<string> sign;

	for (int round = 0; round < cutString.size(); round++)
	{
		// �Y���Χ����r��O�Ʀr || ���Χ������t�� || ���Χ����O�ܼ�
		if ((cutString[round][0] >= '0' && cutString[round][0] <= '9') || (cutString[round][0] == '@' && cutString[round].size() > 1) || (cutString[round][0] >= 'A' && cutString[round][0] <= 'Z') || (cutString[round][0] >= 'a' && cutString[round][0] <= 'z'))
		{
			postfix.push_back(cutString[round]);
		}
		else
		{
			sign.push_back(cutString[round]);
		}

		// �P�_�Ÿ��u����
		if (sign.size() > 0)
		{
			// �Y��i���O�k�A��
			if (sign[sign.size() - 1] == ")")
			{
				sign.pop_back();
				if (sign.size() > 0)
				{
					while (sign[sign.size() - 1] != "(" && sign.size() > 1)
					{
						postfix.push_back(sign[sign.size() - 1]);
						sign.pop_back();
					}
				}
				if (sign.size() > 0)
				{
					sign.pop_back();
				}
			}
			// �����ӲŸ����u����
			else if (sign.size() > 1)
			{
				// �Y�᭱���B����u���Ǥp�󵥩�e�����B���
				while (OperatorPriority(sign[sign.size() - 2][0]) >= OperatorPriority(sign[sign.size() - 1][0]) && sign[sign.size() - 2] != "(" && sign[sign.size() - 1] != "(")
				{
					postfix.push_back(sign[sign.size() - 2]);
					sign[sign.size() - 2] = sign[sign.size() - 1];
					sign.pop_back();
					if (sign.size() <= 1)
					{
						break;
					}
				}
			}
		}
	}

	// �N�Ѿl���Ÿ���i��Ǧ�
	while (sign.size() > 0)
	{
		postfix.push_back(sign[sign.size() - 1]);
		sign.pop_back();
	}

	this->postOrderFormula = postfix;
}

// �p��a�J�Ʀr�����G(��@��)
void Calculate::CalculateAns(double x)
{
	int ans = this->CalculateAnsSingal(x);
	if (this->cError == 0)
	{
		this->ansList.push_back(ans);
	}
}

// �p��a�J�Ʀr�����G(�d���)
void Calculate::CalculateAns(double start, double end)
{
	int precision = 100;	// ��סAstart �� end �n�������h�֡A�Y���C���[1�A�h��1�A�Y���C���[0.1�A�h��10
	int calculateTimes = (end - start) * precision;	// �ݭp�⪺����

	for (int ansRound = 0; ansRound < calculateTimes; ansRound++)
	{
		int x = start + ansRound / precision;

		int ans = this->CalculateAnsSingal(x);
		if (ans != -1)
		{
			this->ansList.push_back(ans);
		}
	}
}

// �p��ƭ�(������)
double Calculate::CalculateAnsSingal(double x)
{
	// �p��
	int formulaDigit = 0;	// �ثe��Ǧ�����쪺���
	vector<string> postOrderCalculation(this->postOrderFormula);
	for (; postOrderCalculation.size() > 1 && formulaDigit < postOrderCalculation.size(); formulaDigit++)
	{
		// �[�k
		if (postOrderCalculation[formulaDigit] == "+")
		{
			if (formulaDigit >= 2)
			{
				string tmp;
				double a = 0, b = 0;
				a = stod(postOrderCalculation[formulaDigit - 2]);
				b = stod(postOrderCalculation[formulaDigit - 1]);
				tmp = to_string(a + b);
				postOrderCalculation[formulaDigit - 2] = tmp;
				postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit - 1, postOrderCalculation.begin() + formulaDigit + 1);
				formulaDigit = 0;
			}
			else
			{
				this->cError = 6;
				return -1;
			}
		}
		// ��k
		else if (postOrderCalculation[formulaDigit] == "-")
		{
			if (formulaDigit >= 2)
			{
				string tmp;
				double a = 0, b = 0;
				a = stod(postOrderCalculation[formulaDigit - 2]);
				b = stod(postOrderCalculation[formulaDigit - 1]);
				tmp = to_string(a - b);
				postOrderCalculation[formulaDigit - 2] = tmp;
				postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit - 1, postOrderCalculation.begin() + formulaDigit + 1);
				formulaDigit = 0;
			}
			else
			{
				this->cError = 7;
				return -1;
			}
		}
		// ���k
		else if (postOrderCalculation[formulaDigit] == "*")
		{
			if (formulaDigit >= 2)
			{
				string tmp;
				double a = 0, b = 0;
				a = stod(postOrderCalculation[formulaDigit - 2]);
				b = stod(postOrderCalculation[formulaDigit - 1]);
				tmp = to_string(a * b);
				postOrderCalculation[formulaDigit - 2] = tmp;
				postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit - 1, postOrderCalculation.begin() + formulaDigit + 1);
				formulaDigit = 0;
			}
			else
			{
				this->cError = 8;
				return -1;
			}
		}
		// ���k
		else if (postOrderCalculation[formulaDigit] == "/")
		{
			if (formulaDigit >= 2)
			{
				if (postOrderCalculation[formulaDigit - 1] == "0")
				{
					this->cError = 9;
					return -1;
				}

				string tmp;
				double a = 0, b = 0;
				a = stod(postOrderCalculation[formulaDigit - 2]);
				b = stod(postOrderCalculation[formulaDigit - 1]);
				tmp = to_string(a / b);
				postOrderCalculation[formulaDigit - 2] = tmp;
				postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit - 1, postOrderCalculation.begin() + formulaDigit + 1);
				formulaDigit = 0;
			}
			else
			{
				this->cError = 9;
				return -1;
			}
		}
		// ����
		else if (postOrderCalculation[formulaDigit] == "^")
		{
			if (formulaDigit >= 2)
			{
				string tmp;
				double a = 0, b = 0;
				a = stod(postOrderCalculation[formulaDigit - 2]);
				b = stod(postOrderCalculation[formulaDigit - 1]);
				tmp = to_string(pow(a, b));
				postOrderCalculation[formulaDigit - 2] = tmp;
				postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit - 1, postOrderCalculation.begin() + formulaDigit + 1);
				formulaDigit = 0;
			}
			else
			{
				this->cError = 10;
				return -1;
			}
		}
		// ���h
		else if (postOrderCalculation[formulaDigit] == "!")
		{
			/*if (formulaDigit >= 1)
			{
				if (!(postOrderCalculation[formulaDigit - 1].denominator == "1") || postOrderCalculation[formulaDigit - 1].sign)
				{
					error = 11;
					return;
				}

				Fraction tmp;
				if (postOrderCalculation[formulaDigit - 1].numerator == "0")
				{
					tmp.numerator = "1";
					tmp.denominator = "1";
				}
				else
				{
					tmp = !postOrderCalculation[formulaDigit - 1];
				}

				postOrderCalculation[formulaDigit - 1] = tmp;
				postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit);
				formulaDigit = 0;
			}
			else
			{
				error = 11;
				return;
			}*/
		}
		// �t��
		else if (postOrderCalculation[formulaDigit] == "@")
		{
			if (formulaDigit >= 1)
			{
				string tmp = "-";
				tmp += postOrderCalculation[formulaDigit - 1];
				postOrderCalculation[formulaDigit - 1] = tmp;
				postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit);
				formulaDigit = 0;
			}
			else
			{
				this->cError = 12;
				return -1;
			}
		}
	}

	// �p�⵲�G
	string result = postOrderCalculation[0];
	// �ˬd�O�_���ݯd�B�⤸
	if (postOrderCalculation.size() > 1 || !(result[0] >= '0' && result[0] <= '9'))
	{
		this->cError = 10;
		return -1;
	}
	
	return stod(result);
}

