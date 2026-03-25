#include <stdio.h>
#include <string.h>

#define TAM_MAX_S 65
#define TAM_MAX_GIGANTE 70000 // Espa�o suficiente para R testes + ornamentos

/* L�gica do Clock:
   1. O primeiro LED sempre inverte.
   2. Se um LED passa de ligado (O) para desligado (X), o pr�ximo inverte.
*/

int main() {
    int R;
    if (scanf("%d", &R) == EOF) return 0;

    char luz_gigante[TAM_MAX_GIGANTE];
    luz_gigante[0] = '\0'; //inicializa a string gigante vazia
    int tamanho_gigante = 0;

    for (int r = 0; r < R; r++) {
        char s[TAM_MAX_S];
        int C;

        scanf("%s %d", s, &C);

        int n = strlen(s);

        //for para cada clock (flash)
        for (int c = 0; c < C; c++) {
            for (int i = 0; i < n; i++) {
                if (s[i] == 'X') { // desligado, vira ligado
                    s[i] = 'O';
                    break; //O sucessor N�O troca de estado
                } else { //ligado ('O'), vira desligado ('X')
                    s[i] = 'X';
                    //como foi desligado, o loop continua para inverter o sucessor
                }
            }
        }

        printf("%s\n", s);

        //Luz Gigante de Soneca (Jun��o dos fios)
        if (r > 0) {
            char ultimo_gigante = luz_gigante[tamanho_gigante - 1];
            char primeiro_novo = s[0];
            char ornamento;

            if (tamanho_gigante % 2 == 0) { //par
                if (ultimo_gigante == primeiro_novo) ornamento = '@';
                else ornamento = '$';
            } else { //�mpar
                if (ultimo_gigante == primeiro_novo) ornamento = '#';
                else ornamento = '%';
            }

            //Adiciona o ornamento
            luz_gigante[tamanho_gigante] = ornamento;
            luz_gigante[tamanho_gigante + 1] = '\0';
            tamanho_gigante++;
        }

        // coloca o fio atual na luz gigante
        for (int i = 0; s[i] != '\0'; i++) {
            luz_gigante[tamanho_gigante] = s[i];
            tamanho_gigante++;
        }
        luz_gigante[tamanho_gigante] = '\0';
    }

    //string final gigante
    printf("%s\n", luz_gigante);

    return 0;
}