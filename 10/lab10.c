#include <stdio.h>
#include <stdlib.h>

//Declaração de estruturas

//Prototipagem de funções
int *CreateTable(int size);
int Hash(int key, int sizeOfTable);
int InsertNum(int number, int *position, int *table, int size);

int main()
{
    //Declaração de variáveis
    int size, num, position, collisions = 0;

    //Criação da tabela hash
    scanf("%d", &size);
    int *table = CreateTable(size);

    //Rotina
    int n = size;
    while (n > 0)
    {
        scanf("%d", &num);
        position = Hash(num, size);
        while (InsertNum(num, &position, table, size))
        {
            collisions++;
            position++;
        }
        n--;
    }
    printf("%d\n", collisions);

    //Liberação da tabela hash
    free(table);

    return 0;
}

//Funções
int Hash(int key, int size)
{
    return key % size;
}

int InsertNum(int num, int *pos, int *table, int size)
{
    if (*pos == size)
        *pos = 0; //Condição de tabela circular
    if (table[*pos] == -1)
    {
        table[*pos] = num;
        return 0; //Retorna 0 se não houve colisão
    }
    return 1; //Retorna 1 se houve colisão
}

int *CreateTable(int size)
{
    int *table = malloc(size * sizeof(int));
    if (table == NULL)
    {
        exit(0);
    }
    for (int i = 0; i < size; i++)
    {
        table[i] = -1; //Inicializa a tabela com -1 em todos os campos
    }
    return table;
}