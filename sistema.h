#ifndef SISTEMA_H
#define SISTEMA_H

#define MAX_PACIENTES 100
#define MAX_MEDICOS 50
#define MAX_HOSPITAIS 20
#define MAX_AGENDAS 200
#define MAX_CONSULTAS 200

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
    char disponibilidade[20];
} AgendaMedica;

typedef struct {
    int codigo;
    int codigo_paciente;
    int codigo_medico;
    int codigo_hospital;
    char data[15];
    char horario[10];
    char status[20];
    char motivo[200];
} Consulta;

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

void limpar_buffer();
void ler_texto(char *destino, int tamanho);

void cadastrar_paciente();
void listar_pacientes();
int buscar_paciente_por_codigo(int codigo);

void cadastrar_medico();
void listar_medicos();
int buscar_medico_por_codigo(int codigo);

void cadastrar_hospital();
void listar_hospitais();
int buscar_hospital_por_codigo(int codigo);

void consultar_medicos_disponiveis();
void consultar_horarios_disponiveis();
void consultar_agenda_medica();

void agendar_consulta();
void listar_consultas();
void confirmar_consulta();
void reagendar_consulta();
void cancelar_consulta();
int buscar_consulta_por_codigo(int codigo);

#endif
