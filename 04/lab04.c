#include <stdio.h>
#include <stdlib.h>

//Definição de structs
typedef struct digito
{
    int valor;
    struct digito *prox;
    struct digito *ant;
} digito;

//Prototipagem de funções
digito *LeBigInt();
digito *FiltraBigInt(digito *primeiro, int qntdRetirar);
int ImprimeBigInt(digito *ultimo);

int main()
{
    digito *primeiro = LeBigInt();

    int k;
    scanf(" %d", &k);

    digito *ultimo = FiltraBigInt(primeiro, k);

    if (!ImprimeBigInt(ultimo))
        printf("0");

    return 0;
}

//Funções
digito *LeBigInt()
{
    char charDgt[2] = {'x', '\0'};
    int num;
    digito *anterior = NULL, *primeiro = NULL;
    scanf("%c", &charDgt[0]);
    while (charDgt[0] != ' ')
    {
        num = atoi(charDgt);
        digito *dgt = malloc(sizeof(digito));
        if (!primeiro)
            primeiro = dgt;
        if (anterior)
            anterior->prox = dgt;
        dgt->valor = num;
        anterior = dgt;
        scanf("%c", &charDgt[0]);
    }
    anterior->prox = NULL;
    return primeiro;
}

digito *FiltraBigInt(digito *iniFila, int retirar)
{
    digito *aux;
    digito *topoPilha = iniFila;
    topoPilha->ant = NULL;
    iniFila = iniFila->prox;
    while (retirar && iniFila != NULL)
    {
        if (topoPilha->valor == 0 && topoPilha->ant == NULL)
        {
            free(topoPilha);
            topoPilha = NULL;
        }
        else if (topoPilha->valor > iniFila->valor)
            while (retirar && topoPilha != NULL && iniFila->valor < topoPilha->valor)
            {
                aux = topoPilha->ant;
                free(topoPilha);
                retirar--;
                topoPilha = aux;
            }
        iniFila->ant = topoPilha;
        topoPilha = iniFila;
        iniFila = iniFila->prox;
    }
    if (retirar)
        while (retirar)
        {
            aux = topoPilha->ant;
            free(topoPilha);
            retirar--;
            topoPilha = aux;
        }
    else
        while (iniFila != NULL)
        {
            iniFila->ant = topoPilha;
            topoPilha = iniFila;
            iniFila = iniFila->prox;
        }
    return topoPilha;
}

int ImprimeBigInt(digito *ultimo)
{
    if (ultimo == NULL)
        return 0;
    int valor = ultimo->valor;
    int soma = ImprimeBigInt(ultimo->ant);
    if (soma + valor)
        printf("%d", ultimo->valor);
    free(ultimo);
    return soma + valor;
}