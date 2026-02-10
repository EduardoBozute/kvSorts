#include <stdio.h>
#include <stdlib.h>
#include "coleta.h"
#include "sort.h"

// Algoritmos de ordenação

// Selection Sort
void selectionsort(int linhas, int colunas, elemento** m){
    int i, j, min;
    elemento x;
    for(int numero_linha = 0; numero_linha<linhas; numero_linha++){
        for(i = 0; i < colunas-1; i++){
            min = i;
            for(j = i+1; j < colunas; j++)
                if(m[numero_linha][j].dist < m[numero_linha][min].dist) min = j;
            x = m[numero_linha][i]; m[numero_linha][i] = m[numero_linha][min]; m[numero_linha][min] = x;
        }
    }
}

// Insertion Sort
void insertionsort(int linhas, int colunas, elemento** m){
    int i, j;
    elemento x;
    for(int linha = 0; linha < linhas; linha++){
        for(j = 1; j < colunas; j++){
            x = m[linha][j];
            for(i = j-1; i >= 0 && m[linha][i].dist > x.dist; i--)
                m[linha][i+1] = m[linha][i];
            m[linha][i+1] = x;
        }
    }
}

//Merge Sort
void intercala(int linha, int p, int q, int r, elemento** m){
    int i, j, k;
    elemento* w;
    w=(elemento*)malloc((r-p)*sizeof(elemento));
    i=p; j=q; k=0;
    while(i<q && j<r){
        if(m[linha][i].dist <= m[linha][j].dist) w[k++] = m[linha][i++];
        else w[k++] = m[linha][j++];
    }
    while(i < q) w[k++]=m[linha][i++];
    while(j < r) w[k++]=m[linha][j++];
    for(i = p; i < r; i++) m[linha][i] = w[i-p];
    free(w);
}

void mergesort(int linha, int inicio, int final, elemento** m){
    if(inicio<final-1){
        int media=(inicio+final)/2;
        mergesort(linha, inicio, media, m);
        mergesort(linha, media, final, m);
        intercala(linha, inicio, media, final, m);
    }
}

//Quick Sort
int separa(int linha, int inicio, int final, elemento** m){
    int j, k;
    elemento c, t;
    c = m[linha][final]; j = inicio;
    for(k = inicio; k < final; k++)
        if(m[linha][k].dist <= c.dist){
            t = m[linha][j], m[linha][j]=m[linha][k], m[linha][k]=t;
            j++;
        }
    m[linha][final]=m[linha][j], m[linha][j]=c;
    return j;
}

void quicksort(int linha, int inicio, int final, elemento** m){
    int j;
    if(inicio < final){
        j = separa(linha, inicio, final, m);
        quicksort(linha, inicio, j-1, m);
        quicksort(linha, j+1, final, m);
    }
}

//Shell Sort
void shellsort(int linhas, int colunas, elemento** m){
    for(int linha = 0; linha < linhas; linha++){
        for(int gap = colunas/2; gap > 0; gap/=2){
            for(int i = gap; i < colunas; i++){
                elemento temp = m[linha][i];
                int j;
                for(j = i; j >= gap && m[linha][j-gap].dist > temp.dist; j -= gap)
                    m[linha][j] = m[linha][j-gap];
                m[linha][j] = temp;
            }
        }
    }
}