// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

struct territorio {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
};

// Função para limpar o buffet de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    struct territorio WAR[MAX_TERRITORIOS];
    int totalTerritorios = 0;

    // Laço Principal do Menu
    
        // Exibe o menu de opções
    printf("============================================================\n");
    printf("        TERRITÓRIO WAR  \n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo\n" );
    printf("------------------------------------------------------------\n");
    
    /* Cadatro de territórios*/
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Cadastro do território %d: \n", i + 1);

        printf("  Nome do Território: ");
        fgets(WAR[totalTerritorios].nome, MAX_NOME, stdin);

        printf("  A cor do Exercíto: ");
        fgets(WAR[totalTerritorios].cor, MAX_COR, stdin);

        WAR[totalTerritorios].nome[strcspn(WAR[totalTerritorios].nome, "\n")] = '\0';
        WAR[totalTerritorios].cor[strcspn(WAR[totalTerritorios].cor, "\n")] = '\0';

        printf("  Número de tropas: ");
        scanf("%d", &WAR[totalTerritorios].tropas);
        limparBufferEntrada();

        totalTerritorios++;
    }
    printf("\n--Territórios Cadastrados--\n");
    for(int i = 0; i < totalTerritorios; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", WAR[i].nome);
        printf("Cor: %s\n", WAR[i].cor);
        printf("Tropas: %d\n", WAR[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
    


       
// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
