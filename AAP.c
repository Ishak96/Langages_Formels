/*
	G={
		S->aAB|bc|cBC
		A->a|cA
		B->b|cB
		C->c
	}
	ex:acaccb
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<malloc.h>

#define TMAX 1000

/* 		<<<<<<<	LES LISTE chaînéés >>>>>>>			*/
typedef char TElement;

typedef struct Cellule{
	TElement donnee;
	struct Cellule *suivant;

}*liste;

/* primitives pour les liste chaînées */
TElement valCellule(liste l){
	return l->donnee;

}

liste suivCellule(liste l){
	return l->suivant;

}

typedef struct
{
	char tabCar[10];
	int taille;
}derivation;

typedef struct 
{
	char variable;
	derivation deriver[20];
	int nbrDeriv;
}production;

typedef struct 
{
	derivation deri;
	char variable;
	char terminal;
}transition;

void aff_deri(derivation deri){
	for (int i = 0; i < deri.taille; i++)
	{
		printf("%c", deri.tabCar[i]);
	}
}

void aff_prod(production prod){
	printf("%c->", prod.variable);
	for (int i = 0; i < prod.nbrDeriv; ++i)
	{
		aff_deri(prod.deriver[i]);
		printf("|");
	}
	printf("\n");
}

void aff_gramaire(production *prod, int nbprod){
	printf("soit G=(N,T,S,P) une 'GNC' sous la 'FNG'\n");
	printf("P={");
	for (int i=0; i<nbprod; i++)
	{
		aff_prod(prod[i]);	
	}
	printf("}\n");
}

void aff_mot(int i, int nm, char *mot){
	for (int j = i; j < nm; j++)
	{
		printf("%c", mot[j]);
	}
	printf("\t");
}

void aff_tabl_transition(transition *tran, int nt){
	transition t;

	for (int i = 0; i < nt; i++)
	{
		t=tran[i];
		printf("Sigma(q,%c,%c)={(q,", t.terminal, t.variable);
		aff_deri(t.deri);
		printf(")}\t\t\t|\n");
	}
}

void fonction_transition(production *prod, int n, transition *tran, int *nt){
	derivation der;
	transition t;

	(*nt)=0;

	for (int i = 0; i < n; ++i)
	{
		t.variable=prod[i].variable;
		for (int j = 0; j < prod[i].nbrDeriv; j++)
		{
			der=prod[i].deriver[j];
			t.terminal=der.tabCar[0];

			for (int k = 0; k < der.taille; k++)
			{
				t.deri.tabCar[k]=der.tabCar[k+1];
			}
			t.deri.taille=der.taille-1;
			tran[(*nt)]=t;
			(*nt)=(*nt)+1;
		}
	}
}

int recherche_table_transition(transition *tran, int nt, char character, char variable, derivation *resultat){
	transition t;
	int trouv=0;

	for (int i = 0; i < nt; i++)
	{
		t=tran[i];
		if (t.terminal==character && t.variable==variable)
		{
			trouv=1;
			*resultat=t.deri;
		}
	}
 return trouv;
}

/* 		<<<<<<<	LES PILE >>>>>>>			*/
/*		{ représentation Chaînées }		*/
typedef liste pile;

/* primitives pour les piles */
TElement sommetPile(pile p){
	return p->donnee;

}

liste suivant(pile p){
	return p->suivant;

}

/*1) initialiser une pile*/
liste initPile(){
	return NULL;

}

/*2) teste si une pile est vide ou pas */
int videPile(pile p){
	return p == NULL;

}

/*3) afficher une pile */
void affPile(pile p){
	while(!videPile(p)){
		printf("%c",sommetPile(p));
		p = suivant(p);
	}
	printf("\n");
}

/*4) determiner la hauteur d'une pile */
int hauteur(pile p){
  int lg = 0;
	while(!videPile(p)){
		lg = lg+1;
		p = suivant(p);
	}
	return lg;
}

/* 5) empiler "ajouter une valeur au sommet d'une pile" */
void empile(TElement X,pile *p){
pile cel;
	//création de la cellule
	cel = (pile) malloc (sizeof(struct Cellule));
	//remplissage de la cellule
	cel->donnee = X;
	//chainage
	cel->suivant = *p;
	*p = cel ;
}

/*6) depiler "retirer la valeur au sommet de la pile */
void depile(pile *p){
pile cel ;
	//préservation de la premier cellule de la liste 
	cel = *p;
	//realisation du chainage
	*p = suivant(*p);
	//liberation de la memeoire de la premier cellule
	free(cel);
}

int accept_mot(char mot[20], int nm, pile AAP, transition *Sigma, int nt){
	char sommet;
	int accept,curseur,rech;
	derivation res_tran;

	accept=0;
	rech=1;
	curseur=0;
	sommet=sommetPile(AAP);
	mot[nm]='$';
	
	while(!accept && rech)
	{
		aff_mot(curseur,nm+1,mot);
		affPile(AAP);

		depile(&AAP);
		rech=recherche_table_transition(Sigma, nt, mot[curseur], sommet, &res_tran);

		for (int i = res_tran.taille-1; i >=0 ; i--)
		{
			empile(res_tran.tabCar[i],&AAP);
		}
		sommet=sommetPile(AAP);
		curseur++;
		
		if ((sommet=='#' && mot[curseur]=='$'))
		{
			aff_mot(curseur,nm+1,mot);
			affPile(AAP);
			accept=1;
		}

		if (sommet=='#' && mot[curseur]!='$')
		{
			rech=0;
		}
	}
	mot[nm]='.';
	return accept;
}
/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/
int main (int argc, char **argv) {
srand(time(0));

int nt,accept,n;
production prod[TMAX];
transition tran[TMAX];
char *mot=malloc(sizeof(char)*50);
char *nstr=malloc(sizeof(char)*5);
pile AAP;

AAP=initPile();
derivation der1={{'a','A','B'},3};
derivation der2={{'b','C'},2};
derivation der3={{'c','B','C'},3};
derivation der4={{'a'},1};
derivation der5={{'c','A'},2};
derivation der6={{'b'},1};
derivation der7={{'c','B'},2};
derivation der8={{'c'},1};

production p1={'S',{der1,der2,der3},3};
production p2={'A',{der4,der5},2};
production p3={'B',{der6,der7},2};
production p4={'C',{der8},1};

empile('#',&AAP);
empile('S',&AAP);

prod[0]=p1;
prod[1]=p2;
prod[2]=p3;
prod[3]=p4;

printf("\033[34m" );
printf("\n======='Fonctions' de transitions=======\n");
fonction_transition(prod,4,tran,&nt);
aff_tabl_transition(tran,nt);
printf("========================================\n\n");

printf("\n===============Gramaire===============\n");
aff_gramaire(prod,4);
printf("========================================\n\n");


strcat(mot,argv[1]);
strcat(nstr,argv[2]);
n=atoi(nstr);

printf("\033[36m" );
accept=accept_mot(mot,n,AAP,tran,nt);


if (accept)
{
	printf("\033[32m" );
	printf("================================\n");
	printf("le mot w=%s a étés accepté|\n", mot);
	printf("================================\n");
}
else
{
	printf("\033[31m" );
	printf("=======================================\n");
	printf("le mot w=%s n'est pas étés accepté|\n", mot);
	printf("=======================================\n");
}

return 0;
}