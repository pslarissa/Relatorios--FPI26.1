#include <stdio.h>
#include <stdlib.h>


/*É graças a esse No e ao ponteiro proximo que a pilha consegue crescer infinitamente (alocação dinâmica com malloc) e que conseguimos caminhar por ela para verificar se existem 3 cores iguais juntas */
//composicao da lista encadeada
struct No {
    char cor;           //armazena o caractere representativo da cor do bloco
    struct No *proximo; //ponteiro para o no  abaixo na struct da pilha
};

//Aloca memoria para um novo elemento e ajusta os ponteiros para inserir ele no topo
void empilhar(struct No **ponteiro_topo, char nova_cor) {
    //reserva dinamicamente o espaco de memoria necessario para o novo no
    struct No *novo_no = (struct No *)malloc(sizeof(struct No));
    if (novo_no != NULL) {
        //atribui o caractere recebido ao campo de dados do novo no
        (*novo_no).cor = nova_cor;
        //responsavel por fazer o  ponteiro do novo no apontar para o antigo topo da pilha
        (*novo_no).proximo = *ponteiro_topo;
        //atualiza o endereco do topo na funcao chamadora para apontar para este novo no
        *ponteiro_topo = novo_no;
    }
}

//remove a referencia do topo corrente resgatando o valor e desaloca a memoria
char desempilhar(struct No **ponteiro_topo) {
    char cor_retorno = '\0';
    if (*ponteiro_topo != NULL) {
        //armazena temporariamente o endereco do no que sera removido
        struct No *temporario = *ponteiro_topo;
        //captura o caractere guardado no topo para posterior retorno
        cor_retorno = (*temporario).cor;
        //avanca o ponteiro de topo da funcao chamadora para o elemento imediatamente inferior
        *ponteiro_topo = (*temporario).proximo;
        //libera o espaco de memoria descartado no heap
        free(temporario);
    }
    return cor_retorno;
}

//percorre toda a estrutura a partir do topo e exibe cada elemento sequencialmente
void imprimir_pilha(struct No *atual) {
    if (atual == NULL) {
        //caso o ponteiro de topo seja nulo, a pilha nao contem elementos
        printf("Pilha vazia!\n");
    } else {
        //utiliza um ponteiro auxiliar para caminhar pela lista sem perder o topo original
        struct No *auxiliar = atual;
        while (auxiliar != NULL) {
            //exibe a cor armazenada no no atual da iteracao
            printf("%c\n", (*auxiliar).cor);
            //desloca o ponteiro auxiliar para o proximo no abaixo na pilha
            auxiliar = (*auxiliar).proximo;
        }
    }
    printf("\n");
}

int main() {
    //inicializa a pilha com o ponteiro de topo apontando para nulo (pilha vazia)
    struct No *topo = NULL;
    char caractere_entrada;

    //vai ler ate EOF
    while (scanf(" %c", &caractere_entrada) != EOF) {
        //insere o caractere lido diretamente no topo da pilha encadeada
        empilhar(&topo, caractere_entrada);

        //variavel de controle para reiniciar as verificacoes sempre que houver modificacao na pilha
        int continuar_verificacao = 1;
        
        //executa varreduras consecutivas para tratar reacoes em cadeia e fusoes sucessivas
        while (continuar_verificacao == 1) {
            //pressupoe que nenhuma alteracao ocorrera nesta iteracao do laco
            continuar_verificacao = 0;

            //condicao para eliminacao de trios: testa se existem pelo menos 3 nos empilhados
            if (topo != NULL && (*topo).proximo != NULL && (*((*topo).proximo)).proximo != NULL) {
                //extrai a cor do no que esta no topo
                char c1 = (*topo).cor;
                //extrai a cor do segundo no (um nivel abaixo do topo)
                char c2 = (*((*topo).proximo)).cor;
                //extrai a cor do terceiro no (dois niveis abaixo do topo)
                char c3 = (*((*((*topo).proximo)).proximo)).cor;

                //se os tres nos vizinhos possuirem cores identicas, remove-os da memoria
                if (c1 == c2 && c2 == c3) {
                    desempilhar(&topo); //remove o primeiro no do topo
                    desempilhar(&topo); //remove o segundo no que assumiu o topo
                    desempilhar(&topo); //remove o terceiro no correspondente ao trio
                    //sinaliza alteracao para avaliar se a nova configuracao gerou novas fusoes
                    continuar_verificacao = 1;
                }
            }

            //condicao para fusao de duplas: avaliada apenas se nao houve eliminacao por trio
            if (continuar_verificacao == 0 && topo != NULL && (*topo).proximo != NULL) {
                //resgata os dados dos dois nos superiores da pilha
                char c1 = (*topo).cor;
                char c2 = (*((*topo).proximo)).cor;

                //conmbinacao do bloco verde (g) com bloco azul (b)
                if ((c1 == 'g' && c2 == 'b') || (c1 == 'b' && c2 == 'g')) {
                    desempilhar(&topo);    //descarta o primeiro componente da fusao
                    desempilhar(&topo);    //descarta o segundo componente da fusao
                    empilhar(&topo, 'c');  //adiciona o resultado da fusao (ciano) no topo
                    continuar_verificacao = 1; //ativa flag para nova inspecao estrutural
                }
                //combinacao: bloco vermelho (r) com bloco azul (b)
                else if ((c1 == 'r' && c2 == 'b') || (c1 == 'b' && c2 == 'r')) {
                    desempilhar(&topo);    //desaloca o primeiro componente
                    desempilhar(&topo);    //desaloca o segundo componente
                    empilhar(&topo, 'm');  //adiciona o resultado da fusao (magenta) no topo
                    continuar_verificacao = 1; //forca nova iteracao de checagem
                }
                //combinacao: bloco vermelho (r) com bloco verde (g)
                else if ((c1 == 'r' && c2 == 'g') || (c1 == 'g' && c2 == 'r')) {
                    desempilhar(&topo);    //remove da estrutura o primeiro componente
                    desempilhar(&topo);    //remove da estrutura o segundo componente
                    empilhar(&topo, 'y');  //adiciona o bloco resultante (amarelo)
                    continuar_verificacao = 1; //sinaliza necessidade de reavaliacao do topo
                }
            }
        }

        //printa a configuracao atual da pilha apos o processamento e fusoes do caractere
        imprimir_pilha(topo);
    }

    printf("Thank You So Much For Playing My Game!\n"); //printe da mensagem orbrigatoria

    //liberacao de toda memoria alocada no heap
    while (topo != NULL) {
        desempilhar(&topo); //Desaloca cada no remanescente recursivamente ate o topo ser NULL
    }

    return 0;
}
