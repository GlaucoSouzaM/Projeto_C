#include <stdio.h>
#include <string.h>
#include "sistema.h"

int buscar_paciente_por_codigo(int codigo) {
    for (int i = 0; i < total_pacientes; i++) {
        if (pacientes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrar_paciente() {
    if (total_pacientes >= MAX_PACIENTES) {
        printf("\n[ERRO] Limite maximo de pacientes atingido!\n");
        return;
    }

    Paciente novo;
    novo.codigo = total_pacientes + 1;

    printf("\n--- CADASTRO DE PACIENTE (Codigo: %d) ---\n", novo.codigo);

    do {
        printf("Nome completo (obrigatorio): ");
        ler_texto(novo.nome, sizeof(novo.nome));
        if (strlen(novo.nome) == 0) {
            printf("[AVISO] O nome completo e obrigatorio!\n");
        }
    } while (strlen(novo.nome) == 0);

    do {
        printf("CPF (obrigatorio): ");
        ler_texto(novo.cpf, sizeof(novo.cpf));
        if (strlen(novo.cpf) == 0) {
            printf("[AVISO] O CPF e obrigatorio!\n");
        }
    } while (strlen(novo.cpf) == 0);

    do {
        printf("Data de nascimento (DD/MM/AAAA) (obrigatorio): ");
        ler_texto(novo.data_nascimento, sizeof(novo.data_nascimento));
        if (strlen(novo.data_nascimento) == 0) {
            printf("[AVISO] A data de nascimento e obrigatoria!\n");
        }
    } while (strlen(novo.data_nascimento) == 0);

    do {
        printf("Telefone (obrigatorio): ");
        ler_texto(novo.telefone, sizeof(novo.telefone));
        if (strlen(novo.telefone) == 0) {
            printf("[AVISO] O telefone e obrigatorio!\n");
        }
    } while (strlen(novo.telefone) == 0);

    printf("E-mail: ");
    ler_texto(novo.email, sizeof(novo.email));

    printf("Endereco: ");
    ler_texto(novo.endereco, sizeof(novo.endereco));

    pacientes[total_pacientes] = novo;
    total_pacientes++;

    printf("\n[SUCESSO] Paciente '%s' cadastrado com sucesso! (Codigo: %d)\n", novo.nome, novo.codigo);
}

void listar_pacientes() {
    printf("\n--- LISTA DE PACIENTES CADASTRADOS ---\n");

    if (total_pacientes == 0) {
        printf("Nenhum paciente cadastrado ate o momento.\n");
        return;
    }

    for (int i = 0; i < total_pacientes; i++) {
        printf("----------------------------------------\n");
        printf("Codigo:          %d\n", pacientes[i].codigo);
        printf("Nome:            %s\n", pacientes[i].nome);
        printf("CPF:             %s\n", pacientes[i].cpf);
        printf("Data Nascimento: %s\n", pacientes[i].data_nascimento);
        printf("Telefone:        %s\n", pacientes[i].telefone);
        printf("E-mail:          %s\n", pacientes[i].email);
        printf("Endereco:        %s\n", pacientes[i].endereco);
    }
    printf("----------------------------------------\n");
    printf("Total de pacientes: %d\n", total_pacientes);
}
