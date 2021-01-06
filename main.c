#include "projetTI.h"


int main()
{

char choix;
//double  *f;
char *chaine;
chaine=(char*)malloc(110*sizeof(char));

do{
    printf("----------MENU----------\n");
    printf("1-HUFFMAN \n");
    printf("2-SHANNON FANO\n");
    printf("0-QUITTER \n");
    printf("------------------------\n");
    printf("Choisissez parmi les numero des options :");
    scanf("%c",&choix);
    if(choix=='0') break;
    else if(choix=='1'){
        fflush(stdin);
        printf("Donner La chaine :");
        gets(chaine);
        printf("\n");
        printf("Code de Huffman :\n");
        pere_huffman(chaine);
        printf("\n");


    }
    else if(choix=='2'){
         fflush(stdin);
        printf("Donner la chaine :");
        gets(chaine);
        printf("\n");
        printf("Code de Shannon Fano :\n");
        shannon_fano(chaine);
        printf("\n");
    }
}while(choix!='1' || choix!='2' );





    return 0;
}
