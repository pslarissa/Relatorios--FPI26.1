#include <stdio.h>

int main() {

    int q;
    scanf("%d", &q); // lê quantas instruções de movimento existirão


    char linhas[200][200];  //cada linha da grade guardada 

    int tamanho[200] = {0}; // guarda até qual coluna cada linha foi usada (para não imprimir espaços extras)

    // posição atual do cursor
    int linha = 0;
    int coluna = 0;

    int max_linha = 0;// maior linha que o cursor já visitou

    for(int i = 0; i < 200; i++){
        for(int j = 0; j < 200; j++){
            linhas[i][j] = ' ';
        }
    }

    for(int i = 0; i < q; i++) {

        int x;
        char c;

        scanf("%d %c", &x, &c); // lê quantidade de passos e direção

        if(c == 'D') {

            for(int j = 0; j < x; j++) {

                coluna++; // move para a direita

                if(coluna >= tamanho[linha]) // atualiza o tamanho da linha usada
                    tamanho[linha] = coluna + 1;

                linhas[linha][coluna] = '.'; // marca visita na posição
            
            }
        }

        else if(c == 'E') {

            //if para saber se e é possível mover para esquerda
            if(coluna - x < 0) {
                printf("Informacao invalida\n");
                return 0;
                // encerra o programa
            }

            for(int j = 0; j < x; j++) {

                coluna--;
                //esquerda

                if(coluna >= tamanho[linha])
                    tamanho[linha] = coluna + 1;

                linhas[linha][coluna] = '.'; // guarda a visita
            }
        }

        else if(c == 'B') {

            for(int j = 0; j < x; j++) {

                linha++;
                //desce uma linha

                if(coluna >= tamanho[linha])
                    tamanho[linha] = coluna + 1;
                //tualiza o tamanho usado dessa linha

                linhas[linha][coluna] = '.';
                //marca a visita na nova linha
            }

            if(linha > max_linha)
                max_linha = linha;
            //atualiza a maior linha que ja foi visitada
        }
    }

    // loop para output da grade final
    for(int i = 0; i <= max_linha; i++) {

        for(int j = 0; j < tamanho[i]; j++) {

            if(linhas[i][j] == '.')
                printf(".");
            else
                printf(" ");
            // printa spaço se a célula nunca foi visitada
        }

        printf("\n");
    }

    return 0;
}