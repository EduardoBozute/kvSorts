#ifndef COLETA_H
#define COLETA_H

// Elemento do vetor de distâncias que guarda o cliente correspondente
typedef struct{
    double dist;
    int cliente;
}elemento;

// Lê dados dos arquivos
void *readDataFromFile(const char* , int* , int*);

// Calcula todos os vetores de distancia
elemento** calculodistancia(int, int, int, float**, float**);

// Calculo dos acertos
void acerto(int, int, elemento**, int**, int**);

#endif