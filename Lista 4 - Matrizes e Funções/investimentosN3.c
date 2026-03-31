#include <stdio.h>

int main() {
    // Vetor para armazenar os 20 passos que Reypedrof vai dar  para fugir da Manuela
    char movimentos[20];
    
    //cidade representada por uma matriz 4x4. com todos os locais inciados  com 0 visitas.
    int matriz[4][4] = {0};
    int i;

    //Reypedrof começa sua fuga no canto superior esquerdo (0,0)
    int x = 0, y = 0;

    //for para recevber  dos 20 comandos de direção (c, b, e, d)
    for(i = 0; i < 20; i++) {
        //O espaço antes de %c ignora espaços em branco entre as letras
        scanf(" %c", &movimentos[i]);
    }

    // movimentação pela cidade 
    for(i = 0; i < 20; i++) {

        // 'c' move para cima: decrementa a linha (x)
        if(movimentos[i] == 'c') {
            if(x > 0) x--; 
        }
        // 'b' move para baixo: incrementa a linha (x)
        else if(movimentos[i] == 'b') {
            if(x < 3) x++; 
        }
        // 'e' move para a esquerda: decrementa a coluna (y)
        else if(movimentos[i] == 'e') {
            if(y > 0) y--; 
        }
        // 'd' move para a direita: incrementa a coluna (y)
        else if(movimentos[i] == 'd') {
            if(y < 3) y++; 
        }

        // Adiciona +1 para cada passo que Pedro segue em um local específico
        matriz[x][y]++;
    }

    //Manuela estará esperando no local onde Pedro passou mais vezes (maior contagem)
    int max = -1; // Iniciado com um valor baixo para encontrar o máximo real
    int posX = 0, posY = 0;

    //leitura da matriz para encontrar a coordenada mais visitada
    for(i = 0; i < 4; i++) {
        int j;
        for(j = 0; j < 4; j++) {
            // Se o local atual tiver mais registros que o máximo encontrado anteriormente
            if(matriz[i][j] > max) {
                max = matriz[i][j];
                // Salva as coordenadas. Seguindo a lógica do exemplo:
                // i representa as linhas (Eixo Y na saída visual) e j as colunas (Eixo X)
                posX = j; 
                posY = i; 
            }
        }
    }

    // print da coordenada final onde a Manuela (executora do agiota) estará esperando
    printf("Coordenada X:%d, Y:%d\n", posX, posY);

    return 0;
}