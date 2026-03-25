#include <stdio.h>
#include <string.h>

int main() {
    char frase[105];
    int inicio_palavras[100]; // Guarda a posi��o (�ndice) inicial de cada palavra
    int tam_palavras[100];    // Guarda o tamanho de cada palavra
    int total_palavras = 0;
    int total_pares = 0;

    // Leitura da string
    if (fgets(frase, sizeof(frase), stdin) == NULL) return 0;

    // Remove o \n manual
    int len_f = 0;
    while (frase[len_f] != '\0') {
        if (frase[len_f] == '\n') frase[len_f] = '\0';
        len_f++;
    }

    //IDENTIFICA PALAVRAS (�NDICES E TAMANHOS) 
    for (int i = 0; frase[i] != '\0'; i++) {
        // erifica se � letra (Mai�scula ou Min�scula)
        if ((frase[i] >= 'a' && frase[i] <= 'z') || (frase[i] >= 'A' && frase[i] <= 'Z')) {
            inicio_palavras[total_palavras] = i; // Guarda onde a palavra come�a
            int cont = 0;

            //Enquanto for letra - avan�a e conta o tamanho
            while (frase[i] != '\0' && ((frase[i] >= 'a' && frase[i] <= 'z') || (frase[i] >= 'A' && frase[i] <= 'Z'))) {
                cont++;
                i++;
            }
            tam_palavras[total_palavras] = cont;
            total_palavras++;
            
            if (frase[i] == '\0') break;
        }
    }

    // COMPARA CADA PAR DE PALAVRAS 
    for (int j = 0; j < total_palavras; j++) {
        for (int k = j + 1; k < total_palavras; k++) {
            
            // S� podem ser anagramas se tiverem o mesmo tamanho
            if (tam_palavras[j] == tam_palavras[k]) {
                int freq[256] = {0};
                int eh_anagrama = 1;

                // Conta letras da palavra J na frase original
                for (int m = 0; m < tam_palavras[j]; m++) {
                    char c = frase[inicio_palavras[j] + m];
                    if (c >= 'A' && c <= 'Z') c += 32; // Converte para min�sculo
                    freq[(unsigned char)c]++;
                }

                // Subtrai letras da palavra K na frase original
                for (int m = 0; m < tam_palavras[k]; m++) {
                    char c = frase[inicio_palavras[k] + m];
                    if (c >= 'A' && c <= 'Z') c += 32; // Converte para min�sculo
                    freq[(unsigned char)c]--;
                }

                // Verifica se as contagens zeraram
                for (int m = 0; m < 256; m++) {
                    if (freq[m] != 0) {
                        eh_anagrama = 0;
                        break;
                    }
                }

                if (eh_anagrama) {
                    if (total_pares == 0) {
                        printf("Pares de anagramas encontrados:\n");
                    }
                    
                    // Imprime a primeira palavra do par
                    for (int m = 0; m < tam_palavras[j]; m++) {
                        printf("%c", frase[inicio_palavras[j] + m]);
                    }
                    printf(" e ");
                    // Imprime a segunda palavra do par
                    for (int m = 0; m < tam_palavras[k]; m++) {
                        printf("%c", frase[inicio_palavras[k] + m]);
                    }
                    printf("\n");
                    
                    total_pares++;
                }
            }
        }
    }

    //print final
    if (total_pares > 0) {
        printf("\nTotal de pares: %d\n", total_pares);
    } else {
        printf("Nao existem anagramas na frase.\n");
    }

    return 0;
}