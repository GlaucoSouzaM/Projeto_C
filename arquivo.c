#include <stdio.h>
#include <string.h>
#include "sistema.h"

void salvaDadosNoArquivo() {
    FILE *fp;
    int i;

    fp = fopen("pacientes.txt", "w");
    if (fp != 0) {
        for (i = 0; i < total_pacientes; i++) {
            fprintf(fp, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n",
                    pacientes[i].codigo,
                    pacientes[i].nome,
                    pacientes[i].cpf,
                    pacientes[i].data_nascimento,
                    pacientes[i].telefone,
                    strlen(pacientes[i].email) > 0 ? pacientes[i].email : "-",
                    strlen(pacientes[i].endereco) > 0 ? pacientes[i].endereco : "-");
        }
        fclose(fp);
    }

    fp = fopen("medicos.txt", "w");
    if (fp != 0) {
        for (i = 0; i < total_medicos; i++) {
            fprintf(fp, "%d\n%s\n%s\n%s\n%s\n%s\n",
                    medicos[i].codigo,
                    medicos[i].nome,
                    medicos[i].crm,
                    medicos[i].especialidade,
                    strlen(medicos[i].telefone) > 0 ? medicos[i].telefone : "-",
                    strlen(medicos[i].email) > 0 ? medicos[i].email : "-");
        }
        fclose(fp);
    }

    fp = fopen("hospitais.txt", "w");
    if (fp != 0) {
        for (i = 0; i < total_hospitais; i++) {
            fprintf(fp, "%d\n%s\n%s\n%s\n%s\n",
                    hospitais[i].codigo,
                    hospitais[i].nome,
                    strlen(hospitais[i].cnpj) > 0 ? hospitais[i].cnpj : "-",
                    hospitais[i].endereco,
                    strlen(hospitais[i].telefone) > 0 ? hospitais[i].telefone : "-");
        }
        fclose(fp);
    }

    fp = fopen("agendas.txt", "w");
    if (fp != 0) {
        for (i = 0; i < total_agendas; i++) {
            fprintf(fp, "%d\n%d\n%s\n%s\n%s\n%s\n",
                    agendas[i].codigo,
                    agendas[i].codigo_medico,
                    agendas[i].data_disponivel,
                    agendas[i].horario_inicial,
                    agendas[i].horario_final,
                    agendas[i].disponibilidade);
        }
        fclose(fp);
    }

    fp = fopen("consultas.txt", "w");
    if (fp != 0) {
        for (i = 0; i < total_consultas; i++) {
            fprintf(fp, "%d\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n",
                    consultas[i].codigo,
                    consultas[i].codigo_paciente,
                    consultas[i].codigo_medico,
                    consultas[i].codigo_hospital,
                    consultas[i].data,
                    consultas[i].horario,
                    consultas[i].status,
                    consultas[i].motivo);
        }
        fclose(fp);
    }
}

void carregaDadosDoArquivo() {
    FILE *fp;
    int i;
    int ret;

    fp = fopen("pacientes.txt", "r");
    if (fp != 0) {
        total_pacientes = 0;
        for (i = 0; i < MAX_PACIENTES; i++) {
            ret = fscanf(fp, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
                         &pacientes[i].codigo,
                         pacientes[i].nome,
                         pacientes[i].cpf,
                         pacientes[i].data_nascimento,
                         pacientes[i].telefone,
                         pacientes[i].email,
                         pacientes[i].endereco);
            if (ret == EOF || ret != 7) {
                break;
            }
            total_pacientes++;
        }
        fclose(fp);
    }

    fp = fopen("medicos.txt", "r");
    if (fp != 0) {
        total_medicos = 0;
        for (i = 0; i < MAX_MEDICOS; i++) {
            ret = fscanf(fp, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
                         &medicos[i].codigo,
                         medicos[i].nome,
                         medicos[i].crm,
                         medicos[i].especialidade,
                         medicos[i].telefone,
                         medicos[i].email);
            if (ret == EOF || ret != 6) {
                break;
            }
            total_medicos++;
        }
        fclose(fp);
    }

    fp = fopen("hospitais.txt", "r");
    if (fp != 0) {
        total_hospitais = 0;
        for (i = 0; i < MAX_HOSPITAIS; i++) {
            ret = fscanf(fp, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
                         &hospitais[i].codigo,
                         hospitais[i].nome,
                         hospitais[i].cnpj,
                         hospitais[i].endereco,
                         hospitais[i].telefone);
            if (ret == EOF || ret != 5) {
                break;
            }
            total_hospitais++;
        }
        fclose(fp);
    }

    fp = fopen("agendas.txt", "r");
    if (fp != 0) {
        total_agendas = 0;
        for (i = 0; i < MAX_AGENDAS; i++) {
            ret = fscanf(fp, "%d\n%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
                         &agendas[i].codigo,
                         &agendas[i].codigo_medico,
                         agendas[i].data_disponivel,
                         agendas[i].horario_inicial,
                         agendas[i].horario_final,
                         agendas[i].disponibilidade);
            if (ret == EOF || ret != 6) {
                break;
            }
            total_agendas++;
        }
        fclose(fp);
    }

    fp = fopen("consultas.txt", "r");
    if (fp != 0) {
        total_consultas = 0;
        for (i = 0; i < MAX_CONSULTAS; i++) {
            ret = fscanf(fp, "%d\n%d\n%d\n%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
                         &consultas[i].codigo,
                         &consultas[i].codigo_paciente,
                         &consultas[i].codigo_medico,
                         &consultas[i].codigo_hospital,
                         consultas[i].data,
                         consultas[i].horario,
                         consultas[i].status,
                         consultas[i].motivo);
            if (ret == EOF || ret != 8) {
                break;
            }
            total_consultas++;
        }
        fclose(fp);
    }
}
