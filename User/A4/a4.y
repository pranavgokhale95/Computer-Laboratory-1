%{

#include "stdio.h"
extern FILE* yyin;

%}

%token MAIN ID DT NUM IF ELSE RELOP FOR WHILE
%left '+' '-'
%left '*' '/'
%start program
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program	: MAIN '(' ')' '{' slist '}'	{ printf ("correct program\n"); }

slist	: varlist s;

varlist	: varstmt varlist
	|
	;

varstmt	: DT vardec ';'			{ printf ("correct declaration\n"); }
	;

vardec	: ID ',' vardec
	| ID
	;
	
s	: stmt s;
	|
	;

stmt	: ID '=' expr ';'
	| expr ';'
	| ifstmt
	| forstmt
	| whilestmt
	;

expr	: expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' expr
	| ID
	| NUM
	;

ifstmt	: IF '(' cond ')' '{' s '}' %prec LOWER_THAN_ELSE { printf("If statement\n");}
	| IF '(' cond ')' '{' s '}' ELSE '{' s '}' { printf("If-ELse statement\n");}

forstmt: FOR '(' assign ';' cond ';' indec ')' '{' s '}' { printf("for loop\n"); }

whilestmt: WHILE '(' cond ')' '{' s '}'	{ printf("while loop\n"); }

cond	: expr RELOP expr
	; 

assign	: ID '=' expr;
	;
indec	: ID '+''+'
	| ID '-''-'
	;


%%


int main(){
	FILE* in = fopen("input.c","r");
	yyin = in;
	yyparse();
	fclose(in);

	return 0;
}

int yyerror(char *err){
	printf("syntax error\n");
}

int yywrap(){
	return 1;
}

