#include "Lexer.h"

Lexer::Lexer(string nameFile) : mySeq(nameFile) //uses Lexer constructor to construct CharSequence's constructor
{
    startProcess();
}

void Lexer::startProcess()
{
    //char blob;
    while(!(mySeq.EoF()))//mySeq.EoF()
    {
        // cout << "Current Char: " << mySeq.currChar() << " index: " << mySeq.currIndex()<<endl;
        // cout << "lineNumber "<<mySeq.currLine() << endl;
        //cout << "tokenList " << tokenList[mySeq.currIndex()].getType()<<endl;
        // cin >> blob;
        //char currentChar = mySeq.currChar();
        switch(mySeq.currChar())
        {
            case '\n':
            cout << "Recs a backslash n"<<endl;
            mySeq.advanceIndex();
            mySeq.incLineNum();
                //advance lineNum and charIndex
            break;
            case ',':
            cout << "Recs a comma"<<endl;
                //basic cases immediately create token to add to tokenList
                tokenList.push_back(Token("COMMA",",",mySeq.currLine()));
                mySeq.advanceIndex();
            break;
            case '.':
            cout << "Recs a period"<<endl;
                tokenList.push_back(Token("PERIOD",".",mySeq.currLine()));
                mySeq.advanceIndex();
            break;
            case '?':
            cout << "Recs a q_mark"<<endl;
                tokenList.push_back(Token("Q_MARK","?",mySeq.currLine()));
                mySeq.advanceIndex();
            break;
            case '(':
            cout << "Recs a left_paren"<<endl;
                tokenList.push_back(Token("LEFT_PAREN","(",mySeq.currLine()));
                mySeq.advanceIndex();
            break;
            case ')':
            cout << "Recs a right_paren"<<endl;
                tokenList.push_back(Token("RIGHT_PAREN",")",mySeq.currLine()));
                mySeq.advanceIndex();
            break;
            case ':':
                cout << "Recs a :" << endl;
                mySeq.advanceIndex(); //Later put inside Colon or Colon_Dash function
            break;
            case '*':
            cout << "Recs a multiply"<<endl;
                tokenList.push_back(Token("MULTIPLY","*",mySeq.currLine()));
                mySeq.advanceIndex();
            break;
            case '+':
            cout << "Recs a add"<<endl;
                tokenList.push_back(Token("ADD","+",mySeq.currLine()));
                mySeq.advanceIndex();
            break;
            case '\'': //check for ' for string
                cout << "Recs a single quote!" << endl;
                determineString();
            break;
            case '#': //comment
                cout << "Recs a Hash Tag!" << endl;
                determineComment();
                mySeq.advanceIndex(); //Later put inside comment function
            break;
            case ' ': //WS need other way to check???
                cout << "Recs a  WS!" << endl;
                mySeq.advanceIndex(); //Later put inside whitespace function
            break;
            default:
                //Check if ID, else make undefined:
                if(isalpha(mySeq.currChar()))
                {
                    cout << "Recs an ID!" << endl;
                    determineID();
                    mySeq.advanceIndex();
                }
                else
                {
                    stringstream ss;
                    string holder;
                    ss << mySeq.currChar();
                    ss >> holder;
                        cout << "undefined" << endl;
                        tokenList.push_back(Token("UNDEFINED",holder,mySeq.currLine()));
                        mySeq.advanceIndex();
                }
            break;
        }
    }//Process Over
    printTokens();
}
void Lexer::printTokens()
{
    for(int i = 0; i < tokenList.size(); i++) //All three vectors' sizes are equal
    {
        printerString << "(" << tokenList[i].getType() << "," << "\"" << tokenList[i].getValue() << "\"" << "," << tokenList[i].getLineNum() << ")" <<endl;   
    }
    cout << printerString.str();
}
void Lexer::determineID()
{
    //at end test for keywords
    // maybe need int startingLineNumber = lineNumber;
        saveLineNum = mySeq.currLine();
        tokenString.clear();
        tokenString += mySeq.currChar();
        if(mySeq.EoF())
        {
            if(determineKeyWords(tokenString, saveLineNum))
            {
                return; //Breaks out of function
            }
            else
            {
                tokenList.push_back(Token("ID", tokenString, saveLineNum));
                tokenString.clear();
                //Need to call startProcess to get to beginning of loop?
            }
        }
        else
        {
            mySeq.advanceIndex();
            mySeq.checkNewLine();
        }
        //Rest needs to be letter or digit and NOT end of line char
        while((isalpha(mySeq.currChar()) || isdigit(mySeq.currChar())) && (mySeq.currChar() != '\n'))
        {
                tokenString += mySeq.currChar();
                if(mySeq.EoF())
                {
                    if(determineKeyWords(tokenString, saveLineNum))
                    {
                        return; //Breaks out of function
                    }
                    else
                    {
                        tokenList.push_back(Token("ID", tokenString, saveLineNum));
                        tokenString.clear();
                        //restart startProcess
                    }
                }
                else
                {
                    mySeq.advanceIndex();
                    mySeq.checkNewLine();
                }
        } 
        //ID Confirmed and finished
        //already incremented index
        if(determineKeyWords(tokenString, saveLineNum))
        {
            return; //Breaks out of function
        }
        else
        {
            tokenList.push_back(Token("ID", tokenString, saveLineNum));
            tokenString.clear();
        }        
}
bool Lexer::determineKeyWords(string stringToken, int theSavedLineNum)
{
    if(stringToken == "Schemes")
    {
        tokenList.push_back(Token("SCHEMES", stringToken, theSavedLineNum));
        tokenString.clear();
        return true;
    }
    else if(stringToken == "Facts")
    {
        tokenList.push_back(Token("FACTS", stringToken, theSavedLineNum));
        tokenString.clear();
        return true;
    }
    else if(stringToken == "Rules")
    {
        tokenList.push_back(Token("RULES", stringToken, theSavedLineNum));
        tokenString.clear();
        return true;
    }
    else if(stringToken == "Queries")
    {
        tokenList.push_back(Token("QUERIES", stringToken, theSavedLineNum));
        tokenString.clear();
        return true;
    }
    else
    {
        return false;
    }
}
void Lexer::determineString()
{
    bool trigger = true;
    saveLineNum = mySeq.currLine();
    tokenString.clear(); //Just in case
    tokenString += mySeq.currChar();
    if(mySeq.EoF())
    {
        tokenList.push_back(Token("UNDEFINED", "'", saveLineNum));
        tokenString.clear();
        //Call startProcess()???
    }
    else
    {
        mySeq.advanceIndex();
        mySeq.checkNewLine();
        while(trigger)
        {
            if(mySeq.currChar() == '\'')
            {
                //determine if last ' or apostraphe:
                tokenString += mySeq.currChar();
                if(mySeq.EoF())
                {
                    //String is complete and empty
                    tokenList.push_back(Token("STRING",tokenString, saveLineNum));
                    tokenString.clear();
                    trigger = false;
                    //Call startProcess()???
                }
                else
                {
                    mySeq.advanceIndex();
                    mySeq.checkNewLine();
                }
                if(mySeq.currChar() == '\'') //Is apostraphe
                {
                    //String not complete yet
                    tokenString += mySeq.currChar();
                    if(mySeq.EoF())
                    {
                        //complete string of ''' or this means incomplete string??
                        tokenList.push_back(Token("UNDEFINED", tokenString, saveLineNum));
                        tokenString.clear();
                        trigger = false;
                        //Call startProcess()???
                    }
                    else
                    {
                        mySeq.advanceIndex();
                        mySeq.checkNewLine(); 
                    }
                }
                else //reached end of string
                {
                    tokenList.push_back(Token("STRING",tokenString,saveLineNum));
                    trigger = false;
                }
            }
            else //string not complete yet
            {
                if(mySeq.currChar() != '\n') //when print, will keep string on same line
                {
                    tokenString += mySeq.currChar();
                }
                if(mySeq.EoF())
                {
                    tokenList.push_back(Token("UNDEFINED", tokenString, saveLineNum));
                    tokenString.clear();
                    trigger = false;
                    //Call startProcess()???
                }
                else
                {
                    mySeq.advanceIndex();
                    mySeq.checkNewLine(); 
                }
            }
        }
    }   
}
void Lexer::determineComment()
{
    char tester;
    bool blockTrigger = true;
    saveLineNum = mySeq.currLine();
    tokenString.clear(); //Just in case
    tokenString += mySeq.currChar();
    if(mySeq.EoF())
    {
        tokenList.push_back(Token("COMMENT", "#", saveLineNum));
        tokenString.clear();
        //Call startProcess()???
    }
    else
    {
        mySeq.advanceIndex();
        mySeq.checkNewLine();
    }
    if(mySeq.currChar() != '|') //then is a Line Comment
    {
        while(mySeq.currChar() != '\n' )
        {
            cout << "Character:" << mySeq.currChar()<<endl;
            cin >> tester;
            tokenString += mySeq.currChar();
            if(mySeq.EoF())
            {
                tokenList.push_back(Token("COMMENT",tokenString,saveLineNum));
                tokenString.clear();
            }
            else
            {
                //Keep going until end of Line
                mySeq.advanceIndex();
                mySeq.checkNewLine();
            }
        }
        //Reached end of line
        tokenList.push_back(Token("COMMENT",tokenString,saveLineNum));
        tokenString.clear();  
    }
    else //Start of Block Comment
    {
        while(blockTrigger)
        { 
            tokenString += mySeq.currChar();  //Add each character                
            if(mySeq.currChar() != '|')
            {
                if(mySeq.EoF())
                {
                    tokenList.push_back(Token("UNDEFINED",tokenString,saveLineNum));
                    tokenString.clear();
                    blockTrigger = false;
                }
                else
                {
                    mySeq.advanceIndex();
                    mySeq.checkNewLine();
                }
            }
            else
            {
                if(mySeq.currChar() != '#')
                {
                    if(mySeq.EoF())
                    {
                        tokenList.push_back(Token("UNDEFINED",tokenString,saveLineNum));
                        tokenString.clear();
                        blockTrigger = false;
                    }
                    else
                    {
                        mySeq.advanceIndex();
                        mySeq.checkNewLine();
                    }
                }
                else //reached complete Block Comment
                {
                    tokenList.push_back(Token("COMMENT",tokenString,saveLineNum));
                    tokenString.clear();
                    blockTrigger = false;
                }
            }
        }
    }
}