#include <stdio.h>
#define MAX 80

int somaDiagonalPrincipal(int matriz[][MAX], int ordem);  //Ok
int somaDiagonalSecundaria(int matriz[][MAX], int ordem); //Ok
int nColunasSomaPar(int matriz[][MAX], int ordem);        //Ok
int nLinhasSomaImpar(int matriz[][MAX], int ordem);       //Ok
void leMatriz(int matriz[][MAX], int ordem);              //Ok
void printaMatriz(int matriz[][MAX], int ordem);          //Ok

int main()
{
    int n;
    int matriz[MAX][MAX];

    scanf("%d", &n);

    leMatriz(matriz, n);
    /* ####### CÓDIGO ####### */
    printf("%d ", somaDiagonalPrincipal(matriz, n));
    printf("%d ", somaDiagonalSecundaria(matriz, n));
    printf("%d ", nColunasSomaPar(matriz, n));
    printf("%d", nLinhasSomaImpar(matriz, n));
    /* ####### ###### ####### */
    // printf("\n\n");
    // printaMatriz(matriz, n);

    return 0;
}

int nLinhasSomaImpar(int matriz[][MAX], int ordem)
{
    int i, j;
    int qntd = 0;
    for (i = 0; i < ordem; i++)
    {
        int soma = 0;
        for (j = 0; j < ordem; j++)
        {
            soma += matriz[i][j];
        }
        if (soma % 2)
            qntd++;
    }
    return qntd;
}

int nColunasSomaPar(int matriz[][MAX], int ordem)
{
    int i, j;
    int qntd = 0;
    for (j = 0; j < ordem; j++)
    {
        int soma = 0;
        for (i = 0; i < ordem; i++)
        {
            soma += matriz[i][j];
        }
        if (!(soma % 2))
            qntd++;
    }
    return qntd;
}

int somaDiagonalPrincipal(int matriz[][MAX], int ordem)
{
    int i;
    int soma = 0;
    for (i = 0; i < ordem; i++)
    {
        soma += matriz[i][i];
    }
    return soma;
}

int somaDiagonalSecundaria(int matriz[][MAX], int ordem)
{
    int i;
    int soma = 0;
    for (i = 0; i < ordem; i++)
    {
        soma += matriz[i][(ordem - 1) - i];
    }
    return soma;
}

void leMatriz(int matriz[][MAX], int ordem)
{
    int i, j;
    for (i = 0; i < ordem; i++)
    {
        for (j = 0; j < ordem; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
}

void printaMatriz(int matriz[][MAX], int ordem)
{
    int i, j;
    for (i = 0; i < ordem; i++)
    {
        for (j = 0; j < ordem; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}
