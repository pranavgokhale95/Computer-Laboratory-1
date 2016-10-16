%{

#include <stdio.h>
#include <string.h>

void insertIntoSymbolTable(char*);
void insertIntoError(char*);
int line_no=1;

struct table_row{
	char type[20];
	char name[20];
	char val[20];
} sym_tbl[50];

int sym_index=0;

struct error_row{
	char name[20];
}err_tbl[50];

int err_index=0;

%}


%%

[ ]	{	}
[\t]	{	}
[\n]	{ line_no++;	}

\#	{ printf("%d\t\t%s\t\tPreprocessor\n",line_no,yytext);	}

include	{ printf("%d\t\t%s\t\tkeyword\n",line_no,yytext);	}

[a-z]*\.h	{printf("%d\t\t%s\t\theader file\n",line_no,yytext);	}

\<	{ printf("%d\t\t%s\t\tless than\n",line_no,yytext);	}

\>	{ printf("%d\t\t%s\t\tgreater than\n",line_no,yytext);	}

\(	{ printf("%d\t\t%s\t\topening paranthesis\n",line_no,yytext);	}

\)	{ printf("%d\t\t%s\t\tclosing paranthesis\n",line_no,yytext);	}

\{	{ printf("%d\t\t%s\t\topening brace\n",line_no,yytext);	}

\}	{ printf("%d\t\t%s\t\tclosing brace\n",line_no,yytext);	}

\;	{ printf("%d\t\t%s\t\tend of statement\n",line_no,yytext);	}

\=|\+|\-|\*|\/	{ printf("%d\t\t%s\t\toperator\n",line_no,yytext);	}

(int|float|double|char)[ ][_a-zA-Z]+[0-9a-zA-Z]*\=[0-9]*	{ insertIntoSymbolTable(yytext); }

int|float|double|char	{ printf("%d\t\t%s\t\tData Type\n",line_no,yytext);	}

[_a-zA-Z]+[0-9a-zA-Z]*	{ printf("%d\t\t%s\t\tIdentifier\n",line_no,yytext);	}

[0-9]+[a-zA-Z]*		{ insertIntoError(yytext); }

%%

int main(){
	printf("Line\t\tLexeme\t\tToken\n");
	FILE *in = fopen("input.c","r");	
	yyin=in;
	yylex();
	fclose(in);

	printf("\n\nSymbol Table:\n");
	printf("Type\t\tName\t\tValue\n");

	int i=0;

	for(i=0;i<sym_index;i++){
		struct table_row row = sym_tbl[i];
		printf("%s\t\t%s\t\t%s\n",row.type,row.name,row.val);

	}

	printf("\n\nLexecal Errors:\n");

	for(i=0;i<err_index;i++){
		struct error_row row = err_tbl[i];
		printf("%s\n",row.name);
	}


	return 0;
}

void insertIntoSymbolTable(char* text){
	int i=0;
	
	while(text[i]!=' ')
		i++;
	
	struct table_row row;

	strncpy(row.type,text,i);
	row.type[i]='\0';


	i++;
	int b_i=i;
	int identifier_len=0;

	while(text[i]!='='){
		i++;
		identifier_len++;
	}

	i++;

	strncpy(row.name,text+b_i,identifier_len);
	row.name[identifier_len]='\0';

	strcpy(row.val,text+i);

	sym_tbl[sym_index]=row;

	printf("%d\t\t%s\t\tData Type\n",line_no,row.type);
	printf("%d\t\t%s\t\tIdentifier\n",line_no,row.name);
	printf("%d\t\t%s\t\tConstant\n",line_no,row.val);

	sym_index++;
}

void insertIntoError(char* text){

	struct error_row row;
	strcpy(row.name,text);
	err_tbl[err_index]=row;
		
	err_index++;
}

int yywrap(){
	return 1;
}
