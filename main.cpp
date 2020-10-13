#include "Expression.h"

int main()
{
	cout << "Please enter expression: ";
	string Value;
	getline(cin, Value);
	Expression Exp(Value);
	cout << Exp.Result();
	system("pause");
}