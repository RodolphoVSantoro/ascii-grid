#include "char_queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

CharQueue *CharQueue_alloc() {
    CharQueue *fila = (CharQueue *)malloc(sizeof(CharQueue));
    fila->first = NULL;
    fila->last = NULL;
    return fila;
}

bool CharQueue_is_empty(CharQueue *fila) {
    return fila->last == NULL;
}

void CharQueue_insert(CharQueue *fila, char c) {
    CharNode *novo = (CharNode *)malloc(sizeof(CharNode));
    novo->c = c;
    novo->next = NULL;
    if (fila->last == NULL) {
        fila->first = novo;
    } else {
        fila->last->next = novo;
    }
    fila->last = novo;
}

char CharQueue_remove(CharQueue *fila) {
    CharNode *old = fila->first;
    if (old == NULL) {
        printf("Tentou dar remove em uma fila vazia\n");
        exit(1);
    }
    fila->first = old->next;
    if (fila->first == NULL) {
        fila->last = NULL;
    }
    char c = old->c;
    free(old);
    return c;
}

void CharQueue_free(CharQueue *fila) {
    while (fila->first != NULL) {
        CharNode *tmp = fila->first;
        fila->first = tmp->next;
        free(tmp);
    }
    free(fila);
}

int CharQueue_length(CharQueue *fila) {
    int i = 0;
    CharNode *tmp = fila->first;
    while (tmp != NULL) {
        i++;
        tmp = tmp->next;
    }
    return i;
}