#include <stdio.h>

int main() {

    int total, x, y, z;
    scanf("%d", &total);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    int A, B, C;
    int resto;
    int investiu = 0;
    int conseguiu_dividir = 0;

    /* verifica se a divis�o original gera valores inteiros */
    if ((total * x) % 100 == 0 && (total * y) % 100 == 0 && (total * z) % 100 == 0) {

        A = (total * x) / 100;
        B = (total * y) / 100;
        C = (total * z) / 100;

        resto = total - (A + B + C);

        conseguiu_dividir = 1;

    } else {

        /* Rebeka tenta adicionar at� 3 reais */
        int i = 1;

        /* continua enquanto ainda n�o encontrou divis�o v�lida */
        while (i <= 3 && conseguiu_dividir == 0) {

            int novo_total = total + i;

            if ((novo_total * x) % 100 == 0 &&
                (novo_total * y) % 100 == 0 &&
                (novo_total * z) % 100 == 0) {

                int a = (novo_total * x) / 100;
                int b = (novo_total * y) / 100;
                int c = (novo_total * z) / 100;

                int r = novo_total - (a + b + c);

                /* precisa sobrar mais do que ela investiu */
                if (r > i) {
                    A = a;
                    B = b;
                    C = c;
                    resto = r;
                    investiu = i;
                    conseguiu_dividir = 1;
                }
            }

            i++;
        }
    }

    int dinheiro_rebeka = 3; /* dinheiro inicial */

    if (conseguiu_dividir) {

        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", A, B, C);

        dinheiro_rebeka = dinheiro_rebeka - investiu + resto;

        /* desafios dependendo do investimento */
        if (investiu == 2) {

            char a, b, c;
            scanf(" %c %c %c", &a, &b, &c);

            /* converte letras para valores (a=1, b=2, ..., z=26) */
            int soma = (a - 'a' + 1) + (b - 'a' + 1) + (c - 'a' + 1);

            printf("%d\n", soma);

        } else if (investiu == 3) {

            int i1, i2, i3;
            scanf("%d %d %d", &i1, &i2, &i3);

            int parcelas = 0;

            /* soma quantas parcelas do n�mero 3 existem nas idades */
            if (i1 % 3 == 0) parcelas += i1 / 3;
            if (i2 % 3 == 0) parcelas += i2 / 3;
            if (i3 % 3 == 0) parcelas += i3 / 3;

            printf("%d\n", parcelas);
        }

    } else {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
    }

    /* verifica se ela conseguiu os 7 reais para o �nibus */
    if (dinheiro_rebeka >= 7) {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }

    return 0;
}
