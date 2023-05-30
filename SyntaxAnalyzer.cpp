#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *l)
{
  la = l;
  nextToken = la->getNextToken();
  nextTokenCode = nextToken->getTokenCode();
}

void SyntaxAnalyzer::Program()
{
	if (nextTokenCode == PROGSYM)
	{
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		if (nextTokenCode == IDENT)
		{
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			if (nextTokenCode == SEMICOLON)
			{
				nextToken = la->getNextToken();
				nextTokenCode = nextToken->getTokenCode();
				DECPART();
				COMPSTMT();
				if (nextTokenCode == NAL)
				{
					nextToken = la->getNextToken();
					nextTokenCode = nextToken->getTokenCode();
					if (nextTokenCode == EOI)
					{
						cout << "Program syntactically correct." << endl;
					}
					else {
						cout << nextToken->getTokenCode()<< endl;
						error("Did not reach the end of the file.");
					}
				}
				else
					error("Missing NAL.");
			}
			else
				error("Missing Semicolon.");
		}
		else
			error("Missing Ident.");
	}
	else
		error("Missing PROGSYM.");
}

void SyntaxAnalyzer::DECPART()
{
	if (nextTokenCode == VARSYM)
	{
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		DECLARATIONS();
	}
}

void SyntaxAnalyzer::DECLARATIONS()
{
	while (nextTokenCode == IDENT) {
		DECLARATION();
	}
}

void SyntaxAnalyzer::DECLARATION()
{
	IDENTLIST();
	if (nextTokenCode == COLON) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		if (nextTokenCode == BOOLSYM) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			if (nextTokenCode == SEMICOLON) {
				nextToken = la->getNextToken();
				nextTokenCode = nextToken->getTokenCode();
			}
			else {
				error("Missing semicolon.");
			}
		}
		else if (nextTokenCode == INTSYM) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			if (nextTokenCode == SEMICOLON) {
				nextToken = la->getNextToken();
				nextTokenCode = nextToken->getTokenCode();
			}
			else {
				error("Missing semicolon.");
			}
		}
		else if (nextTokenCode == REALSYM) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			if (nextTokenCode == SEMICOLON) {
				nextToken = la->getNextToken();
				nextTokenCode = nextToken->getTokenCode();
			}
			else {
				error("Missing semicolon.");
			}
		}
	}
	else {
		error("Missing comma.");
	}
}

void SyntaxAnalyzer::IDENTLIST()
{
	if (nextTokenCode == IDENT) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		while (nextTokenCode == COMMA) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			if (nextTokenCode == IDENT) {
				nextToken = la->getNextToken();
				nextTokenCode = nextToken->getTokenCode();
			}
		}
	}
}

void SyntaxAnalyzer::COMPSTMT()
{
	if (nextTokenCode == BEGINSYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		SEQOFSTMT();
		if (nextTokenCode == ENDSYM) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
		}
		else {
			error("Missing endsym.");
		}
	}
	else {
		error("Missing beginsym.");
	}
}

void SyntaxAnalyzer::SEQOFSTMT()
{
	STATMENT();
	if (nextTokenCode == SEMICOLON) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		SEQOFSTMT();
	}
}

void SyntaxAnalyzer::BLOCK()
{
	if (nextTokenCode == BEGINSYM) {
		COMPSTMT();
	}else STATMENT();
}

void SyntaxAnalyzer::STATMENT()
{
	if (nextTokenCode == FORSYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		if (nextTokenCode == IDENT) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			if (nextTokenCode == BECOMES) {
				nextToken = la->getNextToken();
				nextTokenCode = nextToken->getTokenCode();
				EXPRESSION();
				if (nextTokenCode == TOSYM||nextTokenCode==DOWNTOSYM) {
					nextToken = la->getNextToken();
					nextTokenCode = nextToken->getTokenCode();
					EXPRESSION();
					if (nextTokenCode == DOSYM) {
						nextToken = la->getNextToken();
						nextTokenCode = nextToken->getTokenCode();
						BLOCK();
					}
					else {
						error("Missing dosym.");
					}
				}
				else {
					error("Missing tosym or downtosym.");
				}
			}
			else {
				error("Missing becomes.");
			}
		}
		else {
			error("Missing ident.");
		}
	}
	else if (nextTokenCode == IDENT) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		if (nextTokenCode == BECOMES) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			EXPRESSION();
		}
		else {
			error("Missing becomes.");
		}
	}
	else if(nextTokenCode==IFSYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		EXPRESSION();
		if (nextTokenCode == THENSYM) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			BLOCK();
			if (nextTokenCode == ELSESYM) {
				nextToken = la->getNextToken();
				nextTokenCode = nextToken->getTokenCode();
				BLOCK();
			}
		}
		else {
			error("Missing thensym.");
		}
	}
	else if (nextTokenCode == REPEATSYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		SEQOFSTMT();
		if (nextTokenCode == UNTILSYM) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			EXPRESSION();
		}
		else {
			error("Missing until.");
		}
	}
	else if(nextTokenCode==WHILESYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		EXPRESSION();
		if (nextTokenCode == DOSYM) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			BLOCK();
		}
		else {
			error("Missing dosym.");
		}
	}
	else if (nextTokenCode == READSYM||nextTokenCode==READLNSYM||nextTokenCode==WRITELNSYM||nextTokenCode==WRITESYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		if (nextTokenCode == LPAREN) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
			IDENTLIST();
			if (nextTokenCode == RPAREN) {
				nextToken = la->getNextToken();
				nextTokenCode = nextToken->getTokenCode();
			}
			else {
				error("Missing right paren.");
			}
		}
		else {
			error("Missing left paren.");
		}
	}
	else {
		error("Missing a valid STATEMENT.");
	}
}

void SyntaxAnalyzer::EXPRESSION()
{
	SIMPEXPR();
	if (nextTokenCode == EQL || nextTokenCode == NEQ || nextTokenCode == LSS || nextTokenCode == LEQ || nextTokenCode == GTR || nextTokenCode == GEQ) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		SIMPEXPR();
	}
}

void SyntaxAnalyzer::SIMPEXPR()
{
	TERM();
	while (nextTokenCode == PLUS || nextTokenCode == MINUS || nextTokenCode == ORSYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		TERM();
	}
}

void SyntaxAnalyzer::TERM()
{
	FACTOR();
	while (nextTokenCode == TIMES || nextTokenCode == SLASH || nextTokenCode == DIVSYM || nextTokenCode == MODSYM || nextTokenCode == ANDSYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		FACTOR();
	}
}

void SyntaxAnalyzer::FACTOR()
{
	if (nextTokenCode == NOTSYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		PRIMARY();
	}
	else PRIMARY();
}

void SyntaxAnalyzer::PRIMARY()
{
	if (nextTokenCode == LPAREN) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
		EXPRESSION();
		if (nextTokenCode == RPAREN) {
			nextToken = la->getNextToken();
			nextTokenCode = nextToken->getTokenCode();
		}
		else {
			error("Missing RPAREN.");
		}
	}
	else if (nextTokenCode == IDENT || nextTokenCode == NUMLIT || nextTokenCode == TRUESYM || nextTokenCode == FALSESYM) {
		nextToken = la->getNextToken();
		nextTokenCode = nextToken->getTokenCode();
	}
	else {
		error("Missing LPAREN or IDENT or NUMLIT or TRUESYM or FALSESYM.");
	}
}

void SyntaxAnalyzer::error(string s)
{
	int i=la->getCurrentTokenPosition();
	for (int j = 0; j < i; j++) {
		cout << "  ";
	}cout << "^"<<endl;
	cout << "Error: " << s << endl;
	exit(0);
}