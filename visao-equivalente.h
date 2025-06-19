#include "transacao.h"
#include <string.h>

typedef struct
{
    int tid_escreveu;
    int tid_leu;
    char atributo;
} leitura_t;

void troca_ids(int *ids, int a, int b);

transacao_t *gera_visao_serial(transacao_t *origem, int *ordem_ids, int qtd);

void acha_ultimas_escritas(transacao_t *inicio, int *ultimas_tid_por_atributo);

int acha_relacoes_leitura(transacao_t *inicio, leitura_t *leituras, int tamanho_max);

int visao_equivalente(transacao_t *original, transacao_t *visao, int *ids, int qtd_transacoes);

int verifica_visoes_recursivo(transacao_t *original, int *ids, int n, int tam);

int verifica_equivalencia_visao(transacao_t *original, int *transacoes_id, int qtd);