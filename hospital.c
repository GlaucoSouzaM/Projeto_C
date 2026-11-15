#include <stdio.h>
#include <string.h>
#include "sistema.h"

int buscar_hospital_por_codigo(int codigo) {
    for (int i = 0; i < total_hospitais; i++) {
        if (hospitais[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrar_hospital() {
    if (total_hospitais >= MAX_HOSPITAIS) {
        printf("\n[ERRO] Limite maximo de hospitais atingido!\n");
        return;
    }

    Hospital novo;
    novo.codigo = total_hospitais + 1;

    printf("\n--- CADASTRO DE HOSPITAL (Codigo: %d) ---\n", novo.codigo);

    do {
        printf("Nome do hospital (obrigatorio): ");
        ler_texto(novo.nome, sizeof(novo.nome));
        if (strlen(novo.nome) == 0) {
            printf("[AVISO] O nome do hospital e obrigatorio!\n");
        }
    } while (strlen(novo.nome) == 0);

    printf("CNPJ: ");
    ler_texto(novo.cnpj, sizeof(novo.cnpj));

    do {
        printf("Endereco (obrigatorio): ");
        ler_texto(novo.endereco, sizeof(novo.endereco));
        if (strlen(novo.endereco) == 0) {
            printf("[AVISO] O endereco do hospital e obrigatorio!\n");
        }
    } while (strlen(novo.endereco) == 0);

    printf("Telefone: ");
    ler_texto(novo.telefone, sizeof(novo.telefone));

    hospitais[total_hospitais] = novo;
    total_hospitais++;

    printf("\n[SUCESSO] Hospital '%s' cadastrado com sucesso! (Codigo: %d)\n", novo.nome, novo.codigo);
}

void listar_hospitais() {
    printf("\n--- LISTA DE HOSPITAIS CADASTRADOS ---\n");

    if (total_hospitais == 0) {
        printf("Nenhum hospital cadastrado ate o momento.\n");
        return;
    }

    for (int i = 0; i < total_hospitais; i++) {
        printf("----------------------------------------\n");
        printf("Codigo:   %d\n", hospitais[i].codigo);
        printf("Nome:     %s\n", hospitais[i].nome);
        printf("CNPJ:     %s\n", hospitais[i].cnpj);
        printf("Endereco: %s\n", hospitais[i].endereco);
        printf("Telefone: %s\n", hospitais[i].telefone);
    }
    printf("----------------------------------------\n");
    printf("Total de hospitais: %d\n", total_hospitais);
}
