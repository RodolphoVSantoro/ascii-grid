#include <stdlib.h>

#include "char_queue.h"

int getLength(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *newFrom(char *str) {
    int string_length = getLength(str);
    char *newStr = (char *)malloc(sizeof(char) * (string_length + 1));
    int i;
    for (i = 0; i < string_length; i++) {
        newStr[i] = str[i];
    }
    newStr[i] = '\0';
    return newStr;
}

char *withFolderName(char *folder_name, char *file_name) {
    int folder_name_length = getLength(folder_name);
    int file_name_length = getLength(file_name);
    char *newStr = (char *)malloc(sizeof(char) * (folder_name_length + file_name_length + 2));
    int i;
    for (i = 0; i < folder_name_length; i++) {
        newStr[i] = folder_name[i];
    }
    newStr[i] = '/';
    i++;
    for (int j = 0; j < file_name_length; j++) {
        newStr[i] = file_name[j];
        i++;
    }
    newStr[i] = '\0';
    return newStr;
}
char *CharQueue_into_new_string(CharQueue *queue) {
    int queue_length = CharQueue_length(queue);
    char *str = (char *)malloc(sizeof(char) * (queue_length + 1));
    int i;
    for (i = 0; i < queue_length; i++) {
        str[i] = CharQueue_remove(queue);
    }
    str[i] = '\0';
    return str;
}