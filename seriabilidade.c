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

int tem_ciclo(int **grafo, int n)
{
    int visitado[n];
    memset(visitado, 0, sizeof(visitado));

    for (int i = 0; i < n; i++)
    {
        if (visitado[i] == 0)
        {
            if (dfs(i, grafo, visitado, n))
                return 1;
        }
    }
    return 0;
}

int dfs(int v, int **grafo, int *visitado, int n)
{
    visitado[v] = 1;
    for (int i = 0; i < n; i++)
    {
        if (grafo[v][i])
        {
            if (visitado[i] == 1)
                return 1;
            if (visitado[i] == 0)
            {
                if (dfs(i, grafo, visitado, n))
                    return 1;
            }
        }
    }
    visitado[v] = 2;
    return 0;
}

void monta_grafo(transacao_t *inicio, int **grafo, int *transacoes_id, int qtd_transacoes)
{
    if (!inicio)
        return;

    transacao_t *op1 = inicio;
    do
    {
        transacao_t *op2 = inicio;
        do
        {
            if (op1 != op2 &&
                op1->transacaoI != op2->transacaoI &&
                op1->atributo == op2->atributo &&
                op1->operacao != 'C' && op2->operacao != 'C')
            {

                if ((op1->operacao == 'W' && op2->operacao == 'W') ||
                    (op1->operacao == 'W' && op2->operacao == 'R') ||
                    (op1->operacao == 'R' && op2->operacao == 'W'))
                {

                    // op1 vem antes de op2 no histórico?
                    if (op1->chegadaT < op2->chegadaT)
                    {
                        int i = busca_indice(op1->transacaoI, transacoes_id, qtd_transacoes);
                        int j = busca_indice(op2->transacaoI, transacoes_id, qtd_transacoes);
                        grafo[i][j] = 1;
                    }
                }
            }
            op2 = op2->next;
        } while (op2 != inicio);
        op1 = op1->next;
    } while (op1 != inicio);
}

void printa_transacao(void *elem)
{
    transacao_t *t = (transacao_t *)elem;
    printf("(chegada: %d, identificador: %d, operação: %c, atributo: %c) \n", t->chegadaT, t->transacaoI, t->operacao, t->atributo);
}