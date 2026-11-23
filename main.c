#include <stdio.h>
#include <stdlib.h>
#include "pet.h"

p_pet v[MAX];

// Menu que aparece sempre que o usuario termina uma operacao.
void mostrar_menu(void){
    printf("\n==================================\n");
    printf("       CLINICA VETERINARIA\n");
    printf("==================================\n");
    printf("         MENU PRINCIPAL\n");
    printf("----------------------------------\n");
    printf("1. Cadastrar pet\n");
    printf("2. Listar todos os pets\n");
    printf("3. Buscar pet pelo chip\n");
    printf("4. Relatorio\n");
    printf("5. Salvar e sair\n");
    printf("----------------------------------\n");
}

// Le a opcao escolhida no menu.
int ler_opcao(void){
    int escolha;
    printf("Digite sua opcao: ");
    int leitura;

    leitura = scanf("%d", &escolha);
    if(leitura != 1){
        limpa_buffer();
        return 0;
    }
    limpa_buffer();
    return escolha;
}

int main(void){
    int opcao = 0;
    int pos;
    int chip;
    int qtd;

    inicializa();
    // Recupera os cadastros da ultima vez que o programa foi usado.
    qtd = carregar_arquivo();
    printf("%d pet(s) carregado(s) do arquivo.\n", qtd);

    do{
        // Mostra o menu novamente depois de cada operacao.
        mostrar_menu();
        opcao = ler_opcao();

        switch(opcao){
            case 1:
                pos = posicao_livre();
                if(pos == -1){
                    printf("Limite de %d pets atingido.\n", MAX);
                }
                else{
                    ler_dados(pos);
                }
                break;
            case 2:
                imprimir_tudo();
                break;
            case 3:
                printf("Digite o chip do pet: ");
                if(scanf("%d", &chip) != 1){
                    limpa_buffer();
                    printf("Chip invalido. Digite um numero.\n");
                    break;
                }
                limpa_buffer();
                pos = buscar_chip(chip);
                if(pos == -1){
                    printf("Nenhum pet encontrado com o chip %d\n", chip);
                }
                else{
                    printf("\nPet encontrado:\n");
                    imprimir_unico(pos);
                }
                break;
            case 4:
                relatorio();
                break;
            case 5:
                // Antes de sair, grava os dados e libera a memoria.
                salvar_arquivo();
                liberar_memoria();
                printf("Memoria liberada. Fim!\n");
                break;
            default:
                printf("Opcao invalida\n");
        }

        if(opcao != 5){
            printf("\nTecle ENTER para continuar...");
            getchar();
        }

    }while(opcao != 5);

    return 0;
}
