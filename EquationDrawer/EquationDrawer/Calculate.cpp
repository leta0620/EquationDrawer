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

// 獲取運算式答案(單一數字點)
vector<double> Calculate::GetAnsList(double singalNum)
{
	vector<double> tmp;
	return tmp;
}
// 獲取運算式答案(連續數字串)
vector<double> Calculate::GetAnsList(double start, double end)
{
	vector<double> tmp;
	return tmp;
}

// 計算方程式
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
			if (cutString[errorTest] == "^" && cutString[errorTest - 1] >= "^")
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
		// 若切割完的字串是數字 || 切割完的為負數 || 切割完的是變數
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

	this->postOrderFormula = postfix;
}

// 計算帶入數字的結果(單一值)
void Calculate::CalculateAns(double x)
{
	int ans = this->CalculateAnsSingal(x);
	if (this->cError == 0)
	{
		this->ansList.push_back(ans);
	}
}

// 計算帶入數字的結果(範圍值)
void Calculate::CalculateAns(double start, double end)
{
	int precision = 100;	// 精度，start 到 end 要切分成多少，若為每次加1，則為1，若為每次加0.1，則為10
	int calculateTimes = (end - start) * precision;	// 需計算的次數

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

// 計算數值(內部用)
double Calculate::CalculateAnsSingal(double x)
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
		// 減法
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
		// 乘法
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
		// 次方
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
		// 階層
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
		// 負號
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

	// 計算結果
	string result = postOrderCalculation[0];
	// 檢查是否有殘留運算元
	if (postOrderCalculation.size() > 1 || !(result[0] >= '0' && result[0] <= '9'))
	{
		this->cError = 10;
		return -1;
	}
	
	return stod(result);
}

