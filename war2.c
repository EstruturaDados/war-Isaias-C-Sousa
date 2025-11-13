
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funções do sistema
void cadastrarTerritorios(Territorio* mapa, int qtd);
void exibirTerritorios(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int qtd;
    printf("Digite o número total de territórios: ");
    scanf("%d", &qtd);

    // Alocação dinâmica de memória para os territórios
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro e exibição inicial dos territórios
    cadastrarTerritorios(mapa, qtd);
    exibirTerritorios(mapa, qtd);

    // Simulação de ataque
    int iAtacante, iDefensor;

    printf("\nEscolha o índice do território atacante (0 a %d): ", qtd - 1);
    scanf("%d", &iAtacante);

    printf("Escolha o índice do território defensor (0 a %d): ", qtd - 1);
    scanf("%d", &iDefensor);

    // Validação: não pode atacar a si mesmo ou um território da mesma cor
    if (iAtacante == iDefensor) {
        printf("Um território não pode atacar a si mesmo!\n");
    } else if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) == 0) {
        printf("Você não pode atacar um território da mesma cor!\n");
    } else {
        atacar(&mapa[iAtacante], &mapa[iDefensor]);
    }

    // Exibição após o ataque
    printf("\n=== Estado dos Territórios Após o Ataque ===\n");
    exibirTerritorios(mapa, qtd);

    // Liberação da memória alocada
    liberarMemoria(mapa);

    return 0;
}

/*----------------------------------------------------------
Função: cadastrarTerritorios
Descrição: Lê os dados de cada território informado pelo usuário.
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
Função: exibirTerritorios
Descrição: Exibe as informações de todos os territórios cadastrados.
-----------------------------------------------------------*/
void exibirTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n[%d] Nome: %s | Cor: %s | Tropas: %d",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

/*----------------------------------------------------------
Função: atacar
Descrição: Simula um ataque entre dois territórios utilizando rolagem de dados.
Se o atacante vencer, o defensor muda de cor e perde tropas.
-----------------------------------------------------------*/
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== Início do Ataque ===\n");
    printf("%s (%s) está atacando %s (%s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = rand() % 6 + 1; // valor entre 1 e 6
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor); // muda o controle do território
        defensor->tropas = atacante->tropas / 2; // metade das tropas do atacante
        atacante->tropas -= defensor->tropas / 2; // o atacante perde parte das tropas
    } else {
        printf("\nO defensor resistiu ao ataque!\n");
        atacante->tropas--; // perde uma tropa
    }
}

/*----------------------------------------------------------
Função: liberarMemoria
Descrição: Libera a memória alocada dinamicamente para o mapa.
-----------------------------------------------------------*/
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}