#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int idade;
    int qntd;
} qntdIdade;

void Adicionar(qntdIdade *p, int *nPos, int casos, int idade);
void Consultar(qntdIdade *p, int nPos, int X, int Y);
// void PrintaPonteiro(qntdIdade *p, int nPos);

int main()
{
    int numOp, vaiVer, x, y;
    int tam = 5, numIdades = 0;
    qntdIdade *casos = malloc(tam * sizeof(qntdIdade));

    //Leitura da primeira linha
    scanf("%d", &numOp);

    int i;
    for (i = 0; i < numOp; i++)
    {
        //Checagens iniciais
        if (numIdades == tam)
        {
            tam *= 2;
            casos = realloc(casos, tam * sizeof(qntdIdade));
        }
        if (casos == NULL)
        {
            free(casos);
            exit(1);
        }

        //Lê operação
        scanf("%d %d %d", &vaiVer, &x, &y);

        //Realiza operação pedida
        vaiVer ? Consultar(casos, numIdades, x, y) : Adicionar(casos, &numIdades, x, y);

        // PrintaPonteiro(casos, numIdades);
    }
    free(casos);
    return 0;
}

// void PrintaPonteiro(qntdIdade *p, int nPos)
// {
//     int i;
//     for (i = 0; i < nPos; i++)
//     {
//         printf("[%d %d]\n", p[i].qntd, p[i].idade);
//     }
// }

int Busca(qntdIdade *p, int nPos, int idade, int *i, int querProxMenor)
{
    int n = nPos, esq = 0, dir = nPos - 1;
    int m;
    if (idade < p[esq].idade)
    {
        *i = 0;
        if (querProxMenor)
            return 2;
        return 0;
    }
    if (idade > p[dir].idade)
    {
        *i = nPos - querProxMenor;
        if (!querProxMenor)
            return 2;
        return 0;
    }
    while (n > 2)
    {
        m = (esq + dir) / 2;
        if (p[m].idade == idade)
        {
            *i = m;
            return 1;
        }
        if (p[m].idade > idade)
            dir = m;
        else
            esq = m;
        n = dir - esq + 1;
    }
    if (p[dir].idade == idade)
        *i = dir;
    else if (p[esq].idade == idade)
        *i = esq;
    else
        *i = querProxMenor ? esq : dir;
    return p[*i].idade == idade;
}

void MovePraDireita(qntdIdade *p, int nPos, int ini)
{
    int n = nPos;
    while (ini != n)
    {
        p[n] = p[n - 1];
        n--;
    }
}

void Adicionar(qntdIdade *p, int *nPos, int casos, int idade)
{
    qntdIdade qi = {idade, casos};
    int i;
    //Checo pelos casos bases
    if (*nPos < 2)
    {
        if (*nPos == 0)
            p[0] = qi;
        else if (p[0].idade == idade)
        {
            p[0].qntd += casos;
            return;
        }
        else if (p[0].idade > idade)
        {
            MovePraDireita(p, 1, 0);
            p[0] = qi;
        }
        else
            p[1] = qi;
    }
    //Procuro pela idade no ponteiro
    else if (Busca(p, *nPos, idade, &i, 0) == 1)
    {
        p[i].qntd += casos;
        return;
    }
    else
    {
        MovePraDireita(p, *nPos, i);
        p[i] = qi;
    }
    (*nPos)++;
}

void Consultar(qntdIdade *p, int nPos, int menorIdade, int maiorIdade)
{
    int maior, menor, i;
    int soma = 0;
    //Checo os limites
    if (Busca(p, nPos, menorIdade, &menor, 0) != 2 &&
        Busca(p, nPos, maiorIdade, &maior, 1) != 2)
    {
        for (i = menor; i <= maior; i++)
        {
            soma += p[i].qntd;
        }
    }
    printf("%d\n", soma);
}
