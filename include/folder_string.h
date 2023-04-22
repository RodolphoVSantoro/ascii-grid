#ifndef READ_FOLDER_H
#define READ_FOLDER_H
#include <stdlib.h>

#include "char_queue.h"

int getLength(char *str);
char *newFrom(char *str);
char *withFolderName(char *folder_name, char *file_name);
char *CharQueue_into_new_string(CharQueue *queue);
#endif