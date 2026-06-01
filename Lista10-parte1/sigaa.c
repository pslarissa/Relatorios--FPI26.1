#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//struct para armazenar os dados de cada estudante
typedef struct Student {
    long long matricula; //id de 11 digitos da matricula
    int prioridade; //prioridade do aluno (1 a 3)
    double coeficiente_rendimento; //coeficiente de rendimento (0.00 a 10.00)
    long long tempo_chegada; //segundo exato de chegada do aluno
    long long tempo_timeout; //segundo limite de timeout do aluno
    int score; //resultado do calculo de prioridade para a vaga
} Student;

//no da estrutura encadeada que aponta para o proximo
typedef struct Node {
    Student aluno; //dados do aluno contidos neste no
    struct Node* proximo_no; //ponteiro para o proximo no da fila
} Node;

//estrutura de controle da fila com ponteiros para o inicio e fim
typedef struct Queue {
    Node* ponteiro_inicio; //ponteiro para o primeiro elemento (que remove)
    Node* ponteiro_fim; //ponteiro para o ultimo elemento (que vai inserir)
} Queue;

//inicializa os ponteiros da fila como nulos **usando desreferenciamento explicito* *ideia do gemini
void initQueue(Queue* fila) {
    (*fila).ponteiro_inicio = NULL;
    (*fila).ponteiro_fim = NULL;
}

//retorna verdadeiro se o inicio da fila for nulo usando desreferenciamento explicito 
int isEmpty(Queue* fila) {
    return (*fila).ponteiro_inicio == NULL;
}

//insere um novo aluno no final da fila (fim da linha de espera)
void enqueue(Queue* fila, Student novo_aluno) {
    //aloca memoria dinamicamente para o novo no
    Node* novo_no = (Node*)malloc(sizeof(Node));
    
    //verifica se a alocacao dinamica de memoria falhou antes de acessar os dados
    if (novo_no == NULL) {
        return; //encerra a funcao de forma segura para evitar travamento do sistema
    }
    
    (*novo_no).aluno = novo_aluno; //copia os dados do aluno para o no
    (*novo_no).proximo_no = NULL; //o novo no sera o ultimo entao aponta para nulo
    
    //se a fila estiver vazia - o novo no e o inicio e o fim
    if ((*fila).ponteiro_fim == NULL) {
        (*fila).ponteiro_inicio = novo_no;
        (*fila).ponteiro_fim = novo_no;
    } else {
        //se ja existirem elementos- conecta o antigo ultimo ao novo no
        (*(*fila).ponteiro_fim).proximo_no = novo_no;
        (*fila).ponteiro_fim = novo_no; //atualiza o ponteiro de fim da fila
    }
}

//remove e retorna o aluno que ta na frente da fila 
Student dequeue(Queue* fila) {
    //retorna uma estrutura vazia caso a fila nao tenha ninguem
    if (isEmpty(fila)) {
        Student aluno_vazio = {0};
        return aluno_vazio;
    }
    
    //guarda o no que sera removido para poder liberar a memoria depois
    Node* no_temporario = (*fila).ponteiro_inicio;
    Student aluno_removido = (*no_temporario).aluno; //copia os dados do aluno para o retorno
    
    //avanca o inicio da fila para o proximo elemento
    (*fila).ponteiro_inicio = (*(*fila).ponteiro_inicio).proximo_no;
    
    //se a fila ficou vazia apos a remocao - limpa o ponteiro do fim
    if ((*fila).ponteiro_inicio == NULL) {
        (*fila).ponteiro_fim = NULL;
    }
    
    free(no_temporario); //desaloca a memoria do no removido
    return aluno_removido; //retorna os dados do aluno retirado
}

void freeQueue(Queue* fila) {
    while (!isEmpty(fila)) {
        dequeue(fila); //chama o dequeue ate esvaziar completamente
    }
}

