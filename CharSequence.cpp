#include "CharSequence.h"

CharSequence::CharSequence(string fileName)
{
    lineNumber = 1;
    charIndex = 0;
    setUpVector(fileName); //puts file's chars into seqVec
}

void CharSequence::setUpVector(string inputFile)
{
    in.open(inputFile.c_str(), fstream::in); 
    while(in >> noskipws >> tempHolder)
    {
        //cout << "Chars to Vec: " << tempHolder<<endl;
       seqVec.push_back(tempHolder);        
    }
    in.close();
}
void CharSequence::advanceIndex()
{
    charIndex++;
}
void CharSequence::checkNewLine()
{
    if(seqVec[charIndex] == '\n')
    {
        lineNumber++;
    }
}
void CharSequence::incLineNum()
{
    lineNumber++;
}
char CharSequence::currChar()
{
    //cout << "Index inside Sequence " << charIndex << endl;
    return seqVec[charIndex]; //will be updated by advanceIndex()
}
bool CharSequence::EoF()
{
    if(charIndex >= seqVec.size() -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int CharSequence::currLine()
{
    return lineNumber; //will be updated by incLineNum()
}
int CharSequence::currIndex()
{
    return charIndex;
}
void CharSequence::printSequence()
{
    for(int i = 0; i < seqVec.size(); i++)
    {
        cout << "Index: " << charIndex << "Character: " << seqVec[i] << endl; 
    } 
}
int CharSequence::getVecSize()
{
    return seqVec.size();
}
