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
    int prioridade;
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
typedef struct NoLista{
    Tarefa tarefa;
    struct Lista *prox;
}Lista;
//fução para inicializar lista encadeada
Lista* inicializaLista(){
    return NULL;
}

// protótipo da função menu
void menu();

// protótipo para função coclui tarefa
Lista *ConcluirTarefa(Fila *fila, Lista *lista);

//protótipo para receber a data do sistema
Data recebeData();

// protótipo para função de imprimir tarefa
void imprimeTarefa(Tarefa tarefa);

// protótipo para função de imprimir fila
void imprimeFila(Fila *fila);

// protótipo para função de imprimir lista encadeada
void imprimeLista(Lista* lista);

// protótipo para função de verificar se a lista está vazia
int vazia (Lista *recebida);

// protótipo para função de inserir na lista encadeada
Lista* insere (Lista* recebida, Tarefa valor);

// protótipo para função que atualiza estatus de todas as tarefas
void AtualizaStatus(Fila *fila);

// protótipo para função que seta pendencia
Lista* SetaPendencia(Fila *fila, int codigotarefa, Lista *lista);

// protótipo para função que retira pendencia
Lista* RetiraPendencia(Lista *lista, int codigotarefa , Fila *fila);

// protótipo para função imprimir lista com e sem atraso
void ImprimiListaComESemAtraso(Lista *lista);

// protótipo para função que verifica se o codigo da tarefa ja existe
int verificacodigo(Fila *fila, int codigotarefa);

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
//basicamente cria uma tarefa nova e insere ela na fila no lugar da que o usuario deseja mudar
Tarefa modificatarefa (int codigotarefa, Fila *fila){
    Tarefa tarefa;

    Data dataatual = recebeData();

    //imprimiando a tarefa que o usuario deseja mudar
    printf("\nDados da Tarefa Escolhida:\n");
    No *aux = fila->ini;
    while(aux != NULL){
        if(aux->tarefa.codigoTarefa == codigotarefa){
            imprimeTarefa(aux->tarefa);
        }
        aux = aux->prox;
    }

    tarefa.codigoTarefa = codigotarefa;
    while (getchar() != '\n');
    printf("\nDigite o nome da tarefa: ");
    gets(tarefa.nomeTarefa);
    printf("\nDigite o nome do projeto: ");
    gets(tarefa.nomeProjeto);

    printf("Qual a prioridade da tarefa? (1=Alta, 2=Normal, 3=Baixa)\n");
    scanf("%d", &tarefa.prioridade);
    while(tarefa.prioridade > 3 || tarefa.prioridade < 1)
    {
        printf("Prioridade invalida, digite novamente\n");
        scanf("%d", &tarefa.prioridade);
    }
    
    printf("\ndigite a data de inicio: (dia/mes/ano):\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataInicio.dia);
        }while(tarefa.dataInicio.dia > 31 || tarefa.dataInicio.dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataInicio.mes);
        }while(tarefa.dataInicio.mes > 12 || tarefa.dataInicio.mes < 1);
    do{
        printf("\nDigite o ano: ");
        scanf("%d", &tarefa.dataInicio.ano);
    }while(tarefa.dataInicio.ano < dataatual.ano);
    printf("ignore a data errada abaixo... no final ela fica certa >;D ");
    printf("\nComfirmacao da data de inicio da tarefa: %d/%d/%d", tarefa.dataInicio.dia, tarefa.dataInicio.mes, tarefa.dataInicio.ano);
    
    printf("\ndigite a data de termino: (dia/mes/ano)\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataTermino.dia);
        }while(tarefa.dataTermino.dia > 31 || tarefa.dataTermino.dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataTermino.mes);
        }while(tarefa.dataTermino.mes > 12 || tarefa.dataTermino.mes < 1);
    do{
        printf("\nDigite o ano: ");
        scanf("%d", &tarefa.dataTermino.ano);
        }while(tarefa.dataTermino.ano < tarefa.dataInicio.ano || tarefa.dataTermino.ano < dataatual.ano);
    printf("\nComfirmacao da data de termino da tarefa: %d/%d/%d \n", tarefa.dataTermino.dia, tarefa.dataTermino.mes, tarefa.dataTermino.ano);
    tarefa.status = 0;
    
    return tarefa;
}

