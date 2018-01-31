#include <stdio.h>
#include <stdlib.h>

void(int t)
{
	if(lookahead == t)
		lookahead = lexan();
	else
		error("Syntax Error");
}

void AssignStmt()
{
	match(ID);
	if(lookahead != '=')
	{
		//TODO: Print Error
		;
	}
	else
	{
		match(lookahead);
		expression();
		match(';');
	}
}

void expression()
{
	term();
	while(lookahead = '+' || lookahead = '-')
	{
		match(lookahead);
		term();
	}
}

void term()
{
	factor();
	while(lookahead = '*' || lookahead = '/')
	{
		match(lookahead);
		factor();
	}
}

void factor()
{
	if(lookahead == ID)
	{
		match(ID);
	}
	else if(lookahead == NUM)
	{
		match(NUM);
	}
	else if(lookahead = '(')
	{
		match('(');
		expression();
		match(')');
	}
	else
	{
		//TODO: Print error message
		;
	}
}