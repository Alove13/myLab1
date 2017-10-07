#include <iostream>
#include <string>
#include "Lexer.h"

using namespace std;

int main()
{
    string theFile;
    cout << "File name with .txt at end: " << endl;
    cin >> theFile;
    
    Lexer myLex(theFile); //Starts process

    return 0;
}
