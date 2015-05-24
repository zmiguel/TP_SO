#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "util.h"

int obtem_rand(int min, int max){
    int random;
    random = min + rand() % (max - min + 1);
    return random;
}

int valida_jogador(){
    FILE *f;
    char *nome[TAM], linha[TAM];
    int pass;

    EU val;

    if((f = fopen("jogadores.txt", "rt")) == NULL){
        printf("ERRO na abertura do ficheiro de texto para leitura.\n");
    }

    do{
        fscanf(f, "%s:", nome[TAM]);
        if((strcmp(val.nome,nome[TAM]))==0){
            fscanf(f,"%d", &pass);
            if(pass == val.pass)
                return 1;
        }
    }while(fgets(linha, TAM, f) != NULL);

    return 0;

    fclose(f);
}

//MELHORAR ISTO - ARRANJAR MELHOR MANEIRA DE DEFINIR VALORES NAS ESTRUTURAS E DE FORMA ALEATÓRIA USSANDO A func obtem_rand(min,max)!

//----------DECLARAÇÃO-DE-MONSTROS-----------
monst morcego = {"Morcego", obtem_rand(4,5), obtem_rand(3,4), obtem_rand(4,5), obtem_rand(0,1)};
morcego.ataque = obtem_rand(4,5);

monst escorpiao = {"Escorpião", 7, 5, 3};
monst lobisomem = {"Lobisomem", 8, 6, 6};
monst urso = {"Urso", 10, 10, 8};
monst boss = {"Boss", obtem_rand(10,12), 15, 15};
//------------DECLARACAO-DE-OBJECTOS---------
objecto sandes =    {"Sandes",  0.5, 10, 4, 0 , 0, 1}; //id 1
objecto aspirina =  {"Aspirina",0.1, 20, 6, 0, 0, 1}; //id 2
objecto xarope =    {"Xarope",  1, 4, 2, 0, 0, 1}; //id 3
objecto faca =      {"Faca",    2, 5, 0, 5, 0, 0}; //id 4
objecto espada =    {"Espada",  8, 3, 0, 8, 2, 0}; //id 5
objecto granado =   {"Granada", 1, 2, 0, 30, 0, 1}; //id 6
objecto escudo =    {"Escudo",  4, 4, 0, 5, 0, 0}; //id 7
objecto moeda =     {"Moeda",   0.1, 5, 0, 0, 0}; //id 8


int fd_servidor, fd_cliente;

