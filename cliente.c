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
    char str[80],*palavra[8];
    int i;

    MSG msg;

    /* VERIFICAR SE EXISTE "CP" NO SERVIDOR(access) */
    if(access("CPservidor", F_OK)!=0){
        printf("[ERRO] O servidor nao esta em execucao!\n");
        exit(1);
    };
    /* CRIAR "CP" DO CLIENTE - MINHA (mkfifo) */
    sprintf(msg.endereco, "CPcliente %d\n", getpid());
    mkfifo(msg.endereco, 0600); //0600 READ && WRITE
    /* ABRIR "CP" DO SERVIDOR (open - O_WRONLY) */
    fd_servidor = open("CPservidor", O_WRONLY);

    do{
        printf("> ");
        fgets(str, 80, stdin);
        str[strlen(str)-1]='\0';
        i=0;
        palavra[i]=strtok(str, " ");
        while(palavra[i]!=NULL){
            i++;
            palavra[i] = strtok(NULL," ");
        }

        if(palavra[0]!=NULL){
            if(strcmp(palavra[0], "")==0){
                printf("FIM... \n");
            }
        else if(strcmp(palavra[0],"desliga")==0){
            /*PEDIDO DE SHUTDOWN DO SERVIDOR*/

            /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
            i = write(fd_servidor, &msg, sizeof(msg));
            /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
            fd_cliente = open(msg.endereco, O_RDONLY);
            /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
            i = read(fd_cliente, &msg, sizeof(msg));
            /* FECHAR "CP" DO CLIENTE - MINHA (close) */
            close(fd_cliente);

            /*DESLIGAR O CLIENTE*/
            strcpy(str, "fim");

            printf("Terminei o servidor. Vou embora....\n");
        }
        else if(strcmp(palavra[0],"calcula")==0){
            msg.num1 = atoi(palavra[1]);
            msg.num2 = atoi(palavra[3]);
            msg.op = *palavra[2];

            /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
            write(fd_servidor, &msg, sizeof(msg));
            /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
            fd_cliente = open(msg.endereco, O_RDONLY);
            /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
            read(fd_cliente, &msg, sizeof(msg));
            /* FECHAR "CP" DO CLIENTE - MINHA (close) */
            close(fd_cliente);
            printf("Resultado = %.2f\n", msg.res);
        }
        }
    }while(strcmp(str,"fim")!=0);

    /* FECHAR "CP" DO SERVIDOR (close) */
    close(fd_servidor);
    /* REMOVER "cp" DO CLIENTE - EU (UNLINK) */
    unlink(msg.endereco);

    exit(0);
}
