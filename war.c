
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_TERRITORIOS 5
#define MAX_NOME 100
#define MAX_COR 50

// --- Estrutura de dados ---
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// --- Protótipos ---
void limparBufferEntrada(void);
void cadastrarTerritorios(Territorio mapa[], size_t n);
void exibirMapa(const Territorio mapa[], size_t n);
void removerNovaLinha(char *s);

int main(void) {
    Territorio mapa[N_TERRITORIOS]; // vetor estático de 5 elementos

    printf("Cadastro de %d territórios\n", N_TERRITORIOS);
    cadastrarTerritorios(mapa, N_TERRITORIOS);

    printf("\nEstado atual do mapa:\n");
    exibirMapa(mapa, N_TERRITORIOS);

    return 0;
}

// --- Implementações ---

// Remove \n final deixado por fgets
void removerNovaLinha(char *s) {
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len-1] == '\n') s[len-1] = '\0';
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}

void cadastrarTerritorios(Territorio mapa[], size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("\n--- Território %zu ---\n", i + 1);

        // Nome
        printf("Nome: ");
        if (fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin) == NULL) {
            mapa[i].nome[0] = '\0';
        }
        removerNovaLinha(mapa[i].nome);

        // Cor do Exército
        printf("Cor do exército dominante: ");
        if (fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin) == NULL) {
            mapa[i].cor[0] = '\0';
        }
        removerNovaLinha(mapa[i].cor);

        // Número de Tropas (scanf) - usa limparBufferEntrada depois
        printf("Número de tropas: ");
        if (scanf("%d", &mapa[i].tropas) != 1) {
            // leitura inválida -> definir 0 e limpar buffer
            mapa[i].tropas = 0;
        }
        limparBufferEntrada(); // remove o '\n' deixado pelo usuário
    }
}

void exibirMapa(const Territorio mapa[], size_t n) {
    printf("+----+--------------------------------+----------------------+------------+\n");
    printf("| ID | Nome                           | Cor do Exército      | Tropas     |\n");
    printf("+----+--------------------------------+----------------------+------------+\n");
    for (size_t i = 0; i < n; ++i) {
        // imprime com largura fixa para colunas
        printf("| %2zu | %-30s | %-20s | %10d |\n", i + 1,
               mapa[i].nome[0] ? mapa[i].nome : "(sem nome)",
               mapa[i].cor[0] ? mapa[i].cor : "(sem cor)",
               mapa[i].tropas);
    }
    printf("+----+--------------------------------+----------------------+------------+\n");
}
