#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void selecionaMenu(); // protótipo da função

void menu(){
    printf("1. Adicionar uma nova tarefa\n");
    printf("2. Modificar uma tarefa\n");
    printf("3. Concluir uma tarefa\n");
    printf("4. Atualizacao do status da tarefa\n");
    printf("5. Listar tarefas pendentes\n");
    printf("6. Listar tarefas concluidas\n");
    printf("7. Listar tarefas concluidas com e sem atraso\n");
    printf("8. Sair do programa\n");
    selecionaMenu();
}


/// Inicio do bloco para receber a data do sistema
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
/// Fim do bloco para receber data

 typedef struct Tarefa{
    int codigoTarefa;
    char nomeTarefa;
    char nomeProjeto;
    int dataInicio_dia;
    int dataInicio_mes;
    int dataInicio_ano;
    int dataTermino_dia;
    int dataTermino_mes;
    int dataTermino_ano;
    int status;
} Tarefa;

// struct no da fila 
typedef struct No{
    Tarefa tarefa;
    struct No *prox;
} No;

//struct fila
typedef struct Fila{
    No *ini;
    No *fim;
} Fila;

//função cria fila
Fila *criaFila(){
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    fila->ini = NULL;
    fila->fim = NULL;
    return fila;
}

//função para inserir no fim da fila
No* ins_fim(No* fim, Tarefa A){
    No* p = (No*)
    malloc(sizeof(No));
    p->tarefa=A;
    p->prox = NULL;
    if(fim!= NULL) /*verifica se lista nao estiver vazia*/
    fim->prox=p;
    return p;
}
/*
//função para modificar uma tarefa
Tarefa modificatarefa(Tarefa tarefa , int codigotarefa){
    int flag = 0;
    while(flag != 1){
        if(tarefa.codigoTarefa == codigotarefa){
            printf("\nDigite o nome da tarefa: ");
            scanf("%s", &tarefa.nomeTarefa);
            printf("\nDigite o nome do projeto: ");
            scanf("%s", &tarefa.nomeProjeto);
            printf("\ndigite a data de inicio: (dia/mes/ano):\n");
            do{
                printf("\nDigite o dia: ");
                scanf("%d", &tarefa.dataInicio_dia);
                }while(tarefa.dataInicio_dia > 31 || tarefa.dataInicio_dia < 1);
            do{
                printf("\nDigite o mes: ");
                scanf("%d", &tarefa.dataInicio_mes);
                }while(tarefa.dataInicio_mes > 12 || tarefa.dataInicio_mes < 1);
                printf("\nDigite o ano: ");
                scanf("%d", &tarefa.dataInicio_ano);
            printf("\nData de inicio da tarefa: %d/%d/%d", tarefa.dataInicio_dia, tarefa.dataInicio_mes, tarefa.dataInicio_ano);

            printf("\ndigite a data de termino: (dia/mes/ano)\n");
            do{
                printf("\nDigite o dia: ");
                scanf("%d", &tarefa.dataTermino_dia);
                }while(tarefa.dataTermino_dia > 31 || tarefa.dataTermino_dia < 1);
            do{
                printf("\nDigite o mes: ");
                scanf("%d", &tarefa.dataTermino_mes);
                }while(tarefa.dataTermino_mes > 12 || tarefa.dataTermino_mes < 1);
                printf("\nDigite o ano: ");
            scanf("%d", &tarefa.dataTermino_ano);
            printf("\nData de termino da tarefa: %d/%d/%d", tarefa.dataTermino_dia, tarefa.dataTermino_mes, tarefa.dataTermino_ano);

            flag = 1;
            return tarefa;
        }
        else{
            

            flag = 1;
        }
    }


    return tarefa;
}
*/
//função para criar uma nova tarefa
Tarefa novatarefa(){
    Tarefa tarefa;
    printf("\nDigite o codigo da tarefa: ");
    scanf("%d", &tarefa.codigoTarefa);
    printf("\nDigite o nome da tarefa: ");
    scanf("%s", &tarefa.nomeTarefa);
    printf("\nDigite o nome do projeto: ");
    scanf("%s", &tarefa.nomeProjeto);
    printf("\ndigite a data de inicio: (dia/mes/ano):\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataInicio_dia);
        }while(tarefa.dataInicio_dia > 31 || tarefa.dataInicio_dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataInicio_mes);
        }while(tarefa.dataInicio_mes > 12 || tarefa.dataInicio_mes < 1);
        printf("\nDigite o ano: ");
        scanf("%d", &tarefa.dataInicio_ano);
    printf("\nData de inicio da tarefa: %d/%d/%d", tarefa.dataInicio_dia, tarefa.dataInicio_mes, tarefa.dataInicio_ano);
    
    printf("\ndigite a data de termino: (dia/mes/ano)\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataTermino_dia);
        }while(tarefa.dataTermino_dia > 31 || tarefa.dataTermino_dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataTermino_mes);
        }while(tarefa.dataTermino_mes > 12 || tarefa.dataTermino_mes < 1);
        printf("\nDigite o ano: ");
    scanf("%d", &tarefa.dataTermino_ano);
    printf("\nData de termino da tarefa: %d/%d/%d", tarefa.dataTermino_dia, tarefa.dataTermino_mes, tarefa.dataTermino_ano);
    return tarefa;
};

//função para inserina uma tarefa na fila
void insereFila(Fila* fila, Tarefa tarefa){
    fila->fim=ins_fim(fila->fim,tarefa);
    if(fila->ini==NULL)/*fila antes vazia?*/
    fila->ini=fila->fim;
    menu();
};

void selecionaMenu(){
    Fila *fila = criaFila();
    int opcao;
    scanf("%d", &opcao);
    system("cls");
    Tarefa tarefa;
    int codigo;
    switch(opcao){
        case 1:
            printf("Adicionar uma nova tarefa\n");
            tarefa = novatarefa();
            insereFila(fila , tarefa);
        case 2:
            printf("Modificar uma tarefa\nDigite o codigo da tarefa: ");
            scanf("%d", &codigo);
            tarefa = modificatarefa(tarefa, codigo);
            break;
        case 3:
            printf("Concluir uma tarefa\n");
            break;
        case 4:
            printf("Atualizacao do status da tarefa\n");
            break;
        case 5:
            printf("Listar tarefas pendentes\n");
            break;
        case 6:
            printf("Listar tarefas concluidas\n");
            break;
        case 7:
            printf("Listar tarefas concluidas com e sem atraso\n");
            break;
        case 8:
            printf("Sair do programa\n");
            break;
        default:
            printf("Opcao invalida\n");
            selecionaMenu();
            break;
    }
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