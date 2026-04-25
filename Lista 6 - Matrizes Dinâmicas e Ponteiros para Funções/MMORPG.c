#include <stdio.h> // scanf e printf
#include <stdlib.h> // ponteiros e alocacao dinamica (malloc/free)
#include <string.h> // para comparar as strings 

// funcoes auxiliadres
// n  (HP atual) vai garantir que a vida nao fique negativa (HP minimo = 0)
int validar_hp(int n) {
    if (n < 0) return 0;
    return n;
}

// x, y: coordenadas. L, C: Linhas e Colunas totais. 
//verifica se a casa existe na matriz para evitar erro de memoria 
int dentro_do_mapa(int x, int y, int L, int C) {
    return (x >= 0 && x < L && y >= 0 && y < C);
}

// x, y: celula atual. ax, ay: alvo central do ataque. 
// funcao define se a celula e atingida e por qual camada (1: 50 dano, 2: 25 dano).
int identifica_camada(int x, int y, int ax, int ay) {
    int dx = abs(x - ax); // dx: distancia absoluta em X
    int dy = abs(y - ay); // dy: distancia absoluta em Y
    // Camada 1: Centro ou vizinhos ortogonais (cima, baixo, esquerda, direita).
    if ((dx == 0 && dy == 0) || (dx + dy == 1)) return 1;
    // Camada 2: Area secundaria (todas as 8 direcoes ao redor da camada 1).
    // Correcao: A camada 2 sao os vizinhos da camada 1. Isso equivale a distancia de Manhattan 2 ou os "cantos" proximos.
    if ((dx + dy == 2) || (dx == 2 && dy == 1) || (dx == 1 && dy == 2)) return 2;
    return 0;
}

// Funcoes de Alocacao
// L, C: Linhas e Colunas. 
// funcao da alocacao da matriz dinamica 
int** matriz_dinamica (int L, int C){
    // mat: matriz. vai guardar o endereco do vetor que aponta para as linhas
    // alocacao de um vetor que vai ser responsavel por guardar os enderecos dos ponteiros (LINHAS): 
    int **mat = (int**)malloc(L * sizeof(int*));
    int i = 0; // i: indice da linha atual 
    while (i < L){
        // alocacao do um vetor de inteiros para cada linha, para formar as colunas 
        mat[i] = (int*)malloc(C * sizeof(int));
        i++;
    }
    return mat;
}

// m: matriz a liberar. L: total de linhas. 
// Funcao para liberar a memoria 
void liberar_m(int **m, int L){
    int i = 0; // i: contador de linhas
    while (i < L){
        free(m[i]); // Libera as colunas primeiro
        i++;
    }
    free(m); 
}

// o: matriz origem. L, C: dimensoes. 
// Cria uma copia da matriz. Usado porque o programa deve gerar uma nova matriz sem modificar a original.
int** copiar_m(int **o, int L, int C) {
    int **nova = matriz_dinamica(L, C);
    int i = 0, j; // i, j: navegadores de Linha e Coluna
    while (i < L) {
        j = 0;
        while (j < C) {
            nova[i][j] = o[i][j];
            j++;
        }
        i++;
    }
    return nova;
}

//Logica de Combate

// m: mapa. x, y: posicao da celula. L, C: limites. 
// Conta vizinhos vivos (HP > 0). Usado para calcular o dano da Nuvem Venenosa.
int contar_vivos(int **m, int x, int y, int L, int C) {
    int v = 0; // v: vizinhos vivos (contador)
    // dx, dy: deslocamento x e y. Vetores estaticos para checar as 8 direcoes (vizinhos) -- permitido pelos monitores 
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int k = 0; // k: indice do loop das 8 direcoes
    while (k < 8) {
        int nx = x + dx[k]; // nx: novo x (vizinho calculado)
        int ny = y + dy[k]; // ny: novo y (vizinho calculado)
        if (dentro_do_mapa(nx, ny, L, C)) {
            if (m[nx][ny] > 0) v++;
        }
        k++;
    }
    return v;
}

// duncao Ataques

