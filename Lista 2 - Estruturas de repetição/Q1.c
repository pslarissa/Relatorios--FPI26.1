#include <stdio.h>

int main(){
    char letra; 
    scanf("%c", &letra);

    // calcula a posicao da letra no alfabeto (A = 0, B = 1, C = 2, etc.)
    int posicao = letra - 'A';

    // loop para imprimir cada linha do triângulo
    for (int i = 0; i <= posicao; i++){
        // imprime os pontos antes das letras
        for (int j = 0; j < posicao - i; j++){
            printf(".");
        }

        // letras subindo -- direta 
        for (int l = 0; l <= i; l++){
            printf("%c", 'A' + l);
        }

        // letras descendo -- esquerda
        for (int m = i - 1; m >= 0; m--){
            printf("%c", 'A' + m);
        }
        // imprime os pontos depois das letras
        for (int j = 0; j < posicao - i; j++){
            printf(".");
        }

        printf("\n"); // \n para formar o triangulo 
    }
}
