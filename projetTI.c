#include "projetTI.h"
#include <math.h>

int occurence(char * chaine, char c){
int cpt,i;
cpt=0;
for(i=0;i<strlen(chaine);i++)
    if(chaine[i]==c) cpt++;
    return cpt;
}



char* chaine_nouveau(char* chaine){
char *t,*t2;
int i,j,k,l;
l=strlen(chaine);
t=(char*)malloc((l+1)*sizeof(char));
t2=(char*)malloc((l+1)*sizeof(char));
for(i=0;i<strlen(chaine);i++) t[i]=chaine[i];

k=0;
for(i=0;i<strlen(chaine);i++){
    if(t[i]!='.') {
                      t2[k]=t[i];
                      k++;
                      for(j=i+1;j<strlen(chaine);j++) if(t[j]==t[i]) {
                                                                   t[j]='.';

                                                                   }

                    }

                   }

t2[k]='\0';
if(t) free(t);
return t2;

}



int taille_frequence(char* chaine){
char *t;
int i,j,k,l;
l=strlen(chaine);
t=(char*)malloc((l+1)*sizeof(char));
for(i=0;i<strlen(chaine);i++) t[i]=chaine[i];
k=0;
for(i=0;i<strlen(chaine);i++){
    if(t[i]!='.') {
                      k++;
                      for(j=i+1;j<strlen(chaine);j++) if(t[j]==t[i]) t[j]='.';
                    }
                   }
if(t) free(t);
return k;
}




double *frequence(char* chaine){
char *t;
double *f;
int i,l,l2;
l=strlen(chaine);
f=(double*)malloc((l+1)*sizeof(double));
t=chaine_nouveau(chaine);
l2=strlen(t);
for(i=0;i<l2;i++) f[i]=(double)occurence(chaine,t[i])/l;
 //for( i=0;i<l2;i++)  printf("%.3f ",f[i]);
return f;

}




double entropie(char* chaine){
double s=0;
int i,l;
double * f;
f=frequence(chaine);
l=taille_frequence(chaine);

for(i=0;i<l;i++)  s=s-f[i]*log2(f[i]);

return s;
}





double * trier_croissant(double* f,int taille){
int i,j,pmin;
double c,min;

for(i=0;i<taille;i++){
        min=f[i];
        pmin=i;
        for(j=i;j<taille;j++) {
                if(min>f[j])  {
                        min=f[j];
                        pmin=j;
                              }
               }
        c=f[pmin];
        f[pmin]=f[i];
        f[i]=c;

                   }

//for(i=0;i<taille;i++) printf("%2.lf ; ",f[i]);

return f;
}



ARBRE creer_noeud(char *car,double val){
ARBRE a;
a=(ARBRE)malloc(sizeof(struct arbre));
a->cle=(char*)malloc(15*sizeof(char));
strcpy(a->cle,car);
a->val=val;
a->sag=NULL;
a->sad=NULL;
return a;
}



ARBRE * arbre_huf(char*chaine){
int i,taille;
double *f;
char c[2];
char *nouv=chaine_nouveau(chaine);
f=frequence(chaine);
taille=taille_frequence(chaine);
ARBRE* tab;
tab=(ARBRE*)malloc(taille*(sizeof(ARBRE)));
for(i=0;i<taille;i++){
        //printf("%2.lf - ",f[i]);
        c[0]=nouv[i];
        c[1]='\0';
    tab[i]=creer_noeud(c,f[i]);
                     }

 return tab;
}




ARBRE* trier_arbre(ARBRE *a,int taille){
    int i,j,pmin;
double min;
ARBRE cour;

for(i=0;i<taille;i++){
     if(a[i]!=NULL){min=a[i]->val;
        pmin=i;
        for(j=i;j<taille;j++) {
                if(min>a[j]->val)  {
                        min=a[j]->val;
                        pmin=j;
                              }
               }
        cour=a[pmin];
        a[pmin]=a[i];
        a[i]=cour;
        }

                   }
cour=NULL;
//for( i=0;i<taille;i++)  printf("%.3f ; ",a[i]->val);
return a;
}



int chercher(char *chaine, char c){
int i,l,ok;
l=strlen(chaine);
ok=0;
for(i=0;i<l;i++) {
        if(chaine[i]==c) {
                         ok=1;
                         break;
                         }
                }

return ok;
}




