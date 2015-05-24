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
/*monst morcego = {"Morcego", obtem_rand(4,5), obtem_rand(3,4), obtem_rand(4,5), obtem_rand(0,1)};
morcego.ataque = obtem_rand(4,5);

monst escorpiao = {"Escorpião", 7, 5, 3};
monst lobisomem = {"Lobisomem", 8, 6, 6};
monst urso = {"Urso", 10, 10, 8};
monst boss = {"Boss", obtem_rand(10,12), 15, 15};
//------------DECLARACAO-DE-OBJECTOS---------
objecto sandes = {"Sandes", 0.5, 10, 0 , 0, 1};
objecto aspirina = {"Aspirina", 0.1, 20, 0, 0, 1};
objecto xarope = {"Xarope", 1, 4, 0, 0, 1};
objecto faca = {"Faca", 2, 5, 5, 0, 0};
objecto espada = {"Espada", 8, 3, 8, 2, 0};
objecto granado = {"Granada", 1, 2, 30, 0, 1};
objecto escudo = {"Escudo", 4, 4, 5, 0, 0};
objecto moeda = {"Moeda", 0.1, 5, 0, 0};
*/

int fd_servidor, fd_cliente;

int main(void){
    int n;

    MENSAGEM msg;

    //MATRIZ LABIRINTO, DECLARAÇÃO ETC PRA DEPOIS IMPLEMENTAR A BAIXO...

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
            if(strcmp(msg.op2,"norte")==0){
                printf("Recebi um pedido para mover o jogador para o norte...\n");
                printf("Falta implementar!\n");
                /*LÓGICA DE JOGO NORTE*/
            }
            else if(strcmp(msg.op2,"sul")==0){
                printf("Recebi um pedido para mover o jogador para o sul...\n");
                printf("Falta implementar!\n");
                /*LÓGICA DE JOGO SUL*/
            }
            else if(strcmp(msg.op2,"este")==0){
                printf("Recebi um pedido para mover o jogador para o este...\n");
                printf("Falta implementar!\n");
                /*LÓGICA DE JOGO ESTE*/
            }
            else if(strcmp(msg.op2,"oeste")==0){
                printf("Recebi um pedido para mover o jogador para o este...\n");
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
