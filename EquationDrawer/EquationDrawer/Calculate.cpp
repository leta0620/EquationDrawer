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
	this->runError = false;
	this->ansList.clear();
	this->originFormula = "";
	this->processFormula = "";
}
Calculate::Calculate(string formula)
{
	this->cError = 0;
	this->runError = false;
	this->ansList.clear();
	this->originFormula = "";
	this->processFormula = "";

	Calculation(formula);
}


// �����l�B�⦡
string Calculate::GetOriginFormula()
{
	return this->originFormula;
}
// �����Ǧ�
vector<string> Calculate::GetPostOrderFormula()
{
	return this->postOrderFormula;
}

// ����B�⦡����(�L�a�Jx)
double Calculate::GetAnsList()
{
	return this->CalculateAns();
}

// ����B�⦡����(��@�Ʀr�I)
vector<Pos> Calculate::GetAnsList(double singalNum)
{
	this->ansList.clear();
	CalculateAns(singalNum);

	return this->ansList;
}
// ����B�⦡����(�s��Ʀr��)
vector<Pos> Calculate::GetAnsList(double start, double end)
{
	this->ansList.clear();
	CalculateAns(start, end);

	bool allError = true;
	for (int checkP = 0; checkP < this->ansList.size(); checkP++)
	{
		if (this->ansList[checkP].errorPos == false)
		{
			allError = false;
		}
	}

	if (!allError)
	{
		return this->ansList;
	}
	else
	{
		this->ansList.clear();
		return this->ansList;
	}
}

// �p���{��(�������Ϋ���)
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
		if (!(input[0] == '-' || input[0] == '(' || (input[0] >= 'A' && input[0] <= 'Z') || (input[0] >= 'a' && input[0] <= 'z') || (input[0] >= '0' && input[0] <= '9' || input[0] == '@')))
		{
			this->cError = 1;
			return;
		}
	}

	for (int i = 0; i < input.size(); i++)
	{
		if (!((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '.' || input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '!' || input[i] == '.' || input[i] == '^' || input[i] == '(' || input[i] == ')' || input[0] == '@'))
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
				if (this->processFormula[loc] == 'x')
				{
					continue;
				}
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

			// �p�G��J�O�T�����
			if (tmp == "sin" || tmp == "cos" || tmp == "tan")
			{
				for (; this->processFormula[loc] != ')' && loc < this->processFormula.size(); loc++)
				{
					tmp += this->processFormula[loc];
				}
				if (loc < this->processFormula.size())
				{
					if (this->processFormula[loc] == ')')
					{
						tmp += this->processFormula[loc];
						loc++;
					}
					else
					{
						this->cError = 15;
						return;
					}
				}
				else
				{
					this->cError = 15;
					return;
				}
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
			if (cutString[errorTest] == "^" && cutString[errorTest - 1] >= "^" && cutString[errorTest - 1] != "x")
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
		// �Y���Χ����r��O�Ʀr || ���Χ������t�� || ���Χ����O�ܼ� || ���Χ��O�T�����
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

	// �T�{�Ÿ��ƶq�O�_���T
	int operatorNum = 0, numberNum = 0;
	for (int checkOperator = 0; checkOperator < postfix.size(); checkOperator++)
	{
		if (postfix[checkOperator] == "*" || postfix[checkOperator] == "/" || postfix[checkOperator] == "+" || postfix[checkOperator] == "-" || postfix[checkOperator] == "^")
		{
			operatorNum++;
		}
		else if (postfix[checkOperator] != "@")
		{
			numberNum++;
		}
	}

	if (operatorNum != numberNum - 1)
	{
		this->cError = 10;
	}

	this->postOrderFormula = postfix;
}

// �p��a�J�Ʀr�����G(��@��)
void Calculate::CalculateAns(double x)
{
	double ans = this->CalculateAnsSingal(x);
	if (this->cError == 0)
	{
		Pos tmp;
		tmp.setPos(x, ans);

		this->ansList.push_back(tmp);
	}
}

// �p��a�J�Ʀr�����G(�d���)
void Calculate::CalculateAns(double start, double end)
{
	int calculateTimes = 800;	// �ݭp�⪺����

	vector<Pos> tmpVector;
	for (int ansRound = 0; ansRound < calculateTimes; ansRound++)
	{
		double x = start + (ansRound * ((end - start) / calculateTimes));
		Pos tmp;

		double ans = this->CalculateAnsSingal(x);
		if (ans != -1)
		{
			tmp.setPos(x, ans);

			if (this->runError == true)
			{
				tmp.SetErrorPos(true);
				this->runError = false;
			}
		}
		else
		{
			tmp.setPos(x, ans);
			tmp.errorPos = true;
		}

		this->ansList.push_back(tmp);
	}
}


// ������~�N�X
int Calculate::GetCError()
{
	return this->cError;
}

// ����Ǧ�
void Calculate::SetPostOrder(int Loc, string input)
{
	if (Loc <= this->postOrderFormula.size() - 1)
	{
		this->postOrderFormula[Loc] = input;
	}
}


// �p�⵲�G(������)
double Calculate::CalculateAns()
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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

				if (b == 0)
				{
					this->cError = 9;
					return -1;
				}

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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					this->cError = 13;
					return -1;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

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
			this->cError = 11;
			return -1;
		}
		// �t��
		else if (postOrderCalculation[formulaDigit] == "@")
		{
			if (formulaDigit >= 1)
			{
				if (postOrderCalculation[formulaDigit - 1][0] == '@')
				{
					postOrderCalculation[formulaDigit - 1][0] = '-';
				}

				string tmp = "-";
				if (postOrderCalculation[formulaDigit - 1][0] == '-')
				{
					postOrderCalculation[formulaDigit - 1].erase(0, 1);
				}
				else
				{
					tmp += postOrderCalculation[formulaDigit - 1];
					postOrderCalculation[formulaDigit - 1] = tmp;
					postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit);
					formulaDigit = 0;
				}
			}
			else
			{
				this->cError = 12;
				return -1;
			}
		}
	}

	// �p�⵲�G
	if (postOrderCalculation[0][0] == '@')
	{
		postOrderCalculation[0][0] = '-';
	}

	string result = postOrderCalculation[0];
	// �ˬd�O�_���ݯd�B�⤸
	if (postOrderCalculation.size() > 1 || !((result[0] >= '0' && result[0] <= '9') || result[0] == '-'))
	{
		this->cError = 10;
		return -1;
	}

	return stod(result);
}

