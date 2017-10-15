#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#define TAM 10

//  Gerar a matriz
void gerar_matriz(char matriz[][TAM]) {
    int i,j;
    for(i = 0;i < TAM; i++ ) {
       for(j = 0;j < TAM; j++ ) {
            matriz[i][j] = ' ';
       }
    }
}

//  Converter caractere em inteiro
int conv_char_int(char indice) {
    switch (indice)
    {
        case 'A' :
        case 'a' :
            return 0;
        break;
        case 'B' :
        case 'b' :
            return 1;
        break;
        case 'C' :
        case 'c' :
            return 2;
        break;
        case 'D' :
        case 'd' :
            return 3;
        break;
        case 'E' :
        case 'e' :
            return 4;
        break;
        case 'F' :
        case 'f' :
            return 5;
        break;
        case 'G' :
        case 'g' :
            return 6;
        break;
        case 'H' :
        case 'h' :
            return 7;
        break;
        case 'I' :
        case 'i' :
            return 8;
        break;
        case 'J' :
        case 'j' :
            return 9;
        break;
    }
}

//  Exibe a matriz
void exibir(char matriz[][TAM]) {
    int i, j, x;
    int vetor_int[TAM];
    char vetor_char[TAM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    x = TAM;

    for(i = 0; i < TAM; i++) {
        vetor_int[i] = x ;
        x--;
    }
    printf(" --------------------------------------------\n");
    for(i = 0;i < TAM; i++ ) {
        if(i == 0) {
            printf("| %d", vetor_int[i]);
        } else {
            printf("| 0%d", vetor_int[i]);
        }

        for(j = 0;j < TAM; j++ ) {
            printf(" | %c", matriz[i][j]);
        }

        printf(" |\n --------------------------------------------\n");
    }

    for(i = 0; i < TAM ; i++) {
        if(i == 0) {
            printf("|    |");
        }
        printf(" %c |", vetor_char[i]);

    }
    printf("\n --------------------------------------------");
}

void sementeRand() {
    srand((unsigned)time(NULL));
}

//  Sorteia o balin
int sorteio(){
    int x, y;
    x = rand() % 10;

    return x;
}

//  Limpa a tela
void limpa_tela() {
    system("cls");
}

// CALCULA COLUNA DA JOGADA
int colunaErro(int coluna) {
    int x, y;

    if (coluna == 9) {
        y = (rand() % 2) - 1;
    } else if (coluna == 0) {
        y = rand() % 2;
    } else {
        y = (rand() % 3) - 1;
    }

    x = coluna + y;
    return x;
}

// CALCULA LINHA DA JOGADA
int linhaErro(int linha) {
    int x, y;

    if (linha == 10) {
        y = (rand() % 3) - 2;
    } else if (linha == 9) {
        y = (rand() % 4) - 2;
    } else if (linha == 1) {
        y = (rand() % 3);
    } else if (linha == 2) {
        y = (rand() % 4) - 1;
    } else {
        y = (rand() % 5) - 2;
    }

    x = linha + y;
    return x;
}

//  STRUCT QUE ARMAZENA OS DADOS DE CADA JOGADOR
typedef struct {
    char nome[51];
    int jogadas, pontos;
} jogador;

//  verifica qual jogador está fazendo a jogada
int verifica_jogador(int jogada, int n_jogadores){
    int j;
    if (n_jogadores == 2) {
        if ((jogada%2) == 0) {
            j = 0;
        } else {
            j = 1;
        }
    } else {
        switch(jogada){
            case 0:
            case 4:
                j = 0;
                break;
            case 1:
            case 5:
                j = 1;
                break;
            case 2:
            case 6:
                j = 2;
                break;
            case 3:
            case 7:
                j = 3;
                break;
        }
    }

    return j;
}

// Pede para que o jogador faça uma jogada
void solicita_jogada(char matriz[][TAM], int jogada, int n_jogadores, jogador jogadores[4]){
    char coluna, letra, a;
    int linha, j, linha_desviada, l, coluna_convertida, c;

    j = verifica_jogador(jogada, n_jogadores);

    printf("\n\n");
    printf("%s em qual linha pretende jogar a bocha?  ", jogadores[j].nome);
    scanf("%d", &linha);
    printf("%s em qual coluna pretende jogar a bocha?  ", jogadores[j].nome);
    scanf(" %c", &coluna);

//  desvia a bocha da linha conforme a regra (-2, -1, 0, 1 e 2)
    linha_desviada = linhaErro(linha);
    l = 10 - linha_desviada;

//  desvia a bocha da coluna conforme a regra (-1, 0 e 1)
    coluna_convertida = conv_char_int(coluna);
    c = colunaErro(coluna_convertida);

    a = 'a';
//  adiciona a letra corespondente ao jogador na matriz
    letra = a + j;

    matriz[l][c] = letra;
}

int main() {
    char matriz[TAM][TAM], coluna;
    int n_jogadores, inicia_jogo, i, j, k, linha;
    jogador jogadores[4];

    setlocale(LC_ALL, "");
    sementeRand();

//  Início do jogo
    gerar_matriz(matriz);
    printf("\n          BEM VINDO AO BOCHA SIMULATOR\n\n");
    exibir(matriz);
    printf("\n\n");

//  Pede o número de jogadores
    do {
        printf("Informe o número de jogadores [Escolha 2 ou 4] :  ");
        scanf("%d", &n_jogadores);
        printf("\n");

        if(n_jogadores == 2 || n_jogadores == 4) {
            inicia_jogo = 1;
        }
    } while(inicia_jogo != 1);

//  Informar nome do jogador
    for (i = 0; i < n_jogadores; i++) {
        printf("Informe o nome do jogador %d : ", i+1);
        scanf("%s", jogadores[i].nome);
        jogadores[i].pontos = 0;
        jogadores[i].jogadas = 0;
        printf("\n");
    }

//  Joga-se o bolim
    matriz[sorteio()][sorteio()] = 'X';
    limpa_tela();
    printf("\n\n--------->>> BOLIM JOGADO COM SUCESSO\n\n");
    exibir(matriz);

//  Solicita que sejam feitas as jogadas
    for(i = 0; i < 8; i++) {
        solicita_jogada(matriz, i, n_jogadores, jogadores);
        j = verifica_jogador(i, n_jogadores);
        // aumenta em um o numero de jogadas
        jogadores[j].jogadas += 1;

        limpa_tela();
        exibir(matriz);
        printf("\n");

        // exibe o numero de jogadas de cada jogador
        for(k = 0; k < n_jogadores; k++){
            printf("\nO jogador %s já fez %d jogadas", jogadores[k].nome, jogadores[k].jogadas);
        }
    }

    return 0;
}
