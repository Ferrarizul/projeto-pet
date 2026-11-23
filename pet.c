#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pet.h"

// deixa todas as posicoes do vetor apontando pra NULL
void inicializa(){
    int i;
    for(i=0; i<MAX; i++){
        v[i] = NULL;
    }
}

// pedi ajuda pra IA aqui pq nao estava funcionando de jeito nenhum
// o fgets pulava o campo depois do scanf e o fflush(stdin) nao resolvia
// o problema era o enter que sobrava no buffer, entao le ate achar o \n
void limpa_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// le o dados.txt e coloca os pets no vetor
// retorna quantos pets foram carregados
int carregar_arquivo(){
    FILE *fp;
    char linha[256];
    pet aux;
    int i = 0;
    int qtd = 0;

    fp = fopen(ARQUIVO, "r");
    if(fp == NULL){
        // na primeira vez o arquivo ainda nao existe, entao so comeca vazio
        printf("Arquivo %s nao encontrado, comecando sem nenhum pet.\n", ARQUIVO);
        return 0;
    }

    while(fgets(linha, sizeof(linha), fp) != NULL){
        linha[strcspn(linha, "\n")] = 0;

        if(strlen(linha) == 0){
            continue; // linha em branco
        }

        // formato: chip;nome;especie;raca;idade_em_meses;peso
        // pedi ajuda pra IA aqui pq nao estava funcionando de jeito nenhum
        // com %s ele lia tudo junto ate o fim da linha, o %49[^;] le ate achar o ;
        // (o 49 e pra nao passar do tamanho do nome[50])
        if(sscanf(linha, "%d;%49[^;];%29[^;];%29[^;];%d;%f", &aux.chip, aux.nome, aux.especie, aux.raca, &aux.idade, &aux.peso) == 6){
            if(i >= MAX){
                printf("O arquivo tem mais pets do que o limite (%d), o resto foi ignorado\n", MAX);
                break;
            }

            v[i] = (p_pet) malloc(sizeof(pet));
            if(v[i] == NULL){
                printf("Erro ao alocar memoria!\n");
                break;
            }

            v[i]->chip = aux.chip;
            strcpy(v[i]->nome, aux.nome);
            strcpy(v[i]->especie, aux.especie);
            strcpy(v[i]->raca, aux.raca);
            v[i]->idade = aux.idade;
            v[i]->peso = aux.peso;

            i++;
            qtd++;
        }
        else{
            printf("Aviso: linha invalida ignorada: %s\n", linha);
        }
    }

    fclose(fp);
    return qtd;
}

// grava tudo que ta no vetor no arquivo (apaga o que tinha antes)
void salvar_arquivo(){
    FILE *fp;
    int i;
    int cont = 0;

    fp = fopen(ARQUIVO, "w");
    if(fp == NULL){
        printf("Erro: nao foi possivel abrir o arquivo para salvar!\n");
        return;
    }

    for(i=0; i<MAX; i++){
        if(v[i] != NULL){
            fprintf(fp, "%d;%s;%s;%s;%d;%.2f\n", v[i]->chip, v[i]->nome, v[i]->especie, v[i]->raca, v[i]->idade, v[i]->peso);
            cont++;
        }
    }

    fclose(fp);
    printf("%d pet(s) salvo(s) em %s\n", cont, ARQUIVO);
}

// procura a primeira posicao vazia do vetor, se tiver cheio retorna -1
int posicao_livre(){
    int i;
    for(i=0; i<MAX; i++){
        if(v[i] == NULL){
            return i;
        }
    }
    return -1;
}

// procura o pet pelo chip e retorna a posicao, -1 se nao achar
int buscar_chip(int chip){
    int i;
    for(i=0; i<MAX; i++){
        if(v[i] != NULL && v[i]->chip == chip){
            return i;
        }
    }
    return -1;
}

