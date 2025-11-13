#include <stdio.h>
#include <string.h>

// Estrutura que representa um território no sistema
// Cada território possui um nome, uma cor de exército e uma quantidade de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor que armazena 5 territórios
    struct Territorio territorios[5];
    
    // Loop para cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);
        
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // Lê string com espaços
        
        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor);
        
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
    
    // Exibição dos dados após o cadastro
    printf("\n\n=== Territórios Cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }
    
    return 0;
}