int main(void){
    int n;

    MENSAGEM msg;

    /* CRIAÇAO DAS SALAS E CONTEUDO DAS SALAS DO JOGO */

        //dados das salas
        //linha 1
        lab[0][0].prob_monst = 10;
        lab[0][0].type = 1;
        lab[0][0].x = 1;
        lab[0][0].y = 2;
        lab[0][0].pass_n = 0;
        lab[0][0].pass_s = 1;
        lab[0][0].pass_e = 0;
        lab[0][0].pass_o = 0;

        lab[0][1].prob_monst = 20;
        lab[0][1].type = 0;
        lab[0][1].x = 1;
        lab[0][1].y = 2;
        lab[0][0].pass_n = 0;
        lab[0][0].pass_s = 1;
        lab[0][0].pass_e = 1;
        lab[0][0].pass_o = 0;

        lab[0][2].prob_monst = 40;
        lab[0][2].type = 0;
        lab[0][2].x = 1;
        lab[0][2].y = 3;
        lab[0][0].pass_n = 0;
        lab[0][0].pass_s = 0;
        lab[0][0].pass_e = 0;
        lab[0][0].pass_o = 1;

        lab[0][3].prob_monst = 66;
        lab[0][3].type = 0;
        lab[0][3].x = 1;
        lab[0][3].y = 4;
        lab[0][0].pass_n = 0;
        lab[0][0].pass_s = 1;
        lab[0][0].pass_e = 0;
        lab[0][0].pass_o = 0;

        lab[0][4].prob_monst = 100;
        lab[0][4].type = 5;
        lab[0][4].x = 1;
        lab[0][4].y = 5;
        lab[0][0].pass_n = 0;
        lab[0][0].pass_s = 1;
        lab[0][0].pass_e = 0;
        lab[0][0].pass_o = 0;

        //linha 2
        lab[1][0].prob_monst = 10;
        lab[1][0].type = 0;
        lab[1][0].x = 2;
        lab[1][0].y = 2;

        lab[1][1].prob_monst = 20;
        lab[1][1].type = 0;
        lab[1][1].x = 2;
        lab[1][1].y = 2;

        lab[1][2].prob_monst = 40;
        lab[1][2].type = 0;
        lab[1][2].x = 2;
        lab[1][2].y = 3;

        lab[1][3].prob_monst = 66;
        lab[1][3].type = 0;
        lab[1][3].x = 2;
        lab[1][3].y = 4;

        lab[1][4].prob_monst = 80;
        lab[1][4].type = 0;
        lab[1][4].x = 2;
        lab[1][4].y = 5;

        //linha 3
        lab[2][0].prob_monst = 10;
        lab[2][0].type = 0;
        lab[2][0].x = 3;
        lab[2][0].y = 2;

        lab[2][1].prob_monst = 20;
        lab[2][1].type = 0;
        lab[2][1].x = 3;
        lab[2][1].y = 2;

        lab[2][2].prob_monst = 0;
        lab[2][2].type = 3;
        lab[2][2].x = 3;
        lab[2][2].y = 3;

        lab[2][3].prob_monst = 66;
        lab[2][3].type = 0;
        lab[2][3].x = 3;
        lab[2][3].y = 4;

        lab[2][4].prob_monst = 0;
        lab[2][4].type = 4;
        lab[2][4].x = 3;
        lab[2][4].y = 5;

        //linha 4
        lab[3][0].prob_monst = 10;
        lab[3][0].type = 0;
        lab[3][0].x = 4;
        lab[3][0].y = 2;

        lab[3][1].prob_monst = 20;
        lab[3][1].type = 0;
        lab[3][1].x = 4;
        lab[3][1].y = 2;

        lab[3][2].prob_monst = 40;
        lab[3][2].type = 0;
        lab[3][2].x = 4;
        lab[3][2].y = 3;

        lab[3][3].prob_monst = 66;
        lab[3][3].type = 0;
        lab[3][3].x = 4;
        lab[3][3].y = 4;

        lab[3][4].prob_monst = 80;
        lab[3][4].type = 0;
        lab[3][4].x = 4;
        lab[3][4].y = 5;

        //textos das salas


    /* FIM DA CRIAÇÃO DAS SALAS */

    /* VERIFICAR SE EXISTE "CP" DO SERVIDOR (access) -- APENAS UM!!!*/
    if(access("CPservidor", F_OK)==0){
        printf("[ERRO] Ja existe um servidor!\n");
        exit(1);
    }
    /* CRIAR "CP" DO SERVIDOR - MINHA (mkfifo) */
    mkfifo("CPservidor", 0600);
    /* ABRIR "CP" DO SERVIDOR - MINHA (open - O_RDONLY) */
    fd_servidor = open("CPservidor", O_RDWR);

    printf("[SERVIDRO] SERVIDOR INICIADO!\n");

    do{
        /* RECEBER PEDIDO NA "CP" DO SERVIDOR - MINHA (n = read();) */
        n = read(fd_servidor, &msg, sizeof(data));

        if(n != 3){
            printf("[SERVIDOR] Não existem jogadores suficientes!\n");
            sleep(1);
            continue;
        }
        else if(strcmp(msg.op1,"mov")==0){
            if(strcmp(msg.op2,"frente")==0){
                printf("Recebi um pedido para mover o jogador para a frente...\n");
                printf("Falta implementar!\n");
                /*LÓGICA DE JOGO NORTE*/
            }
            else if(strcmp(msg.op2,"tras")==0){
                printf("Recebi um pedido para mover o jogador para tras...\n");
                printf("Falta implementar!\n");
                /*LÓGICA DE JOGO SUL*/
            }
            else if(strcmp(msg.op2,"direita")==0){
                printf("Recebi um pedido para mover o jogador para a direita...\n");
                printf("Falta implementar!\n");
                /*LÓGICA DE JOGO ESTE*/
            }
            else if(strcmp(msg.op2,"esquerda")==0){
                printf("Recebi um pedido para mover o jogador para a esquerda...\n");
                printf("Falta implementar!\n");
                /*LÓGICA DE JOGO OESTE*/
            }
        }
        else if(strcmp(msg.op1,"atac")==0){
            //FUNCOES PARA BATALHAR MONSTROS
            printf("Falta implementar!\n");
        }
        else if(strcmp(msg.op1,"ver")==0){
            //FUNCOES PARA VISUALIZAR O QUE SE PASSA AO REDOR
            printf("Falta implementar!\n");

        }
        /* ABRIR "CP" DO CLIENTE (open - O_WRONLY) */
        fd_cliente = open(msg.endereco, O_WRONLY);
        /* ENVIAR RESPOSTA PARA A "CP" DO CLIENTE (write) */
        write(fd_cliente, &msg, sizeof(msg));
        /* FECHAR "CP" DO CLIENTE (close) */
        close(fd_cliente);
    }while(msg.desliga != 1);

    printf("[SERVIDOR] SERVIDOR DESLIGADO");

    /* FECHAR "CP" DO SERVIDOR - MINHA (close) */
    close(fd_servidor);
    /* REMOVER "CP" DO SERVIDOR- MINHA (UNLINK) */
    unlink("CPservidor");
    exit(0);
}
