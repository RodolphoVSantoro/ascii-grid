#ifndef CHAR_DOUBLE_QUEUE_H
#define CHAR_DOUBLE_QUEUE_H
#include <stdbool.h>

#include "char_queue.h"

struct CHAR_QUEUE_NODE {
    CharQueue *fila;
    struct CHAR_QUEUE_NODE *next;
};
typedef struct CHAR_QUEUE_NODE CharQueueNode;

struct CHAR_DOUBLE_QUEUE {
    CharQueueNode *first;
    CharQueueNode *last;
};

typedef struct CHAR_DOUBLE_QUEUE CharDoubleQueue;

CharDoubleQueue *CharDoubleQueue_alloc();
bool CharDoubleQueue_is_empty(CharDoubleQueue *fila);
void CharDoubleQueue_insert(CharDoubleQueue *fila, CharQueue *c);
CharQueue *CharDoubleQueue_remove(CharDoubleQueue *fila);
void CharDoubleQueue_free(CharDoubleQueue *fila);
int CharDoubleQueue_length(CharDoubleQueue *fila);
#endif