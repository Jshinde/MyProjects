#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "LexAnalyzer.h"


/* A function to lookup operators, parentheses and semicolons and
   return the token */
int lookup(char ch)
{
	switch(ch)
	{
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;
		
		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;
		
		case '+':
			addChar();
			nextToken = ADD_OP;
			break;
		
		case '-':
			addChar();
			nextToken = SUB_OP;
			break;
			
		case '*':
			addChar();
			nextToken = MULT_OP;
			break;
			
		case '/':
			addChar();
			nextToken = DIV_OP;
			break;
		
		case ';':
			addChar();
			nextToken = SEMI_COLON;
			break;
			
		default:
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

/* A function to add nextChar to lexeme */
void addChar()
{
	if(lexLen <= 9998)
	{
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}

/* A function to get the next character of input and determine its character class */
void getChar()
{
	if((nextChar = getc(in_fp)) != EOF)
	{
		if(isalpha(nextChar))
		{
			charClass = LETTER;
		}
		else if(isdigit(nextChar))
			charClass = DIGIT;
		else
			charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}

/* A function to call getChar until it returns a non-whitespace character */
void getNonBlank()
{
	while(isspace(nextChar))
		getChar();
}

/* A simple lexical analyzer for arithmetic expressions */
int lex()
{
	lexLen = 0;
	getNonBlank();
	switch(charClass)
	{
		/* Parse identifiers */
		case LETTER:
			addChar();
			getChar();
			while(charClass == LETTER || charClass == DIGIT)
			{
				addChar();
				getChar();
			}
			nextToken = ID;
			break;
		
		/* Parse integer literals */
		case DIGIT:
			addChar();
			getChar();
			while(charClass == DIGIT)
			{
				addChar();
				getChar();
			}
			nextToken = INT_LIT;
			break;
			
		/* Parentheses and operators */
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
			
		/* EOF */
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
	} /* End of switch */
	printf("%s", lexeme);
	
	return nextToken;
} /* End of function lex */

