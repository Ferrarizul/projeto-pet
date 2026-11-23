#ifndef PET_H
#define PET_H

#include <stdio.h>

#define MAX 100
#define ARQUIVO "dados.txt"

// registro de cada pet da clinica
typedef struct Pet {
    int chip;           // numero do registro/chip
    char nome[50];
    char especie[30];   // gato, cachorro, etc
    char raca[30];
    int idade;          // idade total em meses
    float peso;         // em kg
} pet;

typedef pet *p_pet;

extern p_pet v[MAX];

// prototipos
void inicializa();
void limpa_buffer();
int carregar_arquivo();
void salvar_arquivo();
int posicao_livre();
int buscar_chip(int chip);
void ler_dados(int i);
void imprimir_unico(int i);
void imprimir_tudo();
void relatorio();
void liberar_memoria();

#endif
