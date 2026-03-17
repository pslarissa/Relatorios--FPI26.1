#include <stdio.h>

int main(){

    long long x; // número da fila de Xupenio
    int n;       // quantidade de canais

    scanf("%lld", &x);
    scanf("%d", &n);

    long long md = -1; // melhor distância
    int mc = -1;       // melhor canal
    int mm = -1;       // melhor minuto
    long long mt = -1; // melhor termo

    for(int i = 1; i <= n; i++){

        long long a, b; // primeiros números da sequência
        scanf("%lld %lld", &a, &b);

        long long t1 = a; // termo anterior
        long long t2 = b; // termo atual

        int min = 2; // minuto da sequência

        // gera sequência até passar de x
        while(t2 < x){
            long long t3 = t1 + t2;
            t1 = t2;
            t2 = t3;
            min++;
        }

        // calcula distância manualmente
        long long d1 = x - t1;
        if(d1 < 0) d1 = -d1;

        long long d2 = x - t2;
        if(d2 < 0) d2 = -d2;

        long long te; // termo escolhido
        int me;       // minuto escolhido

        if(d1 < d2){
            te = t1;
            me = min - 1;
        }
        else if(d2 < d1){
            te = t2;
            me = min;
        }
        else{
            // empate → pega o menor termo
            if(t1 < t2){
                te = t1;
                me = min - 1;
            }else{
                te = t2;
                me = min;
            }
        }

        long long da = x - te;
        if(da < 0) da = -da;

        // verifica se é o melhor canal
        if(md == -1 || da < md || (da == md && i > mc)){
            md = da;
            mc = i;
            mm = me;
            mt = te;
        }
    }

    // soma dos dígitos
    int soma = 0;
    long long temp = mt;

    while(temp > 0){
        soma += temp % 10;
        temp /= 10;
    }

    int vip = 0;
    if(soma > 10){
        vip = 1;
    }

    if(vip){
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", mc, mm);
    }
    else{
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", mc, mm);
    }

    return 0;
}
