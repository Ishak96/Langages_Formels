%{
	#include<stdio.h>
	int result;
	extern FILE *yyin;
%}

%token ENTIER PLUS MOINS MULT
%%

expr:
	nombre		{$$=$1; result=$$;}
	|expr PLUS expr	{$$=$1+$3; result=$$;}
	|expr MULT expr	{$$=$1*$3; result=$$;}
	;
nombre:
	ENTIER		{$$=$1;}
	|MOINS		{$$=-$1;}
	;
%%

main()
{
	while(!feof(stdin))
		yyparse();
	
	printf("result=%d\n",result);
}

void yyerror(const char *msg)
{
	printf("%s\n",msg);
}
