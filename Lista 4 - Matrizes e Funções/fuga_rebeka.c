/*PASSO A PASSO DA LOGICA DA QUESTAO
1- leitura da matriz 
2- localizar origem 
3- fila - guardar as posições que vao ser visitadas
4 - matriz de distancia  (quantos metros beka percorreu)
5 - movimento 

*/

#include <stdio.h>

int main(){
    int total_linhas, total_colunas; // total linhas  e total colunas

    //scanf para ler o formato 3x4 -- esse consegue identidicar o 'x' no meio dos numeros 
    if(scanf("%dx%d", &total_linhas, &total_colunas) != 2) return 0;
    
    char mapa[100][100]; //vai armazenar os caracteres: #, _, o e d 
    int distancia[100][100]; //matiz que vai armazenar quantos passos beka levou para chegar em cada celula 
    int inicio_linha; //linha
    int inicio_coluna; //colunax
    
    // 1. for para ler o mapa e preparar a matriz de distâncias 
    for(int i = 0; i < total_linhas; i++){
        for (int j = 0; j < total_colunas; j++){
            scanf(" %c", &mapa[i][j]);
            distancia[i][j] = -1;// -1 vai indicar que beka ainda nao pisou 
            
            if (mapa[i][j] == 'o'){
                inicio_linha = i;
                inicio_coluna = j; 
                distancia[i][j] = 0;            
            }

        }
    }
 //2. Criando uma "Fila" para explorar o mapa passo a passo (BFS)
    //dvetores para guardar a linha e a coluna de cada posição a ser visitada
    int fila_linha[10000], fila_coluna[10000];
    int ponteiro_leitura = 0;  // ndica quem o sistema esta analisando agora
    int ponteiro_escrita = 0;  //Indica onde colocar o próximo caminho encontrado

    // adicionando osição inicial na fila
    fila_linha[ponteiro_escrita] = inicio_linha;
    fila_coluna[ponteiro_escrita] = inicio_coluna;
    ponteiro_escrita++;

    int encontrou_saida = 0;
    int metros_percorridos = 0;

    //Vetores de direção: Cima, Baixo, Esquerda, Direita -- Ex: {-1, 0} significa subir uma linha e manter a mesma coluna
    int mov_linha[] = {-1, 1, 0, 0};
    int mov_coluna[] = {0, 0, -1, 1};

    //3. Enquanto houver caminhos para explorar na fila
    while (ponteiro_leitura < ponteiro_escrita) {
        
        //Pega a posição atual da fila para checar os vizinhos
        int linha_atual = fila_linha[ponteiro_leitura];
        int coluna_atual = fila_coluna[ponteiro_leitura];
        ponteiro_leitura++;

        //Se a posição atual for a saída 'd', Rebeka escapou!
        if (mapa[linha_atual][coluna_atual] == 'd') {
            encontrou_saida = 1;
            metros_percorridos = distancia[linha_atual][coluna_atual];
            break; // Para o loop imediatamente
        }

        //Tenta se mover para as 4 direções vizinhas
        for (int i = 0; i < 4; i++) {
            int nova_linha = linha_atual + mov_linha[i];
            int nova_coluna = coluna_atual + mov_coluna[i];

            //if para saber se a nova posição está dentro dos limites do mapa
            if (nova_linha >= 0 && nova_linha < total_linhas && nova_coluna >= 0 && nova_coluna < total_colunas) {
                
                // só entra se não for parede ('#') E se Rebeka ainda não passou por lá (-1)
                if (mapa[nova_linha][nova_coluna] != '#' && distancia[nova_linha][nova_coluna] == -1) {
                    
                    //a distância do vizinho é a distância atual + 1 metro
                    distancia[nova_linha][nova_coluna] = distancia[linha_atual][coluna_atual] + 1;
                    
                    //Adiciona esse vizinho na fila para checar os vizinhos DELE depois
                    fila_linha[ponteiro_escrita] = nova_linha;
                    fila_coluna[ponteiro_escrita] = nova_coluna;
                    ponteiro_escrita++;
                }
            }
        }
    }

    //prints do resultado Final
    if (encontrou_saida) {
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", metros_percorridos);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }

    return 0;
}