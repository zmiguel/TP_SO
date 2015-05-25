#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX 5
#include "util.h"

//---------FUNCAO-RANDOM---------------------
int obtem_rand(int min, int max){
    int random;
    random = min + rand() % (max - min + 1);
    return random;
}
//----------DECLARAÇÃO-DE-MONSTROS-----------
monst morcego = {.nome = "Morcego", 3, 3, 4, 1};
monst escorpiao = {"Escorpião", 7, 5, 3};
monst lobisomem = {"Lobisomem", 8, 6, 6};
monst urso = {"Urso", 10, 10, 8};
monst boss = {"Boss", 12, 15, 15};
//------------DECLARACAO-DE-OBJECTOS---------
objecto sandes = {"Sandes", 0.5, 10, 0 , 0, 1};
objecto aspirina = {"Aspirina", 0.1, 20, 0, 0, 1};
objecto xarope = {"Xarope", 1, 4, 0, 0, 1};
objecto faca = {"Faca", 2, 5, 5, 0, 0};
objecto espada = {"Espada", 8, 3, 8, 2, 0};
objecto granado = {"Granada", 1, 2, 30, 0, 1};
objecto escudo = {"Escudo", 4, 4, 5, 0, 0};
objecto moeda = {"Moeda", 0.1, 5, 0, 0};
//---------VALIDA-ENTRADA-DO-JOGADOR----------
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
        else return 0;
    }while(fgets(linha, TAM, f) != NULL);

    fclose(f);
}

/*
void mov_jogador(char labirinto[L][C], char *movimento){

    if(strcmp(movimento,"norte")==0){



        labirinto[L][C] = labirinto[L-1][C];



    }
    else if(strcmp(movimento,"este")==0){
        labirinto[L][C] = labirinto[L][C+1];
    }
    else if(strcmp(movimento,"sul")==0){
        labirinto[L][C] = labirinto[L+1][C];
    }
    else if(strcmp(movimento,"oeste")==0){
        labirinto[L][C] = labirinto[L][C-1];
    }
}
*/

int fd_servidor, fd_cliente;

