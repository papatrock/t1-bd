#include "seriabilidade.h"

transacao_t *cria_transacao(int chegada, int transacao, char operacao, char atributo)
{
    transacao_t *nova_transacao = malloc(sizeof(transacao_t));
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

int busca_indice(int id, int *transacoes_id, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        if (transacoes_id[i] == id)
            return i;
    }
    return -1;
}

void arestaLeituraEscrita()
{
}

void arestaEscritaLeitura()
{
}

void printa_transacao(void *elem)
{
    transacao_t *t = (transacao_t *)elem;
    printf("(chegada: %d, identificador: %d, operação: %c, atributo: %c) \n", t->chegadaT, t->transacaoI, t->operacao, t->atributo);
}