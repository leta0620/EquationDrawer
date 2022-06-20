#include "Calculate.h"

//--------副程式--------//

// 回傳運算符優先度
int OperatorPriority(char in)
{
	switch (in)
	{
	case'@':	// 負號優先度：4
		return 4;
	case'!':	// 階層優先度：3
		return 3;
	case'^':	// 次方優先度：2
		return 2;
	case'*':	// 乘號優先度：1
		return 1;
	case'/':	// 除號優先度：1
		return 1;
	case'+':	// 加號優先度：0
		return 0;
	case'-':	// 減號優先度：0
		return 0;
	default:
		return -1;
	}
}

//--------Calculate類別--------//

// 輸入運算式後，進行處理
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


// 獲取初始運算式
string Calculate::GetOriginFormula()
{
	return this->originFormula;
}
// 獲取後序式
vector<string> Calculate::GetPostOrderFormula()
{
	return this->postOrderFormula;
}

// 獲取運算式答案(無帶入x)
double Calculate::GetAnsList()
{
	return this->CalculateAns();
}

// 獲取運算式答案(單一數字點)
vector<Pos> Calculate::GetAnsList(double singalNum)
{
	this->ansList.clear();
	CalculateAns(singalNum);

	return this->ansList;
}
// 獲取運算式答案(連續數字串)
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

// 計算方程式(執行到切割後續式)
void Calculate::Calculation(string input)
{
	SetInput(input);
	if (this->cError != 0)
	{
		return;
	}
	CutInput();
}

// 輸入數學式
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

