#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "sistema.h"

Paciente pacientes[MAX_PACIENTES];
int total_pacientes = 0;

Medico medicos[MAX_MEDICOS];
int total_medicos = 0;

Hospital hospitais[MAX_HOSPITAIS];
int total_hospitais = 0;

AgendaMedica agendas[MAX_AGENDAS];
int total_agendas = 0;

Consulta consultas[MAX_CONSULTAS];
int total_consultas = 0;

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ler_texto(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

void escolher_dia_semana(char *destino) {
    int op = 0;
    do {
        printf("\nEscolha o dia da semana:\n");
        printf("1 - Segunda-feira\n");
        printf("2 - Terca-feira\n");
        printf("3 - Quarta-feira\n");
        printf("4 - Quinta-feira\n");
        printf("5 - Sexta-feira\n");
        printf("6 - Sabado\n");
        printf("7 - Domingo\n");
        printf("Opcao: ");
        if (scanf("%d", &op) != 1) {
            printf("[ERRO] Digite um numero de 1 a 7!\n");
            limpar_buffer();
            op = 0;
            continue;
        }
        limpar_buffer();

        switch (op) {
            case 1: strcpy(destino, "Segunda-feira"); break;
            case 2: strcpy(destino, "Terca-feira"); break;
            case 3: strcpy(destino, "Quarta-feira"); break;
            case 4: strcpy(destino, "Quinta-feira"); break;
            case 5: strcpy(destino, "Sexta-feira"); break;
            case 6: strcpy(destino, "Sabado"); break;
            case 7: strcpy(destino, "Domingo"); break;
            default:
                printf("[AVISO] Opcao invalida! Escolha entre 1 e 7.\n");
                op = 0;
                break;
        }
    } while (op < 1 || op > 7);
}

void menu_cadastros() {
    int sub = -1;
    do {
        printf("\n----------------------------------------\n");
        printf("            MENU DE CADASTROS\n");
        printf("----------------------------------------\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Cadastrar medico\n");
        printf("3 - Cadastrar hospital\n");
        printf("0 - Voltar ao menu principal\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &sub) != 1) {
            printf("\n[ERRO] Entrada invalida! Digite um numero.\n");
            limpar_buffer();
            sub = -1;
            continue;
        }
        limpar_buffer();

        switch (sub) {
            case 1:
                cadastrar_paciente();
                salvaDadosNoArquivo();
                break;
            case 2:
                cadastrar_medico();
                salvaDadosNoArquivo();
                break;
            case 3:
                cadastrar_hospital();
                salvaDadosNoArquivo();
                break;
            case 0:
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
                break;
        }
    } while (sub != 0);
}

void menu_listagens() {
    int sub = -1;
    do {
        printf("\n----------------------------------------\n");
        printf("       MENU DE LISTAGENS E AGENDA\n");
        printf("----------------------------------------\n");
        printf("1 - Listar pacientes cadastrados\n");
        printf("2 - Listar medicos cadastrados\n");
        printf("3 - Listar hospitais cadastrados\n");
        printf("4 - Consultar medicos disponiveis\n");
        printf("5 - Consultar horarios disponiveis\n");
        printf("6 - Consultar agenda medica\n");
        printf("0 - Voltar ao menu principal\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &sub) != 1) {
            printf("\n[ERRO] Entrada invalida! Digite um numero.\n");
            limpar_buffer();
            sub = -1;
            continue;
        }
        limpar_buffer();

        switch (sub) {
            case 1:
                listar_pacientes();
                break;
            case 2:
                listar_medicos();
                break;
            case 3:
                listar_hospitais();
                break;
            case 4:
                consultar_medicos_disponiveis();
                break;
            case 5:
                consultar_horarios_disponiveis();
                salvaDadosNoArquivo();
                break;
            case 6:
                consultar_agenda_medica();
                break;
            case 0:
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
                break;
        }
    } while (sub != 0);
}

void menu_consultas() {
    int sub = -1;
    do {
        printf("\n----------------------------------------\n");
        printf("            MENU DE CONSULTAS\n");
        printf("----------------------------------------\n");
        printf("1 - Agendar consulta\n");
        printf("2 - Listar consultas agendadas\n");
        printf("3 - Confirmar consulta\n");
        printf("4 - Reagendar consulta\n");
        printf("5 - Cancelar consulta\n");
        printf("0 - Voltar ao menu principal\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &sub) != 1) {
            printf("\n[ERRO] Entrada invalida! Digite um numero.\n");
            limpar_buffer();
            sub = -1;
            continue;
        }
        limpar_buffer();

        switch (sub) {
            case 1:
                agendar_consulta();
                salvaDadosNoArquivo();
                break;
            case 2:
                listar_consultas();
                break;
            case 3:
                confirmar_consulta();
                salvaDadosNoArquivo();
                break;
            case 4:
                reagendar_consulta();
                salvaDadosNoArquivo();
                break;
            case 5:
                cancelar_consulta();
                salvaDadosNoArquivo();
                break;
            case 0:
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
                break;
        }
    } while (sub != 0);
}

void exibir_menu() {
    printf("\n========================================\n");
    printf("   SISTEMA DE AGENDAMENTO DE CONSULTAS\n");
    printf("========================================\n");
    printf("1 - Cadastros (Paciente, Medico, Hospital)\n");
    printf("2 - Consultas (Agendar, Confirmar, Cancelar...)\n");
    printf("3 - Listagens e Agenda Medica\n");
    printf("0 - Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao = -1;

    carregaDadosDoArquivo();

    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida! Digite um numero.\n");
            limpar_buffer();
            opcao = -1;
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                menu_cadastros();
                break;
            case 2:
                menu_consultas();
                break;
            case 3:
                menu_listagens();
                break;
            case 0:
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Escolha entre 0 e 3.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
