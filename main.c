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
Lista* RetiraPendencia(Lista *lista, int codigotarefa, Fila *fila1 , Fila *fila2 , Fila *fila3);

// protótipo para função imprimir lista com e sem atraso
void ImprimiListaComESemAtraso(Lista *lista);

// protótipo para função que verifica se o codigo da tarefa ja existe
int verificacodigo(Fila *fila, int codigotarefa);

// protótipo para função que retira tarefa da fila
void retiraFila(Fila *fila, int codigotarefa);

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

    printf("\nQual a prioridade da tarefa? (1 para Alta, 2 para normal, 3 paraBaixa)\n");
    scanf("%d", &tarefa.prioridade);
    while(tarefa.prioridade > 3 || tarefa.prioridade < 1)
    {
        printf("Prioridade invalida, digite novamente\n");
        scanf("%d", &tarefa.prioridade);
    }
    
    printf("\ndigite a data de inicio (Atencao, digite o dia e de enter e assim por diante)\n");
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
    printf("\nComfirmacao da data de inicio da tarefa: %d/%d/%d", tarefa.dataInicio.dia, tarefa.dataInicio.mes, tarefa.dataInicio.ano);
    
    printf("\ndigite a data de termino (Atencao, digite o dia e de enter e assim por diante)\n");
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
    
    printf("\nQual a prioridade da tarefa? (1=Alta, 2=Normal, 3=Baixa)\n");
    scanf("%d", &tarefa.prioridade);
    while(tarefa.prioridade > 3 || tarefa.prioridade < 1)
    {
        printf("Prioridade invalida, digite novamente\n");
        scanf("%d", &tarefa.prioridade);
    }
    

    printf("\ndigite a data de inicio (Atencao, digite o dia e de enter e assim por diante):\n");
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
    
    printf("\ndigite a data de termino (Atencao, digite o dia e de enter e assim por diante)\n"); 
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
        printf("========================================================================\n");
        printf("Codigo da tarefa: %d\n", aux->tarefa.codigoTarefa);
        printf("Nome da tarefa: %s\n", aux->tarefa.nomeTarefa);
        printf("Nome do projeto: %s\n", aux->tarefa.nomeProjeto);
        printf("Prioridade da tarefa: %d\n", aux->tarefa.prioridade);
        printf("Data de inicio da tarefa: %2d/%2d/%2d\n", aux->tarefa.dataInicio.dia, aux->tarefa.dataInicio.mes, aux->tarefa.dataInicio.ano);
        printf("Data de termino da tarefa: %2d/%2d/%2d\n", aux->tarefa.dataTermino.dia, aux->tarefa.dataTermino.mes, aux->tarefa.dataTermino.ano);
        printf("Status da tarefa: %d\n", aux->tarefa.status);
        printf("========================================================================\n");
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
    
    printf("\n\t\tBem vindo ao gerenciador de tarefas\n========================================================================\n");

