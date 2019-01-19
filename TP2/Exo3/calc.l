%{
	/*calc.l*/
	#include"y.tab.h"
%}
%%
[\t]+;
"("		{return PAR_OUVR;}
")"		{return PAR_FERM;}
"+"		{return PLUS;}
"-"		{return MOINS;}
"*"		{return MULT;}
"/"		{return DIV;}
0\.[0-9]+	{yylval.dval=atof(yytext); return FLOTTANT;}
[0-9]+		{yylval.dval=atof(yytext); return FLOTTANT;}
[0-9]+\.[0-9]+	{yylval.dval=atof(yytext); return FLOTTANT;}
"sin"		{return SIN;}
"cos"		{return COS;}
"tan"		{return TAN;}
"atan"		{return ATAN;}
"sqrt"		{return SQRT;}	
"inv"		{return INV;}
[a-zA-Z]+	{printf("%s mot inconnu\n", yytext);}
%%
