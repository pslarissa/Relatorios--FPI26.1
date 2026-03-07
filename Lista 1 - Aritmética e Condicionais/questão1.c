#include <stdio.h>

int main()
{
    //data de aniversario 
    int n1, n2, n3;
    
    //data atual
    int d1, d2, d3;
    int amor, sorte, trabalho, cor;  
    int diferenca, soma;
    
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
    
    soma = n1+n2+ d1+d2;
    
    sorte = ((soma*9) + diferenca)%101; 
    
    printf("Sorte: %d%%", sorte);
    
    //condicionais de sortef
    if (sorte < 30){
        printf(" Nem jogue moedas pra cima hoje.");
    } else if ( sorte >= 30 && sorte <=50){
        printf(" Melhor nao arriscar.");
    } else if (sorte > 50 && sorte <= 79){
        printf(" Por sua conta em risco.");
    }else if (sorte >= 80 && sorte <= 90){
        printf(" Hoje vale a pena arriscar.");
    }else {
        printf(" Nao tenha medo de virar cartas hoje.");
    }
    printf(" Sem tigrinho nem jogos de azar, por favor!\n");
    
    
    // calculo do trabalho 
    trabalho = (n3 + d3 - (soma * 8))%101;
    
    printf("Trabalho: %d%%", trabalho);
        
    // condicionais do trabalho 
        
    if (trabalho < 40){
        printf(" Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n");
    }else if(trabalho >= 40 && trabalho <= 50){
        printf(" Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n");
    }else if (trabalho > 50 && trabalho <= 69){
        printf(" Um dia proveitoso com certeza, leve sua simpatia consigo.\n");
    }else if (trabalho  >= 70 && trabalho <= 84){
        printf(" Boas vibracoes hoje, chances podem estar ao seu redor.\n");
    }else {
        printf(" Use do maximo de networking possível hoje, dia bom para negocios.\n");
    }   
        
        
    //&n1, &n2, &n3, &d1, &d2, &d3);
    // calculo de cor 
    
    cor = ((n1 *n1) + (n2*n2) + (n3*n3) + (d1*d1) + (d2*d2) + (d3*d3))%11;
    
    printf ("Cor:");
    
    if (cor == 0){
        printf(" Cinza.");
    } else if (cor == 1){
        printf(" Vermelho.");
    }else if (cor ==2 ){
        printf(" Laranja.");
    }else if (cor == 3){
        printf(" Amarelo.");
    }else if (cor == 4){
        printf( " Verde.");
    }else if (cor == 5){
        printf(" Azul.");
    }else if (cor == 6){
        printf(" Roxo.");
    }else if (cor == 7){
        printf(" Marrom.");
    }else if (cor == 8){
        printf(" Rosa.");
    }else if (cor == 9){
        printf(" Preto.");
    }else if (cor == 10){
        printf(" Branco.");
    }
    
    return 0;
}
