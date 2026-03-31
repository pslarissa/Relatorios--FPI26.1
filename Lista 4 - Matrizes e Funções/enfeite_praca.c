#include <stdio.h>

int main() {
    int total_linhas, total_colunas;
    int linha, coluna;

    //scanf que cai receber as dimensões da praça
    scanf("%d %d", &total_linhas, &total_colunas);

    char matriz_praca[total_linhas][total_colunas];

    // for para receber onfiguração inicial da praça
    for (linha = 0; linha < total_linhas; linha++) {
        for (coluna = 0; coluna < total_colunas; coluna++) {
            // O espaço antes de %c ignora o 'enter' e espaços vazios
            scanf(" %c", &matriz_praca[linha][coluna]);
        }
    }

    // matriz para o resultado final
    char matriz_resultado[total_linhas][total_colunas];
    for (linha = 0; linha < total_linhas; linha++) {
        for (coluna = 0; coluna < total_colunas; coluna++) {
            matriz_resultado[linha][coluna] = matriz_praca[linha][coluna];
        }
    }

    //lendo as matriz para encontrar os postes 'P'
    for (linha = 0; linha < total_linhas; linha++) {
        for (coluna = 0; coluna < total_colunas; coluna++) {
            
            if (matriz_praca[linha][coluna] == 'P') {
                
                //1. DESENHANDO AS DIAGONAIS ('x') 
                for (int deslocamento_linha = -1; deslocamento_linha <= 1; deslocamento_linha += 2) {
                    for (int deslocamento_coluna = -1; deslocamento_coluna <= 1; deslocamento_coluna += 2) {
                        
                        int nova_linha = linha + deslocamento_linha;
                        int nova_coluna = coluna + deslocamento_coluna;

                        //  if para verificar limites da praça
                        if (nova_linha >= 0 && nova_linha < total_linhas && 
                            nova_coluna >= 0 && nova_coluna < total_colunas) {
                            
                            //espaços vazios '-' tornam-se 'x'
                            if (matriz_resultado[nova_linha][nova_coluna] == '-') {
                                matriz_resultado[nova_linha][nova_coluna] = 'x';
                            }
                        }
                    }
                }

                //2. DESENHANDO AS DIREÇÕES LATERAIS ('+')  --- O '+' sobrescreve o 'x' caso existam na mesma posição
                
                //Acima
                if (linha - 1 >= 0 && matriz_resultado[linha - 1][coluna] != 'P') {
                    matriz_resultado[linha - 1][coluna] = '+';
                }
                //Abaixo
                if (linha + 1 < total_linhas && matriz_resultado[linha + 1][coluna] != 'P') {
                    matriz_resultado[linha + 1][coluna] = '+';
                }
                //Esquerda
                if (coluna - 1 >= 0 && matriz_resultado[linha][coluna - 1] != 'P') {
                    matriz_resultado[linha][coluna - 1] = '+';
                }
                //Direita
                if (coluna + 1 < total_colunas && matriz_resultado[linha][coluna + 1] != 'P') {
                    matriz_resultado[linha][coluna + 1] = '+';
                }
            }
        }
    }

    // print do  resultado final
    for (linha = 0; linha < total_linhas; linha++) {
        for (coluna = 0; coluna < total_colunas; coluna++) {
            printf("%c", matriz_resultado[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}