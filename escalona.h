#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct transacao
{
    struct transacao *next;
    struct transacao *prev;
    int chegadaT;
    int transacaoI;
    char operacao;
    char atributo;

}transacao_t;

transacao_t *cria_transacao(int chegada, int transacao, char operacao, char atributo);
