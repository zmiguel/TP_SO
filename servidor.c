#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#define MAX 5
#include "util.h"

//-----------------FUNCAO-RANDOM--------------------
int obtem_rand(int min, int max){
    int random;
    random = min + (rand() % (max - min + 1));
    return random;
}
/*
//----------VER-PESO-ACTUAL-NA-MALA----------
int peso_mala(int jogador){
    int i, peso=0;

    if(jogador == 1){
        for(i=0;i<8;i++){
            peso += j1bag[i].peso;
        }
    }else if(jogador == 2){
        for(i=0;i<8;i++){
            peso += j2bag[i].peso;
        }
    }else{
        return 1000;
    }
    return peso;
}
*/
//----------GERAR-ITEMS-NAS-SALAS------------
void gerar_items(void){
    int i;

    for(i=0;i<25;i++){
        labirinto[i].item1 = obtem_rand(0,3);
        labirinto[i].item2 = obtem_rand(0,3);
        labirinto[i].item3 = obtem_rand(0,3);
    }
    printf("Items gerados!!!\n");
}
//---------VERIFICA-POSSIBILIDADE-DE-MOVIMENTOS------
int verifica_sul(){
    if(strcmp(labirinto[jog1.novo].portas,".P..")==0
    ||strcmp(labirinto[jog1.novo].portas,".P.P")==0
    ||strcmp(labirinto[jog1.novo].portas,".PP.")==0
    ||strcmp(labirinto[jog1.novo].portas,".PPP")==0
    ||strcmp(labirinto[jog1.novo].portas,"PP..")==0
    ||strcmp(labirinto[jog1.novo].portas,"PP.P")==0
    ||strcmp(labirinto[jog1.novo].portas,"PPP.")==0
    ||strcmp(labirinto[jog1.novo].portas,"PPPP")==0
    ){
    return 1;
    }
}
int verifica_norte(){
    if(strcmp(labirinto[jog1.novo].portas,"P...")==0
    ||strcmp(labirinto[jog1.novo].portas,"P...P")==0
    ||strcmp(labirinto[jog1.novo].portas,"P.P.")==0
    ||strcmp(labirinto[jog1.novo].portas,"P.PP")==0
    ||strcmp(labirinto[jog1.novo].portas,"PP..")==0
    ||strcmp(labirinto[jog1.novo].portas,"PP.P")==0
    ||strcmp(labirinto[jog1.novo].portas,"PPP.")==0
    ||strcmp(labirinto[jog1.novo].portas,"PPPP")==0
    ){
    return 1;
    }
}
int verifica_este(){
    if(strcmp(labirinto[jog1.novo].portas,"..P.")==0
    ||strcmp(labirinto[jog1.novo].portas,"..PP")==0
    ||strcmp(labirinto[jog1.novo].portas,".PP.")==0
    ||strcmp(labirinto[jog1.novo].portas,".PPP")==0
    ||strcmp(labirinto[jog1.novo].portas,"P.P.")==0
    ||strcmp(labirinto[jog1.novo].portas,"P.PP")==0
    ||strcmp(labirinto[jog1.novo].portas,"PPP.")==0
    ||strcmp(labirinto[jog1.novo].portas,"PPPP")==0
    ){
    return 1;
    }
}
int verifica_oeste(){
    if(strcmp(labirinto[jog1.novo].portas,"...P")==0
    ||strcmp(labirinto[jog1.novo].portas,"..PP")==0
    ||strcmp(labirinto[jog1.novo].portas,".P.P")==0
    ||strcmp(labirinto[jog1.novo].portas,".PPP")==0
    ||strcmp(labirinto[jog1.novo].portas,"P..P")==0
    ||strcmp(labirinto[jog1.novo].portas,"P.PP")==0
    ||strcmp(labirinto[jog1.novo].portas,"PP.P")==0
    ||strcmp(labirinto[jog1.novo].portas,"PPPP")==0
    ){
    return 1;
    }
}
//----------DECLARAÇÃO-DE-MONSTROS---------
monst morcego = {1, "Morcego", 3, 3, 4, 1};
monst escorpiao = {2, "Escorpião", 7, 5, 3};
monst lobisomem = {3, "Lobisomem", 8, 6, 6};
monst urso = {4, "Urso", 10, 10, 8};
monst boss = {5, "Boss", 12, 15, 15};
//------------DECLARACAO-DE-OBJECTOS---------------
objecto sandes = {"Sandes", 0.5, 10, 0 , 0, 1};
objecto aspirina = {"Aspirina", 0.1, 20, 0, 0, 1};
objecto xarope = {"Xarope", 1, 4, 0, 0, 1};
objecto faca = {"Faca", 2, 5, 5, 0, 0};
objecto espada = {"Espada", 8, 3, 8, 2, 0};
objecto granado = {"Granada", 1, 2, 30, 0, 1};
objecto escudo = {"Escudo", 4, 4, 5, 0, 0};
objecto moeda = {"Moeda", 0.1, 5, 0, 0};
/*//mochila jogador 1
BAG sandes = {"Sandes", 0, 0};
j1bag aspirina = {"Aspirina", 0, 0};
j1bag xarope = {"Xarope", 0, 0};
j1bag faca = {"Faca", 0 ,0};
j1bag espada = {"Espada", 0 ,0};
j1bag granado = {"Granada", 0, 0};
j1bag escudo = {"Escudo", 0 , 0};
j1bag moeda = {"Moeda", 0 , 0};
//mochila jogador 2
j2bag sandes = {"Sandes", 0, 0};
j2bag aspirina = {"Aspirina", 0, 0};
j2bag xarope = {"Xarope", 0, 0};
j2bag faca = {"Faca", 0 ,0};
j2bag espada = {"Espada", 0 ,0};
j2bag granado = {"Granada", 0, 0};
j2bag escudo = {"Escudo", 0 , 0};
j2bag moeda = {"Moeda", 0 , 0};
*/
//-------------------VALIDA-ENTRADA-DO-JOGADOR----------------
int valida_jogador(){
    FILE *f;
    char *nome[TAM], linha[TAM];
    int pass;

    JOG play1;

    if((f = fopen("jogadores.txt", "rt")) == NULL){
        printf("ERRO na abertura do ficheiro de texto para leitura.\n");
    }

    do{
        fscanf(f, "%s:", nome[TAM]);
        if((strcmp(jog1.nome,nome[TAM]))==0){
            fscanf(f,"%d", &pass);
            if(pass == jog1.passwd)
                return 1;
        }
        else
            return 0;
    }while(fgets(linha, TAM, f) != NULL);

    fclose(f);
}

