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
        printf("\n[AVISO] Nenhum paciente cadastrado. Cadastre um paciente primeiro (Opcao 1).\n");
        return;
    }

    if (total_medicos == 0) {
        printf("\n[AVISO] Nenhum medico cadastrado. Cadastre um medico primeiro (Opcao 2).\n");
        return;
    }

    if (total_hospitais == 0) {
        printf("\n[AVISO] Nenhum hospital cadastrado. Cadastre um hospital primeiro (Opcao 3).\n");
        return;
    }

    int cod_paciente;
    printf("Informe o codigo do paciente: ");
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

    printf("\nHorarios disponiveis na agenda do(a) Dr(a). %s:\n", medicos[idx_med].nome);
    int horarios_livres = 0;
    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo_medico == cod_medico &&
            strcmp(agendas[i].disponibilidade, "Disponivel") == 0) {
            printf("  Codigo Agenda: %d | Data: %s | Horario: %s as %s\n",
                   agendas[i].codigo, agendas[i].data_disponivel,
                   agendas[i].horario_inicial, agendas[i].horario_final);
            horarios_livres++;
        }
    }

    if (horarios_livres == 0) {
        printf("  [AVISO] Este medico nao possui horarios disponiveis na agenda.\n");
        return;
    }

    int cod_agenda;
    printf("\nInforme o Codigo da Agenda referente ao horario desejado: ");
    if (scanf("%d", &cod_agenda) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx_agenda = -1;
    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo == cod_agenda &&
            agendas[i].codigo_medico == cod_medico &&
            strcmp(agendas[i].disponibilidade, "Disponivel") == 0) {
            idx_agenda = i;
            break;
        }
    }

    if (idx_agenda == -1) {
        printf("\n[ERRO] Horario da agenda invalido ou nao esta disponivel!\n");
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

    for (int i = 0; i < total_consultas; i++) {
        if (consultas[i].codigo_medico == cod_medico &&
            strcmp(consultas[i].data, agendas[idx_agenda].data_disponivel) == 0 &&
            strcmp(consultas[i].horario, agendas[idx_agenda].horario_inicial) == 0 &&
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
    strcpy(nova.data, agendas[idx_agenda].data_disponivel);
    strcpy(nova.horario, agendas[idx_agenda].horario_inicial);
    strcpy(nova.status, "Agendada");

    printf("Motivo da consulta: ");
    ler_texto(nova.motivo, sizeof(nova.motivo));
    if (strlen(nova.motivo) == 0) {
        strcpy(nova.motivo, "Consulta de rotina");
    }

    strcpy(agendas[idx_agenda].disponibilidade, "Ocupado");

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

    int cod_consulta;
    printf("Informe o codigo da consulta que deseja confirmar: ");
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

    int cod_consulta;
    printf("Informe o codigo da consulta que deseja reagendar: ");
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
    int idx_med = buscar_medico_por_codigo(cod_medico);

    printf("\nHorarios disponiveis na agenda do(a) medico(a) %s:\n",
           idx_med != -1 ? medicos[idx_med].nome : "Desconhecido");

    int horarios_livres = 0;
    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo_medico == cod_medico &&
            strcmp(agendas[i].disponibilidade, "Disponivel") == 0) {
            printf("  Codigo Agenda: %d | Data: %s | Horario: %s as %s\n",
                   agendas[i].codigo, agendas[i].data_disponivel,
                   agendas[i].horario_inicial, agendas[i].horario_final);
            horarios_livres++;
        }
    }

    if (horarios_livres == 0) {
        printf("  [AVISO] Nao ha outros horarios disponiveis na agenda deste medico para reagendamento.\n");
        return;
    }

    int cod_nova_agenda;
    printf("\nInforme o Codigo da Agenda para a nova data e horario: ");
    if (scanf("%d", &cod_nova_agenda) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx_nova_agenda = -1;
    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo == cod_nova_agenda &&
            agendas[i].codigo_medico == cod_medico &&
            strcmp(agendas[i].disponibilidade, "Disponivel") == 0) {
            idx_nova_agenda = i;
            break;
        }
    }

    if (idx_nova_agenda == -1) {
        printf("\n[ERRO] Codigo da agenda invalido ou horario indisponivel!\n");
        return;
    }

    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo_medico == cod_medico &&
            strcmp(agendas[i].data_disponivel, consultas[idx].data) == 0 &&
            strcmp(agendas[i].horario_inicial, consultas[idx].horario) == 0) {
            strcpy(agendas[i].disponibilidade, "Disponivel");
            break;
        }
    }

    strcpy(agendas[idx_nova_agenda].disponibilidade, "Ocupado");
    strcpy(consultas[idx].data, agendas[idx_nova_agenda].data_disponivel);
    strcpy(consultas[idx].horario, agendas[idx_nova_agenda].horario_inicial);
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

    int cod_consulta;
    printf("Informe o codigo da consulta que deseja cancelar: ");
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

