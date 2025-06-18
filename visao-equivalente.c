#include "visao-equivalente.h"
#include "seriabilidade.h"
#include "queue.h"

void troca_ids(int *ids, int a, int b)
{
    int tmp = ids[a];
    ids[a] = ids[b];
    ids[b] = tmp;
}

transacao_t *gera_visao_serial(transacao_t *origem, int *ordem_ids, int qtd)
{
    transacao_t *nova_lista = NULL;
    for (int i = 0; i < qtd; i++)
    {
        transacao_t *op = origem;
        do
        {
            if (op->transacaoI == ordem_ids[i])
            {
                transacao_t *nova_op = cria_transacao(op->chegadaT, op->transacaoI, op->operacao, op->atributo);
                queue_append((queue_t **)&nova_lista, (queue_t *)nova_op);
            }
            op = op->next;
        } while (op != origem);
    }
    return nova_lista;
}

void acha_ultimas_escritas(transacao_t *inicio, int *ultimas_tid_por_atributo)
{
    memset(ultimas_tid_por_atributo, -1, 256 * sizeof(int)); // char -> int

    transacao_t *op = inicio->prev;
    do
    {
        if (op->operacao == 'W' && ultimas_tid_por_atributo[(int)op->atributo] == -1)
        {
            ultimas_tid_por_atributo[(int)op->atributo] = op->transacaoI;
        }
        op = op->prev;
    } while (op != inicio->prev);
}

int acha_relacoes_leitura(transacao_t *inicio, leitura_t *leituras, int tamanho_max)
{
    int count = 0;
    transacao_t *op = inicio;
    do
    {
        if (op->operacao == 'R')
        {
            transacao_t *anterior = op->prev;
            while (anterior != op)
            {
                if (anterior->operacao == 'W' && anterior->atributo == op->atributo)
                {
                    leituras[count].tid_escreveu = anterior->transacaoI;
                    leituras[count].tid_leu = op->transacaoI;
                    leituras[count].atributo = op->atributo;
                    count++;
                    break;
                }
                anterior = anterior->prev;
            }
        }
        op = op->next;
    } while (op != inicio);
    return count;
}

int visao_equivalente(transacao_t *original, transacao_t *visao, int *ids, int qtd_transacoes)
{
    int ultimas_orig[256], ultimas_visao[256];
    leitura_t leituras_orig[100], leituras_visao[100]; // ajuste se necessário

    acha_ultimas_escritas(original, ultimas_orig);
    acha_ultimas_escritas(visao, ultimas_visao);

    for (int i = 0; i < 256; i++)
    {
        if (ultimas_orig[i] != -1 && ultimas_orig[i] != ultimas_visao[i])
            return 0;
    }

    int n_leituras_orig = acha_relacoes_leitura(original, leituras_orig, 100);
    int n_leituras_visao = acha_relacoes_leitura(visao, leituras_visao, 100);

    if (n_leituras_orig != n_leituras_visao)
        return 0;

    for (int i = 0; i < n_leituras_orig; i++)
    {
        if (leituras_orig[i].tid_escreveu != leituras_visao[i].tid_escreveu ||
            leituras_orig[i].tid_leu != leituras_visao[i].tid_leu ||
            leituras_orig[i].atributo != leituras_visao[i].atributo)
            return 0;
    }

    return 1;
}

int verifica_visoes_recursivo(transacao_t *original, int *ids, int n, int tam)
{
    if (n == 1)
    {
        transacao_t *visao = gera_visao_serial(original, ids, tam);
        int resultado = visao_equivalente(original, visao, ids, tam);
        // liberar memória de visao se necessário
        return resultado;
    }

    for (int i = 0; i < n; i++)
    {
        if (verifica_visoes_recursivo(original, ids, n - 1, tam))
            return 1;
        troca_ids(ids, (n % 2 == 0) ? i : 0, n - 1);
    }
    return 0;
}

int verifica_equivalencia_visao(transacao_t *original, int *transacoes_id, int qtd)
{
    return verifica_visoes_recursivo(original, transacoes_id, qtd, qtd);
}