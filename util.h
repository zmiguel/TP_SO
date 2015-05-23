typedef struct jogador{
    int vida;
}j_princ;

j_princ jogador1 = {20};
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
//------------DECLARACAO-DE-OBJECTOS---------
objecto sandes = {"Sandes", 0.5, 10, 0 , 0, 1};
objecto aspirina = {"Aspirina", 0.1, 20, 0, 0, 1};
objecto xarope = {"Xarope", 1, 4, 0, 0, 1};
objecto faca = {"Faca", 2, 5, 5, 0, 0};
objecto espada = {"Espada", 8, 3, 8, 2, 0};
objecto granado = {"Granada", 1, 2, 30, 0, 1};
objecto escudo = {"Escudo", 4, 4, 5, 0, 0};
objecto moeda = {"Moeda", 0.1, 5, 0, 0};

//----------ESTRUTURA-DE-MONSTROS------------
typedef struct monstros{
    char nome[20];
    int vida;
    int defesa;
    int ataque;
}monst;
//----------DECLARAÇÃO-DE-MONSTROS-----------
monst morcego = {"Morcego", 4, 3, 1};
monst escorpiao = {"Escorpião", 7, 5, 3};
monst lobisomem = {"Lobisomem", 8, 6, 6};
monst urso = {"Urso", 10, 10, 8};
monst boss = {"Boss", 15, 15, 12};
//----------SALAS----------------------------
typedef struct sala{
    char descricao[100];
    char descricao_monst[100];
    int nivel;
    int prob_monstro;
}sala;

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
