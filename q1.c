#include <stdio.h>

int main()
{
    //data de aniversario 
    int n1, n2, n3;
    
    //data atual
    int d1, d2, d3;
    
    int amor, sorte, trabalho, cor, diferenca;
    
    scanf("%d/%d/%d %d/%d/%d", &n1, &n2, &n3, &d1, &d2, &d3);

    //calculo de amor 
    amor = ((n1+n2+n3 + d1+d2+d3)*7)%101;
    
    printf("Amor: %d%%", amor); // ia usado para o problema  de printar o numero da porcentagem
  
  //condicionais de amor 
    if (amor < 20){
       printf(" Pessimo dia para se apaixonar.\n");
    }else if (amor >= 20 && amor <=  40){
        printf(" Melhor manter o coracao <3 longe de perigo.\n");
    }else if (amor >= 41 && amor <=69 ){
        printf(" Se o papo e as ideias baterem, esta liberado pensar em algo.\n");
    }else if (amor >= 70 && amor <=80){
        printf(" Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.\n");
    }else{
         printf(" Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.\n");
    }
    
    
    //calculo de sorte
    //condicionais para poder calcular a diferença (POSITIVA)
    if (n3> d3){
        diferenca = n3 - d3;
    }else { 
        diferenca = d3 - n3;
    }   
    sorte = (((n1+n2+n3 + d1+d2+d3)*9) - diferenca)%101;  
    
    printf("Sorte: %d%%", sorte);
    
    //condicionais de sortef
    if (sorte < 30){
        printf("Nem jogue moedas pra cima hoje.");
    } else if ( sorte >= 30 && sorte <=50){
        printf("Melhor nao arriscar.");
    } else if (sorte > 50 && sorte <= 79){
        printf("Por sua conta em risco.");
    }else if (sorte >= 80 && sorte <= 90){
        printf("Hoje vale a pena arriscar.");
    }else {
        printf("Nao tenha medo de virar cartas hoje.");
    }
    printf(" Sem tigrinho nem jogos de azar, por favor!");


    
    
    
    
    
    
    
    
    return 0;
}