#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "transacao.h"

/*
    A entrada deve ser feita pela entrada padrão (stdin).
    O arquivo é formado por uma sequência de linhas, onde
    cada linha representa uma transação chegando. Cada linha
    tem 4 campos: o primeiro é o tempo de chegada, o segundo
    é o identificador da transação, o terceiro é a operação
    (R=read, W=write, C=commit) e o quarto o atributo que será
    lido/escrito. Estas linhas estão ordenadas pelo primeiro
    campo (tempos menores no início indicando a linha do tempo).
*/

void monta_grafo(transacao_t *inicio, int **grafo, int *transacoes_id, int qtd_transacoes);

int busca_indice(int id, int *transacoes_id, int qtd);

int dfs(int v, int **grafo, int *visitado, int n);

int tem_ciclo(int **grafo, int n);

void printa_transacao(void *elem);