// m: matriz alvo. L, C: dimensoes. x, y: centro do ataque.
void explosao_arcana(int **m, int L, int C, int x, int y) {
    int i = 0, j; // i, j: indices para percorrer a matriz inteira
    while (i < L) {
        j = 0;
        while (j < C) {
            int cam = identifica_camada(i, j, x, y); // cam: camada da celula
            if (cam == 1) m[i][j] = validar_hp(m[i][j] - 50);
            else if (cam == 2) m[i][j] = validar_hp(m[i][j] - 25);
            j++;
        }
        i++;
    }
}

// funcao para: m: matriz. Retorna 0 se todos na area morrerem
int nuvem_venenosa_turno(int **m, int L, int C, int x, int y) {
    int **tmp = copiar_m(m, L, C); // tmp: matriz temporaria para o dano nao ser "em cascata".
    int i = 0, j, vivo = 0; //para saber se alguem na area ainda tem HP > 0.
    while (i < L) {
        j = 0;
        while (j < C) {
            if (identifica_camada(i, j, x, y) > 0) {
                if (m[i][j] > 0) {
                    int v = contar_vivos(m, i, j, L, C); //v: vizinhos vivos
                    tmp[i][j] = validar_hp(m[i][j] - (5 + 8 * v));
                }
                if (tmp[i][j] > 0) vivo = 1;
            }
            j++;
        }
        i++;
    }
    //sincroniza os danos calculados para a matriz principal.
    i = 0;
    while (i < L) {
        j = 0;
        while (j < C) { m[i][j] = tmp[i][j]; j++; }
        i++;
    }
    liberar_m(tmp, L);
    return vivo;
}

//FUNCAO PARA OUTPUT: m: matriz. L, C: dimensoes. print dos elementos da matriz.
void print_final(int **m, int L, int C){
    int i = 0, j; // i: linha, j: coluna
    while (i < L){
        j = 0;
        while (j < C){
            printf("%d", m[i][j]);
            if (j < C - 1) printf(" "); // espaco entre numeros
            j++;
        }
        printf("\n"); //pula linha ao fim de cada linha da matriz
        i++;
    }
}

int main() {
    int M, N, x, y; // M, N: dimensoes da matriz. x, y: coordenadas do ataque.
    char nome[30]; //nome - ipo de ataque (string)

    // leitura das dimensoes e tratando entrada
    if (scanf("%d %d", &M, &N) != 2) return 0;

    // Criando a matriz dinamica
    int **grid = matriz_dinamica(M, N); //grid: mapa principal
    int i = 0, j;
    while (i < M) {
        j = 0;
        while (j < N) {
            scanf("%d", &grid[i][j]); // elementos 
            j++;
        }
        i++;
    }

    scanf("%d %d", &x, &y); //Coordenadas do ataque
    scanf("%s", nome); //Nome do ataque

    printf("Estado inicial do mapa:\n");
    print_final(grid, M, N);
    printf("\n");

    //strcmp: compara strings. Se o resultado for 0, sao iguais. -- permitido pelos monitores 
    if (strcmp(nome, "EXPLOSAO_ARCANA") == 0) {
        int **res = copiar_m(grid, M, N); // res: matriz resultado
        printf("Estado do mapa após usar a Explosão Arcana:\n");
        explosao_arcana(res, M, N, x, y);
        print_final(res, M, N);
        liberar_m(res, M);
    } 
    else if (strcmp(nome, "NUVEM_VENENOSA") == 0) {
        int **res = copiar_m(grid, M, N);
        printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");
        int t = 0; //t: turno atual
        int cont = 1; //cont: flag de continuidade da simulacao
        while (t < 3 && cont) {
            cont = nuvem_venenosa_turno(res, M, N, x, y);
            print_final(res, M, N);
            t++;
            // Imprime linha em branco apenas entre os turnos, se houver um proximo turno a ser processado
            if (t < 3 && cont) printf("\n");
        }
        liberar_m(res, M);
    }

    liberar_m(grid, M); //liberacao de  memoria
    return 0;
}