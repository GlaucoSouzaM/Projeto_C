#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "sistema.h"

// ============================================================================
// DEFINIÇÃO DOS VETORES GLOBAIS E CONTADORES
// ============================================================================

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

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lê uma string com espaços usando fgets e remove o '\n' do final
void ler_texto(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

void exibir_menu() {
    printf("\n========================================\n");
    printf("   SISTEMA DE AGENDAMENTO DE CONSULTAS\n");
    printf("========================================\n");
    printf("1  - Cadastrar paciente\n");
    printf("2  - Cadastrar medico\n");
    printf("3  - Cadastrar hospital\n");
    printf("4  - Consultar medicos disponiveis\n");
    printf("5  - Consultar horarios disponiveis\n");
    printf("6  - Agendar consulta\n");
    printf("7  - Listar consultas agendadas\n");
    printf("8  - Confirmar consulta\n");
    printf("9  - Reagendar consulta\n");
    printf("10 - Cancelar consulta\n");
    printf("11 - Consultar agenda medica\n");
    printf("12 - Listar pacientes cadastrados\n");
    printf("13 - Listar medicos cadastrados\n");
    printf("14 - Listar hospitais cadastrados\n");
    printf("0  - Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

// ============================================================================
// FUNÇÃO PRINCIPAL (MAIN)
// ============================================================================

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao = -1;

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
                cadastrar_paciente();
                break;
            case 2:
                cadastrar_medico();
                break;
            case 3:
                cadastrar_hospital();
                break;
            case 4:
                printf("\n[Opcao 4] Consultar medicos disponiveis (Em construcao...)\n");
                break;
            case 5:
                printf("\n[Opcao 5] Consultar horarios disponiveis (Em construcao...)\n");
                break;
            case 6:
                printf("\n[Opcao 6] Agendar consulta (Em construcao...)\n");
                break;
            case 7:
                printf("\n[Opcao 7] Listar consultas agendadas (Em construcao...)\n");
                break;
            case 8:
                printf("\n[Opcao 8] Confirmar consulta (Em construcao...)\n");
                break;
            case 9:
                printf("\n[Opcao 9] Reagendar consulta (Em construcao...)\n");
                break;
            case 10:
                printf("\n[Opcao 10] Cancelar consulta (Em construcao...)\n");
                break;
            case 11:
                printf("\n[Opcao 11] Consultar agenda medica (Em construcao...)\n");
                break;
            case 12:
                listar_pacientes();
                break;
            case 13:
                listar_medicos();
                break;
            case 14:
                listar_hospitais();
                break;
            case 0:
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Escolha entre 0 e 14.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
