#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int posicao_valida(int linha, int coluna)
{
  return linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO;
}

int verifica_sobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna)
{
  return tabuleiro[linha][coluna] == 3;
}

int main(void)
{
  char coluna[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  int tabuleiro[10][10];
  int i, j, k;

  // Inicializa o tabuleiro com água (0)
  for (i = 0; i < TAM_TABULEIRO; i++)
  {
    for (j = 0; j < TAM_TABULEIRO; j++)
    {
      tabuleiro[i][j] = 0;
    }
  }

  // Coordenadas dos navios
  int linha_horizontal1 = 2, coluna_horizontal1 = 1; // Navio horizontal na linha 2, começando na coluna 1
  int linha_vertical = 5, coluna_vertical = 7;       // Navio vertical na coluna 7, começando na linha 5
  int linha_diagonal1 = 1, coluna_diagonal1 = 5;     // Navio diagonal descendente começando em (1,5)
  int linha_diagonal2 = 8, coluna_diagonal2 = 3;     // Navio diagonal ascendente começando em (8,3)

  // Validação dos navios
  if (!posicao_valida(linha_horizontal1, coluna_horizontal1) ||
      !posicao_valida(linha_horizontal1, coluna_horizontal1 + TAM_NAVIO - 1))
  {
    printf("Erro: Navio horizontal fora dos limites do tabuleiro.\n");
    return 1;
  }

  if (!posicao_valida(linha_vertical, coluna_vertical) ||
      !posicao_valida(linha_vertical + TAM_NAVIO - 1, coluna_vertical))
  {
    printf("Erro: Navio vertical fora dos limites do tabuleiro.\n");
    return 1;
  }

  if (!posicao_valida(linha_diagonal1, coluna_diagonal1) ||
      !posicao_valida(linha_diagonal1 + TAM_NAVIO - 1, coluna_diagonal1 + TAM_NAVIO - 1))
  {
    printf("Erro: Navio diagonal descendente fora dos limites do tabuleiro.\n");
    return 1;
  }

  if (!posicao_valida(linha_diagonal2, coluna_diagonal2) ||
      !posicao_valida(linha_diagonal2 - TAM_NAVIO + 1, coluna_diagonal2 + TAM_NAVIO - 1))
  {
    printf("Erro: Navio diagonal ascendente fora dos limites do tabuleiro.\n");
    return 1;
  }

  // Posicionamento dos navios
  for (k = 0; k < TAM_NAVIO; k++)
  {
    if (verifica_sobreposicao(tabuleiro, linha_horizontal1, coluna_horizontal1 + k))
    {
      printf("Erro: Sobreposicao detectada no navio horizontal.\n");
      return 1;
    }
    tabuleiro[linha_horizontal1][coluna_horizontal1 + k] = 3;
  }

  for (k = 0; k < TAM_NAVIO; k++)
  {
    if (verifica_sobreposicao(tabuleiro, linha_vertical + k, coluna_vertical))
    {
      printf("Erro: Sobreposicao detectada no navio vertical.\n");
      return 1;
    }
    tabuleiro[linha_vertical + k][coluna_vertical] = 3;
  }

  for (k = 0; k < TAM_NAVIO; k++)
  {
    if (verifica_sobreposicao(tabuleiro, linha_diagonal1 + k, coluna_diagonal1 + k))
    {
      printf("Erro: Sobreposicao detectada no navio diagonal descendente.\n");
      return 1;
    }
    tabuleiro[linha_diagonal1 + k][coluna_diagonal1 + k] = 3;
  }

  for (k = 0; k < TAM_NAVIO; k++)
  {
    if (verifica_sobreposicao(tabuleiro, linha_diagonal2 - k, coluna_diagonal2 + k))
    {
      printf("Erro: Sobreposicao detectada no navio diagonal ascendente.\n");
      return 1;
    }
    tabuleiro[linha_diagonal2 - k][coluna_diagonal2 + k] = 3;
  }

  // Exibe o tabuleiro
  printf("\nTabuleiro de Batalha Naval:\n");
  printf("Legenda: 0 = agua, 3 = navio\n\n");

  // Imprime as letras das colunas
  printf("  ");
  for (j = 0; j < TAM_TABULEIRO; j++)
  {
    printf("%c ", coluna[j]);
  }
  printf("\n");

  // Imprime o tabuleiro com os números das linhas
  for (i = 0; i < TAM_TABULEIRO; i++)
  {
    printf("%2d ", i + 1);
    for (j = 0; j < TAM_TABULEIRO; j++)
    {
      printf("%d ", tabuleiro[i][j]);
    }
    printf("\n");
  }

  return 0;
}