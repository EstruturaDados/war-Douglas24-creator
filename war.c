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
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// Simulação de batalhas
void simularAtaque(struct territorio *atacante, struct  territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("O atacante não possui tropas suficientes para atacar.\n");
        return;
    }
//dado aleatório
    printf("\n Batalha entre %s (Atacante) e %s (Defensor) ---\n",
        atacante->nome, defensor->nome);
    int dadoAtaque = rand() % 6 + 1; // 1 a 6
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado Ataque: %d\n", dadoAtaque);
    printf("Dado Defesa: %d\n", dadoDefensor);

    if (dadoAtaque >= dadoDefensor) {
        defensor->tropas--;
        printf("Atacante venceu! Defensor perdeu 1 tropa.\n");
    } else {
        atacante->tropas--;
        printf("Defensor venceu! Atacante perdeu 1 tropa.\n");
    }

    if (defensor->tropas <= 0) {
        defensor->tropas = 1; // territorio conquistado com uma tropa minima
        strcpy(defensor->cor, atacante->cor);
        printf("\n*** O território %s foi CONQUISTADO pelo jogador %s! ***\n",
            defensor->nome, atacante->cor);
    }
    printf("-------------------------------------");
}

void mostrarMapa(struct territorio *WAR, int total) {
    printf("\n===== SITUAÇÃO ATUAL DO MAPA =====\n");
    for (int i = 0; i < total; i++) {
        printf(" Território %d | Nome: %s | Cor: %s | Tropas: %d\n",
        i + 1, WAR[i].nome, WAR[i].cor, WAR[i].tropas);
    }
    printf("============================================");
}


// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    srand(time(NULL)); //inicia gerador de aleatórios

    struct territorio *WAR = calloc(MAX_TERRITORIOS, sizeof(struct territorio));
    if (WAR == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    int totalTerritorios = 0;

    // Laço Principal do Menu
    
        // Exibe o menu de opções
    printf("============================================================\n");
    printf("        TERRITÓRIO WAR - Cadastro Inicial\n");
    printf("------------------------------------------------------------\n");
    
    /* Cadatro de territórios*/
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Cadastro do território %d: \n", i + 1);

        printf("  Nome do Território: ");
        fgets(WAR[i].nome, MAX_NOME, stdin);

        printf("  A cor do Exercíto: ");
        fgets(WAR[i].cor, MAX_COR, stdin);

        WAR[i].nome[strcspn(WAR[i].nome, "\n")] = '\0';
        WAR[i].cor[strcspn(WAR[i].cor, "\n")] = '\0';

        printf("  Número de tropas: ");
        scanf("%d", &WAR[i].tropas);
        limparBufferEntrada();

        totalTerritorios++;
    }
    printf("\n===== MAPA ATUAL =====\n");
    for(int i = 0; i < totalTerritorios; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", WAR[i].nome);
        printf("Cor: %s\n", WAR[i].cor);
        printf("Tropas: %d\n", WAR[i].tropas);
        printf("-----------------------------\n");
    }

    // loop de ataque
    int opcao = 1;
    while (opcao == 1) {
        int atk, def;

        printf("\nEscolha o território ATACANTE ( 1 a %d): ", totalTerritorios);
        scanf("%d", &atk); limparBufferEntrada();

        printf("Escolha o território DEFENSOR (1 a %d): ", totalTerritorios);
        scanf("%d", &def); limparBufferEntrada();

        if (atk < 1 || atk > totalTerritorios || def < 1 || def > totalTerritorios || atk == def) {
            printf("seleção inválida!\n");
            continue;
        }

        simularAtaque(&WAR[atk - 1], &WAR[def - 1]);
        
        //mostrar mapa após batalha
        mostrarMapa(WAR, totalTerritorios);

        printf("\nDeseja realizar outro ataque? (1 = Sim / 2 = Não)");
        scanf("%d", &opcao);
        limparBufferEntrada();
    }

    printf("\nJogo Finalizado. Estado final dos territórios:\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("Território %d | Nome: %s | Cor: %s | Tropas: %d\n",
        i + 1, WAR[i].nome, WAR[i].cor, WAR[i].tropas);
    }

    free(WAR);
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
