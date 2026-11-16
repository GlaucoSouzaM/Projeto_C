#include <stdio.h>
#include <string.h>
#include "sistema.h"

int buscar_consulta_por_codigo(int codigo) {
    for (int i = 0; i < total_consultas; i++) {
        if (consultas[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void agendar_consulta() {
    printf("\n--- AGENDAR CONSULTA ---\n");

    if (total_consultas >= MAX_CONSULTAS) {
        printf("\n[ERRO] Limite maximo de consultas atingido!\n");
        return;
    }

    if (total_pacientes == 0) {
        printf("\n[AVISO] Nenhum paciente cadastrado. Cadastre um paciente primeiro.\n");
        return;
    }

    if (total_medicos == 0) {
        printf("\n[AVISO] Nenhum medico cadastrado. Cadastre um medico primeiro.\n");
        return;
    }

    if (total_hospitais == 0) {
        printf("\n[AVISO] Nenhum hospital cadastrado. Cadastre um hospital primeiro.\n");
        return;
    }

    printf("\nPacientes cadastrados:\n");
    for (int i = 0; i < total_pacientes; i++) {
        printf("  Codigo: %d | Nome: %s | CPF: %s\n",
               pacientes[i].codigo, pacientes[i].nome, pacientes[i].cpf);
    }

    int cod_paciente;
    printf("\nInforme o codigo do paciente: ");
    if (scanf("%d", &cod_paciente) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx_pac = buscar_paciente_por_codigo(cod_paciente);
    if (idx_pac == -1) {
        printf("\n[ERRO] Paciente com codigo %d nao encontrado!\n", cod_paciente);
        return;
    }

    printf("\nMedicos cadastrados:\n");
    for (int i = 0; i < total_medicos; i++) {
        printf("  Codigo: %d | Dr(a). %s | Especialidade: %s\n",
               medicos[i].codigo, medicos[i].nome, medicos[i].especialidade);
    }

    int cod_medico;
    printf("\nInforme o codigo do medico desejado: ");
    if (scanf("%d", &cod_medico) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx_med = buscar_medico_por_codigo(cod_medico);
    if (idx_med == -1) {
        printf("\n[ERRO] Medico com codigo %d nao encontrado!\n", cod_medico);
        return;
    }

    printf("\nHospitais disponiveis:\n");
    for (int i = 0; i < total_hospitais; i++) {
        printf("  Codigo: %d | Hospital: %s | Endereco: %s\n",
               hospitais[i].codigo, hospitais[i].nome, hospitais[i].endereco);
    }

    int cod_hospital;
    printf("\nInforme o codigo do hospital onde a consulta sera realizada: ");
    if (scanf("%d", &cod_hospital) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx_hosp = buscar_hospital_por_codigo(cod_hospital);
    if (idx_hosp == -1) {
        printf("\n[ERRO] Hospital com codigo %d nao encontrado!\n", cod_hospital);
        return;
    }

    char data_escolhida[25];
    char horario_escolhido[10];
    int idx_agenda = -1;

    int horarios_livres = 0;
    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo_medico == cod_medico &&
            strcmp(agendas[i].disponibilidade, "Disponivel") == 0) {
            horarios_livres++;
        }
    }

    if (horarios_livres > 0) {
        printf("\nHorarios pre-cadastrados na agenda do(a) Dr(a). %s:\n", medicos[idx_med].nome);
        for (int i = 0; i < total_agendas; i++) {
            if (agendas[i].codigo_medico == cod_medico &&
                strcmp(agendas[i].disponibilidade, "Disponivel") == 0) {
                printf("  Codigo Agenda: %d | Dia: %s | Horario: %s as %s\n",
                       agendas[i].codigo, agendas[i].data_disponivel,
                       agendas[i].horario_inicial, agendas[i].horario_final);
            }
        }
        printf("  0 - Escolher outro dia da semana e horario\n");

        int cod_agenda;
        printf("\nInforme o Codigo da Agenda (ou 0 para escolher outro dia/horario): ");
        if (scanf("%d", &cod_agenda) != 1) {
            printf("\n[ERRO] Codigo invalido!\n");
            limpar_buffer();
            return;
        }
        limpar_buffer();

        if (cod_agenda != 0) {
            for (int i = 0; i < total_agendas; i++) {
                if (agendas[i].codigo == cod_agenda &&
                    agendas[i].codigo_medico == cod_medico &&
                    strcmp(agendas[i].disponibilidade, "Disponivel") == 0) {
                    idx_agenda = i;
                    break;
                }
            }
            if (idx_agenda == -1) {
                printf("\n[ERRO] Horario da agenda invalido ou indisponivel!\n");
                return;
            }
            strcpy(data_escolhida, agendas[idx_agenda].data_disponivel);
            strcpy(horario_escolhido, agendas[idx_agenda].horario_inicial);
        }
    }

    if (idx_agenda == -1) {
        escolher_dia_semana(data_escolhida);

        do {
            printf("Informe o horario da consulta (HH:MM): ");
            ler_texto(horario_escolhido, sizeof(horario_escolhido));
            if (strlen(horario_escolhido) == 0) {
                printf("[AVISO] O horario e obrigatorio!\n");
            }
        } while (strlen(horario_escolhido) == 0);
    }

    for (int i = 0; i < total_consultas; i++) {
        if (consultas[i].codigo_medico == cod_medico &&
            strcmp(consultas[i].data, data_escolhida) == 0 &&
            strcmp(consultas[i].horario, horario_escolhido) == 0 &&
            strcmp(consultas[i].status, "Cancelada") != 0) {
            printf("\n[ERRO] Conflito de agendamento! O medico ja possui consulta nesta data e horario.\n");
            return;
        }
    }

    Consulta nova;
    nova.codigo = total_consultas + 1;
    nova.codigo_paciente = cod_paciente;
    nova.codigo_medico = cod_medico;
    nova.codigo_hospital = cod_hospital;
    strcpy(nova.data, data_escolhida);
    strcpy(nova.horario, horario_escolhido);
    strcpy(nova.status, "Agendada");

    printf("Motivo da consulta: ");
    ler_texto(nova.motivo, sizeof(nova.motivo));
    if (strlen(nova.motivo) == 0) {
        strcpy(nova.motivo, "Consulta de rotina");
    }

    if (idx_agenda != -1) {
        strcpy(agendas[idx_agenda].disponibilidade, "Ocupado");
    } else if (total_agendas < MAX_AGENDAS) {
        AgendaMedica nova_ag;
        nova_ag.codigo = total_agendas + 1;
        nova_ag.codigo_medico = cod_medico;
        strcpy(nova_ag.data_disponivel, data_escolhida);
        strcpy(nova_ag.horario_inicial, horario_escolhido);
        strcpy(nova_ag.horario_final, horario_escolhido);
        strcpy(nova_ag.disponibilidade, "Ocupado");
        agendas[total_agendas] = nova_ag;
        total_agendas++;
    }

    consultas[total_consultas] = nova;
    total_consultas++;

    printf("\n[SUCESSO] Consulta agendada com sucesso! (Codigo da Consulta: %d)\n", nova.codigo);
}

void listar_consultas() {
    printf("\n--- LISTA DE CONSULTAS REGISTRADAS ---\n");

    if (total_consultas == 0) {
        printf("Nenhuma consulta registrada ate o momento.\n");
        return;
    }

    for (int i = 0; i < total_consultas; i++) {
        int idx_pac = buscar_paciente_por_codigo(consultas[i].codigo_paciente);
        int idx_med = buscar_medico_por_codigo(consultas[i].codigo_medico);
        int idx_hosp = buscar_hospital_por_codigo(consultas[i].codigo_hospital);

        char nome_pac[100] = "Desconhecido";
        char nome_med[100] = "Desconhecido";
        char nome_hosp[100] = "Desconhecido";

        if (idx_pac != -1) strcpy(nome_pac, pacientes[idx_pac].nome);
        if (idx_med != -1) strcpy(nome_med, medicos[idx_med].nome);
        if (idx_hosp != -1) strcpy(nome_hosp, hospitais[idx_hosp].nome);

        printf("----------------------------------------\n");
        printf("Codigo da Consulta: %d\n", consultas[i].codigo);
        printf("Paciente:           %s (Codigo: %d)\n", nome_pac, consultas[i].codigo_paciente);
        printf("Medico:             %s (Codigo: %d)\n", nome_med, consultas[i].codigo_medico);
        printf("Hospital:           %s (Codigo: %d)\n", nome_hosp, consultas[i].codigo_hospital);
        printf("Data e Horario:     %s as %s\n", consultas[i].data, consultas[i].horario);
        printf("Motivo:             %s\n", consultas[i].motivo);
        printf("Status:             %s\n", consultas[i].status);
    }
    printf("----------------------------------------\n");
    printf("Total de consultas: %d\n", total_consultas);
}

void confirmar_consulta() {
    printf("\n--- CONFIRMAR CONSULTA ---\n");

    if (total_consultas == 0) {
        printf("Nenhuma consulta cadastrada no sistema.\n");
        return;
    }

    listar_consultas();

    int cod_consulta;
    printf("\nInforme o codigo da consulta que deseja confirmar: ");
    if (scanf("%d", &cod_consulta) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx = buscar_consulta_por_codigo(cod_consulta);
    if (idx == -1) {
        printf("\n[ERRO] Consulta com codigo %d nao encontrada!\n", cod_consulta);
        return;
    }

    if (strcmp(consultas[idx].status, "Agendada") != 0) {
        printf("\n[AVISO] Somente consultas com status 'Agendada' podem ser confirmadas (Status atual: %s).\n",
               consultas[idx].status);
        return;
    }

    strcpy(consultas[idx].status, "Confirmada");
    printf("\n[SUCESSO] A consulta (Codigo: %d) foi confirmada com sucesso!\n", cod_consulta);
}

void reagendar_consulta() {
    printf("\n--- REAGENDAR CONSULTA ---\n");

    if (total_consultas == 0) {
        printf("Nenhuma consulta cadastrada no sistema.\n");
        return;
    }

    listar_consultas();

    int cod_consulta;
    printf("\nInforme o codigo da consulta que deseja reagendar: ");
    if (scanf("%d", &cod_consulta) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx = buscar_consulta_por_codigo(cod_consulta);
    if (idx == -1) {
        printf("\n[ERRO] Consulta com codigo %d nao encontrada!\n", cod_consulta);
        return;
    }

    if (strcmp(consultas[idx].status, "Cancelada") == 0) {
        printf("\n[AVISO] Nao e possivel reagendar uma consulta que ja foi cancelada.\n");
        return;
    }

    int cod_medico = consultas[idx].codigo_medico;
    char nova_data[25];
    char novo_horario[10];

    escolher_dia_semana(nova_data);

    do {
        printf("Informe o novo horario da consulta (HH:MM): ");
        ler_texto(novo_horario, sizeof(novo_horario));
        if (strlen(novo_horario) == 0) {
            printf("[AVISO] O novo horario e obrigatorio!\n");
        }
    } while (strlen(novo_horario) == 0);

    for (int i = 0; i < total_consultas; i++) {
        if (i != idx &&
            consultas[i].codigo_medico == cod_medico &&
            strcmp(consultas[i].data, nova_data) == 0 &&
            strcmp(consultas[i].horario, novo_horario) == 0 &&
            strcmp(consultas[i].status, "Cancelada") != 0) {
            printf("\n[ERRO] Conflito! O medico ja possui outra consulta em %s as %s.\n", nova_data, novo_horario);
            return;
        }
    }

    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo_medico == cod_medico &&
            strcmp(agendas[i].data_disponivel, consultas[idx].data) == 0 &&
            strcmp(agendas[i].horario_inicial, consultas[idx].horario) == 0) {
            strcpy(agendas[i].disponibilidade, "Disponivel");
            break;
        }
    }

    strcpy(consultas[idx].data, nova_data);
    strcpy(consultas[idx].horario, novo_horario);
    strcpy(consultas[idx].status, "Agendada");

    printf("\n[SUCESSO] Consulta (Codigo: %d) reagendada para %s as %s!\n",
           consultas[idx].codigo, consultas[idx].data, consultas[idx].horario);
}

void cancelar_consulta() {
    printf("\n--- CANCELAR CONSULTA ---\n");

    if (total_consultas == 0) {
        printf("Nenhuma consulta cadastrada no sistema.\n");
        return;
    }

    listar_consultas();

    int cod_consulta;
    printf("\nInforme o codigo da consulta que deseja cancelar: ");
    if (scanf("%d", &cod_consulta) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx = buscar_consulta_por_codigo(cod_consulta);
    if (idx == -1) {
        printf("\n[ERRO] Consulta com codigo %d nao encontrada!\n", cod_consulta);
        return;
    }

    if (strcmp(consultas[idx].status, "Cancelada") == 0) {
        printf("\n[AVISO] Esta consulta ja encontra-se cancelada.\n");
        return;
    }

    char confirmacao;
    printf("Tem certeza que deseja cancelar a consulta de codigo %d (%s as %s)? (S/N): ",
           consultas[idx].codigo, consultas[idx].data, consultas[idx].horario);
    scanf(" %c", &confirmacao);
    limpar_buffer();

    if (confirmacao != 'S' && confirmacao != 's') {
        printf("\nOperacao de cancelamento abortada.\n");
        return;
    }

    strcpy(consultas[idx].status, "Cancelada");

    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo_medico == consultas[idx].codigo_medico &&
            strcmp(agendas[i].data_disponivel, consultas[idx].data) == 0 &&
            strcmp(agendas[i].horario_inicial, consultas[idx].horario) == 0) {
            strcpy(agendas[i].disponibilidade, "Disponivel");
            break;
        }
    }

    printf("\n[SUCESSO] Consulta cancelada com sucesso! O horario foi liberado na agenda do medico.\n");
}
