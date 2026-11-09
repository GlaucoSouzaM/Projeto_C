#include <stdio.h>
#include <string.h>
#include "sistema.h"

// Verifica se um médico existe no vetor pelo código e retorna o índice (ou -1 se não achar)
int buscar_medico_por_codigo(int codigo) {
    for (int i = 0; i < total_medicos; i++) {
        if (medicos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Opção 2 do Menu - Cadastrar Médico
void cadastrar_medico() {
    if (total_medicos >= MAX_MEDICOS) {
        printf("\n[ERRO] Limite maximo de medicos atingido!\n");
        return;
    }

    Medico novo;
    novo.codigo = total_medicos + 1;

    printf("\n--- CADASTRO DE MEDICO (Codigo: %d) ---\n", novo.codigo);

    // Regra de negócio: Todo médico cadastrado deverá possuir nome completo, CRM e especialidade
    do {
        printf("Nome completo (obrigatorio): ");
        ler_texto(novo.nome, sizeof(novo.nome));
        if (strlen(novo.nome) == 0) {
            printf("[AVISO] O nome completo do medico e obrigatorio!\n");
        }
    } while (strlen(novo.nome) == 0);

    do {
        printf("CRM (obrigatorio): ");
        ler_texto(novo.crm, sizeof(novo.crm));
        if (strlen(novo.crm) == 0) {
            printf("[AVISO] O CRM e obrigatorio!\n");
        }
    } while (strlen(novo.crm) == 0);

    do {
        printf("Especialidade (obrigatorio): ");
        ler_texto(novo.especialidade, sizeof(novo.especialidade));
        if (strlen(novo.especialidade) == 0) {
            printf("[AVISO] A especialidade e obrigatoria!\n");
        }
    } while (strlen(novo.especialidade) == 0);

    printf("Telefone: ");
    ler_texto(novo.telefone, sizeof(novo.telefone));

    printf("E-mail: ");
    ler_texto(novo.email, sizeof(novo.email));

    // Salva no vetor de médicos
    medicos[total_medicos] = novo;
    total_medicos++;

    printf("\n[SUCESSO] Medico(a) '%s' cadastrado(a) com sucesso! (Codigo: %d)\n", novo.nome, novo.codigo);

    // Pergunta se já deseja cadastrar um horário disponível na agenda desse médico
    char resposta;
    printf("\nDeseja cadastrar um horario disponivel para este medico agora? (S/N): ");
    scanf(" %c", &resposta);
    limpar_buffer();

    while (resposta == 'S' || resposta == 's') {
        if (total_agendas >= MAX_AGENDAS) {
            printf("\n[ERRO] Limite maximo de horarios na agenda atingido!\n");
            break;
        }

        AgendaMedica nova_agenda;
        nova_agenda.codigo = total_agendas + 1;
        nova_agenda.codigo_medico = novo.codigo;

        printf("\n--- NOVO HORARIO NA AGENDA (Medico: %s) ---\n", novo.nome);
        do {
            printf("Data disponivel (DD/MM/AAAA): ");
            ler_texto(nova_agenda.data_disponivel, sizeof(nova_agenda.data_disponivel));
        } while (strlen(nova_agenda.data_disponivel) == 0);

        do {
            printf("Horario inicial (HH:MM): ");
            ler_texto(nova_agenda.horario_inicial, sizeof(nova_agenda.horario_inicial));
        } while (strlen(nova_agenda.horario_inicial) == 0);

        do {
            printf("Horario final (HH:MM): ");
            ler_texto(nova_agenda.horario_final, sizeof(nova_agenda.horario_final));
        } while (strlen(nova_agenda.horario_final) == 0);

        strcpy(nova_agenda.disponibilidade, "Disponivel");

        agendas[total_agendas] = nova_agenda;
        total_agendas++;

        printf("[SUCESSO] Horario %s (%s as %s) adicionado a agenda!\n",
               nova_agenda.data_disponivel, nova_agenda.horario_inicial, nova_agenda.horario_final);

        printf("\nDeseja adicionar outro horario para este medico? (S/N): ");
        scanf(" %c", &resposta);
        limpar_buffer();
    }
}

// Opção 13 do Menu - Listar Médicos Cadastrados
void listar_medicos() {
    printf("\n--- LISTA DE MEDICOS CADASTRADOS ---\n");

    if (total_medicos == 0) {
        printf("Nenhum medico cadastrado ate o momento.\n");
        return;
    }

    for (int i = 0; i < total_medicos; i++) {
        printf("----------------------------------------\n");
        printf("Codigo:        %d\n", medicos[i].codigo);
        printf("Nome:          %s\n", medicos[i].nome);
        printf("CRM:           %s\n", medicos[i].crm);
        printf("Especialidade: %s\n", medicos[i].especialidade);
        printf("Telefone:      %s\n", medicos[i].telefone);
        printf("E-mail:        %s\n", medicos[i].email);
    }
    printf("----------------------------------------\n");
    printf("Total de medicos: %d\n", total_medicos);
}

