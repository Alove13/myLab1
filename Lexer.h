//#ifndef LEXER_H_
//#define LEXER_H_
#include <iostream>
#include <string>
#include <sstream>
#include "CharSequence.h"
#include "Token.h"

using namespace std;

class Lexer
{
private:
    string tokenString;
    int saveLineNum;
    stringstream printerString;
    vector<Token> tokenList;
    CharSequence mySeq;

public:
    Lexer(string nameFile);//Calls function that starts process
    void startProcess();
    void determineCOLON();
    void determineID();
    void determineString();
    void determineComment();
    void printTokens();
    bool determineKeyWords(string stringToken, int theSavedLineNum);
};
//#endif LEXER_H_
