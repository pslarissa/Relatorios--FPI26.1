/*
PASSO A PASSO DA LOGICA DA QUESTAO 
1 - Ler T casos de teste
2- Para cada caso:
  - Ler o tamanho N
  - Ler o vetor
3- Percorrer o vetor e encontrar a maior sequência decrescente contínua
4- Guardar:
  - tamanho da maior sequência
  - posição onde ela começa
5 - Imprimir:
  - o tamanho
  - os elementos da sequência
*/

#include <stdio.h>

int main(){
    // numero de casos teste 
    int casos_teste; 
    scanf("%d", &casos_teste); 

    // tamanho da sequencia 
    int tamanho_sequencia;
    // numeros que representam a sequencia 
    int numeros_sequencia; 

    //loop dos casos teste e a cada volta diminui o tamanho da sequencia
    while (casos_teste > 0){
        scanf("%d", &tamanho_sequencia);// recendo o tamanho da sequencia / vetor
        casos_teste--; 

        int vetor[100]; //  vetor armazena ate 100 numeros

        // loop que vai ler os valores do vetor 
        for(int i = 0; i < tamanho_sequencia; i++){
            scanf("%d",&vetor[i]);// [i] representa cada posicao e preenche o vetor
        }

        // variaveis de controle 
        int tamanho_maximo = 0; // maior sequencia encontrada
        int tamanho_atual = 1; // tamanho da sequencia atual
        int inicio_maximo = 0; // onde comeca a maior sequencia 
        int inicio_atual = 0; // onde começa a sequencia atual

        // for para percorrer o vetor
        for (int i =1; i < tamanho_sequencia; i++){// começa no indice 1 porque vai ser comparado com o vetor anterior 
            // condicao para verificar se o numero atual é menor que o anterior 
            if (vetor[i] < vetor[i-1]){
                tamanho_atual++;
            }else{
                if (tamanho_atual > tamanho_maximo && tamanho_atual > 1){
                    tamanho_maximo = tamanho_atual; // salva o tamnho
                    inicio_maximo = inicio_atual; // salva onde ela começou
                }
                // começa uma nova sequencia a partir do numero atual
                tamanho_atual = 1;
                inicio_atual = i;
            }
        }

        // verifica a ultima sequencia 
        if (tamanho_atual > tamanho_maximo && tamanho_atual> 1){
            tamanho_maximo = tamanho_atual;
            inicio_maximo = inicio_atual; 
        }

        if(tamanho_maximo == 0){
            printf("0\n");

        }else{
            printf("%d\n", tamanho_maximo); // print tmanho 
            // print sequencia  com for 
            for (int i = 0; i < tamanho_maximo; i++){
                printf("%d ", vetor[inicio_maximo + i]);
            }

            printf("\n");
        }
    }

    return 0;

}