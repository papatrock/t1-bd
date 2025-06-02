#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define READ R
#define WRITE W
#define COMMIT C

typedef struct transacao
{
    struct transacao *next;
    struct transacao *prev; 
    int chegadaT;
    int transacaoI;
    char operacao;
    char atributo;

}transacao_t;

// gcc escalona.c queue.c queue.h -Wall -g -o escalona
transacao_t *queue;
int main (int argc, char *argv[]){

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
    int commitCount = 0;
    char *atributos;

    // Leitura de dados
    do
    {   
        transacao_t *transacao = malloc(sizeof(transacao_t));
        transacao->next = NULL;
        transacao->prev = NULL;

        scanf("%d  %d %c %c",&transacao->chegadaT, &transacao->transacaoI, &transacao->operacao, &transacao->atributo);
        ifNotPresentAdd(atributos,transacao->atributo);
        queue_append((queue_t**) queue, (queue_t*)transacao);
        
        if(transacao->operacao == 'c')
            queue_remove((queue_t**) queue, (queue_t *)transacao);
    }while (queue_size(queue) > 0);
    

    transacao_t *aux = queue;
    do
    {
    printf("%c\n",aux->atributo);
    aux = aux->next;
    } while (aux != queue);
    
    return 0;
}

void ifNotPresentAdd(){

}