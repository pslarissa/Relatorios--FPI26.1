#include <stdio.h>

int main(){
    //definiçao de variaveis 
    int x, y, z, total;
    int valorx, valory, valorz;
    int investimento = 0;
    int resto;   
    
    scanf("%d", &total);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    // para divisao inteira 
    if ((total * x) % 100 == 0 && (total * y) % 100 == 0 && (total * z) % 100 == 0){
        valorx = (total * x) / 100;
        valory = (total * y) / 100;
        valorz = (total * z) / 100;
        
        resto = total - (valorx + valory + valorz);
        
    } else {
        //para disao com resto (totsal com resto)
        int tcr = total + 1;

        if ((tcr * x) % 100 == 0 && (tcr * y) % 100 == 0 && (tcr * z) % 100 == 0){
            valorx = (tcr * x) / 100;
            valory = (tcr * y) / 100;
            valorz = (tcr * z) / 100;
            
            resto = tcr - (valorx + valory + valorz);
            
            if (resto >= 2){ // precisa sobrar mais do que ela investiu
                investimento = 1;
            }
        }

        // 2 reais investidos 
        if (investimento == 0) {
            tcr = total + 2;

            if ((tcr * x) % 100 == 0 && (tcr * y) % 100 == 0 && (tcr * z) % 100 == 0){
                valorx = (tcr * x) / 100;
                valory = (tcr * y) / 100;
                valorz = (tcr * z) / 100;
                
                resto = tcr - (valorx + valory + valorz);
                
                if (resto >= 3){ // precisa sobrar mais do que ela investiu
                    investimento = 2;
                }
            }
        } 

        // 3 reais 
        if (investimento == 0) {
            tcr = total + 3;

            if ((tcr * x) % 100 == 0 && (tcr * y) % 100 == 0 && (tcr * z) % 100 == 0){
                valorx = (tcr * x) / 100;
                valory = (tcr * y) / 100;
                valorz = (tcr * z) / 100;
                
                resto = tcr - (valorx + valory + valorz);
                
                if (resto >= 4){ // precisa sobrar mais do que ela investiu
                    investimento = 3;
                }
            }
        }  
        
        // se der tudo errado 
        if (investimento == 0) {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
            printf("E parece que Rebeka vai ter que voltar andando...\n");
            return 0;   // parar o programa
        }
    }

    // divisao resultado 
    printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n",valorx, valory, valorz);

    // condicional caso Rebeka tenha investido 2 reais
    if (investimento == 2) {    
        char l1, l2, l3;

        scanf(" %c %c %c", &l1, &l2, &l3);

        //conversao leras - numeros 
        int v1 = l1 - 'a' + 1;
        int v2 = l2 - 'a' + 1;
        int v3 = l3 - 'a' + 1;

        int soma = v1 + v2 + v3;

        printf("%d\n", soma);
    }

    if (investimento == 3){
        int idade1, idade2, idade3;
        int cont = 0; // contador 
        
        scanf("%d %d %d", &idade1, &idade2, &idade3);

        //fatores de 3 na primeira idade
        if (idade1 % 3 == 0){
            cont++;
            idade1 = idade1 / 3;
        }
         if (idade1 % 3 == 0){
            cont++;
            idade1 = idade1 / 3;
        }
        if (idade1 % 3 == 0){
            cont++;
            idade1 = idade1 / 3;
        }
        if (idade1 % 3 == 0){
            cont++;
        }//fatores de 3 na segunda idade
        if (idade2 % 3 == 0){
            cont++;
            idade2 = idade2 / 3;
        }
        if (idade2 % 3 == 0){
            cont++;
            idade2 = idade2 / 3;
        }
        if (idade2 % 3 == 0){
            cont++;
            idade2 = idade2 / 3;
        }
        if (idade2 % 3 == 0){
            cont++;
        }

        //fatores de 3 na terceira idade
        if (idade3 % 3 == 0){
            cont++;
            idade3 = idade3 / 3;
        }
        if (idade3 % 3 == 0){
            cont++;
            idade3 = idade3 / 3;
        }
        if (idade3 % 3 == 0){
            cont++;
            idade3 = idade3 / 3;
        }
        if (idade3 % 3 == 0){
            cont++;
        }

        printf("%d\n", cont);
    }

    int dinrebeka = resto;

    if (dinrebeka >= 7){
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    }
    else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }
    
    return 0;
}
