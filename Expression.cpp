#include "Expression.h"
//using E = Expression;

void Expression::Remove_Key_Space()
{
	smatch m;
	while (regex_search(Exp, m, regex("(.*)\\s(.*)")))
		Exp = m.str(1) + m.str(2);
}

void Expression::Invalid_Symbol()
{
	if (!regex_match(Exp, regex("[\\d|\\+|\\-|\\*|\\(|\\)|/|\\^|\\.]+")))
		throw "Invalid character in expression!\n";
}

void Expression::Invalid_Operations()
{
	if (regex_search(Exp, regex("[\\+|\\-|\\*|/|\\^|\\.]{2,}")))
		throw "There are two operation signs in the expression!\n";
}

void Expression::Invalid_Dots()
{
	if (regex_search(Exp, regex("\\.{2,}")))
		throw "The expression has two decimal points in a row!\n";
	if (regex_search(Exp, regex("^\\.|\\.$")))
		throw "Dot!\n";
}

void Expression::Invalid_Number_Open_Bracket()
{
	if (regex_search(Exp, regex("\\d+\\(")))
		throw "There is no operation sign between the number and the opening bracket!\n";
}

void Expression::Invalid_Number_Close_Bracket()
{
	if (regex_search(Exp, regex("\\)\\d+")))
		throw "There is no binary operation sign between the closing bracket and the number!\n";
}

void Expression::No_Expression_Brackets()
{
	if (regex_search(Exp, regex("\\([\\+|\\-|\\*|/|\\^|\\.]?\\)")))
		throw "There is no expression between the opening and closing brackets!\n";
}

void Expression::Invalid_Exp_Open_Bracket()
{
	if (regex_search(Exp, regex("\\([\\+|\\-|\\*|/|\\^|\\.]")))
		throw "There is no expression between the opening bracket and the binary operation sign!\n";
}

void Expression::Invalid_Exp_Close_Bracket()
{
	if (regex_search(Exp, regex("[\\+|\\-|\\*|/|\\^|\\.]\\)")))
		throw "There is no expression between the binary operation sign and the closing bracket!\n";
}

void Expression::No_Operation_in_Brackets()
{
	if (regex_search(Exp, regex("\\(\\d\\)")))
		throw "There is no binary operation sign between the closing and opening brackets!\n";
}

void Expression::Binary_Operation_Start()
{
	if (regex_search(Exp, regex("^[\\+|\\-|\\*|/|\\^]")))
		throw "An expression begins with a binary operation sign!\n";
}

void Expression::Close_Bracket_Start()
{
	if (regex_search(Exp, regex("^\\)")))
		throw "The expression begins with a closing bracket!\n";
}

void Expression::Binary_Operation_End()
{
	if (regex_search(Exp, regex("[\\+|\\-|\\*|/|\\^]$")))
		throw "The expression ends with a binary operation sign!\n";
}

void Expression::Invalid_Decimal()
{
	if (regex_search(Exp, regex("\\d+\\.\\d+\\.")))
		throw "Invalid decimal notation!\n";
}

void Expression::Open_Close_Brackets()
{
	auto count_open = 0, count_close = 0;
	for (size_t i = 0; i < Exp.length(); i++)
	{
		if (Exp[i] == '(')
			count_open++;
		if (Exp[i] == ')')
			count_close++;
	}
	if (count_open != count_close)
		throw "Discrepancy between the number of opening and closing brackets!\n";
}

//void Expression::Push(vector<string>& expression, int &i)
//{
//	regex_search(expression[i], regex("^\\d")) ? Operand.push(expression[i++]) : Operation.push(expression[i++]);
//}

void Expression::Push_All(vector<string>& Collection, string reg)
{
	smatch m;
	for (string Value = Exp; regex_search(Value, m, regex(reg)); Value.replace(Value.find(m.str()), m.str().length(), ""))
		Collection.push_back(m.str());
}

void Expression::Degree_Transformation()
{
	smatch m;
	for (string Value = Exp; regex_search(Value, m, regex("([\\d\\.?]+)\\^([\\d\\.?]+)")); Value.replace(Value.find(m.str()), m.str().length(), ""))
		Exp.replace(Exp.find(m.str()), m.str().length(), to_string(pow(atof(m.str(1).c_str()), atof(m.str(2).c_str()))));
}

Expression::Expression(string NewExp)
{
	Exp = NewExp;
	Remove_Key_Space();
	try
	{
		Invalid_Symbol();
		Invalid_Dots();
		Invalid_Operations();
		Invalid_Number_Open_Bracket();
		Invalid_Number_Close_Bracket();
		No_Expression_Brackets();
		Invalid_Exp_Open_Bracket();
		Invalid_Exp_Close_Bracket();
		No_Operation_in_Brackets();
		Binary_Operation_Start();
		Close_Bracket_Start();
		Binary_Operation_End();
		Invalid_Decimal();
		Open_Close_Brackets();
		//Devide_Null();
	}
	catch (const char* Str)
	{
		cout << Str;
		//Sleep(3000);
		exit(1);
	}
	Degree_Transformation();
}

void Expression::Intermediate_Result()
{
	string first_operand, second_operand;
	first_operand = Operand.top();
	Operand.pop();
	second_operand = Operand.top();
	Operand.pop();
	Operand.push(Transform(second_operand, first_operand, Operation.top()));
	Operation.pop();
}

int Expression::Priority(string operation)
{
	if (operation == "(")
		return -1;
	if (operation == "+" || operation == "-")
		return 2;
	return operation == "*" || operation == "/" ? 4 : NULL;
}

string Expression::Result()
{
	vector<string> expression;
	Push_All(expression, "[^\\d]|[\\d\\.?]+");
	expression.push_back(")");
	expression.insert(expression.begin(), "(");
	size_t index = 0;
	do
	{
		if (regex_search(expression[index], regex("[\\d\\.?]+")))
			Operand.push(expression[index++]);
		else
		{
			if (Operand.size() > 0 && Priority(Operation.top()) && Priority(Operation.top()) >= Priority(expression[index]) && expression[index] != "(")
				Intermediate_Result();
			if (expression[index] != ")")
				Operation.push(expression[index++]);
			else
			{
				while (Operation.size() > 0 && Operation.top() != "(")
					Intermediate_Result();
				index++;
				Operation.pop();
			}
		}
	} while (expression.size() != index);
	return Exp + "=" + Operand.top();
}

string Expression::Transform(string fp, string sp, string operation)
{
	if (operation == "+")
		return to_string(atof(fp.c_str()) + atof(sp.c_str()));
	if (operation == "-")
		return to_string(atof(fp.c_str()) - atof(sp.c_str()));
	if (operation == "*")
		return to_string(atof(fp.c_str()) * atof(sp.c_str()));
	if (operation == "/")
		/*if (atof(fp.c_str()) == 0.0)
			throw "NULL!";
		else*/
		return to_string(atof(fp.c_str()) / atof(sp.c_str()));
	else
		return "Error!";
}