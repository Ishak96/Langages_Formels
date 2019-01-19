%{
 /*prem.l : 1er exemple */
%}

%%
[\t ]+;

toto |
tit |
tonton    {printf("garçon\n");}

tata |  
tutu       {printf("fille\n"); }

[a-zA-Z]+   {printf("%s est un nom inconnu\n", yytext);}
%%
main()
{
yylex();
}
