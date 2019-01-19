/* Recursive_Descent.c
   descente recursive pour

   S->aAb|bBa
   A->aA|bB
   B->aB|ba

   word=aabbab
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
void A(void){
	#if(DEBUG > 0)
		printf("\033[36m" );
		printf("A\n");
	#endif
		
	switch(c){
		case 'a':
			next_c();
			A();
			break;

		case 'b':
			next_c();
			B();
			break;

		default:error("erreur dans A() : a ou b attendu\n");
	}
}

/*----------------------*/
void B(void){
	#if(DEBUG > 0)
		printf("\033[36m" );
		printf("B\n");
	#endif
	
	switch(c){
		case 'a':
			next_c();
			B();
			break;

		case 'b':
			next_c();
			
			if (c!='a')
				error("erreur dans B() : a attendu\n");
			else
				next_c();
			break;

		default:error("erreur dans B() : a ou b attendu\n");
	}
}

/*----------------------*/
void S(void){
	#if(DEBUG > 0)
		printf("\033[36m" );
		printf("S\n");
	#endif
	
	switch(c){
		case 'a':
			next_c();
			A();

			if(c!='b')
				error("erreur dans S() : b attendu\n");
			else
				next_c();
			break;

		case 'b':
			next_c();
			B();

			if(c!='a')
				error("erreur dans S() : a attendu\n");
			else
				next_c();
			break;

		default:error("erreur dans S() : a ou b attendu\n");
	}
}