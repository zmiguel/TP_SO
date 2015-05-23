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

    COMMS comms;

    /* VERIFICAR SE EXISTE "CP" NO SERVIDOR(access) */
    if(access("CPservidor", F_OK)!=0){
        printf("[ERRO] O servidor nao esta em execucao!\n");
        exit(1);
    };
    /* CRIAR "CP" DO CLIENTE - MINHA (mkfifo) */
    sprintf(comms.endereco, "CPcliente %d\n", getpid());
    mkfifo(comms.endereco, 0600); //0600 READ && WRITE
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
        else if(strcmp(palavra[0],"off")==0){
            /*PEDIDO DE SHUTDOWN DO SERVIDOR*/

            comms.comando = "off";

            /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
            i = write(fd_servidor, &comms, sizeof(comms));
            /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
            fd_cliente = open(comms.endereco, O_RDONLY);
            /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
            i = read(fd_cliente, &comms, sizeof(comms));
            /* FECHAR "CP" DO CLIENTE - MINHA (close) */
            close(fd_cliente);

            /*DESLIGAR O CLIENTE*/
            strcpy(str, "fim\n");

            printf("Terminei o servidor. Vou embora....\n");
        }
        /*ENVIO DE INSTRUCOES DE MOVIMENTO*/
        else if(strcmp(palavra[0],"teste")==0){
            *comms.comando = *palavra[0];
            *comms.opt = *palavra[1];

            /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
            write(fd_servidor, &comms, sizeof(comms));
            /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
            fd_cliente = open(comms.endereco, O_RDONLY);
            /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
            read(fd_cliente, &comms, sizeof(comms));
            /* FECHAR "CP" DO CLIENTE - MINHA (close) */
            close(fd_cliente);
            printf("Resposta: %s", comms.resp);
        }
        }
    }while(strcmp(str,"fim")!=0);

    /* FECHAR "CP" DO SERVIDOR (close) */
    close(fd_servidor);
    /* REMOVER "cp" DO CLIENTE - EU (UNLINK) */
    unlink(comms.endereco);

    exit(0);
}
