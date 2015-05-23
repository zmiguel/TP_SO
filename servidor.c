#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "util.h"

int fd_servidor, fd_cliente;

int main(void){
    int n;

    DATA data;

    //matrix do labirinto

    /* VERIFICAR SE EXISTE "CP" DO SERVIDOR (access) -- APENAS UM!!!*/
    if(access("CPservidor", F_OK)==0){
        printf("[ERRO] Ja existe um servidor!\n");
        exit(1);
    }
    /* CRIAR "CP" DO SERVIDOR - MINHA (mkfifo) */
    mkfifo("CPservidor", 0600);
    /* ABRIR "CP" DO SERVIDOR - MINHA (open - O_RDONLY) */
    fd_servidor = open("CPservidor", O_RDWR);

    printf("[SERVIDRO] Ja entrou o primeiro cliente!\n");

    do{
            /* RECEBER PEDIDO NA "CP" DO SERVIDOR - MINHA (n = read();) */
        n = read(fd_servidor, &data, sizeof(data));

        if(n != 3){
            printf("[SERVIDOR] Nao ha jogadores suficientes!\n");
            sleep(1);
            continue;
        }

    //printf com o pedido do cliente
    printf();

    //main switch

    switch(data.op1){
    case "mover":
        if(strcmp(data.op2, "frente")==0){

        }else if(strcmp(data.op2, "tras")==0){

        }else if(strcmp(data.op2, "direita")==0){

        }else if(strcmp(data.op2, "esquerda")==0){

        }else{
            strcpy(data.resposta, "ERRO! A direcao intruduzida nao e valida!\n");
        }
        break;
    }


            /* ABRIR "CP" DO CLIENTE (open - O_WRONLY) */
            fd_cliente = open(data.endereco, O_WRONLY);
            /* ENVIAR RESPOSTA PARA A "CP" DO CLIENTE (write) */
            write(fd_cliente, &data, sizeof(data));
            /* FECHAR "CP" DO CLIENTE (close) */
            close(fd_cliente);

    }while(PRECISAMOS DE ALGUMA COISA AQUI);

    /* FECHAR "CP" DO SERVIDOR - MINHA (close) */
    close(fd_servidor);
    /* REMOVER "CP" DO SERVIDOR- MINHA (UNLINK) */
    unlink("CPservidor");
    exit(0);
}
