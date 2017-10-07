#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Creates a Token to be stored in Lexer vector<Token> to be printed at end
class CharSequence
{
private:
    vector<char> seqVec;
    int lineNumber;
    int charIndex;
    ifstream in;
    char tempHolder;

public:
    CharSequence(string fileName);
    void setUpVector(string inputFile);
    void advanceIndex();
    void checkNewLine(); //When inside ID, String, or Comment functions
    void incLineNum(); 
    char currChar();
    bool EoF();
    int currLine();
    int currIndex(); //testing purposes
    int getVecSize(); //testing purposes
    void printSequence(); //testing purposes
    //char peak(); //returns value of char ahead one.
};