// 判斷輸入字串、轉後序、計算完放進ans(注意變數？)(會有小數輸入)
void Calculate::CutInput()
{
	// 將負號變成'@'
	this->processFormula = this->originFormula;
	for (int transNeg = 0; transNeg < this->processFormula.size(); transNeg++)
	{
		if (transNeg < this->processFormula.size() - 1)
		{
			// 若輸入的第一個字元為負 
			if ((transNeg == 0 && this->processFormula[transNeg] == '-'))
			{
				this->processFormula[transNeg] = '@';
			}
			// 若輸入字元為任意符號 接 負號 ，例：(5+-4) or (5+(-6))
			else if (((this->processFormula[transNeg] < '0' || this->processFormula[transNeg] == '^') && this->processFormula[transNeg] != ')' && this->processFormula[transNeg] != '!' && this->processFormula[transNeg + 1] == '-'))
			{
				this->processFormula[transNeg + 1] = '@';
			}
		}
	}

	// 檢查小數點
	for (int dotErrorTest = 0; dotErrorTest < this->processFormula.size(); dotErrorTest++)
	{
		// 符號.23 or 0.-1 or 0.+1
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

	// 對字串進行分割處裡
	vector<string> cutString;
	string tmp;
	int loc = 0;

	while (loc < this->processFormula.size())
	{
		if (this->processFormula[loc] >= '0' && this->processFormula[loc] <= '9')
		{
			bool hasDot = false;

			// 正數
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

			// 輸入為 56ABC 等等，先數字再文字的錯誤輸入
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
			// 變數名
			for (; (this->processFormula[loc] >= 'A' && this->processFormula[loc] <= 'Z') || (this->processFormula[loc] >= 'a' && this->processFormula[loc] <= 'z') || (this->processFormula[loc] >= '0' && this->processFormula[loc] <= '9'); loc++)
			{
				tmp += this->processFormula[loc];
			}

			// 如果輸入是三角函數
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
			// 負數
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

					// 數字
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

					// 輸入為 56ABC 等等，先數字再文字的錯誤輸入
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
			// 其他運算符號
			tmp += this->processFormula[loc];
			cutString.push_back(tmp);
			loc++;
			tmp.clear();
		}
		else
		{
			// 其他字元，給error，並終止運算
			this->cError = 1;
			return;
		}
	}

	// 檢查分割結果
	int frontBrackets = 0, backBrackets = 0;
	for (int errorTest = 0; errorTest < cutString.size(); errorTest++)
	{
		// 判斷前後括號數量是否相同
		if (cutString[errorTest] == "(")
		{
			frontBrackets++;
		}
		else if (cutString[errorTest] == ")")
		{
			backBrackets++;
		}

		// 判斷是否為0000
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
	// 前括號後括號數量不同，報錯
	if (frontBrackets != backBrackets)
	{
		this->cError = 10;
		return;
	}

	// 轉後序
	vector<string> postfix;
	vector<string> sign;

	for (int round = 0; round < cutString.size(); round++)
	{
		// 若切割完的字串是數字 || 切割完的為負數 || 切割完的是變數 || 切割完是三角函數
		if ((cutString[round][0] >= '0' && cutString[round][0] <= '9') || (cutString[round][0] == '@' && cutString[round].size() > 1) || (cutString[round][0] >= 'A' && cutString[round][0] <= 'Z') || (cutString[round][0] >= 'a' && cutString[round][0] <= 'z'))
		{
			postfix.push_back(cutString[round]);
		}
		else
		{
			sign.push_back(cutString[round]);
		}

		// 判斷符號優先序
		if (sign.size() > 0)
		{
			// 若放進的是右括弧
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
			// 比較兩個符號的優先序
			else if (sign.size() > 1)
			{
				// 若後面的運算符優先序小於等於前面的運算符
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

	// 將剩餘的符號放進後序式
	while (sign.size() > 0)
	{
		postfix.push_back(sign[sign.size() - 1]);
		sign.pop_back();
	}

	// 確認符號數量是否正確
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

// 計算帶入數字的結果(單一值)
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

// 計算帶入數字的結果(範圍值)
void Calculate::CalculateAns(double start, double end)
{
	int calculateTimes = 800;	// 需計算的次數

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


// 獲取錯誤代碼
int Calculate::GetCError()
{
	return this->cError;
}

// 更改後序式
void Calculate::SetPostOrder(int Loc, string input)
{
	if (Loc <= this->postOrderFormula.size() - 1)
	{
		this->postOrderFormula[Loc] = input;
	}
}


// 計算結果(內部用)
double Calculate::CalculateAns()
{
	// 計算
	int formulaDigit = 0;	// 目前後序式執行到的位數
	vector<string> postOrderCalculation(this->postOrderFormula);
	for (; postOrderCalculation.size() > 1 && formulaDigit < postOrderCalculation.size(); formulaDigit++)
	{
		// 加法
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
		// 減法
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
		// 乘法
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
		// 除法
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
		// 次方
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
		// 階層
		else if (postOrderCalculation[formulaDigit] == "!")
		{
			this->cError = 11;
			return -1;
		}
		// 負號
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

	// 計算結果
	if (postOrderCalculation[0][0] == '@')
	{
		postOrderCalculation[0][0] = '-';
	}

	string result = postOrderCalculation[0];
	// 檢查是否有殘留運算元
	if (postOrderCalculation.size() > 1 || !((result[0] >= '0' && result[0] <= '9') || result[0] == '-'))
	{
		this->cError = 10;
		return -1;
	}

	return stod(result);
}

// 計算數值(內部用)
double Calculate::CalculateAnsSingal(double x)
{
	// 計算
	int formulaDigit = 0;	// 目前後序式執行到的位數
	vector<string> postOrderCalculation(this->postOrderFormula);
	for (; postOrderCalculation.size() > 1 && formulaDigit < postOrderCalculation.size(); formulaDigit++)
	{
		// 三角函數
		if (postOrderCalculation[formulaDigit].substr(0, 3) == "sin" || postOrderCalculation[formulaDigit].substr(0, 3) == "cos" || postOrderCalculation[formulaDigit].substr(0, 3) == "tan")
		{
			string tmp;
			string triangle = postOrderCalculation[formulaDigit].substr(0, 3);
			postOrderCalculation[formulaDigit].erase(0, 3);

			// 進行錯誤判斷
			// 括號錯誤
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

			// (X)長度<=2 || 前後括號數量不為1 || 首位不為'(' || 末位不為')'
			if (postOrderCalculation[formulaDigit].size() <= 2 || start != 1 || end != 1 || postOrderCalculation[formulaDigit][0] != '(' || postOrderCalculation[formulaDigit][postOrderCalculation[formulaDigit].size() - 1] != ')')
			{
				this->cError = 15;
				return -1;
			}

			// sin
			if (triangle == "sin")
			{
				// 運算
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
				// 運算
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
				// 運算
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
		// 加法
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
		// 減法
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
		// 乘法
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
		// 除法
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
		// 次方
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

				// 次方運算計算
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
		// 階層
		else if (postOrderCalculation[formulaDigit] == "!")
		{
			this->cError = 11;
			return -1;
		}
		// 負號
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

	// 計算結果

	// 若結果是三角函數
	if (postOrderCalculation.size() > 0)
	{
		if (postOrderCalculation[0].substr(0, 3) == "sin" || postOrderCalculation[0].substr(0, 3) == "cos" || postOrderCalculation[0].substr(0, 3) == "tan")
		{
			string triangle = postOrderCalculation[0].substr(0, 3);
			postOrderCalculation[0].erase(0, 3);

			// 進行錯誤判斷
			// 括號錯誤
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

			// (X)長度<=2 || 前後括號數量不為1 || 首位不為'(' || 末位不為')'
			if (postOrderCalculation[0].size() <= 2 || start != 1 || end != 1 || postOrderCalculation[0][0] != '(' || postOrderCalculation[0][postOrderCalculation[0].size() - 1] != ')')
			{
				this->cError = 15;
				return -1;
			}

			// sin
			if (triangle == "sin")
			{
				// 運算
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
				// 運算
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
				// 運算
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

		// 若結果為負數的處理
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

		// 檢查是否有殘留運算元
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