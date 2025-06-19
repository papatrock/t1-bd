#include "transacao.h"
#include <stdio.h>

void libera_lista_transacoes(transacao_t *fila)
{
    queue_t *q_ptr = (queue_t *)fila;

    while (q_ptr != NULL)
    {
        transacao_t *no_para_liberar = (transacao_t *)q_ptr;
        queue_remove(&q_ptr, q_ptr);
        free(no_para_liberar);
    }
}

transacao_t *cria_transacao(int chegada, int transacao, char operacao, char atributo)
{
    transacao_t *nova_transacao = calloc(1, sizeof(transacao_t));

    if (nova_transacao == NULL)
    {
        printf("Falha ao alocar memoria para transacao\n");
        exit(1);
    }

#ifdef DEUBG
    printf("criada T%d em %p -> next=%p, prev=%p\n", transacao, (void *)nova_transacao, (void *)nova_transacao->next, (void *)nova_transacao->prev);
#endif

    nova_transacao->chegadaT = chegada;
    nova_transacao->transacaoI = transacao;
    nova_transacao->operacao = operacao;
    nova_transacao->atributo = atributo;

    return nova_transacao;
}

int adiciona_transacao(int id, int **transacoes_id, int *qtd)
{
    for (int i = 0; i < *qtd; i++)
    {
        if ((*transacoes_id)[i] == id)
            return i;
    }

    *transacoes_id = realloc(*transacoes_id, (*qtd + 1) * sizeof(int));
    (*transacoes_id)[*qtd] = id;
    (*qtd)++;
    return (*qtd) - 1;
}