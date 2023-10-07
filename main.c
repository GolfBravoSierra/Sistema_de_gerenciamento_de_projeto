#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/// struct de data
typedef struct Data{
    int dia;
    int mes;
    int ano;
} Data;

/// Estrutura da tarefa
 typedef struct Tarefa{
    int codigoTarefa;
    char nomeTarefa[30];
    char nomeProjeto[30];
    Data dataInicio;
    Data dataTermino;
    int status;
} Tarefa;

/// Estrutura No da fila 
typedef struct No{
    Tarefa tarefa;
    struct No *prox;
} No;

/// Estrutura fila
typedef struct Fila{
    No *ini;
    No *fim;
} Fila;

//struct de lista encadeada
typedef struct Lista{
    Tarefa tarefa;
    struct Lista *prox;
}lista;

// protótipo da função menu
void menu();

// protótipo para função coclui tarefa
Tarefa ConcluirTarefa(Fila *fila);

// protótipo para função retira da fila
Tarefa retiraFila(Fila *fila);

//protótipo para receber a data do sistema
int recebeData(int *dia, int *mes, int *ano);



/// Função cria fila
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

//função para modificar uma tarefa
Tarefa modificatarefa (int codigotarefa){
   // int flag = 0;
    Tarefa tarefa;
    tarefa.codigoTarefa = codigotarefa;
    while (getchar() != '\n');
    printf("\nDigite o nome da tarefa: ");
    gets(tarefa.nomeTarefa);
    printf("\nDigite o nome do projeto: ");
    gets(tarefa.nomeProjeto);
    printf("\ndigite a data de inicio: (dia/mes/ano):\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataInicio.dia);
        }while(tarefa.dataInicio.dia > 31 || tarefa.dataInicio.dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataInicio.mes);
        }while(tarefa.dataInicio.mes > 12 || tarefa.dataInicio.mes < 1);
        printf("\nDigite o ano: ");
        scanf("%d", &tarefa.dataInicio.ano);
    printf("\nData de inicio da tarefa: %d/%d/%d", tarefa.dataInicio.ano, tarefa.dataInicio.ano, tarefa.dataInicio.ano);
    
    printf("\ndigite a data de termino: (dia/mes/ano)\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataTermino.dia);
        }while(tarefa.dataTermino.dia > 31 || tarefa.dataTermino.dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataTermino.mes);
        }while(tarefa.dataTermino.mes > 12 || tarefa.dataTermino.mes < 1);
        printf("\nDigite o ano: ");
    scanf("%d", &tarefa.dataTermino.ano);
    printf("\nData de termino da tarefa: %d/%d/%d", tarefa.dataTermino.dia, tarefa.dataTermino.mes, tarefa.dataTermino.ano);
    
    return tarefa;
}

//função para criar uma nova tarefa
Tarefa novatarefa(){
    Tarefa tarefa;
    printf("\nDigite o codigo da tarefa: ");
    scanf("%d", &tarefa.codigoTarefa);
    while (getchar() != '\n');
    printf("\nDigite o nome da tarefa: ");
    gets(tarefa.nomeTarefa);
    printf("\nDigite o nome do projeto: ");
    gets(tarefa.nomeProjeto);
    printf("\ndigite a data de inicio: (dia/mes/ano):\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataInicio.dia);
        }while(tarefa.dataInicio.dia > 31 || tarefa.dataInicio.dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataInicio.mes);
        }while(tarefa.dataInicio.mes > 12 || tarefa.dataInicio.mes < 1);
        printf("\nDigite o ano: ");
        scanf("%d", &tarefa.dataInicio.ano);
    printf("\nData de inicio da tarefa: %d/%d/%d", tarefa.dataInicio.dia, tarefa.dataInicio.mes, tarefa.dataInicio.ano);
    
    printf("\ndigite a data de termino: (dia/mes/ano)\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataTermino.dia);
        }while(tarefa.dataTermino.dia > 31 || tarefa.dataTermino.dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataTermino.mes);
        }while(tarefa.dataTermino.mes > 12 || tarefa.dataTermino.mes < 1);
        printf("\nDigite o ano: ");
    scanf("%d", &tarefa.dataTermino.ano);
    printf("\nData de termino da tarefa: %d/%d/%d", tarefa.dataTermino.dia, tarefa.dataTermino.mes, tarefa.dataTermino.ano);
    return tarefa;
};