// �p��ƭ�(������)
double Calculate::CalculateAnsSingal(double x)
{
	// �p��
	int formulaDigit = 0;	// �ثe��Ǧ�����쪺���
	vector<string> postOrderCalculation(this->postOrderFormula);
	for (; postOrderCalculation.size() > 1 && formulaDigit < postOrderCalculation.size(); formulaDigit++)
	{
		// �T�����
		if (postOrderCalculation[formulaDigit].substr(0, 3) == "sin" || postOrderCalculation[formulaDigit].substr(0, 3) == "cos" || postOrderCalculation[formulaDigit].substr(0, 3) == "tan")
		{
			string tmp;
			string triangle = postOrderCalculation[formulaDigit].substr(0, 3);
			postOrderCalculation[formulaDigit].erase(0, 3);

			// �i����~�P�_
			// �A�����~
			int start = 0, end = 0;
			for (int checkSin = 0; checkSin < postOrderCalculation[formulaDigit].size(); checkSin++)
			{
				if (postOrderCalculation[formulaDigit][checkSin] == '(')
				{
					start++;
				}
				else if (postOrderCalculation[formulaDigit][checkSin] == ')')
				{
					end++;
				}
			}

			// (X)����<=2 || �e��A���ƶq����1 || ���줣��'(' || ���줣��')'
			if (postOrderCalculation[formulaDigit].size() <= 2 || start != 1 || end != 1 || postOrderCalculation[formulaDigit][0] != '(' || postOrderCalculation[formulaDigit][postOrderCalculation[formulaDigit].size() - 1] != ')')
			{
				this->cError = 15;
				return -1;
			}

			// sin
			if (triangle == "sin")
			{
				// �B��
				postOrderCalculation[formulaDigit].erase(0, 1);
				postOrderCalculation[formulaDigit].erase(postOrderCalculation[formulaDigit].end() - 1);

				Calculate sinInNum(postOrderCalculation[formulaDigit]);

				this->cError = sinInNum.cError;

				if (this->cError == 0)
				{
					vector<Pos> inNum = sinInNum.GetAnsList(x);

					this->cError = sinInNum.cError;

					if (this->cError == 0 && !inNum.empty())
					{
						if (!inNum[0].errorPos)
						{
							tmp = to_string(sin(inNum[0].y));
						}
					}
				}
			}
			// cos
			else if (triangle == "cos")
			{
				// �B��
				postOrderCalculation[formulaDigit].erase(0, 1);
				postOrderCalculation[formulaDigit].erase(postOrderCalculation[formulaDigit].end() - 1);

				Calculate cosInNum(postOrderCalculation[formulaDigit]);

				this->cError = cosInNum.cError;

				if (this->cError == 0)
				{
					vector<Pos> inNum = cosInNum.GetAnsList(x);

					this->cError = cosInNum.cError;

					if (this->cError == 0 && !inNum.empty())
					{
						if (!inNum[0].errorPos)
						{
							tmp = to_string(cos(inNum[0].y));
						}
					}
				}
			}
			// tan
			else if (triangle == "tan")
			{
				// �B��
				postOrderCalculation[formulaDigit].erase(0, 1);
				postOrderCalculation[formulaDigit].erase(postOrderCalculation[formulaDigit].end() - 1);

				Calculate tanInNum(postOrderCalculation[formulaDigit]);

				this->cError = tanInNum.cError;

				if (this->cError == 0)
				{
					vector<Pos> inNum = tanInNum.GetAnsList(x);

					this->cError = tanInNum.cError;

					if (this->cError == 0 && !inNum.empty())
					{
						if (!inNum[0].errorPos)
						{
							tmp = to_string(tan(inNum[0].y));
						}
					}
				}
			}

			postOrderCalculation[formulaDigit] = tmp;
			formulaDigit = 0;
		}
		// �[�k
		else if (postOrderCalculation[formulaDigit] == "+")
		{
			if (formulaDigit >= 2)
			{
				string tmp;
				double a = 0, b = 0;

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					a = x;
				}
				else if (postOrderCalculation[formulaDigit - 2] == "-x" || postOrderCalculation[formulaDigit - 2] == "@x")
				{
					a = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					b = x;
				}
				else if (postOrderCalculation[formulaDigit - 1] == "-x" || postOrderCalculation[formulaDigit - 1] == "@x")
				{
					b = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					a = x;
				}
				else if (postOrderCalculation[formulaDigit - 2] == "-x" || postOrderCalculation[formulaDigit - 2] == "@x")
				{
					a = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					b = x;
				}
				else if (postOrderCalculation[formulaDigit - 1] == "-x" || postOrderCalculation[formulaDigit - 1] == "@x")
				{
					b = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					a = x;
				}
				else if (postOrderCalculation[formulaDigit - 2] == "-x" || postOrderCalculation[formulaDigit - 2] == "@x")
				{
					a = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					b = x;
				}
				else if (postOrderCalculation[formulaDigit - 1] == "-x" || postOrderCalculation[formulaDigit - 1] == "@x")
				{
					b = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					a = x;
				}
				else if (postOrderCalculation[formulaDigit - 2] == "-x" || postOrderCalculation[formulaDigit - 2] == "@x")
				{
					a = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					b = x;
				}
				else if (postOrderCalculation[formulaDigit - 1] == "-x" || postOrderCalculation[formulaDigit - 1] == "@x")
				{
					b = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

				if (b == 0)
				{
					this->cError = 9;
					return -1;
				}

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

				if (postOrderCalculation[formulaDigit - 2] == "x")
				{
					a = x;
				}
				else if (postOrderCalculation[formulaDigit - 2] == "-x" || postOrderCalculation[formulaDigit - 2] == "@x")
				{
					a = 0 - x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 2][0] == '@')
					{
						postOrderCalculation[formulaDigit - 2][0] = '-';
					}
					a = stod(postOrderCalculation[formulaDigit - 2]);
				}

				if (postOrderCalculation[formulaDigit - 1] == "x")
				{
					b = x;
				}
				else
				{
					if (postOrderCalculation[formulaDigit - 1][0] == '@')
					{
						postOrderCalculation[formulaDigit - 1][0] = '-';
					}
					b = stod(postOrderCalculation[formulaDigit - 1]);
				}

				// ����B��p��
				tmp = to_string(pow(a, b));
				if (tmp == "-nan(ind)")
				{
					this->cError = 10;
					return -1;
				}

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
			this->cError = 11;
			return -1;
		}
		// �t��
		else if (postOrderCalculation[formulaDigit] == "@")
		{
			if (formulaDigit >= 1)
			{
				string tmp = "-";

				if (postOrderCalculation[formulaDigit - 1][0] == '@')
				{
					postOrderCalculation[formulaDigit - 1][0] = '-';
				}

				if (postOrderCalculation[formulaDigit - 1][0] == '-')
				{
					postOrderCalculation[formulaDigit - 1].erase(0, 1);
				}
				else
				{
					tmp += postOrderCalculation[formulaDigit - 1];
					postOrderCalculation[formulaDigit - 1] = tmp;
					postOrderCalculation.erase(postOrderCalculation.begin() + formulaDigit);
					formulaDigit = 0;
				}
			}
			else
			{
				this->cError = 12;
				return -1;
			}
		}
	}

	// �p�⵲�G

	// �Y���G�O�T�����
	if (postOrderCalculation.size() > 0)
	{
		if (postOrderCalculation[0].substr(0, 3) == "sin" || postOrderCalculation[0].substr(0, 3) == "cos" || postOrderCalculation[0].substr(0, 3) == "tan")
		{
			string triangle = postOrderCalculation[0].substr(0, 3);
			postOrderCalculation[0].erase(0, 3);

			// �i����~�P�_
			// �A�����~
			int start = 0, end = 0;
			for (int checkSin = 0; checkSin < postOrderCalculation[0].size(); checkSin++)
			{
				if (postOrderCalculation[0][checkSin] == '(')
				{
					start++;
				}
				else if (postOrderCalculation[0][checkSin] == ')')
				{
					end++;
				}
			}

			// (X)����<=2 || �e��A���ƶq����1 || ���줣��'(' || ���줣��')'
			if (postOrderCalculation[0].size() <= 2 || start != 1 || end != 1 || postOrderCalculation[0][0] != '(' || postOrderCalculation[0][postOrderCalculation[0].size() - 1] != ')')
			{
				this->cError = 15;
				return -1;
			}

			// sin
			if (triangle == "sin")
			{
				// �B��
				postOrderCalculation[0].erase(0, 1);
				postOrderCalculation[0].erase(postOrderCalculation[0].end() - 1);

				Calculate sinInNum(postOrderCalculation[0]);

				this->cError == sinInNum.cError;

				if (this->cError == 0)
				{
					vector<Pos> inNum = sinInNum.GetAnsList(x);
					this->cError == sinInNum.cError;

					if (this->cError == 0 && !inNum.empty())
					{
						if (!inNum[0].errorPos)
						{
							postOrderCalculation[0] = to_string(sin(inNum[0].y));
						}
					}
				}
			}
			// cos
			else if (triangle == "cos")
			{
				// �B��
				postOrderCalculation[0].erase(0, 1);
				postOrderCalculation[0].erase(postOrderCalculation[0].end() - 1);

				Calculate cosInNum(postOrderCalculation[0]);

				this->cError == cosInNum.cError;

				if (this->cError == 0)
				{
					vector<Pos> inNum = cosInNum.GetAnsList(x);
					this->cError == cosInNum.cError;

					if (this->cError == 0 && !inNum.empty())
					{
						if (!inNum[0].errorPos)
						{
							postOrderCalculation[0] = to_string(cos(inNum[0].y));
						}
					}
				}
			}
			// tan
			else if (triangle == "tan")
			{
				// �B��
				postOrderCalculation[0].erase(0, 1);
				postOrderCalculation[0].erase(postOrderCalculation[0].end() - 1);

				Calculate tanInNum(postOrderCalculation[0]);

				this->cError == tanInNum.cError;

				if (this->cError == 0)
				{
					vector<Pos> inNum = tanInNum.GetAnsList(x);
					this->cError == tanInNum.cError;

					if (this->cError == 0 && !inNum.empty())
					{
						if (!inNum[0].errorPos)
						{
							postOrderCalculation[0] = to_string(tan(inNum[0].y));
						}
					}
				}
			}
		}

		// �Y���G���t�ƪ��B�z
		if (postOrderCalculation[0][0] == '@')
		{
			postOrderCalculation[0][0] = '-';
		}

		if (postOrderCalculation[0] == "x")
		{
			postOrderCalculation[0] = to_string(x);
		}
		else if (postOrderCalculation[0] == "-x")
		{
			postOrderCalculation[0] = to_string(0 - x);
		}

		string result = postOrderCalculation[0];

		// �ˬd�O�_���ݯd�B�⤸
		if (postOrderCalculation.size() > 1 || !((result[0] >= '0' && result[0] <= '9') || result[0] == '-'))
		{
			this->cError = 10;
			return -1;
		}

		if (this->cError != 0)
		{
			runError = true;
			this->cError = 0;
		}

		return stod(result);
	}
}