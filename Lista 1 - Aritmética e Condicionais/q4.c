#include <stdio.h>

int main(){
    int x, y, c; 
    int quadrante; 
    int destino; // quadrante diagonal 
    int passosx; 
    int passosy;

    scanf("%d %d %d", &x, &y, &c);

    // quadrante inicial 
    /*
    Quadrante	condição
        1	    x > 0 e y > 0
        2	    x < 0 e y > 0
        3	    x < 0 e y < 0
        4	    x > 0 e y < 0
    */
    if (x > 0 && y> 0) quadrante = 1;
    else if (x < 0 && y > 0) quadrante = 2;
    else if (x < 0 && y < 0) quadrante = 3;
    else quadrante = 4;

    if (quadrante == 1) destino = 3;
    else if (quadrante == 2) destino = 4;
    else if (quadrante == 3) destino = 1 ;
    else destino = 2;
    
    //caminhada e=inválida
    if (c == quadrante || c == destino){
        printf("caminhada invalida\n");
        return 0; //encerra
    }
    
    if (x < 0){
        passosx = -x +1;
    }else {
        passosx = x +1;
    }

    if (y < 0){
        passosy = -y + 1;
    }else {
        passosy = y + 1;
    }
    
    // ordem
    if (c == 2 || c == 4) {
        printf ("%d passos em y e %d passos em x\n", passosy, passosx);
    }else {
        printf("%d passos em x e %d passos em y\n", passosx, passosy);
    }

    return 0;
}
