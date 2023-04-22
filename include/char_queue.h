#ifndef CHAR_QUEUE_H
#define CHAR_QUEUE_H
#include <stdbool.h>
struct CHAR_NODE {
    char c;
    struct CHAR_NODE *next;
};
typedef struct CHAR_NODE CharNode;

struct CHAR_QUEUE {
    CharNode *first;
    CharNode *last;
};

typedef struct CHAR_QUEUE CharQueue;

CharQueue *CharQueue_alloc();
bool CharQueue_is_empty(CharQueue *fila);
void CharQueue_insert(CharQueue *fila, char c);
char CharQueue_remove(CharQueue *fila);
void CharQueue_free(CharQueue *fila);
int CharQueue_length(CharQueue *fila);
#endif