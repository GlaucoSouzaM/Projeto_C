#include <stdio.h>
#include <string.h>
#include "sistema.h"

void consultar_medicos_disponiveis() {
    printf("\n--- MEDICOS DISPONIVEIS PARA CONSULTA ---\n");

    if (total_medicos == 0) {
        printf("Nenhum medico cadastrado no sistema.\n");
        return;
    }

    int encontrou_algum = 0;

    for (int i = 0; i < total_medicos; i++) {
        int horarios_livres = 0;

        for (int j = 0; j < total_agendas; j++) {
            if (agendas[j].codigo_medico == medicos[i].codigo &&
                strcmp(agendas[j].disponibilidade, "Disponivel") == 0) {
                horarios_livres++;
            }
        }

        if (horarios_livres > 0) {
            printf("----------------------------------------\n");
            printf("Codigo:           %d\n", medicos[i].codigo);
            printf("Nome:             %s\n", medicos[i].nome);
            printf("CRM:              %s\n", medicos[i].crm);
            printf("Especialidade:    %s\n", medicos[i].especialidade);
            printf("Horarios livres:  %d\n", horarios_livres);
            encontrou_algum = 1;
        }
    }

    if (!encontrou_algum) {
        printf("Nenhum medico possui horarios disponiveis no momento.\n");
    } else {
        printf("----------------------------------------\n");
    }
}

void consultar_horarios_disponiveis() {
    printf("\n--- HORARIOS DISPONIVEIS PARA AGENDAMENTO ---\n");

    int encontrou = 0;

    for (int i = 0; i < total_agendas; i++) {
        if (strcmp(agendas[i].disponibilidade, "Disponivel") == 0) {
            int idx_med = buscar_medico_por_codigo(agendas[i].codigo_medico);
            char nome_medico[100] = "Desconhecido";
            char especialidade[50] = "-";

            if (idx_med != -1) {
                strcpy(nome_medico, medicos[idx_med].nome);
                strcpy(especialidade, medicos[idx_med].especialidade);
            }

            printf("----------------------------------------\n");
            printf("Codigo da Agenda: %d\n", agendas[i].codigo);
            printf("Medico:           %s (Codigo: %d - %s)\n", nome_medico, agendas[i].codigo_medico, especialidade);
            printf("Dia da semana:    %s\n", agendas[i].data_disponivel);
            printf("Horario:          %s as %s\n", agendas[i].horario_inicial, agendas[i].horario_final);
            printf("Status:           %s\n", agendas[i].disponibilidade);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum horario disponivel cadastrado no momento.\n");
    } else {
        printf("----------------------------------------\n");
    }

    if (total_medicos > 0) {
        char resp;
        printf("\nDeseja cadastrar um novo horario disponivel para um medico? (S/N): ");
        scanf(" %c", &resp);
        limpar_buffer();

        if (resp == 'S' || resp == 's') {
            if (total_agendas >= MAX_AGENDAS) {
                printf("\n[ERRO] Limite maximo de horarios na agenda atingido!\n");
                return;
            }

            int cod_med;
            printf("Informe o codigo do medico: ");
            if (scanf("%d", &cod_med) != 1) {
                printf("\n[ERRO] Codigo invalido!\n");
                limpar_buffer();
                return;
            }
            limpar_buffer();

            int idx_med = buscar_medico_por_codigo(cod_med);
            if (idx_med == -1) {
                printf("\n[ERRO] Medico com codigo %d nao encontrado!\n", cod_med);
                return;
            }

            AgendaMedica nova_agenda;
            nova_agenda.codigo = total_agendas + 1;
            nova_agenda.codigo_medico = cod_med;

            escolher_dia_semana(nova_agenda.data_disponivel);

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

            printf("\n[SUCESSO] Horario (%s) adicionado para o(a) medico(a) %s!\n",
                   nova_agenda.data_disponivel, medicos[idx_med].nome);
        }
    }
}

void consultar_agenda_medica() {
    printf("\n--- CONSULTAR AGENDA MEDICA ---\n");

    if (total_medicos == 0) {
        printf("Nenhum medico cadastrado no sistema.\n");
        return;
    }

    int cod_medico;
    printf("Informe o codigo de identificacao do medico: ");
    if (scanf("%d", &cod_medico) != 1) {
        printf("\n[ERRO] Codigo invalido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx_med = buscar_medico_por_codigo(cod_medico);
    if (idx_med == -1) {
        printf("\n[ERRO] Medico com codigo %d nao encontrado.\n", cod_medico);
        return;
    }

    printf("\nAgenda do(a) Medico(a): %s (CRM: %s - %s)\n",
           medicos[idx_med].nome, medicos[idx_med].crm, medicos[idx_med].especialidade);

    printf("\n[1] Horarios Cadastrados na Agenda:\n");
    int achou_horario = 0;
    for (int i = 0; i < total_agendas; i++) {
        if (agendas[i].codigo_medico == cod_medico) {
            printf("  - Codigo Agenda %d | Dia: %s | Horario: %s as %s | Status: %s\n",
                   agendas[i].codigo, agendas[i].data_disponivel,
                   agendas[i].horario_inicial, agendas[i].horario_final,
                   agendas[i].disponibilidade);
            achou_horario = 1;
        }
    }
    if (!achou_horario) {
        printf("  Nenhum horario registrado na agenda deste medico.\n");
    }

    printf("\n[2] Consultas Associadas ao Medico:\n");
    int achou_consulta = 0;
    for (int i = 0; i < total_consultas; i++) {
        if (consultas[i].codigo_medico == cod_medico) {
            int idx_pac = buscar_paciente_por_codigo(consultas[i].codigo_paciente);
            int idx_hosp = buscar_hospital_por_codigo(consultas[i].codigo_hospital);

            char nome_pac[100] = "Desconhecido";
            char tel_pac[20] = "-";
            char nome_hosp[100] = "Desconhecido";

            if (idx_pac != -1) {
                strcpy(nome_pac, pacientes[idx_pac].nome);
                strcpy(tel_pac, pacientes[idx_pac].telefone);
            }
            if (idx_hosp != -1) {
                strcpy(nome_hosp, hospitais[idx_hosp].nome);
            }

            printf("----------------------------------------\n");
            printf("Codigo da Consulta: %d\n", consultas[i].codigo);
            printf("Data e Horario:     %s as %s\n", consultas[i].data, consultas[i].horario);
            printf("Paciente:           %s (Tel: %s)\n", nome_pac, tel_pac);
            printf("Hospital:           %s\n", nome_hosp);
            printf("Motivo:             %s\n", consultas[i].motivo);
            printf("Status:             %s\n", consultas[i].status);
            achou_consulta = 1;
        }
    }

    if (!achou_consulta) {
        printf("  Nenhuma consulta agendada para este medico ate o momento.\n");
    } else {
        printf("----------------------------------------\n");
    }
}

