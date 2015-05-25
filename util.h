#define TAM 10
typedef struct entidade_utilizador{
    char nome[TAM];
    int pass;
    int perm;
}EU;
typedef struct mensagem{
	char op1[TAM], op2[TAM];
	char frase[100];
    char endereco[20];
    int desliga;
}MENSAGEM;
//----------ESTRUTURA-DE-JOGADOR-------------
typedef struct jogador{
    int vida;
    int posx;
    int posy;
    int novo;
}JOG;
//----------DECLARAÇÃO-DE-JOGADORES----------
JOG jog1 = {20, 0, 0, 0};
//JOG jog2 = {20, 4, 0};
//-------------------SALAS-------------------
typedef struct sala{
    int tipo_monst;
    char portas[5];
    int posy;
    int posx;
}SALA;
//----------DECLARAÇÃO-DE-SALAS--------------
SALA labirinto[25] = {
    {0, ".PP.\0", 0, 0},
    {0, ".PP.\0", 0, 1},
    {0, ".PP.\0", 0, 2},
    {0, ".P..\0", 0, 3},
    {0, "....\0", 0, 4},//5
    {0, ".PP.\0", 1, 0},
    {0, ".PP.\0", 1, 1},
    {0, ".PP.\0", 1, 2},
    {0, ".P..\0", 1, 3},
    {0, "P..P\0", 1, 4},//10
    {0, "..P.\0", 2, 0},
    {0, ".P..\0", 2, 1},
    {0, ".P.P\0", 2, 2},
    {0, "..PP\0", 2, 3},
    {0, "PP..\0", 2, 4},//15
    {0, "..P.\0", 3, 0},
    {0, "..P.\0", 3, 1},
    {0, "..P.\0", 3, 2},
    {0, "P..P\0", 3, 3},
    {0, "...P\0", 3, 4},
    {0, "P.P.\0", 4, 0},//20
    {0, "P.P.\0", 4, 1},
    {0, "P.P.\0", 4, 2},
    {0, "..P.\0", 4, 3},
    {0, "..P.\0", 4, 4},
};
//-------------ESTRUTURA-DE-OBJECTOS---------
typedef struct objectos{
    char nome[20];
    int peso;
    int raridade;
    int forca_ataque;
    int forca_defesa;
    int max_usos;
}objecto;
//----------ESTRUTURA-DE-MONSTROS------------
typedef struct monstros{
    //int id_monst;
    char nome[20];
    int ataque;
    int defesa;
    int vida;
    int agress_pass;  //0 - Passivo, 1 - Agressivo
}monst;
