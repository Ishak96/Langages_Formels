/* Recursive_Descent.c
   descente recursive pour

   S->(S)S|e


   word=((())())
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include<string.h>

#define DEBUG 0
#define WORDMAX 100

void error(char *messge);
void next_c(void);
void S(void);
void A(void);
void B(void);
void check(char cc);

/*-------- Variables globales ---------*/

static char c;
static char word[WORDMAX];
static int position;

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/
int main (int argc, char *argv[]) {
srand(time(0));

strcat(word,argv[1]);
strcat(word,"$");

position=0;

printf("prêt a analyser le mot %s.\n", word);

next_c();
S();

if(c=='$')
{
	printf("\033[32m" );
	printf("================================\n");
	printf("le mot w=%s a étés accepté|\n", word);
	printf("================================\n");
}
else
{
	printf("\033[31m" );
	printf("=======================================\n");
	printf("le mot w=%s n'est pas étés accepté|\n", word);
	printf("=======================================\n");
}

return 0;
}

/*------------------------*/
void error(char *messge){
	printf("\033[31m" );
	printf("%s\n", messge);
	exit(0);
}

/*-----------------------*/
void next_c(void){
	c=word[position++];
	
	#if(DEBUG > 0)
		printf("\033[36m" );
		printf("next_c(): c == %c\n", c);
	#endif
}

/*----------------------*/
void S(void){
	#if(DEBUG > 0)
		printf("\033[36m" );
		printf("S\n");
	#endif
	
	switch(c){
		case '(':
			next_c();
			S();
			if (c!=')')
				error("erreur dans S() : ) attendu\n");
			else
				next_c();
			S();
			break;
		
		case')':
		case'$':
			return;

		default:error("erreur dans S() : )\n");
	}
}