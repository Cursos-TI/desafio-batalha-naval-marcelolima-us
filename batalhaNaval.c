#include <stdio.h>
// Tamanho fixo do tabuleiro
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int main()
{
  // Array para identificar as colunas do tabuleiro
  char coluna[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  // 1. Criando o Tabuleiro (Matriz 10x10)
  int tabuleiro[10][10];

  // Inicializa todas as posições do tabuleiro com 0 (água)
  int i, j, k;
  for (i = 0; i < TAM_TABULEIRO; i++)
  {
    for (j = 0; j < TAM_TABULEIRO; j++)
    {
      tabuleiro[i][j] = 0;
    }
  }

  // Vetores para representar os navios (apenas para referência)
  int navio_horizontal[TAM_NAVIO] = {3, 3, 3};
  int navio_vertical[TAM_NAVIO] = {3, 3, 3};

  // Coordenadas iniciais dos navios (definidas diretamente)
  int linha_horizontal = 2, coluna_horizontal = 4; // Navio horizontal começa em (2,4)
  int linha_vertical = 5, coluna_vertical = 7;     // Navio vertical começa em (5,7)

  // Validação dos limites do tabuleiro para navio horizontal
  if (coluna_horizontal + TAM_NAVIO > TAM_TABULEIRO)
  {
    printf("Erro: Navio horizontal fora dos limites do tabuleiro.\n");
    return 1;
  }
  // Validação dos limites do tabuleiro para navio vertical
  if (linha_vertical + TAM_NAVIO > TAM_TABULEIRO)
  {
    printf("Erro: Navio vertical fora dos limites do tabuleiro.\n");
    return 1;
  }

  // Validação de sobreposição simplificada
  int sobreposicao = 0;
  for (k = 0; k < TAM_NAVIO; k++)
  {
    if (linha_horizontal == linha_vertical + k && coluna_horizontal + k == coluna_vertical)
    {
      sobreposicao = 1;
      break;
    }
  }
  if (sobreposicao)
  {
    printf("Erro: Os navios estão sobrepostos.\n");
    return 1;
  }

  // Posiciona o navio horizontal no tabuleiro
  for (k = 0; k < TAM_NAVIO; k++)
  {
    tabuleiro[linha_horizontal][coluna_horizontal + k] = navio_horizontal[k];
  }

  // Posiciona o navio vertical no tabuleiro
  for (k = 0; k < TAM_NAVIO; k++)
  {
    tabuleiro[linha_vertical + k][coluna_vertical] = navio_vertical[k];
  }

  // Exibe o tabuleiro no console
  printf("\nTabuleiro de Batalha Naval:\n\n");

  // Imprime a linha das letras (A-J)
  printf("  "); // Espaço inicial para alinhar com os números
  for (j = 0; j < TAM_TABULEIRO; j++)
  {
    printf("%c ", coluna[j]);
  }
  printf("\n");

  // Imprime o resto do tabuleiro com números nas linhas (1-10)
  for (i = 0; i < TAM_TABULEIRO; i++)
  {
    printf("%2d ", i + 1); // Número da linha (1-10) com 2 espaços para alinhamento
    for (j = 0; j < TAM_TABULEIRO; j++)
    {
      printf("%d ", tabuleiro[i][j]); // Imprime cada posição com espaço
    }
    printf("\n"); // Nova linha ao final de cada linha do tabuleiro
  }

  return 0;
}