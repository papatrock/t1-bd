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

//#include "queue.h"
#include "escalona.h"

#define READ R
#define WRITE W
#define COMMIT C


// gcc escalona.c queue.c queue.h -Wall -g -o escalona
transacao_t *fila_transacoes;
int main (int argc, char *args[]){

//    int commitCount = 0;
//    char *atributos;

    int transacao_map [1000] = {0};

    int chegada, transacao; char operacao, atributo;

    scanf("%d  %d %c %c",&chegada, &transacao, &operacao, &atributo);
    //Leitura de dados
    if(!transacao_map[transacao]){
        transacao_t *nova_transacao = cria_transacao(chegada, transacao, operacao, atributo);
        queue_append((queue_t**)fila_transacoes, (queue_t*) nova_transacao);
        transacao_map[transacao] = 1;
        printf("transacao: %d %d %c %c\n", nova_transacao->chegadaT, nova_transacao->transacaoI, nova_transacao->operacao, nova_transacao->atributo);
    }
    printf("fila: %d %d %c %c\n", fila_transacoes->chegadaT, fila_transacoes->transacaoI, fila_transacoes->operacao, fila_transacoes->atributo);
    // do
    // {

    //     // nova transação

    //     if(operacao == 'c')
    //         queue_remove((queue_t**) fila_transacoes, (queue_t *)transacao);

    //     // transacao_t *transacao = malloc(sizeof(transacao_t));
    //     // transacao->next = NULL;
    //     // transacao->prev = NULL;
    // }while (queue_size(fila_transacoes) > 0);


    // transacao_t *aux = fila_transacoes;
    // do
    // {
    //     printf("%c\n",aux->atributo);
    //     aux = aux->next;
    // } while (aux != fila_transacoes);

    return 0;
}

int remove_transacao(int identificador){


    return 0;
}

int insere_nova_transacao(){

    return 0;
}

transacao_t *cria_transacao(int chegada, int transacao, char operacao, char atributo){
    transacao_t *nova_transacao = malloc(sizeof (transacao_t));
    nova_transacao->chegadaT = chegada;
    nova_transacao->transacaoI = transacao;
    nova_transacao->operacao = operacao;
    nova_transacao->atributo = atributo;

    return nova_transacao;
}