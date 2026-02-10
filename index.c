#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "coleta.h"
#include "sort.h"

int main() {

    // Nomes dos arquivos binários
    char *filename_cliente_dados = "clientes_dados_referencia.dat";
    char *filename_cliente_credito = "clientes_credito_referencia.dat";
    char *filename_cliente_dados_avaliar = "clientes_dados_avaliar.dat";
    char *filename_cliente_credito_avaliar = "clientes_credito_avaliar.dat";

    // Variáveis para armazenar as dimensões
    int rows_X, cols_X, rows_Y, cols_Y, rows_Z, cols_Z, rows_W, cols_W;

    // Variável para escolha;
    int escolha;

    // Variáveis para matriz de vetores de distância
    elemento** matrizd;
    int D[5]={100, 1000, 2000, 5000, 10000};

    //Variáveis para medir o tempo de execução
    clock_t inicio, fim;
    double tempo, tempomedio;

    // Ler a matriz de dados do arquivo (float)
    float **X = (float **)readDataFromFile(filename_cliente_dados, &rows_X, &cols_X);

    // Ler a "matriz de uma coluna" de rótulos do arquivo (int)
    int **Y = (int **)readDataFromFile(filename_cliente_credito, &rows_Y, &cols_Y);

    // Ler a matriz de dados do arquivo (float)
    float **Z = (float **)readDataFromFile(filename_cliente_dados_avaliar, &rows_Z, &cols_Z);

    // Ler a "matriz de uma coluna" de rótulos do arquivo (int)
    int **W = (int **)readDataFromFile(filename_cliente_credito_avaliar, &rows_W, &cols_W);

    /*
    
    // Exemplo: Imprimir as primeiras 5 linhas de X e os primeiros 5 elementos de Y
    printf("\nPrimeiras linhas da matriz X:\n");
    for (int i = 0; i < rows_X && i < 5; i++) {
        for (int j = 0; j < cols_X; j++) {
            printf("%lf ", X[i][j]);
        }
        printf("\n");
    }
    printf("\nPrimeiros elementos da matriz Y (coluna  ́unica):\n");
    for (int i = 0; i < rows_Y && i < 5; i++) {
        printf("%d\n", Y[i][0]);
    }

    // Exemplo: Imprimir as primeiras 5 linhas de Z e os primeiros 5 elementos de W
    printf("\nPrimeiras linhas da matriz Z:\n");
    for (int i = 0; i < rows_Z && i < 5; i++) {
        for (int j = 0; j < cols_Z; j++) {
            printf("%lf ", Z[i][j]);
        }
        printf("\n");
    }
    printf("\nPrimeiros elementos da matriz W (coluna  ́unica):\n");
    for (int i = 0; i < rows_W && i < 5; i++) {
        printf("%d\n", W[i][0]);
    }

    */

    do{

        // Escolha do algoritmo
        printf("\nInsira o algoritmo de ordenação desejado:\n");
        printf("\n1 - Selection Sort\n");
        printf("2 - Insertion Sort\n");
        printf("3 - Merge Sort\n");
        printf("4 - Quick Sort\n");
        printf("5 - Shell Sort\n");
        printf("6 - Sair do programa\n\n");
        scanf("%d", &escolha);

        // Execução do algoritmo desejado
        switch(escolha){
            case 1: 

            // Selection Sort
            for(int i=0; i<5; i++){

                //Cálculo da matriz dos vetores de distância
                matrizd=calculodistancia(rows_Z, rows_X, cols_X, Z, X);

                inicio=clock();

                //Execução do algoritmo
                selectionsort(rows_Z, D[i], matrizd); 

                fim=clock();

                //Cálculo da taxa de acerto
                printf("\n|-----------------------------------------------|\n");
                printf("|\t\tReferencia: %d \t\t|", D[i]);
                printf("\n|-----------------------------------------------|");
                for(int kvizinhos=1; kvizinhos<=11; kvizinhos+=2){
                    acerto(kvizinhos, rows_Z, matrizd, W, Y);
                }
                printf("\n|-----------------------------------------------|\n");

                tempo=(double)(fim-inicio)/CLOCKS_PER_SEC;

                //Liberação de memória da matriz para rearranjá-la para o próximo sort
                for (int i = 0; i < rows_Z; i++) free(matrizd[i]);
                    free(matrizd);

                printf("\nTempo de execução: %lf s\n\n", tempo);
                tempomedio=tempo/rows_Z;
                printf("Tempo médio por vetor: %lf s\n\n", tempomedio);
            }
            break;

            case 2:

            //Insertion Sort
            for(int i=0; i<5; i++){

                //Cálculo da matriz dos vetores de distância
                matrizd=calculodistancia(rows_Z, rows_X, cols_X, Z, X);

                inicio=clock();

                //Execução do algoritmo
                insertionsort(rows_Z, D[i], matrizd); 

                fim=clock();

                //Cálculo da taxa de acerto
                printf("\n|-----------------------------------------------|\n");
                printf("|\t\tReferencia: %d \t\t|", D[i]);
                printf("\n|-----------------------------------------------|");
                for(int kvizinhos=1; kvizinhos<=11; kvizinhos+=2){
                    acerto(kvizinhos, rows_Z, matrizd, W, Y);
                }
                printf("\n|-----------------------------------------------|\n");

                tempo=(double)(fim-inicio)/CLOCKS_PER_SEC;

                //Liberação de memória da matriz para rearranjá-la para o próximo sort
                for (int i = 0; i < rows_Z; i++) free(matrizd[i]);
                    free(matrizd);

                printf("\nTempo de execução: %lf s\n\n", tempo);
                tempomedio=tempo/rows_Z;
                printf("Tempo médio por vetor: %lf s\n\n", tempomedio);
            }
            break;

            case 3: 

            //Merge Sort
            for(int i=0; i<5; i++){

                //Cálculo da matriz dos vetores de distância
                matrizd=calculodistancia(rows_Z, rows_X, cols_X, Z, X);

                inicio=clock();

                //Execução do algoritmo
                for(int linha=0; linha < rows_Z; linha++)
                    mergesort(linha, 0, D[i], matrizd);
                //Aqui, o laço de repetição definido é fora
                //O algoritmo é recursivo, divide para conquistar

                fim=clock();

                //Cálculo da taxa de acerto
                printf("\n|-----------------------------------------------|\n");
                printf("|\t\tReferencia: %d \t\t|", D[i]);
                printf("\n|-----------------------------------------------|");
                for(int kvizinhos=1; kvizinhos<=11; kvizinhos+=2){
                    acerto(kvizinhos, rows_Z, matrizd, W, Y);
                }
                printf("\n|-----------------------------------------------|\n");

                tempo=(double)(fim-inicio)/CLOCKS_PER_SEC;

                //Liberação de memória da matriz para rearranjá-la para o próximo sort
                for (int i = 0; i < rows_Z; i++) free(matrizd[i]);
                    free(matrizd);

                printf("\nTempo de execução: %lf s\n\n", tempo);
                tempomedio=tempo/rows_Z;
                printf("Tempo médio por vetor: %lf s\n\n", tempomedio);
            }
            break;

            case 4:

            //Quick Sort
            for(int i=0; i<5; i++){

                //Cálculo da matriz dos vetores de distância
                matrizd=calculodistancia(rows_Z, rows_X, cols_X, Z, X);

                inicio=clock();

                //Execução do algoritmo
                for(int linha=0; linha < rows_Z; linha++)
                    quicksort(linha, 0, D[i]-1, matrizd);
                //Aqui, o laço de repetição definido é fora, o Quick Sort usa o índice final, não o tamanho
                //O algoritmo é recursivo, divide para conquistar

                fim=clock();

                //Cálculo da taxa de acerto
                printf("\n|-----------------------------------------------|\n");
                printf("|\t\tReferencia: %d \t\t|", D[i]);
                printf("\n|-----------------------------------------------|");
                for(int kvizinhos=1; kvizinhos<=11; kvizinhos+=2){
                    acerto(kvizinhos, rows_Z, matrizd, W, Y);
                }
                printf("\n|-----------------------------------------------|\n");

                tempo=(double)(fim-inicio)/CLOCKS_PER_SEC;

                //Liberação de memória da matriz para rearranjá-la para o próximo sort
                for (int i = 0; i < rows_Z; i++) free(matrizd[i]);
                    free(matrizd);

                printf("\nTempo de execução: %lf s\n\n", tempo);
                tempomedio=tempo/rows_Z;
                printf("Tempo médio por vetor: %lf s\n\n", tempomedio);
            }
            break;

            case 5: 

            //Shell Sort
            for(int i=0; i<5; i++){

                //Cálculo da matriz dos vetores de distância
                matrizd=calculodistancia(rows_Z, rows_X, cols_X, Z, X);

                inicio=clock();

                //Execução do algoritmo
                shellsort(rows_Z, D[i], matrizd); 

                fim=clock();

                //Cálculo da taxa de acerto
                printf("\n|-----------------------------------------------|\n");
                printf("|\t\tReferencia: %d \t\t|", D[i]);
                printf("\n|-----------------------------------------------|");
                for(int kvizinhos=1; kvizinhos<=11; kvizinhos+=2){
                    acerto(kvizinhos, rows_Z, matrizd, W, Y);
                }
                printf("\n|-----------------------------------------------|\n");

                tempo=(double)(fim-inicio)/CLOCKS_PER_SEC;

                //Liberação de memória da matriz para rearranjá-la para o próximo sort
                for (int i = 0; i < rows_Z; i++) free(matrizd[i]);
                    free(matrizd);

                printf("\nTempo de execução: %lf s\n", tempo);
                tempomedio=tempo/rows_Z;
                printf("Tempo médio por vetor: %lf s\n\n", tempomedio);
            }
            break;

            case 6: 
            
            //Sair do programa
            break;

            default: printf("\nErro! Entrada fora das opções!\n"); break;
        }

        /*
        // Exemplo: Amostragem de elementos para verificação
        if(escolha!=6){
            printf("\nPrimeiros 5x6 da matrizd:\n");
            for (int i = 0; i < rows_Z && i < 5; i++){
                for (int j = 0; j < rows_X && j < 6; j++){
                    printf("%f ", matrizd[i][j].dist);
                }
                printf("\n");
            }
        }
        */

    }   
    // Repete até o usuário desejar sair;
    while(escolha!=6);

    // Liberar memória alocada
    for (int i = 0; i < rows_X; i++) free(X[i]);
        free(X);
    for (int i = 0; i < rows_Y; i++) free(Y[i]);
        free(Y);
    for (int i = 0; i < rows_Z; i++) free(Z[i]);
        free(Z);
    for (int i = 0; i < rows_W; i++) free(W[i]);
        free(W);

    // Fim do programa
    return 0;
}

//compilar: gcc index.c coleta.c sort.c -o index.exe -lm