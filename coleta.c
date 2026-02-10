#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coleta.h"

// Lê dados dos arquivos
void *readDataFromFile(const char *filename, int *rows, int *cols) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", filename);
        return NULL;
    }
    void *data = NULL;
    // Ler o cabeçalho: número de linhas e colunas
    fread(rows, sizeof(int), 1, file);
    fread(cols, sizeof(int), 1, file);
    printf("Matriz %s - Linhas: %d, Colunas: %d\n", filename, *rows, *cols);
    // Verifica se  ́e uma matriz com uma coluna (nesse caso, trata como int) ou uma matriz com m ́ultiplas colunas (trata como float)
    if (*cols == 1) {
        // Tratar como matriz de uma coluna de inteiros
        data = (int **)malloc(*rows * sizeof(int *));
        for (int i = 0; i < *rows; i++) {
            ((int **)data)[i] = (int *)malloc(sizeof(int));
            fread(((int **)data)[i], sizeof(int), 1, file); // Ler cada elemento como int
        }
    } else {
        // Tratar como matriz de m ́ultiplas colunas de floats
        data = (float **)malloc(*rows * sizeof(float *));
        for (int i = 0; i < *rows; i++) {
            ((float **)data)[i] = (float *)malloc(*cols * sizeof(float));
            fread(((float **)data)[i], sizeof(float), *cols, file); // Ler linha por linha como float
        }
    }
    fclose(file);
    return data;
}

// Calculo dos vetores de distancia
elemento** calculodistancia(int tamanho, int colunas, int colunas_somatoria, float **avaliar, float **referencia){

    // Alocação da matriz dos vetores de distância
    elemento** d=(elemento**)malloc(tamanho*sizeof(elemento*));
    for (int i = 0; i < tamanho; i++){
        ((elemento**)d)[i]=(elemento*)malloc(colunas*sizeof(elemento));
    }
    // Linhas da matriz
    for (int i = 0; i < tamanho; i++){

        // Colunas da matriz
        for (int j = 0; j < colunas; j++){

            // Atribuição do cliente e inicialização da distância
            d[i][j].cliente = j;
            d[i][j].dist = 0;

            // Atribuição da somatória na distância
            for(int k = 0; k < colunas_somatoria; k++){
                double acrescimo = avaliar[i][k];
                acrescimo -= referencia[j][k];
                acrescimo = pow(acrescimo, 2);
                d[i][j].dist += acrescimo;
            }

            // Conclusão do cálculo da distância
            d[i][j].dist = sqrt(d[i][j].dist);
        }
    }
    return d;
}

// Calculo dos acertos
void acerto(int k, int linhas, elemento** avaliar, int** dados, int** referencia){
    double acuracia = 0;
    for(int i = 0; i < linhas; i++){
        int acertos = 0;
        for(int j = 0; j < k; j++){
            int cliente = avaliar[i][j].cliente;
            if(dados[i][0] == referencia[cliente][0])
                acertos++;
        }
        if(k - acertos < acertos)
            acuracia++;
    }
    double resultado = (double)(acuracia/linhas)*100;
    printf("\n| k = %d \t | taxa de acerto = %lf \t|", k, resultado);
}