void pere_huffman(char* chaine){

ARBRE* tab;
ARBRE nouv;
char *seq[12][2];// NIVEAU
char *nomp,*lettre;
int i,j,n,k;
double cap;
double *f;
n=taille_frequence(chaine);
tab=arbre_huf(chaine);
for(i=0;i<10;i++)
    for(j=0;j<2;j++) seq[i][j]=(char*)malloc(n*sizeof(char));
i=0;
k=0;

nomp=(char*)malloc(15*sizeof(char));
while(i<n-1){
                           tab=trier_arbre(tab,n);
                           j=i+1;
                           strcpy(nomp,tab[i]->cle);
                           strcat(nomp,tab[j]->cle);
                           nouv=creer_noeud(nomp,tab[i]->val+tab[j]->val);
                           nouv->sag=tab[i];
                           nouv->sad=tab[j];
                           if(k<12){
                                    strcpy(seq[k][0],tab[i]->cle);
                                    strcpy(seq[k][1],tab[j]->cle);
                                    k++;
                                   }
                           tab[j]=nouv;
                           tab[i]->val=0;
                           i++;
                           //if(nouv) vider_arbre(nouv);
                           nouv=NULL;
            }

cap=0;
f=frequence(chaine);
lettre=chaine_nouveau(chaine);
for(j=0;j<n;j++){
        printf("%c -> ",lettre[j]);

    for(i=k-1;i>=0;i--){
                    if(chercher(seq[i][0],lettre[j])==1) {
                                                          printf("0");
                                                          cap=cap+f[j];

                                                         }
                    if(chercher(seq[i][1],lettre[j])==1){
                                                          printf("1");
                                                          cap=cap+f[j];

                                                         }

                     }
printf("\n");


}

printf("L'entropie H(S), la longueur moyenne |C| et l'efficacite E valent:\n");
printf("  H(S) = %.2f \n",entropie(chaine));
printf("  |C|  = %.2f \n",cap);
printf("   E   = %.2f \n\n",entropie(chaine)/cap);

//VIDER LA MEMOIRE
//for(i=0;i<n;i++) vider_arbre(tab[i]);


}








void vider_arbre(ARBRE a){

if(a!=NULL){

 vider_arbre(a->sag);
 vider_arbre(a->sad);
 free(a->cle);
 free(a);
          }

}

double * trier_decroissant(double* f,int taille){
int i,j,pmax;
double c,max;

for(i=0;i<taille;i++){
        max=f[i];
        pmax=i;
        for(j=i;j<taille;j++) {
                if(max<f[j])  {
                        max=f[j];
                        pmax=j;
                              }
               }
        c=f[pmax];
        f[pmax]=f[i];
        f[i]=c;

                   }

                   return f;
}



double** pour_shannon(char* chaine){
double **mat;
double *f;
int i,j,l;
f=frequence(chaine);
l=taille_frequence(chaine);
f=trier_decroissant(f,l);
mat=(double**)malloc(l*sizeof(double*));
for(i=0;i<l;i++) mat[i]=(double*)malloc(l*sizeof(double));
for(i=0;i<l;i++) mat[i][0]=f[i];
for(i=0;i<l;i++) for(j=1;j<l;j++) mat[i][j]=-1;

return mat;
}



int couper(double **f,int i,int j,int k){
int l,mil;
double somme,sommil;

if(i<j && i>=0){


     somme=0;
     for(l=i;l<=j;l++) somme=somme+f[l][0];
     sommil=0;
     mil=i;
     for(l=i;l<=j;l++) {
                       sommil=sommil+f[l][0];
                       if(sommil>=(somme/2)){
                                     mil=l;
                                     break;
                                     }
                  }
     for(l=i;l<=mil;l++) f[l][k]=1;
     for(l=mil+1;l<=j;l++) f[l][k]=0;
     couper(f,i,mil,k+1);
     couper(f,mil+1,j,k+1);

}
//else return 0;


}


void shannon_fano(char*chaine){
double **f;
int i,j,l,k;
char* nouv;
double cap;
nouv=chaine_nouveau(chaine);
l=taille_frequence(chaine);
f=pour_shannon(chaine);
k=1;
couper(f,0,l-1,k);

cap=0;
for(i=0;i<l;i++) {
        printf("%c -> ",nouv[i]);
        for(j=1;j<l;j++) {
        if(f[i][j]>=0) {
                        printf("%.f",f[i][j]);
                        cap=cap+f[i][0];
                        }
                         }
                 printf("\n");
                 }


printf("L'entropie H(S), la longueur moyenne |C| et l'efficacite E valent:\n");
printf("  H(S) = %.2f \n",entropie(chaine));
printf("  |C|  = %.2f \n",cap);
printf("   E   = %.2f \n\n",entropie(chaine)/cap);
}

