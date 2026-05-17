#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef previa para o ponteiro de funcao
typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib_1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib_2;     // Atk: Custo Ener. | Def: Bonus de Slot   | Utl: Multiplicador
    
    // Ponteiro de funcao para execucao direta via hardware
    void (*sub_rotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                
    char modelo[50];
    int energia_at;      // Energia atual
    int num_sist;        // Numero de sistemas
    int val_winter;      // Contexto de dano
    SubSistema sistemas[]; // Flexible Array Member (FAM)
};

// Sub-rotinas de Combate

//Calcula impacto final: input - atrib_1 - (slot * atrib_2)
void def_sub(Mecha *m, int slot, int input, int *output) {
    int dano_f = input - (*m).sistemas[slot].atrib_1 - (slot * (*m).sistemas[slot].atrib_2);
    if (dano_f < 0) dano_f = 0;
    *output = dano_f;
}

//Recupera energia: atrib_1 + (slot * atrib_2)
void utl_sub(Mecha *m, int slot, int input, int *output) {
    int rec_base = (*m).sistemas[slot].atrib_1 + (slot * (*m).sistemas[slot].atrib_2);
    (*m).energia_at += rec_base;
    *output = (*m).energia_at; 
}

//Ataque: atrib_1 + energia_at + slot - input
void atk_sub(Mecha *m, int slot, int input, int *output) {
    int custo_en = (*m).sistemas[slot].atrib_2;
    if ((*m).energia_at < custo_en) {
        *output = -1; //Energia insuficiente
    } else {
        int dano_at = (*m).sistemas[slot].atrib_1 + (*m).energia_at + slot - input;
        (*m).energia_at -= custo_en;
        *output = dano_at;
    }
}

int main() {
    int n_mechas;
    if (scanf("%d", &n_mechas) != 1) return 0;

    //Vetor de ponteiros para o esquadrao
    Mecha **esquadrao = (Mecha **)malloc(n_mechas * sizeof(Mecha *));

    // Fase de Montagem
    for (int i = 0; i < n_mechas; i++) {
        int id_m, ene_ini, q_sist;
        char mod_m[50];
        scanf("%d %s %d %d", &id_m, mod_m, &ene_ini, &q_sist);

        //Alocacao em bloco unico (Mecha + Sistemas)
        Mecha *novo_m = (Mecha *)malloc(sizeof(Mecha) + (q_sist * sizeof(SubSistema)));
        (*novo_m).id = id_m;
        strcpy((*novo_m).modelo, mod_m);
        (*novo_m).energia_at = ene_ini;
        (*novo_m).num_sist = q_sist;

        for (int j = 0; j < q_sist; j++) {
            char tipo_s;
            scanf(" %c %s %d %d", &tipo_s, (*novo_m).sistemas[j].nome, &((*novo_m).sistemas[j].atrib_1), &((*novo_m).sistemas[j].atrib_2));
            
            //Atribuicao de sub-rotinas
            if (tipo_s == 'A') (*novo_m).sistemas[j].sub_rotina = atk_sub;
            else if (tipo_s == 'D') (*novo_m).sistemas[j].sub_rotina = def_sub;
            else if (tipo_s == 'U') (*novo_m).sistemas[j].sub_rotina = utl_sub;
        }
        
        scanf("%d", &((*novo_m).val_winter));
        *(esquadrao + i) = novo_m; 
    }

    // Ordenacao por ID 
    for (int i = 0; i < n_mechas - 1; i++) {
        for (int j = 0; j < n_mechas - i - 1; j++) {
            if ((*(*(esquadrao + j))).id > (*(*(esquadrao + j + 1))).id) {
                Mecha *temp_m = *(esquadrao + j);
                *(esquadrao + j) = *(esquadrao + j + 1);
                *(esquadrao + j + 1) = temp_m;
            }
        }
    }

    //Relatorio Final  da Fase de Combate 
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");
    for (int i = 0; i < n_mechas; i++) {
        Mecha *m_at = *(esquadrao + i);
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", (*m_at).id, (*m_at).modelo, (*m_at).energia_at);

        int res_sist;

        //PRIORIDADE 1: DEFESA
        for (int j = 0; j < (*m_at).num_sist; j++) {
            if ((*m_at).sistemas[j].sub_rotina == def_sub) {
                (*m_at).sistemas[j].sub_rotina(m_at, j, (*m_at).val_winter, &res_sist);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", (*m_at).sistemas[j].nome, res_sist);
            }
        }

        //PRIORIDADE 2: UTILIDADE
        for (int j = 0; j < (*m_at).num_sist; j++) {
            if ((*m_at).sistemas[j].sub_rotina == utl_sub) {
                (*m_at).sistemas[j].sub_rotina(m_at, j, (*m_at).val_winter, &res_sist);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", (*m_at).sistemas[j].nome, res_sist);
            }
        }

        //PRIORIDADE 3: ATAQUE
        for (int j = 0; j < (*m_at).num_sist; j++) {
            if ((*m_at).sistemas[j].sub_rotina == atk_sub) {
                (*m_at).sistemas[j].sub_rotina(m_at, j, (*m_at).val_winter, &res_sist);
                if (res_sist == -1) {
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", (*m_at).sistemas[j].nome);
                } else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", 
                           (*m_at).sistemas[j].nome, res_sist, (*m_at).energia_at);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", (*m_at).energia_at);
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");

    //Limpeza de memoria (boas praricasS)
    for (int i = 0; i < n_mechas; i++) free(*(esquadrao + i));
    free(esquadrao);

    return 0;
}