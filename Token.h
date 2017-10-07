#pragma once
#include <iostream>
#include <string>
using namespace std;

//Creates a Token to be stored in Lexer vector<Token> to be printed at end
class Token
{
private:
    string tokenType;
    string tokenValue;
    int tokenLineNum;
public:
    Token(string Type, string Value, int LineNum);
    string getType();
    string getValue();
    int getLineNum();
};