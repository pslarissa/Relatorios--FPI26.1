#include <stdio.h>

int main(){

    int x, y, c; 
    int quadrante; 
    int destino;
    int passosx; 
    int passosy;

    scanf("%d %d %d", &x, &y, &c);

     // quadrante inicial 
    /*
    Quadrante	
        1	    x > 0 e y > 0
        2	    x < 0 e y > 0
        3	    x < 0 e y < 0
        4	    x > 0 e y < 0
    */
    // descobrir quadrante inicial
    if (x > 0 && y > 0) quadrante = 1;
    else if (x < 0 && y > 0) quadrante = 2;
    else if (x < 0 && y < 0) quadrante = 3;
    else quadrante = 4;

    // quadrante diagonal
    if (quadrante == 1) destino = 3;
    else if (quadrante == 2) destino = 4;
    else if (quadrante == 3) destino = 1;
    else destino = 2;

    // se tentar evitar o destino ? impossovel
    if (c == destino){
        printf("caminhada invalida\n");
        return 0;
    }

    // verificar se c a adjacente ao quadrante inicial
    if ((quadrante == 1 && c != 2 && c != 4) ||
        (quadrante == 2 && c != 1 && c != 3) ||
        (quadrante == 3 && c != 2 && c != 4) ||
        (quadrante == 4 && c != 1 && c != 3)){

        printf("caminhada invalida\n");
        return 0;
    }

    // calculo dos passos
    if (x < 0) passosx = -x + 1;
    else passosx = x + 1;

    if (y < 0) passosy = -y + 1;
    else passosy = y + 1;

    // decidir ordem para evitar o quadrante proibido
    if ((quadrante == 1 && c == 2) ||
        (quadrante == 2 && c == 1) ||
        (quadrante == 3 && c == 4) ||
        (quadrante == 4 && c == 3)){

        printf("%d passos em y e %d passos em x\n", passosy, passosx);
    }
    else{

        printf("%d passos em x e %d passos em y\n", passosx, passosy);
    }

    return 0;
}
