#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;


struct _Stack {
    string value;
    struct _Stack* next;
};

int stackSize(_Stack* head);
void stackPush(_Stack*& head, string data);
string stackPop(_Stack*& head);
_Stack* pop(_Stack* str);
_Stack* stackLast(_Stack* head);
void stackClear(_Stack* head);
_Stack* stackGetLastButOne(_Stack* head);
void stackPrint(_Stack* head);
bool empty(_Stack* str);
void stackPushBack(_Stack* head, string data);
string stackPopBack(_Stack* head);
void stackAdd(_Stack*& head, const string& data);
string stackTake(_Stack*& head);
bool isOperation(const string& str);
bool isLiteral(const string& str);
bool isNumber(const string& str);
vector<string> tokenize(const string& text);
bool MoveOperation(string token, _Stack* opstack);
int _switch(char p);
bool correct(string& str);
string reversePolishNotation(string& inpt_str, ofstream& ofs, bool silent = false);
double calculatorRpn(string& rpn, ofstream& ofs);

int mainRPN();