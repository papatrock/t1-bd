#ifndef TRANSACAO_H
#define TRANSACAO_H

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
} transacao_t;

transacao_t *cria_transacao(int chegada, int transacao, char operacao, char atributo);

int adiciona_transacao(int id, int **transacoes_id, int *qtd);

void libera_lista_transacoes(transacao_t *fila);

#endif