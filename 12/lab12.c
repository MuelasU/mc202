#include <stdio.h>
#include <stdlib.h>

//Declaração de estruturas
typedef struct node
{
    int val;
    struct node *prox;
} node;

//Prototipagem de funções
int **CriaGrafo(int numV, int numA);
void PrintaGrafo(int **grafo, int numV);
void CalculaRotas(int **grafo, int numV, node **rotas, int atual, int andado);
void PrintaPilha(node *v);
int ApagaOMenor(node **lista);
void DestroiGrafo(int **grafo, int numV);

int main()
{
    int N, M;

    scanf("%d %d", &N, &M);

    int **mapa = CriaGrafo(N, M);
    mapa[0][0] = 1;

    node *distancias = NULL;
    CalculaRotas(mapa, N, &distancias, 0, 0);

    DestroiGrafo(mapa, N);

    ApagaOMenor(&distancias);
    printf("%d\n", ApagaOMenor(&distancias));
    free(distancias);

    return 0;
}

//Funções
void verifica_posicao(int *i, int *j)
//para sempre trabalhar na matriz superior
{
    if (*i > *j)
    {
        int aux = *i;
        *i = *j;
        *j = aux;
    }
}

int **CriaGrafo(int numV, int numA)
{
    //matriz superior com diagonal principal Ann = 0
    int **matriz = malloc(numV * sizeof(int *));
    int i;
    for (i = 0; i < numV; i++)
        //inicia todos caminhos em 0
        matriz[i] = calloc(numV, sizeof(int));
    int de, para, quanto;
    while (numA > 0)
    {
        scanf("%d %d %d", &de, &para, &quanto);
        verifica_posicao(&de, &para);
        //anota o tempo que demora no caminho
        matriz[de][para] = quanto;
        numA--;
    }
    return matriz;
}

void DestroiGrafo(int **grafo, int numV)
{
    for (int i = 0; i < numV; i++)
        free(grafo[i]);
    free(grafo);
}

void CalculaRotas(int **grafo, int numV, node **rotas, int atual, int andado)
{
    // printf("fui pro %d\n", atual);
    int aux1, aux2;
    for (int i = 0; i < numV; i++)
    {
        aux1 = atual;
        aux2 = i;
        verifica_posicao(&aux1, &aux2);
        if (grafo[aux1][aux2] > 0 && !(grafo[i][i]))
        {
            // printf("distancia do %d pro %d: %d\n", atual, i, grafo[aux1][aux2]);
            if (i == numV - 1)
            {
                node *aux = *rotas;
                *rotas = malloc(sizeof(node));
                (*rotas)->val = andado + grafo[aux1][aux2];
                (*rotas)->prox = aux;
                // printf("adicionei o caminho com uma distancia de %d\n", (*rotas)->val);
                return;
            }
            grafo[i][i] = 1;
            CalculaRotas(grafo, numV, rotas, i, andado + grafo[aux1][aux2]);
            // printf("voltei pro %d\n", atual);
            grafo[i][i] = 0;
        }
    }
}

int ApagaOMenor(node **lista)
{
    node *l = *lista;
    node *menor = *lista;
    node *anterior = NULL;
    while (l->prox != NULL)
    {
        if (l->prox->val < menor->val)
        {
            menor = l->prox;
            anterior = l;
        }
        l = l->prox;
    }
    int r;
    if (anterior == NULL)
        *lista = menor->prox;
    else
        anterior->prox = menor->prox;
    r = menor->val;
    free(menor);
    return r;
}

void PrintaGrafo(int **matriz, int numV)
{
    for (int i = 0; i < numV; i++)
    {
        for (int j = 0; j < numV; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

void PrintaPilha(node *v)
{
    while (v != NULL)
    {
        printf("%d ", v->val);
        v = v->prox;
    }
    printf("\n");
}