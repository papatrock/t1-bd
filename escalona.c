#include <stdio.h>
#include "queue.h"
#include "seriabilidade.h"
#include "visao-equivalente.h"
#include "transacao.h"

void imprimeMatriz(int **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void libera_matriz(int **m, int n)
{
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}
// gcc escalona.c queue.c queue.h -Wall -g -o escalona

int main(int argc, char *args[])
{

    transacao_t *fila_transacoes = NULL;
    int chegada, transacao;
    char operacao, atributo;
    int qtdTransacoesUnicas = 0;
    int *transacoes_id = NULL;

    // Leitura de dados
    while (scanf("%d %d %c %c", &chegada, &transacao, &operacao, &atributo) == 4)
    {
        transacao_t *nova_transacao = cria_transacao(chegada, transacao, operacao, atributo);
        queue_append((queue_t **)&fila_transacoes, (queue_t *)nova_transacao);
        adiciona_transacao(transacao, &transacoes_id, &qtdTransacoesUnicas);
    }

#ifdef DEBUG
    queue_print("Fila", (queue_t *)fila_transacoes, printa_transacao);
#endif

    int **matrizAdjacencia = malloc(qtdTransacoesUnicas * sizeof(int *));
    for (int i = 0; i < qtdTransacoesUnicas; i++)
    {
        matrizAdjacencia[i] = calloc(qtdTransacoesUnicas, sizeof(int)); // inicia com 0
    }

#ifdef DEBUG
    imprimeMatriz(matrizAdjacencia, qtdTransacoesUnicas, qtdTransacoesUnicas);
#endif

    monta_grafo((transacao_t *)fila_transacoes, matrizAdjacencia, transacoes_id, qtdTransacoesUnicas);

    int serializavel = !tem_ciclo(matrizAdjacencia, qtdTransacoesUnicas);

    int equivalente_visao = verifica_equivalencia_visao(fila_transacoes, transacoes_id, qtdTransacoesUnicas);

    printf("1 ");

    for (int i = 0; i < qtdTransacoesUnicas; i++)
    {
        printf("T%d", transacoes_id[i]);
        if (i < qtdTransacoesUnicas - 1)
            printf(",");
        else
            printf(" ");
    }
    printf("%s ", serializavel ? "SS" : "NS");

    printf("%s\n", equivalente_visao ? "SV" : "NV");

    // imprimeMatriz(matrizAdjacencia, qtdTransacoesUnicas, qtdTransacoesUnicas);
    for (int i = 0; i < qtdTransacoesUnicas; i++)
        free(matrizAdjacencia[i]);
    free(matrizAdjacencia);
    free(transacoes_id);

    return 0;
}