void ler_dados(int i){
    int chip = 0;

    if(v[i] == NULL){
        printf("\n--- CADASTRO DE PET ---\n");
        printf("Numero do chip/registro: ");
        if(scanf("%d", &chip) != 1 || chip <= 0){
            limpa_buffer();
            printf("Chip invalido. Use um numero positivo.\n");
            return;
        }
        limpa_buffer();

        // nao deixa cadastrar dois pets com o mesmo chip
        if(buscar_chip(chip) != -1){
            printf("Ja existe um pet cadastrado com o chip %d!\n", chip);
            return;
        }

        v[i] = (p_pet) malloc(sizeof(pet));
        if(v[i] == NULL){
            printf("Erro ao alocar memoria!\n");
            return;
        }

        v[i]->chip = chip;

        printf("Nome do pet: ");
        fgets(v[i]->nome, 50, stdin);
        v[i]->nome[strcspn(v[i]->nome, "\n")] = 0;
        if(strlen(v[i]->nome) == 0){
            strcpy(v[i]->nome, "Sem nome");
        }

        printf("Especie (Gato, Cachorro...): ");
        fgets(v[i]->especie, 30, stdin);
        v[i]->especie[strcspn(v[i]->especie, "\n")] = 0;
        if(strlen(v[i]->especie) == 0){
            strcpy(v[i]->especie, "Nao informado");
        }

        printf("Raca (se nao souber aperta enter): ");
        fgets(v[i]->raca, 30, stdin);
        v[i]->raca[strcspn(v[i]->raca, "\n")] = 0;
        if(strlen(v[i]->raca) == 0){
            strcpy(v[i]->raca, "SRD"); // sem raca definida (vira-lata)
        }

        // A idade fica guardada em meses para aceitar filhotes tambem.
        int anos, meses;
        printf("Idade - anos completos: ");
        while(scanf("%d", &anos) != 1 || anos < 0){
            limpa_buffer();
            printf("Ano invalido. Digite novamente: ");
        }
        limpa_buffer();

        printf("Meses adicionais (0 a 12): ");
        while(scanf("%d", &meses) != 1 || meses < 0 || meses > 12){
            limpa_buffer();
            printf("Meses invalidos. Digite de 0 a 12: ");
        }
        limpa_buffer();
        v[i]->idade = anos * 12 + meses;

        printf("Peso em kg (usar ponto, ex: 4.5): ");
        while(scanf("%f", &v[i]->peso) != 1 || v[i]->peso <= 0){
            limpa_buffer();
            printf("Peso invalido. Digite novamente (ex: 4.5): ");
        }
        limpa_buffer();

        printf("\nPet cadastrado com sucesso!\n");
    }
}

void imprimir_unico(int i){
    if(v[i] != NULL){
        printf("Chip/Registro: %d\n", v[i]->chip);
        printf("Nome.........: %s\n", v[i]->nome);
        printf("Especie......: %s\n", v[i]->especie);
        printf("Raca.........: %s\n", v[i]->raca);
        // Divide por 12 para obter os anos; o resto sao os meses.
        int anos = v[i]->idade / 12;
        int meses = v[i]->idade % 12;
        if(anos == 0){
            if(meses == 1){
                printf("Idade........: 1 mes\n");
            }else{
                printf("Idade........: %d meses\n", meses);
            }
        }else if(meses == 0){
            if(anos == 1){
                printf("Idade........: 1 ano\n");
            }else{
                printf("Idade........: %d anos\n", anos);
            }
        }else{
            printf("Idade........: %d ano(s) e %d mes(es)\n", anos, meses);
        }
        printf("Peso.........: %.2f kg\n", v[i]->peso);
        printf("\n");
    }
}

void imprimir_tudo(){
    int i;
    int cont = 0;

    printf("\n========== LISTA DE PETS ==========\n\n");
    for(i=0; i<MAX; i++){
        if(v[i] != NULL){
            imprimir_unico(i);
            cont++;
        }
    }

    if(cont == 0){
        printf("Nenhum pet cadastrado ainda.\n");
    }
    else{
        printf("Total: %d pet(s)\n", cont);
    }
}

void relatorio(){
    int i;
    int qtd = 0;
    float soma = 0;
    int velho = -1;   // posicao do pet mais idoso
    int gatos = 0, cachorros = 0;

    for(i=0; i<MAX; i++){
        if(v[i] != NULL){
            qtd++;
            soma = soma + v[i]->peso;

            if(velho == -1 || v[i]->idade > v[velho]->idade){
                velho = i;
            }

            if(strcmp(v[i]->especie, "Gato") == 0 || strcmp(v[i]->especie, "gato") == 0){
                gatos++;
            }
            if(strcmp(v[i]->especie, "Cachorro") == 0 || strcmp(v[i]->especie, "cachorro") == 0){
                cachorros++;
            }
        }
    }

    printf("\n======= RELATORIO DA CLINICA =======\n\n");

    if(qtd == 0){
        printf("Nao tem pets cadastrados para gerar o relatorio.\n");
        return;
    }

    printf("Pets atendidos: %d\n", qtd);
    printf("Gatos: %d | Cachorros: %d | Outros: %d\n", gatos, cachorros, qtd - gatos - cachorros);
    printf("Peso medio dos pets: %.2f kg\n", soma / qtd);
    printf("\nPet mais idoso:\n");
    imprimir_unico(velho);
}

// da free em tudo que foi alocado com malloc
void liberar_memoria(){
    int i;
    for(i=0; i<MAX; i++){
        if(v[i] != NULL){
            free(v[i]);
            v[i] = NULL;
        }
    }
}
