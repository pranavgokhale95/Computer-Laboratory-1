%{
#include "y.tab.h"

%}

%%

[ \t]	{ };

[\n]	{ };

[0-9]+		{ return NUM; }

main		{ return MAIN; }

if		{ return IF; }
else		{ return ELSE; }
for		{ return FOR; }
while		{ return WHILE; }

\>|\<|\==	{ return RELOP; }

char|int|double	{ return DT; }

[_a-zA-Z]+[a-zA-Z0-9]*	{ return ID;}

.		{ return yytext[0]; }

