%{

#include "y.tab.h"
#include "stdlib.h"
#include "string.h"

%}

%%

[\n]		{}

[ \t]		{}

main		{ return MAIN; }

int|char|double	{ strcpy(yylval.sval,yytext); return DT;}

[_a-zA-Z]+[a-zA-Z0-9]*	{ strcpy(yylval.sval,yytext); return ID; }

[0-9]+		{ strcpy(yylval.sval,yytext); return NUM; }

.		{ return yytext[0]; }	
