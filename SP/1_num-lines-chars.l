%{
	#include <stdio.h>
	int num_lines = 0, num_chars = 0;
%}

%option noyywrap

%%

\n	++num_lines; ++num_chars;
. 	++num_chars;

%%

int main(void) {
	yylex();
	printf("# of lines = %d, # of chars = %d\n", num_lines, num_chars);
	return 0;
}
