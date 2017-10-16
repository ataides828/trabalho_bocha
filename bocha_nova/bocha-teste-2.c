#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
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

//  Sorteia o bolim
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
    char nome[100];
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
void solicita_jogada(char matriz[][TAM], int jogada, int n_jogadores, jogador jogadores[2]){
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

// VERIFICA A pONTUAÇÃO TOTAL
void verifica_pontuacao(char matriz[][TAM],jogador jogadores[2]) {

    int i,j,z,y;
    int bolin_lin, bolin_col;
    int form_euclidiana;
    int booleano = 0;

    // PROCURA A LOCALIZAÇÃO DO BALIN
    for (i = 0; i < TAM && !booleano; i++) {
        for (j = 0; j < TAM && !booleano; j++) {
            if (matriz[i][j] == 'X') {
                bolin_lin = i;
                bolin_col = j;
                booleano = 1;
            }
        }
    }


    // CALCULA A PONTUAÇÃO TOTAL
    for(z = 0; z < TAM; z++) {
        for(y = 0; y < TAM; y++) {

            if(matriz[z][y] == 'a') {
                form_euclidiana = sqrt(pow(z - bolin_lin, 2) + pow(y - bolin_col, 2));
                    if (form_euclidiana == 1) {
                    jogadores[0].pontos += 2;
                    } else {
                    jogadores[0].pontos++;
                    }
            }

            if(matriz[z][y] == 'b') {
                form_euclidiana = sqrt(pow(z - bolin_lin, 2) + pow(y - bolin_col, 2));
                    if (form_euclidiana == 1) {
                        jogadores[1].pontos += 2;
                    } else {
                        jogadores[1].pontos++;
                    }
            }
        }
    }


  }


int main() {
    char matriz[TAM][TAM], coluna;
    int n_jogadores = 2;
    int i, j, k, linha;
    jogador jogadores[2];


    setlocale(LC_ALL, "");
    sementeRand();

//  Início do jogo
    gerar_matriz(matriz);
    printf("\n          BEM VINDO AO BOCHA SIMULATOR\n\n");
    exibir(matriz);
    printf("\n\n");

//  Informar nome do jogador
    for (i = 0; i < n_jogadores; i++) {
        printf("Informe o nome do jogador %d : ", i+1);
        gets(jogadores[i].nome);
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
            printf("\nO jogador %s ja fez %d jogadas", jogadores[k].nome, jogadores[k].jogadas);
        }
    }

    // Verifica a pontuação
    verifica_pontuacao(matriz,jogadores);


    int houve_ven = 0, venc_a_b;

    limpa_tela();
    exibir(matriz);

    // Verifica o vencedor ou se houve empate
    if (jogadores[0].pontos > jogadores[1].pontos) {
            houve_ven = 1;
            venc_a_b = 0;
        } else if(jogadores[0].pontos < jogadores[1].pontos) {
            houve_ven = 1;
            venc_a_b = 1;
        }

    //DECLARAÇÃO FINAL
    printf("\n====================================================\n\n\n");
    printf("                  PONTUACAO FINAL                         ");
        for(k = 0; k < n_jogadores; k++) {
            printf("\n\nJogador %s :  %d pontos \n", jogadores[k].nome,jogadores[k].pontos);
        }

    if (houve_ven == 0) {
        printf("\n\nO BOCHA SIMULATOR TERMINOU EMPATADO !! ");
    } else if (houve_ven == 1 && venc_a_b == 0) {
        printf("\n\nO GRANDE VENCEDOR DE BOCHA SIMULATOR FOI  %s !!!!", jogadores[0].nome);
    } else if (houve_ven == 1 && venc_a_b == 1){
        printf("\n\nO GRANDE VENCEDOR DE BOCHA SIMULATOR FOI  %s !!!!", jogadores[1].nome);
    }
    printf("\n====================================================\n\n\n");


    return 0;
}
