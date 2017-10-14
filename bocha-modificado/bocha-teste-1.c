#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#define TAM 10


//Gerar a matriz
void gerar_matriz(char matriz[][TAM]) {
    int i,j;
    for(i = 0;i < TAM; i++ ) {
       for(j = 0;j < TAM; j++ ) {
            matriz[i][j] = ' ';
       }
    }
}

//Converter caractere em inteiro
int conv_char_int(char indice) {
    switch (indice)
    {
        case 'a' :
            return 0;
        break;
        case 'b' :
            return 1;
        break;
        case 'c' :
            return 2;
        break;
        case 'd' :
            return 3;
        break;
        case 'e' :
            return 4;
        break;
        case 'f' :
            return 5;
        break;
        case 'g' :
            return 6;
        break;
        case 'h' :
            return 7;
        break;
        case 'i' :
            return 8;
        break;
        case 'j' :
            return 9;
        break;
    }
}
char converter_char_int(char indice) {
    char a, letra;
    a = 'A';
    letra = toupper(indice) - a;

    return letra;
}

//Exibe a matriz
void exibir(char matriz[][TAM]) {
    int i, j, x;
    int vetor_int[TAM];
    char vetor_char[TAM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    x = TAM;

    for(i = 0 ;i < TAM;i++) {
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




//Sorteia o balin
int sorteio(){
    int x;
    srand((unsigned)time(NULL));

    x = rand() % 10;
    return x;
}

//Limpa a tela
void limpa_tela() {
    system("cls");
}

typedef struct {
    char nome[51];
    int jogadas, pontos;
} jogador;


int main() {
    char matriz[TAM][TAM];
    int n_jogadores, inicia_jogo, i;
    jogador jogadores[4];
    int linha;
    char coluna;

    setlocale(LC_ALL, "");

    //Início do jogo
    gerar_matriz(matriz);
    printf("\n          BEM VINDO AO BOCHA SIMULATOR\n\n");
    exibir(matriz);

    printf("\n\n");


    //Pede o número de jogadores
    do {
        printf("Informe o número de jogadores [Escolha 2 ou 4] :  ");
        scanf("%d", &n_jogadores);
        printf("\n");

        if(n_jogadores == 2 || n_jogadores == 4) {
            inicia_jogo = 1;
        }
    } while(inicia_jogo != 1);


    //Informar nome do jogador
    for (i = 0; i < n_jogadores ; i++) {
        printf("Informe o nome do jogador %d : ", i+1);
        scanf("%s", jogadores[i].nome);
        printf("\n");
    }


    // Joga-se o balin
    matriz[sorteio()][sorteio()] = 'X';
    limpa_tela();



    printf("\n\n--------->>> BALIN JOGADO COM SUCESSO\n\n");
    exibir(matriz);


    printf("\n\n");
    printf(" Em qual linha pretende jogar a bocha ?  ");
    scanf("%d", &linha);
    printf("Informe a coluna da matriz ?  ");
    scanf(" %c", &coluna);


    linha = 10 - linha;
    printf("\n\n");
    matriz[linha][conv_char_int(coluna)] = 'a';


    exibir(matriz);


    return 0;
}
