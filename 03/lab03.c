#include <stdio.h>
#include <stdlib.h>

typedef struct client
{
    struct client *prev;
    int psw; //senha que recebe
    struct client *next;
} client;

//Criará a fila de atendimento
// - len: numero de clientes a serem atendidos
// - head: senha do cliente que encabeçará a fila
client *createList(int len, int head);

//Engloba todo trabalho de atendimento
// - queueLen: numero de clientes a serem atendidos
// - listsHead: ponteiro para o cliente "cabeça" de fila
// - firstsStep: passo usado pelo primeiro atendente
// - secondsStep: passo usado pelo segundo atendente
void DNAttendance(int queueLen, client *listsHead, int firstsStep, int secondsStep);

int main()
{
    //variáveis de entrada
    int N, C, k, l;
    scanf("%d %d %d %d", &N, &C, &k, &l);

    //cria a fila e retorna o endereço do cliente "cabeça" de fila
    client *head = createList(N, C);

    DNAttendance(N, head, k, l);
    return 0;
}

client *createList(int len, int head)
{
    //aloca memória para o "cabeça" de fila e define sua senha
    client *header = malloc(sizeof(client));
    header->psw = head;

    //define um ponteiro que armazenará o endereço do cliente que antecede o próximo
    client *previous = header;

    //'for' começa no próximo ao "cabeça" e faz uma volta até anteceder o "cabeça"
    int i; //representará a senha
    for (i = head + 1; i != head; i++)

    {
        //se a senha for o tamanho da fila, este é meu cliente 0
        if (i == len)
            i = 0;
        //define o cliente de senha i
        client *cell = malloc(sizeof(client));
        cell->psw = i;
        cell->prev = previous;
        //o cliente anterior aponta para o novo "próximo"
        previous->next = cell;
        //o anterior passa a ser o atual
        previous = cell;
    }
    //por fim, completa o cliente "cabeça" e o último a ter sido iterado
    header->prev = previous;
    previous->next = header;

    //retorna o cabeça da fila
    return header;
}

client *clerkWork(int step, client **reference, int isFirstClerk)
//Executa o trabalho de um atendente
// - step: passo usado pelo atendente
// - reference: endereço do ponteiro para o cliente usado como referência para início de
//contagem (o início da contagem é o cliente adjacente ao último que foi atendido)
// - isFirstClerk: valor booleano que indica se é o atendente 1 (aquele que conta
//sentido crescente de senha)
{
    //cria um ponteiro que será usado na iteração
    //ele aponta para o cliente referência de início da contagem
    client *toClerk = *reference;

    //executa a contagem até o cliente que será atendido
    int i;
    for (i = 1; i < step; i++)
        toClerk = isFirstClerk ? toClerk->next : toClerk->prev;

    //define a nova referência
    *reference = isFirstClerk ? toClerk->next : toClerk->prev;

    //retorna o cliente que será atendido
    return toClerk;
}

void removeFromList(client *el, int *len)
//Remove um cliente da fila
// - el: cliente a ser removido
// - len: número de clientes na fila incluindo o que será removido (passado por ref)
// - dbg: variável de teste que mostrará quanto de memória foi liberada (passado por ref)
{
    //associa os cliente adjacentes ao que será removido para garantir coesão da fila
    (el->next)->prev = el->prev;
    (el->prev)->next = el->next;

    //libera a memória do cliente removido
    free(el);

    //decrementa o tamanho da fila
    (*len)--;
}

void DNAttendance(int queueLen, client *listsHead, int firstsStep, int secondsStep)
{
    client *refForFirst = listsHead->next; //referência de contagem para o atendente 1
    client *firstsClient;                  //cliente que é atendido pelo atendente 1

    client *refForSecond = listsHead->prev; //referência de contagem para o atendente 2
    client *secondsClient;                  //cliente que é atendido pelo atendente 2

    //itera na fila enquanto ela não zerar
    while (queueLen > 0)
    {
        firstsClient = clerkWork(firstsStep, &refForFirst, 1);
        secondsClient = clerkWork(secondsStep, &refForSecond, 0);

        printf("%d %d\n", firstsClient->psw, secondsClient->psw);

        if (firstsClient->next == secondsClient)
        //trata do caso dos clientes serem vizinhos na fila
        {
            refForFirst = secondsClient->next;
            refForSecond = firstsClient->prev;
        }

        if (firstsClient == secondsClient)
        //se os clientes forem os mesmo, remove uma vez só
        {
            removeFromList(firstsClient, &queueLen);
        }
        else
        {
            removeFromList(firstsClient, &queueLen);
            removeFromList(secondsClient, &queueLen);
        }
    }
}