//função para inserina uma tarefa na fila
void insereFila(Fila* fila, Tarefa tarefa){
    fila->fim=ins_fim(fila->fim,tarefa);
    if(fila->ini==NULL)/*fila antes vazia?*/
    fila->ini=fila->fim;
};


/// Busca o codigo na fila
Fila *trocatarefa(Fila *fila , int codigotarefa , Tarefa tarefa){

    No *aux = fila->ini;
    while(aux != NULL){
        if(aux->tarefa.codigoTarefa == codigotarefa){
            printf("Tarefa encontrada\n");

            aux->tarefa = tarefa;
        }
        aux = aux->prox;
    }
    
    return fila;
    menu();
}

/// Imprime a fila inteira
void imprimeFila(Fila *fila){
    No *aux = fila->ini;
    while(aux != NULL){
        printf("Codigo da tarefa: %d\n", aux->tarefa.codigoTarefa);
        printf("Nome da tarefa: %s\n", aux->tarefa.nomeTarefa);
        printf("Nome do projeto: %s\n", aux->tarefa.nomeProjeto);
        printf("Data de inicio da tarefa: %2d/%2d/%2d\n", aux->tarefa.dataInicio.dia, aux->tarefa.dataInicio.mes, aux->tarefa.dataInicio.ano);
        printf("Data de termino da tarefa: %2d/%2d/%2d\n", aux->tarefa.dataTermino.dia, aux->tarefa.dataTermino.mes, aux->tarefa.dataTermino.ano);
        printf("Status da tarefa: %d\n", aux->tarefa.status);
        printf("\n");
        aux = aux->prox;
    }
}

int main(){

    int i = 0;
    Fila *fila = criaFila();
    Tarefa tarefa;
    int codigo;
    
while(i == 0){
    menu();
    int opcao = 0;
    scanf("%d", &opcao);
    system("cls");
    switch(opcao){
        case 1:
        /// Cria uma nova tarefa e insere na fila
            printf("\nAdicionar uma nova tarefa\n");
            tarefa = novatarefa();
            insereFila(fila , tarefa);
            imprimeFila(fila);
            break;
        case 2:
        /* programa pergunta o código da tarefa que deseja altera; cria uma nova tarefa com o mesmo código 
        porem dando ao usuario a oportunidade de trocar todos os dados da tarefa; depois o programa chama uma 
        função a qual pega a nova tarefa criada e seu código com isso ela procura na fila o código e caso ache 
        ele coloca a nova tarefa na posição da com o mesmo código */
            printf("Modificar uma tarefa\nDigite o codigo da tarefa: ");
            scanf("%d", &codigo);
            tarefa = modificatarefa(codigo);
            trocatarefa( fila, codigo , tarefa);
            codigo = 0;
            imprimeFila(fila);
            break;
        case 3:
            printf("Concluir a primeira tarefa;\n");
            ConcluirTarefa(fila);
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
          // selecionaMenu();
            break;
    }
}


    return 0;
}

//função auxiliar para retirar tarefa da fila 
No *ret_ini(No* ini){
    No* p = ini->prox;
    free(ini);
    return p;
}

// função para concluir uma tarefa
Tarefa ConcluirTarefa(Fila *fila){

    //retirada da primeira Tkarefa da fila e colaca ela em um variavel auxiliar(tarefa)
    Tarefa tarefa;
    tarefa = fila->ini->tarefa;
    fila->ini = ret_ini(fila->ini);
    if(fila->ini==NULL)
    fila->fim=NULL;
    printf("Tarefa %d conclida com sucesso\n", tarefa.codigoTarefa);

    return tarefa;
}

// função de imprimir menu
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

// função para receber a data do sistema
int recebeData(int *dia, int *mes, int *ano){
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    *dia = tm.tm_mday;
    *mes = tm.tm_mon + 1;
    *ano = tm.tm_year + 1900;
    return 0;
}