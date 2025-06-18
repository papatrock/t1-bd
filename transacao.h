#ifndef TRANSACAO_H
#define TRANSACAO_H

typedef struct transacao
{
    struct transacao *next;
    struct transacao *prev;
    int chegadaT;
    int transacaoI;
    char operacao;
    char atributo;
} transacao_t;

#endif