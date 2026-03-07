#include <stdio.h>

int main (){

    long N, A, B;
    
    scanf("%ld", &N);
    scanf("%ld %ld", &A, &B);

    //soma total de 1 até N usando: N*(N+1)/2
    long total = N * (N + 1) / 2;

    // calculoa quantidade de múltiplos de A e a soma desses múltiplos (mA) usando: A * (mA*(mA+1)/2)
    long mA = N / A;    
    long somamA = A * (mA * (mA + 1) / 2);

    // calculo da quantidade de múltiplos de B e a soma desses múltiplos (mB) usando: B * (mB*(mB+1)/2)
    long mB = N / B;    
    long somamB = B * (mB * (mB + 1) / 2);      

    // calculo da quantidade de múltiplos de A*B e a soma desses múltiplos
    long mAB = N / (A * B); 
    long somamAB = (A * B) * (mAB * (mAB + 1) / 2);

    //resultado
    long resultado = total - somamA - somamB + somamAB;

    printf("%ld\n", resultado);

    // condicionais se o resultado é par ou ímpar
    if (resultado % 2 == 0) {
        printf("Lá ele!!!\n"); // se for par
    } else {
        printf("Opa xupenio AULAS...\n"); // se for ímpar
    }
    return 0;
}


