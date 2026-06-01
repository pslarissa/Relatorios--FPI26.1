#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct chamada Tarefa para armazenar os dados de cada no da fila
typedef struct Tarefa {
    int id; //id da tarefa
    int prioridade; //prioridade (1 a 5)
    struct Tarefa* prox; //ponteiro para o proximo no da lista
} Tarefa;

//struct de controle para gerenciar o inicio e o fim da fila de tarefas
typedef struct FilaTarefas {
    Tarefa* ponteiro_inicio; //ponteiro para o primeiro no da lista (head)
    Tarefa* ponteiro_fim; //ponteiro para o ultimo no da lista (tail)
} FilaTarefas;

//inicializa os ponteiros de controle da fila como nulos
void inicializarFila(FilaTarefas* fila) {
    (*fila).ponteiro_inicio = NULL;
    (*fila).ponteiro_fim = NULL;
}

//retorna verdadeiro se o inicio da fila for nulo
int filaVazia(FilaTarefas* fila) {
    return (*fila).ponteiro_inicio == NULL;
}

//adiciona uma nova tarefa no final da fila alocando memoria dinamicamente
void inserir(FilaTarefas* fila, int identificador, int prioridade_tarefa) {
    //aloca memoria dinamicamente para o novo no do tipo Tarefa
    Tarefa* nova_tarefa = (Tarefa*)malloc(sizeof(Tarefa));
    
    //verifica se a alocacao dinamica de memoria falhou antes de acessar os dados
    if (nova_tarefa == NULL) {
        return; //encerra a funcao de forma segura para evitar travamento do sistema
    }
    
    (*nova_tarefa).id = identificador; //atribui o identificador fornecido para a tarefa
    (*nova_tarefa).prioridade = prioridade_tarefa; //atribui a prioridade fornecida para a tarefa
    (*nova_tarefa).prox = NULL; //a nova tarefa sera a ultima - entao seu proximo aponta para nulo
    
    //se a fila estiver vazia - a nova tarefa sera o inicio e o fim simultaneamente
    if (filaVazia(fila)) {
        (*fila).ponteiro_inicio = nova_tarefa;
        (*fila).ponteiro_fim = nova_tarefa;
    } else {
        //conecta a tarefa que estava no fim atual ao novo no criado
        (*(*fila).ponteiro_fim).prox = nova_tarefa;
        (*fila).ponteiro_fim = nova_tarefa; //atualiza o ponteiro de fim para a nova tarefa
    }
}

//retira a tarefa do inicio da fila - printa os dados e libera a memoria
void remover(FilaTarefas* fila) {
    //verifica se nao ha tarefas para remover na fila
    if (filaVazia(fila)) {
        printf("Fila vazia\n");
        return; //encerra a funcao caso esteja vazia
    }
    
    //guarda o ponteiro do no do inicio para podermos desalocar depois
    Tarefa* no_temporario = (*fila).ponteiro_inicio;
    
    //printa os dados da tarefa que esta sendo removida de acordo com a especificacao
    printf("Removida: id=%d prioridade=%d\n", (*no_temporario).id, (*no_temporario).prioridade);
    
    //avanca o ponteiro de inicio para a proxima tarefa da fila
    (*fila).ponteiro_inicio = (*(*fila).ponteiro_inicio).prox;
    
    //se a fila se tornou vazia apos a remocao, limpa tambem o ponteiro do fim
    if ((*fila).ponteiro_inicio == NULL) {
        (*fila).ponteiro_fim = NULL;
    }
    
    free(no_temporario); //libera a memoria alocada para o no que foi removido
}

//percorre a fila do inicio ao fim e printa os dados de cada tarefa
void listar(FilaTarefas* fila) {
    //verifica se a fila nao possui nenhuma tarefa cadastrada
    if (filaVazia(fila)) {
        printf("Fila vazia\n");
        return; //encerra a funcao caso esteja vazia
    }
    
    //ponteiro auxiliar para caminhar pela lista comecando pelo primeiro elemento
    Tarefa* navegador = (*fila).ponteiro_inicio;
    
    //percorre toda a lista ate encontrar o ponteiro nulo que indica o fim
    while (navegador != NULL) {
        //printa os dados da tarefa atual na linha correspondente
        printf("id=%d prioridade=%d\n", (*navegador).id, (*navegador).prioridade);
        navegador = (*navegador).prox; //avanca o ponteiro auxiliar para a proxima tarefa
    }
}

//limpa toda a memoria que restou da fila 
void liberarFila(FilaTarefas* fila) {
    while (!filaVazia(fila)) {
        Tarefa* no_temporario = (*fila).ponteiro_inicio;
        (*fila).ponteiro_inicio = (*(*fila).ponteiro_inicio).prox;
        free(no_temporario); //libera cada no ate que a lista esteja zerada
    }
    (*fila).ponteiro_fim = NULL;
}

int main() {
    char comando_lido; //armazena o caractere identificador do comando (I, R, L, F)
    int id_digitado; //variavel para armazenar o identificador lido no comando I
    int prioridade_digitada; //variavel para armazenar a prioridade lida no comando I
    int continuar_execucao = 1; //variavel de controle para encerrar o laco sem usar break
    FilaTarefas fila_sistema; //declara a fila de tarefas principal do sistema
    
    //inicializa a fila limpando seus ponteiros com o caractere nulo
    inicializarFila(&fila_sistema);
    
    //loop que le os comandos da entrada padrao continuamente enquanto a variavel de controle for verdadeira
    while (continuar_execucao && scanf(" %c", &comando_lido) != EOF) {
        
        //comando para inserir uma nova tarefa na fila
        if (comando_lido == 'I') {
            scanf("%d %d", &id_digitado, &prioridade_digitada); //le os dados complementares
            inserir(&fila_sistema, id_digitado, prioridade_digitada); //chama a funcao de insercao
        }
        
        //condicao para remover a tarefa do inicio da fila
        else if (comando_lido == 'R') {
            remover(&fila_sistema); //chama a funcao de remocao e exibicao
        }
        
        //comando para listar todas as tarefas presentes na fila
        else if (comando_lido == 'L') {
            listar(&fila_sistema); //chama a funcao de listagem sequencial
        }
        
        //condicao para encerrar o codigo 
        else if (comando_lido == 'F') {
            liberarFila(&fila_sistema); //limpa toda a memoria dinamicamente alocada antes de sair
            continuar_execucao = 0; //altera a condicao para finalizar o laco na proxima iteracao
        }
    }

    return 0; 
}
    
 