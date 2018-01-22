#include <stdio.h>
#include "LexAnalyzer.h"

main()
{
	/* Open the input data file and process its contents */
	if((in_fp = fopen("program.txt", "r")) == NULL)
		printf("Error - Cannot open file \n");
	else
	{
		getChar();
		do
		{
			lex();
		}
		while(nextToken != EOF);
	}
}
