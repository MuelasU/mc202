#include <stdio.h>
#include <stdlib.h>

//Declaração de estruturas
typedef struct node
{
    int num;
    struct node *prox;
} node;

//Prototipagem de funções
node *MergeSort(node *head, int tam, long *inversoes); //retorna o head da lista
node *LeEntrada(int tam);                              //retorna o head da lista
void DeletaLista(node *head);
void PrintaLista(node *head);

int main()
{
    long numInversoes = 0;

    int n;
    scanf("%d", &n);

    node *cabeca = LeEntrada(n);
    cabeca = MergeSort(cabeca, n, &numInversoes);
    DeletaLista(cabeca);

    printf("%ld\n", numInversoes);

    return 0;
}

//Funções
node *DivideLista(node *head)
{
    node *smallStep = head;
    for (node *bigStep = head->prox; bigStep != NULL; bigStep = bigStep->prox)
    {
        bigStep = bigStep->prox;
        if (bigStep != NULL)
        {
            smallStep = smallStep->prox;
            continue;
        }
        break;
    }
    node *aux = smallStep;
    smallStep = smallStep->prox;
    aux->prox = NULL;
    return smallStep;
}

node *Merge(node *headOne, node *headTwo, int lenOne, long *inversoes)
{
    node *reader;
    int iterateInOne = headOne->num <= headTwo->num;
    if (iterateInOne)
        lenOne--;
    else
        *inversoes += lenOne;
    node **actualHead = iterateInOne ? &headOne : &headTwo;
    reader = *actualHead;
    *actualHead = (*actualHead)->prox;
    node *finalHead = reader;
    while (headOne != NULL && headTwo != NULL)
    {
        iterateInOne = headOne->num <= headTwo->num;
        if (iterateInOne)
            lenOne--;
        else
            *inversoes += lenOne;
        actualHead = iterateInOne ? &headOne : &headTwo;
        reader->prox = *actualHead;        //adiciona na lista
        reader = *actualHead;              //vai pro fim
        *actualHead = (*actualHead)->prox; //avança na lista
    }
    actualHead = (headOne == NULL) ? &headTwo : &headOne;
    do
    {
        reader->prox = *actualHead;
        reader = *actualHead;
        *actualHead = (*actualHead)->prox;
    } while (*actualHead != NULL);
    return finalHead;
}

node *MergeSort(node *head, int tam, long *inversoes)
{
    if (head->prox == NULL)
    {
        return head;
    }
    int impar = tam % 2;
    tam /= 2;
    node *half = DivideLista(head);
    head = MergeSort(head, (impar ? tam + 1 : tam), inversoes);
    half = MergeSort(half, tam, inversoes);
    return Merge(head, half, (impar ? tam + 1 : tam), inversoes);
}

node *LeEntrada(int tam)
{
    node *head = malloc(sizeof(node));
    scanf("%d", &(head->num));
    node *aux = head;
    node *reader;
    for (int i = 1; i < tam; i++)
    {
        reader = malloc(sizeof(node));
        scanf("%d", &(reader->num));
        aux->prox = reader;
        aux = reader;
    }
    reader->prox = NULL;
    return head;
}

void DeletaLista(node *head)
{
    node *aux;
    do
    {
        aux = head->prox;
        free(head);
        head = aux;
    } while (head != NULL);
}

void PrintaLista(node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->num);
        head = head->prox;
    }
    printf("\n");
}