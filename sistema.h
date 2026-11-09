#ifndef SISTEMA_H
#define SISTEMA_H

// Limites máximos de armazenamento em arrays
#define MAX_PACIENTES 100
#define MAX_MEDICOS 50
#define MAX_HOSPITAIS 20
#define MAX_AGENDAS 200
#define MAX_CONSULTAS 200

// STRUCTS

typedef struct {
    int codigo;
    char nome[100];
    char cpf[20];
    char data_nascimento[15];
    char telefone[20];
    char email[100];
    char endereco[150];
} Paciente;

typedef struct {
    int codigo;
    char nome[100];
    char crm[20];
    char especialidade[50];
    char telefone[20];
    char email[100];
} Medico;

typedef struct {
    int codigo;
    char nome[100];
    char cnpj[25];
    char endereco[150];
    char telefone[20];
} Hospital;

typedef struct {
    int codigo;
    int codigo_medico;
    char data_disponivel[15];
    char horario_inicial[10];
    char horario_final[10];
    char disponibilidade[20]; // "Disponivel" ou "Ocupado"
} AgendaMedica;

typedef struct {
    int codigo;
    int codigo_paciente;
    int codigo_medico;
    int codigo_hospital;
    char data[15];
    char horario[10];
    char status[20]; // "Agendada", "Confirmada", "Cancelada", "Realizada"
    char motivo[200];
} Consulta;

// VETORES GLOBAIS

extern Paciente pacientes[MAX_PACIENTES];
extern int total_pacientes;

extern Medico medicos[MAX_MEDICOS];
extern int total_medicos;

extern Hospital hospitais[MAX_HOSPITAIS];
extern int total_hospitais;

extern AgendaMedica agendas[MAX_AGENDAS];
extern int total_agendas;

extern Consulta consultas[MAX_CONSULTAS];
extern int total_consultas;

// ============================================================================
// PROTÓTIPOS DAS FUNÇÕES
// ============================================================================

// Funções utilitárias (em main.c)
void limpar_buffer();
void ler_texto(char *destino, int tamanho);

// Funções de Paciente (em paciente.c)
void cadastrar_paciente();
void listar_pacientes();
int buscar_paciente_por_codigo(int codigo);

// Funções de Médico (em medico.c)
void cadastrar_medico();
void listar_medicos();
int buscar_medico_por_codigo(int codigo);

// Funções de Hospital (em hospital.c)
void cadastrar_hospital();
void listar_hospitais();
int buscar_hospital_por_codigo(int codigo);

#endif

