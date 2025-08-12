#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5 // Tamanho da matriz de habilidades (5x5)
#define AGUA 0
#define NAVIO 3
#define AREA_AFETADA 5

// Estrutura para representar uma habilidade
typedef struct
{
  int matriz[TAM_HABILIDADE][TAM_HABILIDADE];
  char nome[20];
} Habilidade;

// Função para criar a habilidade Cone
void criar_cone(Habilidade *hab)
{
  for (int i = 0; i < TAM_HABILIDADE; i++)
  {
    for (int j = 0; j < TAM_HABILIDADE; j++)
    {
      // Cone começa no topo e expande para baixo
      if (i >= TAM_HABILIDADE / 2 - j / 2 && i <= TAM_HABILIDADE / 2 + j / 2)
      {
        hab->matriz[i][j] = 1;
      }
      else
      {
        hab->matriz[i][j] = 0;
      }
    }
  }
  sprintf(hab->nome, "Cone");
}

// Função para criar a habilidade Cruz
void criar_cruz(Habilidade *hab)
{
  for (int i = 0; i < TAM_HABILIDADE; i++)
  {
    for (int j = 0; j < TAM_HABILIDADE; j++)
    {
      // Cruz é formada pela linha e coluna do meio
      if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
      {
        hab->matriz[i][j] = 1;
      }
      else
      {
        hab->matriz[i][j] = 0;
      }
    }
  }
  sprintf(hab->nome, "Cruz");
}

// Função para criar a habilidade Octaedro (Losango)
void criar_octaedro(Habilidade *hab)
{
  int centro = TAM_HABILIDADE / 2;
  for (int i = 0; i < TAM_HABILIDADE; i++)
  {
    for (int j = 0; j < TAM_HABILIDADE; j++)
    {
      // Losango é baseado na distância Manhattan do centro
      if ((abs(i - centro) + abs(j - centro)) <= TAM_HABILIDADE / 2)
      {
        hab->matriz[i][j] = 1;
      }
      else
      {
        hab->matriz[i][j] = 0;
      }
    }
  }
  sprintf(hab->nome, "Octaedro");
}

// Função para aplicar uma habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                        Habilidade *hab, int linha_origem, int coluna_origem)
{
  int offset = TAM_HABILIDADE / 2;

  for (int i = 0; i < TAM_HABILIDADE; i++)
  {
    for (int j = 0; j < TAM_HABILIDADE; j++)
    {
      int linha_tab = linha_origem - offset + i;
      int coluna_tab = coluna_origem - offset + j;

      // Verifica se a posição está dentro dos limites do tabuleiro
      if (linha_tab >= 0 && linha_tab < TAM_TABULEIRO &&
          coluna_tab >= 0 && coluna_tab < TAM_TABULEIRO)
      {
        // Se a posição está na área de efeito da habilidade
        if (hab->matriz[i][j] == 1)
        {
          // Marca a posição como afetada (se não for um navio)
          if (tabuleiro[linha_tab][coluna_tab] != NAVIO)
          {
            tabuleiro[linha_tab][coluna_tab] = AREA_AFETADA;
          }
        }
      }
    }
  }
}

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

  // Criar e aplicar as habilidades
  Habilidade cone, cruz, octaedro;
  criar_cone(&cone);
  criar_cruz(&cruz);
  criar_octaedro(&octaedro);

  // Aplicar cada habilidade em uma posição diferente do tabuleiro
  aplicar_habilidade(tabuleiro, &cone, 4, 4);     // Cone no centro
  aplicar_habilidade(tabuleiro, &cruz, 7, 2);     // Cruz na parte inferior esquerda
  aplicar_habilidade(tabuleiro, &octaedro, 2, 7); // Octaedro na parte superior direita

  // Exibe o tabuleiro
  printf("\nTabuleiro de Batalha Naval:\n");
  printf("Legenda: %d = agua, %d = navio, %d = area afetada\n\n",
         AGUA, NAVIO, AREA_AFETADA);

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