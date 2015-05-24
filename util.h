#define TAM 10
typedef struct entidade_utilizador{
    char nome[TAM], endereco[20];
    int pass;
}EU;

typedef struct mensagem{
	char op1[TAM], op2[TAM];
    char endereco[20];
    int desliga;
}MENSAGEM;

typedef struct jogador1{
    int vida;
}jog_1;

jog_1 jogador1 = {20};
//p_princ jogador2 = {20};
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
    char nome[20];
    int ataque;
    int defesa;
    int vida;
    int agress_pass;  //0 - Passivo, 1 - Agressivo
}monst;

//-------------------SALAS---------------------------- ISTRO TEM QUE SER REVISTI - AS SALAS
typedef struct sala{
    char descricao[100];
    char descricao_monst[100];
    int nivel;
    int prob_monstro;
}sala;
//----------------------------------------------------------------------
typedef struct{
	char op;
	int num1,num2;
	float res;
	char endereco[20];
}MSG;

typedef struct{
    char comando[15];
    char opt[25];
    char resp[250];
    char respopt[25];
    char extra[50];
    char endereco[20];
}COMMS;

typedef struct mensagem{
	char op1, op2;
    char endereco[20];
}DATA;
