#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class SyntaxAnalyzer
{
  private:
    LexicalAnalyzer *la;
    Token *nextToken;
    TokenCodes nextTokenCode;

  public:
    SyntaxAnalyzer(LexicalAnalyzer*);
    void Program();
    void DECPART();
    void COMPSTMT();
    void DECLARATIONS();
    void DECLARATION();
    void IDENTLIST();
    void SEQOFSTMT();
    void BLOCK();
    void STATMENT();
    void EXPRESSION();
    void SIMPEXPR();
    void TERM();
    void FACTOR();
    void PRIMARY();
    void error(string s);
};

#endif
