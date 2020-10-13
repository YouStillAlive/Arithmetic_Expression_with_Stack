#pragma once
#include <regex>
#include <stack>
#include <iostream>
using namespace std;

class Expression
{
	string Exp;
	stack<string> Operand;
	stack<string> Operation;

	string Transform(string fp, string sp, string operation);
	void Remove_Key_Space();
	void Invalid_Symbol();
	void Invalid_Operations();
	void Invalid_Dots();
	void Invalid_Number_Open_Bracket();
	void Invalid_Number_Close_Bracket();
	void No_Expression_Brackets();
	void Invalid_Exp_Open_Bracket();
	void Invalid_Exp_Close_Bracket();
	void No_Operation_in_Brackets();
	void Binary_Operation_Start();
	void Close_Bracket_Start();
	void Binary_Operation_End();
	void Invalid_Decimal();
	void Degree_Transformation();
	void Open_Close_Brackets();
	//void Push(vector<string>& expression, int &i);
	int Priority(string);
	void Push_All(vector<string>& Collection, string reg);
	void Intermediate_Result();
public:
	Expression(string Exp);
	string Result();
};