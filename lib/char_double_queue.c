#include "char_double_queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

CharDoubleQueue *CharDoubleQueue_alloc() {
    CharDoubleQueue *fila = (CharDoubleQueue *)malloc(sizeof(CharDoubleQueue));
    fila->first = NULL;
    fila->last = NULL;
    return fila;
}

bool CharDoubleQueue_is_empty(CharDoubleQueue *fila) {
    return fila->last == NULL;
}

void CharDoubleQueue_insert(CharDoubleQueue *fila, CharQueue *c) {
    CharQueueNode *novo = (CharQueueNode *)malloc(sizeof(CharQueueNode));
    novo->fila = c;
    novo->next = NULL;
    if (fila->last == NULL) {
        fila->first = novo;
    } else {
        fila->last->next = novo;
    }
    fila->last = novo;
}

CharQueue *CharDoubleQueue_remove(CharDoubleQueue *fila) {
    CharQueueNode *old = fila->first;
    if (old == NULL) {
        printf("Tentou dar remove em uma fila vazia\n");
        exit(1);
    }
    fila->first = old->next;
    if (fila->first == NULL) {
        fila->last = NULL;
    }
    CharQueue *c = old->fila;
    free(old);
    return c;
}

void CharDoubleQueue_free(CharDoubleQueue *fila) {
    while (fila->first != NULL) {
        CharQueueNode *tmp = fila->first;
        fila->first = tmp->next;
        CharQueue_free(tmp->fila);
        free(tmp);
    }
    free(fila);
}

int CharDoubleQueue_length(CharDoubleQueue *fila) {
    int i = 0;
    CharQueueNode *tmp = fila->first;
    while (tmp != NULL) {
        i++;
        tmp = tmp->next;
    }
    return i;
}