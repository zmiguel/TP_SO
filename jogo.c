#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>

#include "util.h"

//----------JOGO----------------
void ini_jogo(){
    char opcao;


    do{
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("Entraste num labirinto, a porta fechou-se atrás de ti! uuuuuuuuuuhhhh!");
        printf("O que pretendes fazer?");
        scanf("%s", &opcao);




    }while(opcao != 's');
}

//----------CRÉDITOS-------------------------
void creditos(){
    printf("\n\n");
    printf("\n\t\t--------------------------------------------------");
    printf("\n\t\t-------------JOGO DESENVOLVIDO POR:---------------");
    printf("\n\t\t--------------------------------------------------");
    printf("\n\t\t-----ANDRE-PASCOAL-BENTO----N.21240008------------");
    printf("\n\t\t-----JOSE-MIGUEL-VALDEVIESSO-ALVES--N.21240042----");
    printf("\n\t\t--------------------------------------------------");
    printf("\n\t\t--------------------------------------------------");
    printf("\n\n");
}

int main(){

    char labirinto[10][10];
    int opcao;

    do{
        printf("\n\t\t--------------------------------------------------");
        printf("\n\t\t---------------MULTI--USER--DUNGEON---------------");
        printf("\n\t\t--------------------------------------------------");
        printf("\n\t\t---------------------MENU-------------------------");
        printf("\n\t\t--------------------------------------------------");
        printf("\n\t\t1 - INICIAR JOGO----------------------------------");
        printf("\n\t\t2 - CRÉDITOS--------------------------------------");
        printf("\n\t\t3 - SAIR------------------------------------------\n");

        printf("\tVAMOS JOGAR? ");
        scanf("%d", &opcao);
        fflush(stdin);

        if(opcao == 1 || opcao == 2 && opcao != 3){
            switch(opcao){
                case 1:ini_jogo();
                    break;
                case 2:creditos();
                    break;
            }
        }
        else if(opcao != 3)
            printf("\nA opção pretendida não se encontra contemplada no menu!");
    }while(opcao != 3);

    return 0;
}