//funcao principal que gerencia o fluxo do sistema
int main() {
    char comando_lido[55]; //armazena o comando lido (START, ADD, PROC, FIM)
    char nome_disciplina[55] = ""; //guarda o nome da disciplina atual
    int vagas_disponiveis = 0; //quantidade de vagas disponiveis no momento
    long long tempo_atual = 1; //relogio interno do servidor que comeca em 1
    
    Queue fila_requisicoes; //fila que armazena os alunos aguardando processamento
    Queue fila_confirmados; //fila secundaria que guarda quem conseguiu a vaga

    //inicializa ambas as filas zerando seus ponteiros passando o endereco com &
    initQueue(&fila_requisicoes);
    initQueue(&fila_confirmados);

    //loop principal que le comandos ate o final do arquivo de entrada
    while (scanf("%s", comando_lido) != EOF) {
        
        //comando para iniciar as configuracoes de uma nova materia
        if (strcmp(comando_lido, "START") == 0) {
            //limpa os dados das filas de execucoes anteriores
            freeQueue(&fila_requisicoes);
            freeQueue(&fila_confirmados);
            //le o nome da materia e as vagas totais ofertadas
            scanf("%s %d", nome_disciplina, &vagas_disponiveis);
            tempo_atual = 1; //reinicia o relogio do servidor para 1
        } 
        
        //comando para adicionar um aluno no fim da fila de triagem
        else if (strcmp(comando_lido, "ADD") == 0) {
            Student aluno_atual;
            //le as variaveis do aluno de acordo com a especificacao
            scanf("%lld %d %lf %lld %lld", 
                  &aluno_atual.matricula, 
                  &aluno_atual.prioridade, 
                  &aluno_atual.coeficiente_rendimento, 
                  &aluno_atual.tempo_chegada, 
                  &aluno_atual.tempo_timeout);
            //calcula o score aplicando o round() da math.h
            aluno_atual.score = (int)round(aluno_atual.coeficiente_rendimento * 100.0) / aluno_atual.prioridade;
            //coloca o aluno na fila de espera por ordem de chegada
            enqueue(&fila_requisicoes, aluno_atual);
        } 
        
        //comando para processar um numero especifico de requisicoes
        else if (strcmp(comando_lido, "PROC") == 0) {
            int quantidade_processamento;
            scanf("%d", &quantidade_processamento); //le a quantidade de processamentos solicitada
            
            //executa o loop ate bater a quantidade ou a fila esvaziar
            for (int contador_loop = 0; contador_loop < quantidade_processamento && !isEmpty(&fila_requisicoes); contador_loop++) {
                //retira o primeiro aluno que estava aguardando
                Student aluno_em_analise = dequeue(&fila_requisicoes);
                
                //se o relogio do servidor estiver ocioso, salta para o tempo de chegada do aluno
                if (tempo_atual < aluno_em_analise.tempo_chegada) {
                    tempo_atual = aluno_em_analise.tempo_chegada;
                }
                
                //verifica se o tempo atual do servidor ultrapassou o limite do aluno
                if (tempo_atual > aluno_em_analise.tempo_timeout) {
                    printf("[TIMEOUT] mat=%lld | Desconectado da fila.\n", aluno_em_analise.matricula);
                    //alunos em timeout nao avancam o relogio do servidor
                } else {
                    //se ainda existirem vagas na disciplina
                    if (vagas_disponiveis > 0) {
                        printf("[ALOCADO] mat=%lld | score=%d | Processado no seg: %lld\n", 
                               aluno_em_analise.matricula, 
                               aluno_em_analise.score, 
                               tempo_atual);
                        //insere o aluno de forma ordenada na lista oficial de confirmados
                        enqueue(&fila_confirmados, aluno_em_analise);
                        vagas_disponiveis--; //decrementa as vagas disponiveis
                    } else {
                        //caso o aluno nao sofra timeout mas nao tenha mais vagas
                        printf("[LOTADO] mat=%lld | score=%d | Processado no seg: %lld\n", 
                               aluno_em_analise.matricula, 
                               aluno_em_analise.score, 
                               tempo_atual);
                    }
                    tempo_atual++; //avanca o relogio do servidor em 1 segundo por processamento valido
                }
            }
        } 
        
        //comando que encerra a listagem da materia atual
        else if (strcmp(comando_lido, "FIM") == 0) {
            //print o cabecalho oficial com o nome da disciplina
            printf("--- LISTA OFICIAL: %s ---\n", nome_disciplina);
            int posicao_lista = 1;
            
            //esvazia a fila de confirmados mostrando o resultado final
            while (!isEmpty(&fila_confirmados)) {
                Student aluno_final = dequeue(&fila_confirmados);
                printf("%d. Matricula: %lld\n", posicao_lista, aluno_final.matricula);
                posicao_lista++; //incrementa o contador de posicoes da lista
            }
            //limpa qualquer coisa que sobrar na fila de requisicoes
            freeQueue(&fila_requisicoes);
        }
    }

    return 0; 
}