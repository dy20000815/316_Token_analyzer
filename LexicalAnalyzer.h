#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class LexicalAnalyzer
{
private:
    ifstream* sourceCodeFile;
    int lexcompare(string);
    int currentTokenPosition=0;


public:
    LexicalAnalyzer(ifstream*);
    Token* getNextToken();
    int getCurrentTokenPosition();
};

#endif