//função para criar uma nova tarefa
Tarefa novatarefa(Fila *fila){
    Tarefa tarefa;
    int flag = 0;

    Data dataatual = recebeData();

    //verifica se o codigo da tarefa ja existe
    while (flag == 0)
    {
       
        printf("\nDigite o codigo da tarefa: ");
        scanf("%d", &tarefa.codigoTarefa);
        while(verificacodigo(fila,tarefa.codigoTarefa)==1)
        {
            printf("\nCodigo ja existente, digite outro codigo\nPor favor insira um novo codigo:\n");
            scanf("%d", &tarefa.codigoTarefa);
            flag = 0;
        }
        flag = 1;
    }
    while (getchar() != '\n');

    printf("\nDigite o nome da tarefa: ");
    gets(tarefa.nomeTarefa);

    printf("\nDigite o nome do projeto: ");
    gets(tarefa.nomeProjeto);

    /// Recebe a prioridade da tarefa, caso usuario digite errado uma nova tentativa é feita
    
    printf("Qual a prioridade da tarefa? (1=Alta, 2=Normal, 3=Baixa)\n");
    scanf("%d", &tarefa.prioridade);
    while(tarefa.prioridade > 3 || tarefa.prioridade < 1)
    {
        printf("Prioridade invalida, digite novamente\n");
        scanf("%d", &tarefa.prioridade);
    }
    

    printf("\ndigite a data de inicio: (dia/mes/ano):\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataInicio.dia);
        }while(tarefa.dataInicio.dia > 31 || tarefa.dataInicio.dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataInicio.mes);
        }while(tarefa.dataInicio.mes > 12 || tarefa.dataInicio.mes < 1);
    do{
        printf("\nDigite o ano: ");
        scanf("%d", &tarefa.dataInicio.ano);
    }while(tarefa.dataInicio.ano < dataatual.ano);
    printf("\nComfirmacoa da data de inicio da tarefa: %d/%d/%d", tarefa.dataInicio.dia, tarefa.dataInicio.mes, tarefa.dataInicio.ano);
    
    printf("\ndigite a data de termino: (dia/mes/ano)\n");
    do{
        printf("\nDigite o dia: ");
        scanf("%d", &tarefa.dataTermino.dia);
        }while(tarefa.dataTermino.dia > 31 || tarefa.dataTermino.dia < 1);
    do{
        printf("\nDigite o mes: ");
        scanf("%d", &tarefa.dataTermino.mes);
        }while(tarefa.dataTermino.mes > 12 || tarefa.dataTermino.mes < 1);
    do{
        printf("\nDigite o ano: ");
        scanf("%d", &tarefa.dataTermino.ano);
        }while(tarefa.dataTermino.ano < tarefa.dataInicio.ano || tarefa.dataTermino.ano < dataatual.ano);
    printf("\nComfirmacao da data de termino da tarefa: %d/%d/%d \n", tarefa.dataTermino.dia, tarefa.dataTermino.mes, tarefa.dataTermino.ano);
    tarefa.status = 0;
    return tarefa;

    
};

//função para inserina uma tarefa na fila
void insereFila(Fila* fila, Tarefa tarefa){
    fila->fim=ins_fim(fila->fim,tarefa);
    if(fila->ini==NULL)/*fila antes vazia?*/
    fila->ini=fila->fim;
};


/// Busca o codigo na fila e inseri a nova tarefa no lugar da antiga
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
        printf("Prioridade da tarefa: %d\n", aux->tarefa.prioridade);
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
    Fila *filaPrioridade1 = criaFila();
    Fila *filaPrioridade2 = criaFila();
    Fila *filaPrioridade3 = criaFila();
    Tarefa tarefa;
    int codigo;

    //lista de tarefas concluidas
    Lista *lista;
    lista = inicializaLista();

    //Lista de tarefas pendentes
    Lista *listaPendente;
    listaPendente = inicializaLista();

    //variaveis para o caso 4
    int resposta = 0;
    int CodMod = 0;
    int CodRet = 0;

    system("cls");

