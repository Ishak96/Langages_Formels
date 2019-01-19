%{
	/*ess.l :partie lex de ess*/

	#include "y.tab.h"
	extern int yylval;
%}

%%
[\t ]+;

"+"	{return PLUS;}
"-"	{return MOINS;}
"*"	{return MULT;}
[0-9]+	{yylval=atoi(yytext); return ENTIER;}
[a-zA-Z]+   {printf("%s mot inconnu\n", yytext);}
%%