int fd_servidor, fd_cliente;

int main(void){
    char movimento[20];
    int m, n, permissao = 0, x, y;
    int i, j, k;

    MENSAGEM msg;
    JOG play1;
    SALA lab;

    srand(time(NULL));

    gerar_items();

    /* VERIFICAR SE EXISTE "CP" DO SERVIDOR (access) -- APENAS UM!!!*/
    if(access("CPservidor", F_OK)==0){
        printf("[SERVIDOR] Ja existe um servidor!\n");
        exit(1);
    }
    /* CRIAR "CP" DO SERVIDOR - MINHA (mkfifo) */
    mkfifo("CPservidor", 0600);
    /* ABRIR "CP" DO SERVIDOR - MINHA (open - O_RDONLY) */
    fd_servidor = open("CPservidor", O_RDWR);

    printf("[SERVIDOR] Servidor Iniciado!\n");
    /*
        // RECEBER PEDIDO NA "CP" DO SERVIDOR - MINHA (n = read();)
        m = read(fd_servidor, &msg, sizeof(msg));
        printf("m = %d\n", m);
        if(n == 0){
            printf("[SERVIDOR] NÃO É POSSÍVEL!\n");
        }
        printf("Recebi um pedido: NOME - %s, PASSWD - %d, PERMISS - %d", jog1.nome, jog1.passwd, jog1.permissao);
        //permissao = valida_jogador();
        printf("Vou enviar a resposta: NOME - %s, PASSWD - %d, PERMISS - %d", jog1.nome, jog1.passwd, jog1.permissao);
        // ABRIR "CP" DO CLIENTE (open - O_WRONLY)
        fd_cliente = open(msg.endereco, O_WRONLY);
        // ENVIAR RESPOSTA PARA A "CP" DO CLIENTE (write)
        write(fd_cliente, &play1, sizeof(play1));
        // FECHAR "CP" DO CLIENTE (close)
        close(fd_cliente);

    if(permissao = 1){
    */
        do{
            /* RECEBER PEDIDO NA "CP" DO SERVIDOR - MINHA (n = read();) */
            n = read(fd_servidor, &msg, sizeof(msg));

            if(n == 0){
                printf("[SERVIDOR] Fiquei sem jogadores!\n");
                sleep(1);
                continue;
            }
            //-------------------MOVIMENTOS-DE-JOGADOR----------------
            else if(strcmp(msg.op1,"mov")==0){
                //-------------MOVER-NORTE----------------------------
                if(strcmp(msg.op2,"norte")==0){
                    printf("[SERVIDOR] Recebi um pedido para mover o jogador para norte...\n");
                    if(labirinto[jog1.novo].posy == 0){
                    printf("[SERVIDOR] O jogador está em x = [%d] y = [%d]\n", labirinto[jog1.novo].posx, labirinto[jog1.novo].posy);
                    printf("[SERVIDOR] Não posso mover o jogador para norte!\n");
                    }
                    else{
                    if(verifica_norte()==1){
                            printf("[SERVIDOR] Recebi um pedido para mover o jogador para norte...\n");
                            printf("[SERVIDOR] Vou mover o jogador para norte!\n");
                            //strcpy(msg.frase,"Entraste numa sala escura e fria, a porta fechou-se atras de ti!\n");
                            jog1.novo -= 5;
                            printf("[SERVIDOR] O jogador está em x = [%d] y = [%d]\n", labirinto[jog1.novo].posx, labirinto[jog1.novo].posy);
                            jog1.posx = labirinto[jog1.novo].posx;
                            jog1.posy = labirinto[jog1.novo].posy;
                    }
                    }
                }
                else
                //-------------MOVER-SUL--------------------------
                if(strcmp(msg.op2,"sul")==0){
                    if(labirinto[jog1.novo].posy == 4){
                        printf("[SERVIDOR] O jogador está em x = [%d] y = [%d]\n", labirinto[jog1.novo].posx, labirinto[jog1.novo].posy);
                        printf("[SERVIDOR] Não posso mover o jogador para sul!\n");
                    }
                    else{
                    if(verifica_sul()==1){
                            printf("[SERVIDOR] Recebi um pedido para mover o jogador para sul...\n");
                            printf("[SERVIDOR] Vou mover o jogador para sul!\n");
                            //strcpy(msg.frase,"Entraste numa sala escura e fria, a porta fechou-se atras de ti!\n");
                            jog1.novo += 5;
                            printf("[SERVIDOR] O jogador está em x = [%d] y = [%d]\n", labirinto[jog1.novo].posx, labirinto[jog1.novo].posy);
                            jog1.posx = labirinto[jog1.novo].posx;
                            jog1.posy = labirinto[jog1.novo].posy;
                    }
                    }
                }
                else
                //-------------MOVER-ESTE--------------------------
                if(strcmp(msg.op2,"este")==0){
                    printf("[SERVIDOR] Recebi um pedido para mover o jogador para o este...\n");
                    if(labirinto[jog1.novo].posx == 4){
                    printf("[SERVIDOR] O jogador está em x = [%d] y = [%d]\n", labirinto[jog1.novo].posx, labirinto[jog1.novo].posy);
                    printf("[SERVIDOR] Não posso mover o jogador para este!\n");
                    }
                    else{
                    if(verifica_este()==1){
                            printf("[SERVIDOR] Recebi um pedido para mover o jogador para o este...\n");
                            printf("[SERVIDOR] Vou mover o jogador para este!\n");
                            //strcpy(msg.frase,"Entraste numa sala escura e fria, a porta fechou-se atras de ti!\n");
                            jog1.novo += 1;
                            printf("[SERVIDOR] O jogador está em x = [%d] y = [%d]\n", labirinto[jog1.novo].posx, labirinto[jog1.novo].posy);
                            jog1.posx = labirinto[jog1.novo].posx;
                            jog1.posy = labirinto[jog1.novo].posy;
                    }
                    }
                }
                else
                //-------------MOVER-OESTE--------------------------
                if(strcmp(msg.op2,"oeste")==0){
                    printf("[SERVIDOR] Recebi um pedido para mover o jogador para o oeste...\n");
                    if(labirinto[jog1.novo].posx == 0){
                    printf("[SERVIDOR] O jogador está em x = [%d] y = [%d]\n", labirinto[jog1.novo].posx, labirinto[jog1.novo].posy);
                    printf("[SERVIDOR] Não posso mover o jogador para oeste!\n");
                    }
                    else{
                    if(verifica_oeste()==1){
                            printf("[SERVIDOR] Recebi um pedido para mover o jogador para o oeste...\n");
                            printf("[SERVIDOR] Vou mover o jogador para sul!\n");
                            //strcpy(msg.frase,"Entraste numa sala escura e fria, a porta fechou-se atras de ti!\n");
                            jog1.novo -= 1;
                            printf("[SERVIDOR] O jogador está em x = [%d] y = [%d]\n", labirinto[jog1.novo].posx, labirinto[jog1.novo].posy);
                            jog1.posx = labirinto[jog1.novo].posx;
                            jog1.posy = labirinto[jog1.novo].posy;
                    }
                    }
                }
            }
            //------------ATAQUE-DE-JOGADOR---------------
            else if(strcmp(msg.op1,"atac")==0){
                //FUNCOES PARA BATALHAR MONSTROS
                printf("Falta implementar!\n");
            }
            else if(strcmp(msg.op1,"ver")==0){
            //FUNCOES PARA VISUALIZAR O QUE SE PASSA AO REDOR
            printf("Falta implementar!\n");
            }
            else if(strcmp(msg.op1,"verificaritems")==0){
            //FUNCOES PARA VISUALIZAR O QUE SE PASSA AO REDOR

            for(i=0;i<25;i++){
                printf("Sala %d:  \t", i+1);
                printf("%d\t%d\t%d\n", labirinto[i].item1, labirinto[i].item2, labirinto[i].item3);
            }

            }
            else if(strcmp(msg.op1,"geraritems")==0){
            //FUNCOES PARA VISUALIZAR O QUE SE PASSA AO REDOR

            gerar_items();
            strcpy(msg.frase, "Items novos gerados!\n");

            }
            /* ABRIR "CP" DO CLIENTE (open - O_WRONLY) */
            fd_cliente = open(msg.endereco, O_WRONLY);
            /* ENVIAR RESPOSTA PARA A "CP" DO CLIENTE (write) */
            write(fd_cliente, &msg, sizeof(msg));
            write(fd_cliente, &jog1, sizeof(jog1));
            /* FECHAR "CP" DO CLIENTE (close) */
            close(fd_cliente);
        }while(msg.desliga != 1);
    //}
    printf("[SERVIDOR] SERVIDOR DESLIGADO\n");

    /* FECHAR "CP" DO SERVIDOR - MINHA (close) */
    close(fd_servidor);
    /* REMOVER "CP" DO SERVIDOR- MINHA (UNLINK) */
    unlink("CPservidor");
    exit(0);
}
