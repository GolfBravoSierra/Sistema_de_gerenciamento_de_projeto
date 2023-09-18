#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Data{
    int dia;
    int mes;
    int ano;
};

int recebeData(int *dia, int *mes, int *ano){
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    *dia = tm.tm_mday;
    *mes = tm.tm_mon + 1;
    *ano = tm.tm_year + 1900;
    return 0;
}

struct Tarefa{
    int codigoTarefa;
    char nomeTarefa[30];
    char nomeProjeto[30];
    char dataInicio;
    char dataTermino;
    int status;
};

void menu(){
    printf("1. Adicionar uma nova tarefa\n");
    printf("2. Modificar uma tarefa\n");
    printf("3. Concluir uma tarefa\n");
    printf("4. Atualizacao do status da tarefa\n");
    printf("5. Listar tarefas pendentes\n");
    printf("6. Listar tarefas concluidas\n");
    printf("7. Listar tarefas concluidas com e sem atraso\n");
    printf("8. Sair do programa\n");
}



int main(){

    system("cls");
    menu();

    /// Recebe data atual
    int dd, mm, aa;
    recebeData(&dd, &mm, &aa);
    printf("Data: %d/%d/%d\n", dd, mm, aa);

    return 0;
}