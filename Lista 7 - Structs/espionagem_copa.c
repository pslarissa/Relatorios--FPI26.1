#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// type def para os dados das cidadelas registradas
typedef struct {
    char *nome_cid;
    char *func_cid;
    char *per_str;    // Periculosidade (string de asteriscos)
    int pop_cid;      // Populacao em milhares
    int niv_per;      // Contador de periculosidade
} Cidadela;

// Ponteiro para funcao de ordenacao
typedef int (*ptr_ord)(Cidadela *, Cidadela *);

// Formata strings: Primeira letra em Maiuscula e demais em Minuscula
void format_str(char *s) {
    if (*s != '\0') {
        *s = (char)toupper((int)*s); //Primeira letra
        char *p_aux = s + 1;
        while (*p_aux != '\0') {
            *p_aux = (char)tolower((int)*p_aux); //Restante
            p_aux++;
        }
    }
}

//Comparacao lexicografica manual
int comp_str(char *s1, char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    //unsigned char garante que caracteres especiais sejam tratados como valores positivos (0-255), evitando erros de sinal na subtracao.
    return (unsigned char)*s1 - (unsigned char)*s2;
}

// ordenacao: Pop (desc), Perigo (desc), Nome (asc)
int ord_cid(Cidadela *a, Cidadela *b) {
    //1. Populacao decrescente
    if ((*a).pop_cid != (*b).pop_cid) {
        return (*b).pop_cid - (*a).pop_cid;
    }
    //2. Periculosidade decrescente
    if ((*a).niv_per != (*b).niv_per) {
        return (*b).niv_per - (*a).niv_per;
    }
    //3. Alfabetica crescente (Desempate final)
    return comp_str((*a).nome_cid, (*b).nome_cid);
}

int main() {
    //Alocacao de buffers e lista de ponteiros
    char *msg_in = (char *)malloc(300 * sizeof(char));
    Cidadela **lista_c = (Cidadela **)malloc(1000 * sizeof(Cidadela *));
    int cont_cid = 0;
    int chave_n = -1;
    int msg_esp = 0;

    //processamento do fluxo de entrada
    while (fgets(msg_in, 290, stdin) != NULL) {
        int is_esp = 0;
        //Identifica se a mensagem possui a exclamacao
        for (int i = 0; *(msg_in + i) != '\0'; i++) {
            if (*(msg_in + i) == '!') is_esp = 1;
        }

        if (is_esp) {
            int n_aux = 0;
            //Extrai os digitos para formar a chave N
            for (int i = 0; *(msg_in + i) != '\0'; i++) {
                if (isdigit((int)*(msg_in + i))) n_aux = (n_aux * 10) + (*(msg_in + i) - '0');
            }
            chave_n = n_aux;
            msg_esp = 1;
        } else {
            //nova cidadela
            Cidadela *nova_c = (Cidadela *)malloc(sizeof(Cidadela));
            (*nova_c).nome_cid = (char *)calloc(210, sizeof(char));
            (*nova_c).func_cid = (char *)calloc(210, sizeof(char));
            (*nova_c).per_str = (char *)calloc(210, sizeof(char));
            
            int p_nom = 0, p_fun = 0, p_per = 0;
            long pop_tot = 0;

            //Varredura da frase para extrair os codigos
            for (int i = 0; *(msg_in + i) != '\0' && *(msg_in + i) != '\n' && *(msg_in + i) != '\r'; i++) {
                char c = *(msg_in + i);
                
                //Extrai Nome (Letras Maiusculas)
                if (isupper((int)c)) {
                    *((*nova_c).nome_cid + p_nom) = c;
                    p_nom++;
                }
                //Extrai Populacao
                else if (isdigit((int)c)) {
                    pop_tot = (pop_tot * 10) + (c - '0');
                }
                //Extrai Periculosidade
                else if (c == '*') {
                    *((*nova_c).per_str + p_per) = '*';
                    p_per++;
                }
                //Regra do Espaco Duplo: Ativa captura da Funcao (apenas iniciais)
                if (c == ' ' && *(msg_in + i + 1) == ' ') {
                    while (*(msg_in + i) == ' ') i++; 
                    if (isalpha((int)*(msg_in + i))) {
                        *((*nova_c).func_cid + p_fun) = *(msg_in + i);
                        p_fun++;
                    }
                    i--; 
                }
            }
            
            //Finalizando as strings e dados
            (*nova_c).pop_cid = (int)pop_tot;
            (*nova_c).niv_per = p_per;
            format_str((*nova_c).nome_cid);
            format_str((*nova_c).func_cid);
            
            //Valida se a mensagem continha um nome (Cidadela valida)
            if (p_nom > 0) {
                *(lista_c + cont_cid) = nova_c;
                cont_cid++;
            } else {
                free((*nova_c).nome_cid); free((*nova_c).func_cid);
                free((*nova_c).per_str); free(nova_c);
            }
        }
    }

    //conclusao da missao
    if (msg_esp == 0) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } else {
        //Bubble Sort via ponteiro de funcao
        ptr_ord f_ord = ord_cid;
        for (int i = 0; i < cont_cid - 1; i++) {
            for (int j = 0; j < cont_cid - i - 1; j++) {
                if (f_ord(*(lista_c + j), *(lista_c + j + 1)) > 0) {
                    Cidadela *c_tmp = *(lista_c + j);
                    *(lista_c + j) = *(lista_c + j + 1);
                    *(lista_c + j + 1) = c_tmp;
                }
            }
        }

        //Loc da Gingrey
        if (chave_n > 0 && chave_n <= cont_cid) {
            Cidadela *res_c = *(lista_c + chave_n - 1);
            printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade %s.", 
                   (*res_c).nome_cid, (*res_c).pop_cid, (*res_c).func_cid, (*res_c).per_str);
            
            int is_den = ((*res_c).pop_cid >= 1000);
            int is_per = ((*res_c).niv_per > 3);
            
            if (is_den && is_per) printf(" Talvez seja melhor desistir...\n");
            else if (is_den) printf(" Um lugar denso, vai ser difícil achar ela.\n");
            else if (is_per) printf(" Vai ser complicado entrar lá.\n");
            else printf("\n");
        } else {
            printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        }
    }

    //Limpeza de memoria (boas praticas)
    for (int k_idx = 0; k_idx < cont_cid; k_idx++) {
        free((*(*(lista_c + k_idx))).nome_cid);
        free((*(*(lista_c + k_idx))).func_cid);
        free((*(*(lista_c + k_idx))).per_str);
        free(*(lista_c + k_idx));
    }
    free(lista_c);
    free(msg_in);

    return 0;
}