while(i == 0){
    menu();
    int opcao = 0;
    scanf("%d", &opcao);
    system("cls");
    int prioridade = 0;
    switch(opcao){
        case 1:
        /// Cria uma nova tarefa e insere na fila
            printf("\nAdicionar uma nova tarefa\n");

            tarefa = novatarefa(fila);
            insereFila(fila , tarefa);

                switch (tarefa.prioridade)
                {
                case 1:
                    insereFila(filaPrioridade1 , tarefa);
                    system("cls");
                    printf("FILA DE PRIORIDADE 1 COM A NOVA TAREFA:\n");
                    AtualizaStatus(filaPrioridade1);
                    imprimeFila(filaPrioridade1);
                    break;
                case 2:
                    insereFila(filaPrioridade2 , tarefa);
                    system("cls");
                    printf("FILA DE PRIORIDADE 2 COM A NOVA TAREFA:\n");
                    AtualizaStatus(filaPrioridade2);
                    imprimeFila(filaPrioridade2);
                    break;
                case 3:
                    insereFila(filaPrioridade3 , tarefa);
                    system("cls");
                    printf("FILA DE PRIORIDADE 3 COM A NOVA TAREFA:\n");
                    AtualizaStatus(filaPrioridade3);
                    imprimeFila(filaPrioridade3);
                    break;
            }
        break;
            
        case 2:

            
            printf("\nQual a prioridade da tarefa que desaja alterar(1 ou 2 ou 3): ");
            scanf("%d", &prioridade);

            switch(prioridade){
                case 1:
                    system("cls");
                    printf("FILA PRIORIDADE 1:\n");
                    imprimeFila(filaPrioridade1);
                    printf("Modificar uma tarefa\nDigite o codigo da tarefa que deseja modificar: ");
                    scanf("%d", &codigo);
                    system("cls");
                    tarefa = modificatarefa(codigo , filaPrioridade1);

                    switch (tarefa.prioridade)
                    {
                    case 1:
                        trocatarefa( filaPrioridade1, codigo , tarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 1 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade1);
                        break;
                    case 2:
                        insereFila(filaPrioridade2 , tarefa);
                        retiraFila(filaPrioridade1 , tarefa.codigoTarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 2 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade2);
                        break;
                    case 3:
                        insereFila(filaPrioridade3 , tarefa);
                        retiraFila(filaPrioridade1 , tarefa.codigoTarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 3 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade3);
                        break;
                    }
                    break;
                case 2:
                    system("cls");
                    printf("FILA PRIORIDADE 2:\n");
                    imprimeFila(filaPrioridade2);
                    printf("Modificar uma tarefa\nDigite o codigo da tarefa que deseja modificar: ");
                    scanf("%d", &codigo);
                    system("cls");
                    tarefa = modificatarefa(codigo , filaPrioridade2);
                    switch (tarefa.prioridade)
                    {
                    case 1:
                        insereFila(filaPrioridade1 , tarefa);
                        retiraFila(filaPrioridade2 , tarefa.codigoTarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 1 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade1);
                        break;
                    case 2:
                        trocatarefa( filaPrioridade2, codigo , tarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 2 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade2);
                        break;
                    case 3:
                        insereFila(filaPrioridade3 , tarefa);
                        retiraFila(filaPrioridade2 , tarefa.codigoTarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 3 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade3);
                        break;
                    }
                    break;
                case 3:
                    system("cls");
                    printf("FILA PRIORIDADE 3 COM A NOVA TAREFA:\n");
                    imprimeFila(filaPrioridade3);
                    printf("Modificar uma tarefa\nDigite o codigo da tarefa que deseja modificar: ");
                    scanf("%d", &codigo);
                    system("cls");
                    tarefa = modificatarefa(codigo , filaPrioridade3);
                    switch (tarefa.prioridade)
                    {
                    case 1:
                        insereFila(filaPrioridade1 , tarefa);
                        retiraFila(filaPrioridade3 , tarefa.codigoTarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 1 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade1);
                        break;
                    case 2:
                        insereFila(filaPrioridade2 , tarefa);
                        retiraFila(filaPrioridade3 , tarefa.codigoTarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 2 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade2);
                        break;
                    case 3:
                        trocatarefa( filaPrioridade3, codigo , tarefa);
                        system("cls");
                        printf("FILA PRIORIDADE 3 COM A TAREFA MODIFICADA:\n");
                        imprimeFila(filaPrioridade3);
                        break;
                    }
                    break;
                default:
                    printf("Opcao invalida\n");
            }

            prioridade = 0;
            
        break;


        case 3:
            system("cls");
            printf("Digite de qual a prioridade da fila que desaja finalizar uma tarefa(1 ou 2 ou 3):\n");
            scanf("%d", &prioridade);
 
            switch(prioridade){
                case 1:
                    AtualizaStatus(filaPrioridade1);
                    lista = ConcluirTarefa(filaPrioridade1 , lista);
                break;
                case 2:
                    AtualizaStatus(filaPrioridade2);
                    lista = ConcluirTarefa(filaPrioridade2 , lista);
                    break;
                case 3:
                    AtualizaStatus(filaPrioridade3);
                    lista = ConcluirTarefa(filaPrioridade3 , lista);
                default:
                    printf("Opcao invalida\n");
            }
            prioridade = 0;
        break;

        case 4:
            printf("Atualizacao do status da tarefa\n");
            printf("O que deseja fazer?\n1 -> Atualizar status de todas as tarefas: \n2 -> Colocar terafa como pendente: \n3 -> Retirar pendencia:\n4 -> Retornar ao menu:\n");
            scanf("%d", &resposta);
            switch (resposta)
            {
            case 1:
                AtualizaStatus(fila);
                AtualizaStatus(filaPrioridade1);
                AtualizaStatus(filaPrioridade2);
                AtualizaStatus(filaPrioridade3);
                system("cls");
                printf("STATUS DA FILA ATUALIZADO COM SUCESSO\n");
            break;
            case 2: 
                system("cls");

                printf("\nEm qual fila de voce deseja setar um tarefa como pendente?\n(1 ou 2 ou 3):");
                scanf("%d", &prioridade);
                switch(prioridade){
                    case 1:
                        system("cls");
                        printf("FILA PRIORIDADE 1:\n");
                        imprimeFila(filaPrioridade1);
                        printf("Digite o codigo da tarefa que deseja colocar na lista de pendentes: ");
                        scanf("%d", &CodMod);
                        system("cls");
                        listaPendente = SetaPendencia(filaPrioridade1, CodMod, listaPendente);
                    break;
                    case 2:
                        system("cls");
                        printf("FILA PRIORIDADE 2:\n");
                        imprimeFila(filaPrioridade2);
                        printf("Digite o codigo da tarefa que deseja colocar na lista de pendentes: ");
                        scanf("%d", &CodMod);
                        system("cls");
                        listaPendente = SetaPendencia(filaPrioridade2, CodMod, listaPendente);
                    break;
                    case 3:
                        system("cls");
                        printf("FILA PRIORIDADE 3:\n");
                        imprimeFila(filaPrioridade3);
                        printf("Digite o codigo da tarefa que deseja colocar na lista de pendentes: ");
                        scanf("%d", &CodMod);
                        system("cls");
                        listaPendente = SetaPendencia(filaPrioridade3, CodMod, listaPendente);
                    break;
                    default:
                        printf("Opcao invalida\n");
                }
        
            break;
                
            case 3:
                system("cls");
                printf("LISTA DE TAREFAS PENDENTES:\n");
                imprimeLista(listaPendente);
                printf("Digite o codigo da tarefa que deseja retirar pendencia na fila: ");
                scanf("%d", &CodRet);
                system("cls");
                listaPendente =  RetiraPendencia(listaPendente, CodRet, filaPrioridade1, filaPrioridade2, filaPrioridade3);
                AtualizaStatus(fila);
                AtualizaStatus(filaPrioridade1);
                AtualizaStatus(filaPrioridade2);
                AtualizaStatus(filaPrioridade3);
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
        case 12:
            printf("nao ta perfeito a gente sabe, mas tentamos... corriga com carinho >;b\n");//easter egg
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
    printf("Tarefa %d concluida com sucesso\n", tarefa.codigoTarefa);

    SistemData = recebeData();

    tarefa.dataTermino = SistemData;


    //função para inserir na lista encadeada
    lista = insere (lista,tarefa);

    imprimeTarefa(tarefa);

    return  lista;
}

// função de imprimir menu
void menu(){

    printf("\nEscolha uma opcao digitando o numero indicado de seu item\n\n");
    printf("\t1. Adicionar uma nova tarefa\n");
    printf("\t2. Modificar uma tarefa\n");
    printf("\t3. Concluir uma tarefa\n");
    printf("\t4. Atualizacao do status da tarefa\n");
    printf("\t5. Listar tarefas pendentes\n");
    printf("\t6. Listar tarefas concluidas\n");
    printf("\t7. Listar tarefas concluidas com e sem atraso\n");
    printf("\t8. Impirimir fila de tarefas\n");
    printf("\t9. Sair do programa\n");
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
    printf("========================================================================\n");
    printf("Codigo da tarefa: %d\n", tarefa.codigoTarefa);
    printf("Nome da tarefa: %s\n", tarefa.nomeTarefa);
    printf("Nome do projeto: %s\n", tarefa.nomeProjeto);
    printf("Prioridade da tarefa: %d\n", tarefa.prioridade);
    printf("Data de inicio da tarefa: %2d/%2d/%2d\n", tarefa.dataInicio.dia, tarefa.dataInicio.mes, tarefa.dataInicio.ano);
    printf("Data de termino da tarefa: %2d/%2d/%2d\n", tarefa.dataTermino.dia, tarefa.dataTermino.mes, tarefa.dataTermino.ano);
    printf("Status da tarefa: %d\n", tarefa.status);
    printf("========================================================================\n");
    printf("\n");
}

// função para imprimir lista encadeada
void imprimeLista(Lista* lista) 
{
    if(vazia(lista))
    {
        printf("\n\t => LISTA VAZIA <==\n ");
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
            printf("Lista de pendentes\n");
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
Lista* RetiraPendencia(Lista *lista, int codigotarefa, Fila *fila1 , Fila *fila2 , Fila *fila3){
    Tarefa tarefaaux1 , tarefaaux2;
    Lista *listaaux = inicializaLista();
    Lista *aux = lista;
    while(aux != NULL){
        if(aux->tarefa.codigoTarefa == codigotarefa){
            tarefaaux1 = aux -> tarefa;
            
            printf("A tarefa foi removida da lista de pendencia\n");
            imprimeTarefa(tarefaaux1);
            switch (tarefaaux1.prioridade)
            {
            case 1:
                insereFila(fila1 , tarefaaux1);
            break;
            case 2:
                insereFila(fila2 , tarefaaux1);
            break;
            case 3:
                insereFila(fila3 , tarefaaux1);
            break;
            }
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

//função para retirar tarefa da fila
void retiraFila(Fila *fila, int codigotarefa){
    Tarefa tarefaaux1 , tarefaaux2;
    Fila *filaaux = criaFila();
    No *aux = fila->ini;
    while(aux != NULL){
        if(aux->tarefa.codigoTarefa == codigotarefa){
            tarefaaux1 = aux -> tarefa;
        }
        else{
            tarefaaux2 = aux -> tarefa;
            insereFila(filaaux, tarefaaux2);
        }
        aux = aux->prox;
    }
    fila-> ini = filaaux -> ini;
    fila-> fim = filaaux -> fim;
}