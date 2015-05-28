#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define TAM 10

#include "util.h"

int fd_servidor, fd_cliente;

int main(void){
    char str[80], *palavra[TAM];
    int i;

    MENSAGEM msg;
    JOG play1;

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

    printf("-----BEM-VINDO-----\n");
    /*
    do{
        printf("\nINTRODUZA O SEU USERNAME:");
        scanf(" %[^\n]", play1.nome);
        fflush(stdin);
        printf("INTRODUZA A SUA PASSWORD:");
        scanf("%d", &jog1.passwd);
        printf("%s\n",jog1.nome);
        printf("%d",jog1.passwd);
        printf("%d",jog1.permissao);
        // ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write)
        write(fd_servidor, &jog1, sizeof(jog1));
        // ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY)
        fd_cliente = open(msg.endereco, O_RDONLY);
        // RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read)
        read(fd_cliente, &jog1, sizeof(jog1));
        printf("\n%s\n",jog1.nome);
        printf("\n%d",jog1.passwd);
        // FECHAR "CP" DO CLIENTE - MINHA (close)
        close(fd_cliente);
        printf("\n%d", jog1.permissao);
    */
        do{
            printf("> ");
            fgets(str, 80, stdin);
            str[strlen(str)-1]='\0';
            i = 0;
            palavra[i]=strtok(str, " ");
            while(palavra[i]!=NULL){
                i++;
                palavra[i] = strtok(NULL," ");
            }
                if(palavra[0]!=NULL){
                    if(strcmp(palavra[0], "desistir")==0){
                        strcpy(str,"jogar");
                        printf("O jogador 1 não pode desistir!\n");
                    }
                    else if(strcmp(palavra[0],"desligar")==0){
                        strcpy(msg.op1, "Desligar");
                        /*PEDIDO DE SHUTDOWN DO SERVIDOR*/
                        msg.desliga = 1;
                        /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
                        i = write(fd_servidor, &msg, sizeof(msg));
                        /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
                        fd_cliente = open(msg.endereco, O_RDONLY);
                        /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
                        i = read(fd_cliente, &msg, sizeof(msg));
                        /* FECHAR "CP" DO CLIENTE - MINHA (close) */
                        close(fd_cliente);

                        /*DESLIGAR O CLIENTE*/
                        strcpy(str, "desistir");

                        printf("SERVIDOR DESLIGADO\n");
                    }
                    /*ENVIO DE INSTRUCOES DE MOVIMENTO*/
                    else if(strcmp(palavra[0],"mov")==0){
                        strcpy(msg.op1, palavra[0]);
                        strcpy(msg.op2, palavra[1]);
                        /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
                        write(fd_servidor, &msg, sizeof(msg));
                        /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
                        fd_cliente = open(msg.endereco, O_RDONLY);
                        /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
                        read(fd_cliente, &msg, sizeof(msg));
                        read(fd_cliente, &jog1, sizeof(jog1));//ver recebimento.
                        /* FECHAR "CP" DO CLIENTE - MINHA (close) */
                        close(fd_cliente);
                        printf("Estou na posição x = [%d], y = [%d]\n", jog1.posx, jog1.posy);
                    }
                    else if(strcmp(palavra[0],"atac")==0){
                        strcpy(msg.op1, palavra[0]);
                        strcpy(msg.op2, palavra[1]);
                        /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
                        write(fd_servidor, &msg, sizeof(msg));
                        /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
                        fd_cliente = open(msg.endereco, O_RDONLY);
                        /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
                        read(fd_cliente, &msg, sizeof(msg));//ver recebimento.
                        /* FECHAR "CP" DO CLIENTE - MINHA (close) */
                        close(fd_cliente);
                        //FAZER RECEBIMENTO - PERGUNTAR AO ZÉ A IMPLEMENTACAO
                        //printf("Resultado = %.2f\n", msg.res);//ver recebimento
                    }
                    else if(strcmp(palavra[0],"ver")==0){
                        /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
                        write(fd_servidor, &msg, sizeof(msg));
                        /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
                        fd_cliente = open(msg.endereco, O_RDONLY);
                        /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
                        read(fd_cliente, &msg, sizeof(msg));//ver recebimento.
                        /* FECHAR "CP" DO CLIENTE - MINHA (close) */
                        close(fd_cliente);
                        //FAZER RECEBIMENTO - PERGUNTAR AO ZÉ A IMPLEMENTACAO
                        //printf("Resultado = %.2f\n", msg.res);//ver recebimento
                    }else if(strcmp(palavra[0],"verificaritems")==0){

                        strcpy(msg.op1, palavra[0]);

                        /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
                        write(fd_servidor, &msg, sizeof(msg));
                        /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
                        fd_cliente = open(msg.endereco, O_RDONLY);
                        /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
                        read(fd_cliente, &msg, sizeof(msg));//ver recebimento.
                        /* FECHAR "CP" DO CLIENTE - MINHA (close) */
                        close(fd_cliente);
                        //FAZER RECEBIMENTO - PERGUNTAR AO ZÉ A IMPLEMENTACAO
                        //printf("Resultado = %.2f\n", msg.res);//ver recebimento
                    }else if(strcmp(palavra[0],"geraritems")==0){

                        strcpy(msg.op1, palavra[0]);

                        /* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
                        write(fd_servidor, &msg, sizeof(msg));
                        /* ABRIR "CP" DO CLIENTE - MINHA (open - O_RDONLY) */
                        fd_cliente = open(msg.endereco, O_RDONLY);
                        /* RECEBER RESPOSTA NA "CP" DO CLIENTE - MINHA (read) */
                        read(fd_cliente, &msg, sizeof(msg));//ver recebimento.
                        /* FECHAR "CP" DO CLIENTE - MINHA (close) */
                        close(fd_cliente);
                        //FAZER RECEBIMENTO - PERGUNTAR AO ZÉ A IMPLEMENTACAO
                        printf("%s", msg.frase);//ver recebimento
                    }
                    else
                        printf("Comando invalido, tenta novamente!\n");
                }
        }while(strcmp(str,"desistir")!=0);
    //}while(play1.permissao != 1);
    /* FECHAR "CP" DO SERVIDOR (close) */
    close(fd_servidor);
    /* REMOVER "cp" DO CLIENTE - EU (UNLINK) */
    unlink(msg.endereco);

    exit(0);
}
