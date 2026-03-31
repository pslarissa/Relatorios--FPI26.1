#include <stdio.h>

int main() {
    int total_linhas, total_colunas;

    //scanf para a altura e largura da parede (m e n)
    if (scanf("%d %d", &total_linhas, &total_colunas) != 2) return 0;

    //matriz que representa a parede
    char parede[total_linhas][total_colunas];

    //preenchendo a matriz com o que for recebidos no input 
    for (int linha = 0; linha < total_linhas; linha++) {
        for (int coluna = 0; coluna < total_colunas; coluna++) {
            //espaço antes do %c serve para ignorar quebras de linha 
            scanf(" %c", &parede[linha][coluna]);
        }
    }

    // toda a logica funciona percorrendo de cima para baixo
    // vai apenas até a penúltima linha, pois a última não tem onde "cair"
    for (int linha = 0; linha < total_linhas - 1; linha++) {
        
        //Primeira passada na linha: Identifica gotas e espalha sobre prateleiras
        for (int coluna = 0; coluna < total_colunas; coluna++) {
            
            //condficional para saber se a posição atual tem água (aceita 'o' ou 'O')
            if (parede[linha][coluna] == 'o' || parede[linha][coluna] == 'O') {
                
                //A: O caminho abaixo está livre ('.')
                if (parede[linha + 1][coluna] == '.') {
                    parede[linha + 1][coluna] = 'o'; // A gota cai verticalmente
                } 
                
                //B: Existe uma prateleira ('#') logo abaixo
                else if (parede[linha + 1][coluna] == '#') {
                    
                    //movimento para a ESQUERDA sobre a prateleira
                    int auxiliar_esquerda = coluna - 1;
                    while (auxiliar_esquerda >= 0) {
                        parede[linha][auxiliar_esquerda] = 'o'; // qundo a agua escorre pro lado
                        
                        //Se a prateleira embaixo acabou, a água para de escorrer e cairá ali
                        if (parede[linha + 1][auxiliar_esquerda] != '#') {
                            break; 
                        }
                        auxiliar_esquerda--;
                    }

                    //movimento para a DIREITA sobre a prateleira
                    int auxiliar_direita = coluna + 1;
                    while (auxiliar_direita < total_colunas) {
                        parede[linha][auxiliar_direita] = 'o'; // Água escorre pro lado
                        
                        //se a prateleira embaixo acabou, a água para de escorrer e cairá ali
                        if (parede[linha + 1][auxiliar_direita] != '#') {
                            break;
                        }
                        auxiliar_direita++;
                    }
                }
            }
        }
        
        for (int coluna = 0; coluna < total_colunas; coluna++) {
            if (parede[linha][coluna] == 'o' && parede[linha + 1][coluna] == '.') {
                parede[linha + 1][coluna] = 'o';
            }
        }
    }

    //for para o print final (Matriz atualizada)
    for (int linha = 0; linha < total_linhas; linha++) {
        for (int coluna = 0; coluna < total_colunas; coluna++) {
            printf("%c", parede[linha][coluna]);
        }
        printf("\n"); 
    }

    return 0;
}