#include <stdio.h>

int main() {
    int N, X, Y;
    if (scanf("%d %d %d", &N, &X, &Y) != 3) return 0;

    // Usamos um mapa de latas por minuto para busca instantânea O(1)
    int extras_por_minuto[10001]; 
    for(int i = 0; i < 10001; i++) extras_por_minuto[i] = 0;

    for (int i = 0; i < Y; i++) {
        int h, m, l;
        scanf("%d:%d %d", &h, &m, &l);
        int total_m = (h - 7) * 60 + m;
        // horários inválidos ou fora do limite do array
        if (total_m >= 0 && total_m < 10001) {
            extras_por_minuto[total_m] = l;
        }
    }

    int total_latas = 0;
    int vencedor_encontrado = 0;

    for (int i = 1; i <= N; i++) {
        // Cálculo: 50 * 3 min = 150 min. 07:00 + 150 min = 09:30.
        int minuto_atual = i * 3;
        int latas_do_cliente = 0;

        // mais de 1 lata
        if (extras_por_minuto[minuto_atual] > 0) {
            latas_do_cliente = extras_por_minuto[minuto_atual];
        } 
        // Múltiplos de X (1 lata)
        else if (X > 0 && i % X == 0) {
            latas_do_cliente = 1;
        }

        total_latas += latas_do_cliente;

        // Verifica se a 50ª lata foi atingida AGORA
        if (!vencedor_encontrado && total_latas >= 50) {
            int hh = 7 + (minuto_atual / 60);
            int mm = minuto_atual % 60;
            
            // PLUSRAL
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d %s.\n",i, hh, mm, latas_do_cliente, (latas_do_cliente == 1) ? "lata" : "latas");
            
            vencedor_encontrado = 1;
        }
    }

    if (!vencedor_encontrado) {
        int faltam = 50 - total_latas;
        // PLURAL
        if (faltam == 1) {
            printf("Ainda nao foram vendidas latas suficientes. Falta 1 lata.\n");
        } else {
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", faltam);
        }
    }

    return 0;
}