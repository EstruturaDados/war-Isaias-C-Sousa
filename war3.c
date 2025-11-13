#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Protótipos das funções ---
void cadastrarTerritorios(Territorio* mapa, int qtd);
void exibirMapa(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2);

int main() {
    srand(time(NULL));

    int qtd;
    printf("Digite o número total de territórios: ");
    scanf("%d", &qtd);

    // Alocação dinâmica para o vetor de territórios
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para os territórios.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);
    exibirMapa(mapa, qtd);

    // --- Sistema de Missões ---
    // Vetor de missões disponíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos.",
        "Eliminar todas as tropas da cor vermelha.",
        "Controlar metade dos territórios do mapa.",
        "Ter mais de 20 tropas no total.",
        "Dominar todos os territórios azuis."
    };
    int totalMissoes = 5;

    // Alocação dinâmica para as missões dos jogadores
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    if (missaoJogador1 == NULL || missaoJogador2 == NULL) {
        printf("Erro ao alocar memória para as missões.\n");
        liberarMemoria(mapa, missaoJogador1, missaoJogador2);
        return 1;
    }

    // Atribuição das missões
    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\nMissão do Jogador 1: %s\n", missaoJogador1);
    printf("Missão do Jogador 2: %s\n", missaoJogador2);

    // --- Simulação simples de ataque ---
    int iAtacante, iDefensor;
    printf("\nEscolha o índice do território atacante (0 a %d): ", qtd - 1);
    scanf("%d", &iAtacante);
    printf("Escolha o índice do território defensor (0 a %d): ", qtd - 1);
    scanf("%d", &iDefensor);

    if (iAtacante == iDefensor) {
        printf("Um território não pode atacar a si mesmo!\n");
    } else if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) == 0) {
        printf("Você não pode atacar um território da mesma cor!\n");
    } else {
        atacar(&mapa[iAtacante], &mapa[iDefensor]);
    }

    printf("\n=== Estado do Mapa Após o Ataque ===\n");
    exibirMapa(mapa, qtd);

    // --- Verificação das missões ---
    if (verificarMissao(missaoJogador1, mapa, qtd)) {
        printf("\n🎉 O Jogador 1 cumpriu sua missão e venceu o jogo!\n");
    } else if (verificarMissao(missaoJogador2, mapa, qtd)) {
        printf("\n🎉 O Jogador 2 cumpriu sua missão e venceu o jogo!\n");
    } else {
        printf("\nNenhum jogador cumpriu sua missão ainda.\n");
    }

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);

    return 0;
}

/*----------------------------------------------------------
Função: cadastrarTerritorios
Descrição: Permite ao usuário cadastrar os territórios do jogo.
-----------------------------------------------------------*/
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/*----------------------------------------------------------
Função: exibirMapa
Descrição: Exibe o estado atual dos territórios cadastrados.
-----------------------------------------------------------*/
void exibirMapa(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/*----------------------------------------------------------
Função: atacar
Descrição: Simula uma batalha entre dois territórios com dados.
-----------------------------------------------------------*/
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== Início do Ataque ===\n");
    printf("%s (%s) está atacando %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas / 2;
    } else {
        printf("O defensor resistiu!\n");
        atacante->tropas--;
    }
}

/*----------------------------------------------------------
Função: atribuirMissao
Descrição: Sorteia e copia uma missão aleatória para o jogador.
-----------------------------------------------------------*/
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

/*----------------------------------------------------------
Função: verificarMissao
Descrição: Verifica se o jogador cumpriu sua missão (lógica simples).
-----------------------------------------------------------*/
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo básico de lógica:
    // Se a missão contém a palavra "vermelha", verifica se não há territórios vermelhos
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) {
                return 0; // Ainda há inimigos vermelhos
            }
        }
        return 1; // Missão cumprida
    }
    // Outras missões podem ser expandidas com novas regras
    return 0;
}

/*----------------------------------------------------------
Função: liberarMemoria
Descrição: Libera toda a memória alocada dinamicamente.
-----------------------------------------------------------*/
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
    printf("\nMemória liberada com sucesso!\n");
}