while(i == 0){
    menu();
    int opcao = 0;
    scanf("%d", &opcao);
    system("cls");
    Tarefa tarefaaux;
    switch(opcao){
        case 1:
        /// Cria uma nova tarefa e insere na fila
            printf("\nAdicionar uma nova tarefa\n");
            tarefa = novatarefa(fila);
            /*
            aux = fila->ini;
            while(aux != NULL){
                tarefaaux = aux->tarefa;
                switch (tarefa.prioridade)
                {
                case 1:
                    insereFila(filaPrioridade1 , tarefa);
                    break;
                case 2:
                    insereFila(filaPrioridade2 , tarefa);
                    break;
                case 3:
                    insereFila(filaPrioridade3 , tarefa);
                    break;
                {
            }
            */
            insereFila(fila , tarefa);
            system("cls");
            printf("LISTA COM A NOVA TAREFA:\n");
           
            imprimeFila(fila);
            break;
        case 2:
        /* programa pergunta o código da tarefa que deseja altera; cria uma nova tarefa com o mesmo código 
        porem dando ao usuario a oportunidade de trocar todos os dados da tarefa; depois o programa chama uma 
        função a qual pega a nova tarefa criada e seu código com isso ela procura na fila o código e caso ache 
        ele coloca a nova tarefa na posição da com o mesmo código */
            printf("Modificar uma tarefa\nDigite o codigo da tarefa que deseja modificar: ");
            scanf("%d", &codigo);
            tarefa = modificatarefa(codigo , fila);
            trocatarefa( fila, codigo , tarefa);
            codigo = 0;
            system("cls");
            printf("LISTA COM A TAREFA MODIFICADA:\n");
            AtualizaStatus(fila);
            imprimeFila(fila);
            break;
        case 3:
            system("cls");
            printf("PRIMEIRA TAREFA CONCLUIDA;\n");
            AtualizaStatus(fila);
            lista = ConcluirTarefa(fila , lista);
            break;
        case 4:
            printf("Atualizacao do status da tarefa\n");
            printf("O que deseja fazer?\n1 -> Atualizar status de todas as tarefas: \n2 -> Colocar terafa como pendente: \n3 -> Retirar pendencia:\n4 -> Retornar ao menu:\n");
            scanf("%d", &resposta);
            switch (resposta)
            {
            case 1:
                AtualizaStatus(fila);
                system("cls");
                printf("STATUS DA FILA ATUALIZADO COM SUCESSO\n");
                break;
            case 2: 
                system("cls");
                printf("FILA DE TAREFAS:\n");
                imprimeFila(fila);
                printf("Digite o codigo da tarefa que deseja colocar na lista de pendentes: ");
                scanf("%d", &CodMod);
                system("cls");
                listaPendente = SetaPendencia(fila, CodMod, listaPendente);
                break;
            case 3:
                system("cls");
                printf("LISTA DE TAREFAS PENDENTES:\n");
                imprimeLista(listaPendente);
                printf("Digite o codigo da tarefa que deseja retirar pendencia na fila: ");
                scanf("%d", &CodRet);
                system("cls");
                listaPendente =  RetiraPendencia(listaPendente, CodRet, fila);
                AtualizaStatus(fila);
                break;
            case 4:
                system("cls");
                break;
            default:
                break;
            }
            break;
        case 5:
            system("cls");
            printf("LISTA DE TAREFAS PENDENTES:\n");
            imprimeLista(listaPendente);
            break;
        case 6:
            system("cls");
            printf("LISTA DE TAREFAS COCLUIDAS:\n");
            imprimeLista(lista);
            break;
        case 7:
            system("cls");
            ImprimiListaComESemAtraso(lista);
            break;
        case 8:
            system("cls");
            printf("FILA DE TAREFAS:\n");
            imprimeFila(fila);
            break;
        case 9:
            system("cls");
            printf("Ate mais!\n");
            return 0;
            break;
        default:
            printf("Opcao invalida\n");
          // selecionaMenu();
            break;
    }
    AtualizaStatus(fila);
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
Lista *ConcluirTarefa(Fila *fila, Lista *lista){

    //retirada da primeira Tarefa da fila e colaca ela em um variavel auxiliar(tarefa)
    Tarefa tarefa;
    Data SistemData;
    tarefa = fila->ini->tarefa;
    fila->ini = ret_ini(fila->ini);
    if(fila->ini==NULL)
    fila->fim=NULL;
    printf("Tarefa %d conclida com sucesso\n", tarefa.codigoTarefa);

    SistemData = recebeData();

    tarefa.dataTermino = SistemData;


    //função para inserir na lista encadeada
    lista = insere (lista,tarefa);

    imprimeTarefa(tarefa);

    return  lista;
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
    printf("8. Impirimir fila de tarefas\n");
    printf("9. Sair do programa\n");
}

// função para receber a data do sistema
Data recebeData(){
    Data SistemData;
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    SistemData.dia = tm.tm_mday;
    SistemData.mes = tm.tm_mon + 1;
    SistemData.ano = tm.tm_year + 1900;
    return SistemData;
}

// função para imprimir tarefa
void imprimeTarefa(Tarefa tarefa){
    printf("Codigo da tarefa: %d\n", tarefa.codigoTarefa);
    printf("Nome da tarefa: %s\n", tarefa.nomeTarefa);
    printf("Nome do projeto: %s\n", tarefa.nomeProjeto);
    printf("Prioridade da tarefa: %d\n", tarefa.prioridade);
    printf("Data de inicio da tarefa: %2d/%2d/%2d\n", tarefa.dataInicio.dia, tarefa.dataInicio.mes, tarefa.dataInicio.ano);
    printf("Data de termino da tarefa: %2d/%2d/%2d\n", tarefa.dataTermino.dia, tarefa.dataTermino.mes, tarefa.dataTermino.ano);
    printf("Status da tarefa: %d\n", tarefa.status);
    printf("\n");
}

// função para imprimir lista encadeada
void imprimeLista(Lista* lista) 
{
    if(vazia(lista))
    {
        printf("\n\n\t\t => LISTA VAZIA  <==\n\n ");
    }
    else
    {
        for (; lista != NULL; lista = lista->prox) {
            imprimeTarefa(lista->tarefa);
        }
        printf("\n\n");
    }

}

// função para verificar se a lista está vazia
int vazia (Lista *recebida)
{
	if (recebida == NULL)
	{
		return 1;

	}
    return 0;
}

// função para inserir na lista encadeada
Lista* insere (Lista* recebida, Tarefa valor)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if (novo == NULL) {
        // tratamento de erro
        return recebida;
    }
    novo->tarefa = valor;
    novo->prox = recebida;
    return novo;;
}

