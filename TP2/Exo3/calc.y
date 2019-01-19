%{
	/*calc.y*/
	#include<stdio.h>
	#include<math.h>

%}

%union{
	double dval;
	int ival;
}

%token <dval> FLOTTANT
%token PAR_OUVR PAR_FERM
%type <dval> expr nombre ligne
%left PLUS MOINS
%left MULT DIV
%right SIN COS TAN ATAN SQRT INV MOINSUNAIRE
%%

ligne:
	expr{printf("expresion=%.10g\n",$1);}
	;

expr:
	nombre {$$=$1;}
	|PAR_OUVR expr PAR_FERM {$$=$2;}
	|expr PLUS expr {$$=$1+$3;}
	|expr MOINS expr {$$=$1-$3;}
	|expr MULT expr {$$=$1*$3;}
	|expr DIV expr {$$=$1/$3;}
	|SIN expr {$$=sin($2);}
	|COS expr {$$=cos($2);}
	|TAN expr {$$=tan($2);}
	|SQRT expr {$$=sqrt($2);}
	|INV expr {$$=1.0/$2;}
	|MOINS expr %prec MOINSUNAIRE {$$=-$2;}
	;

nombre:
	FLOTTANT {$$=$1;}
	;
%%

main()
{
	yyparse();
}

void yyerror(const char *msg)
{
	printf("%s\n",msg);
}
