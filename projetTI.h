#ifndef PROJETTI_H_INCLUDED
#define PROJETTI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int occurence(char*,char);
char* chaine_nouveau(char *);
int taille_frequence(char*);
double * frequence(char*);
double entropie(char *);
void calcul(char *);



struct arbre{
char *cle;
double val;
struct arbre* sag;
struct arbre* sad;

};



double* trier_decroissant(double*,int);
typedef struct arbre *ARBRE;
ARBRE creer_noeud(char*,double);
ARBRE *arbre_huf(char* chaine);
ARBRE *trier_arbre(ARBRE*,int );
void pere_huffman(char*);


void vider_arbre(ARBRE );
int chercher(char*,char);




double** pour_shannon(char*);
int couper(double** ,int ,int ,int );
void shannon_fano(char*);




#endif // PROJETTI_H_INCLUDED