// função para Atualiuzar status de todas as tarefas
void AtualizaStatus(Fila *fila){
    No *aux = fila->ini;
    Data dataSistem = recebeData();
    int FlagMes = 0, FlagAno = 0;  

    while (aux != NULL)
    {
    FlagMes = 0;
    FlagAno = 0;
        if (aux->tarefa.dataTermino.ano > dataSistem.ano){
            FlagAno = 1; 
        }
        else if(aux->tarefa.dataTermino.ano == dataSistem.ano){
            FlagAno = 2;
        }
        else if(aux->tarefa.dataTermino.ano < dataSistem.ano){
            FlagAno = 3;
        }

        switch(FlagAno)
        {
        case(1):
            aux->tarefa.status = 0;
        break;
        case(2):
            if (aux->tarefa.dataTermino.mes > dataSistem.mes){
                FlagMes = 1;
            }
            else if(aux->tarefa.dataTermino.mes == dataSistem.mes){
                FlagMes = 2;
            }
            else if(aux->tarefa.dataTermino.mes < dataSistem.mes){
                FlagMes = 3;
            }
            switch(FlagMes)
            {
            case(1):
                aux->tarefa.status = 0;
            break;
            case(2):
                if(aux->tarefa.dataTermino.dia > dataSistem.mes)
                {
                    aux->tarefa.status = 1;
                }
                else
                {
                    aux->tarefa.status = 0;
                }
            break;
            case(3):
                aux->tarefa.status = 1;
            break;
            }
            break;
        case(3):
            aux->tarefa.status = 1;
        break;
        default:
        break;
        }
        aux = aux->prox;
    }

}

// função para setar pendencia
Lista* SetaPendencia(Fila *fila, int codigotarefa, Lista *listaPendente){
    Tarefa tarefaaux1 , tarefaaux2;
    Fila *filaaux = criaFila();
    No *aux = fila->ini;
    while(aux != NULL){
        if(aux->tarefa.codigoTarefa == codigotarefa){
            tarefaaux1 = aux -> tarefa;
            tarefaaux1.status = -1;
            listaPendente = insere(listaPendente, tarefaaux1);
            printf("lista de pendentes\n");
            imprimeLista(listaPendente);
        }
        else{
            tarefaaux2 = aux -> tarefa;
            insereFila(filaaux, tarefaaux2);
        }
        aux = aux->prox;
    }
    fila-> ini = filaaux -> ini;
    fila-> fim = filaaux -> fim;
    return listaPendente;
}

// função para retirar pendencia
Lista* RetiraPendencia(Lista *lista, int codigotarefa, Fila *fila){
    Tarefa tarefaaux1 , tarefaaux2;
    Lista *listaaux = inicializaLista();
    Lista *aux = lista;
    while(aux != NULL){
        if(aux->tarefa.codigoTarefa == codigotarefa){
            tarefaaux1 = aux -> tarefa;
            
            printf("tarefa retirada da lista de pendentes\n");
            imprimeTarefa(tarefaaux1);
            insereFila (fila, tarefaaux1);
        }
        else{
            tarefaaux2 = aux -> tarefa;
            listaaux = insere(listaaux, tarefaaux2);
        }
        aux = aux->prox;
    }
    return listaaux;
}

// função para imprimir lista com e sem atraso
void ImprimiListaComESemAtraso(Lista *lista){
    Lista *listaux1 = lista;
    Lista *listaux2 = lista;
    printf("->TAREFAS CONCLUIDAS SEM ATRASO:\n");
    while(listaux1 != NULL){
        if(listaux1->tarefa.status == 0){
            imprimeTarefa(listaux1->tarefa);
        }
        listaux1 = listaux1->prox;
    }
    printf("->TAREFAS CONCLUIDAS COM ATRASO:\n");
    while(listaux2 != NULL){
        if(listaux2->tarefa.status == 1){
            imprimeTarefa(listaux2->tarefa);
        }
        listaux2 = listaux2->prox;
    }
}

// função para verificar se o codigo da tarefa ja existe
int verificacodigo(Fila *fila, int codigotarefa){
    No *aux = fila->ini;
    while(aux != NULL){
        if(aux->tarefa.codigoTarefa == codigotarefa){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}