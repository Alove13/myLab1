#include "Token.h"

Token::Token(string Type, string Value, int LineNum)
{
    tokenType = Type;
    tokenValue = Value;
    tokenLineNum = LineNum;
}
string Token::getType()
{
    return tokenType;
}
string Token::getValue()
{
    return tokenValue;
}
int Token::getLineNum()
{
    return tokenLineNum;
}
