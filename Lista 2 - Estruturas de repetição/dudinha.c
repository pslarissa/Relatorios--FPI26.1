#include <stdio.h>

int main() {
    // N = iniio do intervalo
    // K = fim do intervalo (não incluido)
    // P = quantidade de fatores primos impares distintos desejada
    int N, K, P;
    scanf("%d %d %d", &N, &K, &P);

    // Variavel que vai guardar o primeiro numero valido encontrado. Começa com -1 para indicar que ainda nao encontrou nenhum.
    int primeiro = -1;

    // Q- quantos outros números válidos aparecem depois do primeiro dentro do intervalo.
    int Q = 0;

    // Percorre o intervalo [N, K) >> começa em N e vai até K-1
    for(int num = N; num < K; num++) {

        // Copia  o numero atual para outra variável porque ele vai ser modificador durante a fatoracao
        int n = num;

        // count vai guardar quantos fatores primos ímpares distintos foram encontrados 
        int count = 0;

        // invalido marca se o número possui fator primo repetido
        int invalido = 0;

        // Remove todos os fatores 2 do número.
        while(n % 2 == 0 && n > 0) {
            n = n / 2;
        }

        //teste de possíveis fatores primos ímpares.
        //Começa em 3 e aumentamos de 2 em 2 (3,5,7,9,...).
        //condição i*i <= n é suficiente para fatoração eficiente.
        for(int i = 3; i * i <= n && invalido == 0; i += 2) {

            // Contador de  quantas vezes o fator atual divide o número
            int vezes = 0;

            // Divide n por i enquanto i for fator -- encontra quantas vezes o primo aparece
            while(n % i == 0) {
                n = n / i;
                vezes++;
            }
            // o número possui fator repetido e não é válido
            if(vezes > 1) {
                invalido = 1;
            }

            // Se apareceu exatamente uma vez:encontra um novo fator primo ímpar distinto
            if(vezes == 1) {
                count++;
            }
        }

        // Após o loop, se n ainda for maior que 1, significa que ele próprio é um primo restante
        //(um primo grande que não foi dividido antes)
        if(n > 1) {
            count++;
        }

        //se o número atende às regras:
        // - não pode ser inválido
        // - precisa ter exatamente P primos ímpares distintos
        if(invalido == 0 && count == P) {

            // Se ainda não encontramos nenhum número válido, este será o primeiro
            if(primeiro == -1) {
                primeiro = num;
            } 
            else {
                //contacomo mais um depois do primeiro
                Q++;
            }
        }
    }

    // Depois de testar todos os números do intervalo:

    // Se primeiro continua -1, nenhum número válido foi encontrado
    if(primeiro == -1) {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.");
    } 
    else {
        // Caso contrário, mostramos o primeiro encontrado
        // e quantos outros apareceram depois dele
        printf("%d %d", primeiro, Q);
    }

    return 0;
}