#define TAM 10
typedef struct entidade_utilizador{
    char nome[TAM], endereco[20];
    int pass;
}EU;

typedef struct mensagem{
	char op1[TAM], op2[TAM];
	char resposta[150];
    char endereco[20];
    int desliga;
}MENSAGEM;

typedef struct jogador1{
    int vida;
    char direccao;
}jog_1;

jog_1 jogador1 = {20};
//p_princ jogador2 = {20};

typedef struct {
    char entrada[100]; //texto
    char monst[100]; //texto
    int x, y; //coordenadas da sala
    int prob_monst; //% de probabilidade de aparecer um monstro
    int type; // 0 = normal, 1 = p1 start, 2 = p2 start, 3 = meeting room, 4 = loot room, 5 = boss room.
    int pass_n; // 0 = nao, 1 = sim
    int pass_s; // 0 = nao, 1 = sim
    int pass_e; // 0 = nao, 1 = sim
    int pass_o; // 0 = nao, 1 = sim
}LAB;

LAB lab[5][5];


//-------------ESTRUTURA-DE-OBJECTOS---------
typedef struct objectos{
    char nome[20];
    int peso;
    int raridade;
    int vida;
    int forca_ataque;
    int forca_defesa;
    int max_usos;
}objecto;
//----------ESTRUTURA-DE-MONSTROS------------
typedef struct monstros{
    char nome[20];
    int ataque;
    int defesa;
    int vida;
    int agress_pass;  //0 - Passivo, 1 - Agressivo
}monst;

