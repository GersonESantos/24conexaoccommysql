#include <stdio.h>
#include <string.h>
#include <mysql.h>

// Definição da struct aluno
typedef struct {
    char nome[255];
    int matricula;
    int anoIngresso;
    char curso[100];
} aluno;

// Função para imprimir os dados do aluno
void Imprimealuno(aluno alunoRecebido) {
    printf("\n\n --------- Lendo os dados da TAD aluno - struct ---------\n\n");
    printf("Nome: %s", alunoRecebido.nome);
    printf("Matricula: %d \n", alunoRecebido.matricula);
    printf("Ano de Ingresso: %d\n", alunoRecebido.anoIngresso);
    printf("Curso: %s", alunoRecebido.curso);
}

// Função para gravar os dados do aluno no banco de dados
void GravaalunoNoBanco(MYSQL *conexao, aluno alunoRecebido) {
    char query[1000]; // Buffer para armazenar a consulta SQL

    // Cria a string da consulta SQL
    snprintf(query, sizeof(query),
             "INSERT INTO aluno (nome, matricula, anoIngresso, curso) VALUES ('%s', %d, %d, '%s')",
             alunoRecebido.nome, alunoRecebido.matricula, alunoRecebido.anoIngresso, alunoRecebido.curso);

    // Executa a consulta SQL
    if (mysql_query(conexao, query)) {
        printf("Erro ao inserir os dados: %s\n", mysql_error(conexao));
    } else {
        printf("Dados gravados no banco de dados com sucesso!\n");
    }
}

int main() {
    // Variável para a conexão com o MySQL
    MYSQL conexao;
    mysql_init(&conexao); // Inicializa a estrutura de conexão

    // Conexão ao banco de dados
    if (mysql_real_connect(&conexao, "localhost", "root", "Gabibi89*", "alunodb", 3306, NULL, 0)) {
        printf("\nConexão ao banco realizada com sucesso!\n");
    } else {
        printf("Falha de conexão: %s\n", mysql_error(&conexao));
        return 1;
    }

    // Definição da variável aluno usando a struct aluno
    aluno alunoTeste;

    printf("Nome do aluno: ");
    fflush(stdin);
    fgets(alunoTeste.nome, 255, stdin);
    alunoTeste.nome[strcspn(alunoTeste.nome, "\n")] = 0; // Remove a nova linha do final da string

    printf("Matricula: ");
    scanf("%d", &alunoTeste.matricula);

    printf("Ano de Ingresso: ");
    scanf("%d", &alunoTeste.anoIngresso);

    printf("Curso: ");
    fflush(stdin);
    fgets(alunoTeste.curso, 100, stdin);
    alunoTeste.curso[strcspn(alunoTeste.curso, "\n")] = 0; // Remove a nova linha do final da string

    // Chamada da função para imprimir os dados do aluno
    Imprimealuno(alunoTeste);

    // Chamada da função para gravar os dados no banco de dados
    GravaalunoNoBanco(&conexao, alunoTeste);

    // Fecha a conexão com o banco de dados
    mysql_close(&conexao);

    return 0;
}
