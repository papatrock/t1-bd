#include <stdio.h>
#include "queue.h"
#include "seriabilidade.h"
#include "visao-equivalente.h"
#include "transacao.h"

void imprimeMatriz(int **matriz, int linhas, int colunas);

void libera_matriz(int **m, int n);

// gcc escalona.c queue.c queue.h -Wall -g -o escalona
int main(int argc, char *args[])
{
    int escalonamento_id = 1;
    transacao_t *fila_transacoes = NULL;
    int qtdTransacoesUnicas = 0;
    int *transacoes_id = NULL;
    int qtdCommits = 0;

    int chegada;
    int transacao_id_lido;
    char operacao;
    char atributo;

    while (scanf("%d %d %c %c", &chegada, &transacao_id_lido, &operacao, &atributo) == 4)
    {

        transacao_t *nova_transacao = cria_transacao(chegada, transacao_id_lido, operacao, atributo);
        queue_append((queue_t **)&fila_transacoes, (queue_t *)nova_transacao);

        int ja_existe = 0;
        for (int i = 0; i < qtdTransacoesUnicas; i++)
        {
            if (transacoes_id[i] == transacao_id_lido)
            {
                ja_existe = 1;
                break;
            }
        }
        if (!ja_existe)
        {
            qtdTransacoesUnicas++;
            transacoes_id = realloc(transacoes_id, qtdTransacoesUnicas * sizeof(int));
            transacoes_id[qtdTransacoesUnicas - 1] = transacao_id_lido;
        }

        if (operacao == 'C')
        {
            qtdCommits++;
        }

        if (qtdTransacoesUnicas > 0 && qtdCommits == qtdTransacoesUnicas)
        {

            int **matrizAdjacencia = malloc(qtdTransacoesUnicas * sizeof(int *));
            for (int i = 0; i < qtdTransacoesUnicas; i++)
            {
                matrizAdjacencia[i] = calloc(qtdTransacoesUnicas, sizeof(int));
            }

            monta_grafo(fila_transacoes, matrizAdjacencia, transacoes_id, qtdTransacoesUnicas);
            int serializavel = !tem_ciclo(matrizAdjacencia, qtdTransacoesUnicas);
            int equivalente_visao = verifica_equivalencia_visao(fila_transacoes, transacoes_id, qtdTransacoesUnicas);

            for (int i = 0; i < qtdTransacoesUnicas - 1; i++)
            {
                for (int j = 0; j < qtdTransacoesUnicas - i - 1; j++)
                {
                    if (transacoes_id[j] > transacoes_id[j + 1])
                    {
                        int temp = transacoes_id[j];
                        transacoes_id[j] = transacoes_id[j + 1];
                        transacoes_id[j + 1] = temp;
                    }
                }
            }

            printf("%d ", escalonamento_id);
            for (int i = 0; i < qtdTransacoesUnicas; i++)
            {
                printf("%d", transacoes_id[i]);
                if (i < qtdTransacoesUnicas - 1)
                    printf(",");
            }
            printf(" %s %s\n", serializavel ? "SS" : "NS", equivalente_visao ? "SV" : "NV");

            for (int i = 0; i < qtdTransacoesUnicas; i++)
                free(matrizAdjacencia[i]);
            free(matrizAdjacencia);
            free(transacoes_id);
            libera_lista_transacoes(fila_transacoes);

            escalonamento_id++;
            fila_transacoes = NULL;
            qtdTransacoesUnicas = 0;
            transacoes_id = NULL;
            qtdCommits = 0;
        }
    }

    return 0;
}

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