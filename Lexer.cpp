#include "Lexer.h"

Lexer::Lexer(string nameFile) : mySeq(nameFile) //uses Lexer constructor to construct CharSequence's constructor
{
    startProcess();
}

void Lexer::startProcess()
{
    while(!(mySeq.EoF()))//mySeq.EoF()
    {
        switch(mySeq.currChar())
        {
            case '\n':
            mySeq.advanceIndex();
            //mySeq.incLineNum();
            break;
            case ',':
                //basic cases immediately create token to add to tokenList
                tokenList.push_back(Token("COMMA",",",mySeq.currLine()));
                mySeq.advanceIndex();
        	mySeq.checkNewLine();
	    break;
            case '.':
                tokenList.push_back(Token("PERIOD",".",mySeq.currLine()));
                mySeq.advanceIndex();
        	mySeq.checkNewLine();
            break;
            case '?':
                tokenList.push_back(Token("Q_MARK","?",mySeq.currLine()));
                mySeq.advanceIndex();
        	mySeq.checkNewLine();
            break;
            case '(':
                tokenList.push_back(Token("LEFT_PAREN","(",mySeq.currLine()));
                mySeq.advanceIndex();
        	mySeq.checkNewLine();
	    break;
            case ')':
                tokenList.push_back(Token("RIGHT_PAREN",")",mySeq.currLine()));
                mySeq.advanceIndex();
        	mySeq.checkNewLine();
            break;
            case ':':
	    	determineCOLON();
	    break;
            case '*':
                tokenList.push_back(Token("MULTIPLY","*",mySeq.currLine()));
                mySeq.advanceIndex();
        	mySeq.checkNewLine();
            break;
            case '+':
                tokenList.push_back(Token("ADD","+",mySeq.currLine()));
                mySeq.advanceIndex();	
        	mySeq.checkNewLine();
            break;
            case '\'': //check for ' for string
                determineString();
            break;
            case '#': //comment
                determineComment();
            break;
            case ' ': //WS need other way to check???
                mySeq.advanceIndex(); //Later put inside whitespace function
            break;
            default:
                //Check if ID, else make undefined:
                if(isalpha(mySeq.currChar()))
                {
                    determineID();
                    mySeq.advanceIndex();
                }
                else
                {
                    stringstream ss;
                    string holder;
                    ss << mySeq.currChar();
                    ss >> holder;
                        tokenList.push_back(Token("UNDEFINED",holder,mySeq.currLine()));
                        mySeq.advanceIndex();
			mySeq.checkNewLine();
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
    cout << "Total Tokens = " << tokenList.size()<< endl;
}
void Lexer::determineCOLON()
{
	saveLineNum = mySeq.currLine();
        if(mySeq.EoF())
        {
		tokenList.push_back(Token("COLON",":", saveLineNum));
        	tokenString.clear();
	}    
	else
            {//Check next char:
               mySeq.advanceIndex();
	       mySeq.checkNewLine();
		if(mySeq.currChar() == '-')
		{
			if(mySeq.EoF())
			{
				tokenList.push_back(Token("COLON_DASH", ":-", saveLineNum));
			}	
			else
			{
				tokenList.push_back(Token("COLON_DASH", ":-", saveLineNum));
				mySeq.advanceIndex();
				mySeq.checkNewLine();
			}		
		}
		else
		{
			tokenList.push_back(Token("COLON",":",saveLineNum)); //still is a colon
		}
            }
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
    bool lineTrigger = true;
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
	while(lineTrigger)
	{
	    if(mySeq.currChar() == '\n') //check end of line
	    {
		tokenList.push_back(Token("COMMENT",tokenString,saveLineNum));
		lineTrigger = false;
	    }
	    else
	    {
            	tokenString += mySeq.currChar();
            	if(mySeq.EoF()) //then check EOF
            	{
                	tokenList.push_back(Token("COMMENT",tokenString,saveLineNum));
                	tokenString.clear();
	    		lineTrigger = false;
		}
            	else
            	{
                	//Keep going until end of Line
                	mySeq.advanceIndex();
                	mySeq.checkNewLine();
            	}
	    }
         }
    }
    else //Start of Block Comment
    {

	tokenString += mySeq.currChar();
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
        while(blockTrigger)
        { 
            if(mySeq.currChar() != '\n') //when print, will keep string on same line
            {
                 tokenString += mySeq.currChar();
            }
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

            	if(mySeq.currChar() != '\n') //when print, will keep string on same line
            	{
                	 tokenString += mySeq.currChar();
            	}
		else
		{
			mySeq.advanceIndex();
			mySeq.checkNewLine();
			tokenString += mySeq.currChar();
		}

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
		    if(mySeq.EoF())
		    {
                    	tokenList.push_back(Token("COMMENT",tokenString,saveLineNum));
                    	tokenString.clear();
                    	blockTrigger = false;
		    }
		    else
		    {
                    	tokenList.push_back(Token("COMMENT",tokenString,saveLineNum));
                    	tokenString.clear();
                    	blockTrigger = false;
					
			mySeq.advanceIndex();
			mySeq.checkNewLine();
		    }
                }
            }
        }
    }
}