int main(void){
    char movimento[20];
    int m, n, permissao = 0, x, y;

    MENSAGEM msg;
    EU ent;
    JOG play1;
    SALA lab;

    /* VERIFICAR SE EXISTE "CP" DO SERVIDOR (access) -- APENAS UM!!!*/
    if(access("CPservidor", F_OK)==0){
        printf("[ERRO] Ja existe um servidor!\n");
        exit(1);
    }
    /* CRIAR "CP" DO SERVIDOR - MINHA (mkfifo) */
    mkfifo("CPservidor", 0600);
    /* ABRIR "CP" DO SERVIDOR - MINHA (open - O_RDONLY) */
    fd_servidor = open("CPservidor", O_RDWR);

    printf("[SERVIDOR] SERVIDOR INICIADO!\n");

    /*
    do{
        // RECEBER PEDIDO NA "CP" DO SERVIDOR - MINHA (n = read();)
        n = read(fd_servidor, &ent, sizeof(ent));
        printf("%d", n);
        if(n == 0){
            printf("[SERVIDOR] NÃO É POSSÍVEL!\n");
            sleep(1);
            continue;
        }
        printf("Recebi um pedido: %s, %d, %d", ent.nome, ent.pass, ent.perm);
        //permissao = valida_jogador();
        printf("Vou enviar a resposta: %s, %d, %d", ent.nome, ent.pass, ent.perm);
        // ABRIR "CP" DO CLIENTE (open - O_WRONLY)
        fd_cliente = open(msg.endereco, O_WRONLY);
        // ENVIAR RESPOSTA PARA A "CP" DO CLIENTE (write)
        write(fd_cliente, &ent, sizeof(ent));
        // FECHAR "CP" DO CLIENTE (close)
        close(fd_cliente);
    */
        do{
            /* RECEBER PEDIDO NA "CP" DO SERVIDOR - MINHA (n = read();) */
            n = read(fd_servidor, &msg, sizeof(msg));

            if(n == 0){
                printf("[SERVIDOR] Fiquei sem jogadores!\n");
                sleep(1);
                continue;
            }
            else if(strcmp(msg.op1,"mov")==0){
                if(strcmp(msg.op2,"norte")==0){
                    printf("Recebi um pedido para mover o jogador para norte...\n");
                    if(labirinto[jog1.novo].posy == 0){
                    printf("O jogador está em y = [%d] x = [%d]\n", labirinto[jog1.novo].posy, labirinto[jog1.novo].posx);
                    printf("Não posso mover o jogador para norte!\n");
                    }
                    else{
                    if(strcmp(labirinto[jog1.novo].portas, ".P..")==0){
                            printf("Recebi um pedido para mover o jogador para o sul...\n");
                            printf("Vou mover o jogador para sul!\n");
                            strcpy(msg.frase,"Entraste numa sala escura e fria, a porta fechou-se atras de ti!\n");
                            jog1.novo -= 5;
                            printf("%s", labirinto[jog1.novo].portas);
                            printf("Jogador 1 - y = [%d] x = [%d]\n", labirinto[jog1.novo].posy, labirinto[jog1.novo].posx);
                            jog1.posx = labirinto[jog1.novo].posx;
                            jog1.posy = labirinto[jog1.novo].posy;
                    }
                    }
                }
                else if(strcmp(msg.op2,"sul")==0){
                    if(labirinto[jog1.novo].posy == 4){
                        printf("O jogador está em y = [%d] x = [%d]\n", labirinto[jog1.novo].posy, labirinto[jog1.novo].posx);
                        printf("Não posso mover o jogador para sul!\n");
                    }
                    else{
                    if(strcmp(labirinto[jog1.novo].portas, ".P..")==0){
                            printf("Recebi um pedido para mover o jogador para o sul...\n");
                            printf("Vou mover o jogador para sul!\n");
                            strcpy(msg.frase,"Entraste numa sala escura e fria, a porta fechou-se atras de ti!\n");
                            jog1.novo += 5;
                            printf("%s", labirinto[jog1.novo].portas);
                            printf("Jogador 1 - y = [%d] x = [%d]\n", labirinto[jog1.novo].posy, labirinto[jog1.novo].posx);
                            jog1.posx = labirinto[jog1.novo].posx;
                            jog1.posy = labirinto[jog1.novo].posy;
                    }
                    }
                }
                else if(strcmp(msg.op2,"este")==0){
                    printf("Recebi um pedido para mover o jogador para o este...\n");
                    if(labirinto[jog1.novo].posx == 4){
                    printf("O jogador está em y = [%d] x = [%d]\n", labirinto[jog1.novo].posy, labirinto[jog1.novo].posx);
                    printf("Não posso mover o jogador para este!\n");
                    }
                    else{
                    if(strcmp(labirinto[jog1.novo].portas, "..P.")==0){
                            printf("Recebi um pedido para mover o jogador para o este...\n");
                            printf("Vou mover o jogador para este!\n");
                            strcpy(msg.frase,"Entraste numa sala escura e fria, a porta fechou-se atras de ti!\n");
                            jog1.novo += 1;
                            printf("Jogador 1 - y = [%d] x = [%d]\n", labirinto[jog1.novo].posy, labirinto[jog1.novo].posx);
                            jog1.posx = labirinto[jog1.novo].posx;
                            jog1.posy = labirinto[jog1.novo].posy;
                    }
                    }
                }
                else if(strcmp(msg.op2,"oeste")==0){
                    printf("Recebi um pedido para mover o jogador para o oeste...\n");
                    if(labirinto[jog1.novo].posx == 0){
                    printf("O jogador está em y = [%d] x = [%d]\n", labirinto[jog1.novo].posy, labirinto[jog1.novo].posx);
                    printf("Não posso mover o jogador para oeste!\n");
                    }
                    else{
                    if(strcmp(labirinto[jog1.novo].portas, "...P")==0){
                            printf("Recebi um pedido para mover o jogador para o oeste...\n");
                            printf("Vou mover o jogador para sul!\n");
                            strcpy(msg.frase,"Entraste numa sala escura e fria, a porta fechou-se atras de ti!\n");
                            jog1.novo -= 1;
                            printf("Jogador 1 - y = [%d] x = [%d]\n", labirinto[jog1.novo].posy, labirinto[jog1.novo].posx);
                            jog1.posx = labirinto[jog1.novo].posx;
                            jog1.posy = labirinto[jog1.novo].posy;
                    }
                    }
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
            write(fd_cliente, &play1, sizeof(play1));
            /* FECHAR "CP" DO CLIENTE (close) */
            close(fd_cliente);
        }while(msg.desliga != 1);
    //}while(close(fd_cliente)!=0);
    printf("[SERVIDOR] SERVIDOR DESLIGADO\n");

    /* FECHAR "CP" DO SERVIDOR - MINHA (close) */
    close(fd_servidor);
    /* REMOVER "CP" DO SERVIDOR- MINHA (UNLINK) */
    unlink("CPservidor");
    exit(0);
}
