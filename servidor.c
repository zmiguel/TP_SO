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

    COMMS comms;

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
        n = read(fd_servidor, &comms, sizeof(comms));

        if(n == 0){
            printf("[SERVIDOR] Fiquei sem clientes!\n");
            sleep(1);
            continue;
        }

// CALCULO
        printf("Recebi um pedido... comando:%s - opt:%s - resp:%s - respopt:%s - extra:%s (%d bytes)\n", comms.comando, comms.opt, comms.resp, comms.respopt, comms.extra, n);


            /* ABRIR "CP" DO CLIENTE (open - O_WRONLY) */
            fd_cliente = open(comms.endereco, O_WRONLY);
            /* ENVIAR RESPOSTA PARA A "CP" DO CLIENTE (write) */
            write(fd_cliente, &comms, sizeof(comms));
            /* FECHAR "CP" DO CLIENTE (close) */
            close(fd_cliente);

    }while(strcmp(comms.comando, "off")!=0);

    /* FECHAR "CP" DO SERVIDOR - MINHA (close) */
    close(fd_servidor);
    /* REMOVER "CP" DO SERVIDOR- MINHA (UNLINK) */
    unlink("CPservidor");
    exit(0);
}
