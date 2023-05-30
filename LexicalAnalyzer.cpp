#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream* scf)
{
	sourceCodeFile = scf;
}

Token* LexicalAnalyzer::getNextToken()
{
	currentTokenPosition++;
	TokenCodes tcs=EOI;
	string lexeme="";
	ifstream* scf = sourceCodeFile;
	//cout << scf->eof() << endl;
	if (scf->eof() == false) {
		unsigned char c;
		*scf >> c;
		if (c == '.') {
			lexeme = c;
			tcs = NAL;
		}else
		if (isdigit(c)) {
			while (isdigit(scf->peek()) && scf->eof() == false) {
				lexeme += c;
				*scf >> c;
			}lexeme += c;
			tcs=NUMLIT;
		}
		else if (c == '+') {
			lexeme = c;
			tcs=PLUS;
		}
		else if (c == '-') {
			lexeme = c;
			tcs=MINUS;
		}
		else if (c == '*') {
			lexeme = c;
			tcs=TIMES;
		}
		else if (c == '/') {
			lexeme = c;
			tcs=SLASH;
		}
		else if (c == '=') {
			lexeme = c;
			tcs=EQL;
		}
		else if (c == '(') {
			lexeme = c;
			tcs = LPAREN;
		}
		else if (c == ')') {
			lexeme = c;
			tcs=RPAREN;
		}
		else if (c == '.') {
			lexeme = c;
			tcs=PERIOD;
		}
		else if (c == ',') {
			lexeme = c;
			tcs=COMMA;
		}
		else if (c == ';') {
			lexeme = c;
			tcs=SEMICOLON;
		}
		else if (c == ':') {
			lexeme = c;
			c = scf->peek();
			if (c == '=') {
				*scf >> c;
				lexeme += c;
				tcs = BECOMES;
			}
			else {
				tcs = COLON;
			}
		}
		else if (c == '<') {
			lexeme = c;
			c = scf->peek();
			if (c == '=') {
				*scf >> c;
				lexeme += c;
				tcs = LEQ;
			}
			else if (c == '>') {
				*scf >> c;
				lexeme += c;
				tcs = NEQ;
			}
			else {
				tcs = LSS;
			}
		}
		else if (c == '>') {
			lexeme = c;
			c = scf->peek();
			if (c == '=') {
				*scf >> c;
				lexeme += c;
				tcs = GTR;
			}
			else {
				tcs = GEQ;
			}
		}
		else if (isalpha(c)){
			while ((isdigit(scf->peek()) || isalpha(scf->peek()))&&scf->eof()!=true) {
				lexeme += c;
				*scf >> c;
			}lexeme += c;
			if (lexcompare(lexeme) != 30) {
				int i = lexcompare(lexeme);
				switch (i) {
				case 0:
					tcs = ANDSYM;
					break;
				case 1:
					tcs = BEGINSYM;
					break;
				case 2:
					tcs = BOOLSYM;
					break;
				case 3:
					tcs = DIVSYM;
					break;
				case 4:
					tcs = DOSYM;
					break;
				case 5:
					tcs = DOWNTOSYM;
					break;
				case 6:
					tcs = ELSESYM;
					break;
				case 7:
					tcs = ENDSYM;
					break;
				case 8:
					tcs = FALSESYM;
					break;
				case 9:
					tcs = FORSYM;
					break;
				case 10:
					tcs = IFSYM;
					break;
				case 11:
					tcs = INTSYM;
					break;
				case 12:
					tcs = MODSYM;
					break;
				case 13:
					tcs = NOTSYM;
					break;
				case 14:
					tcs = ORSYM;
					break;
				case 15:
					tcs = PROGSYM;
					break;
				case 16:
					tcs = READSYM;
					break;
				case 17:
					tcs = READLNSYM;
					break;
				case 18:
					tcs = REALSYM;
					break;
				case 19:
					tcs = REPEATSYM;
					break;
				case 20:
					tcs = THENSYM;
					break;
				case 21:
					tcs = TOSYM;
					break;
				case 22:
					tcs = TRUESYM;
					break;
				case 23:
					tcs = UNTILSYM;
					break;
				case 24:
					tcs = VARSYM;
					break;
				case 25:
					tcs = WHILESYM;
					break;
				case 26:
					tcs = WRITESYM;
					break;
				case 27:
					tcs = WRITELNSYM;
					break;
				}
			}
			else tcs = IDENT;
		}
		else {
			tcs = EOI;
		}
	}
	Token* t;
	t = new Token(tcs,lexeme);
	return t;
}

int LexicalAnalyzer::getCurrentTokenPosition()
{
	return currentTokenPosition;
}

int LexicalAnalyzer::lexcompare(string lex) {
	string list[] = { "and","begin","boolean","div","do","downto","else","end","false","for","if","integer","mod","not","or","program","read","readln","real","repeat","then","to","true","until","var","while","write","writeln" };
	for (int i = 0; i < 28; i++) {
		if (lex.compare(list[i]) == 0) {
			return i;
		}
	}
	return 30;
}