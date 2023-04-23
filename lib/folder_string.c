#include <stdio.h>
#include <stdlib.h>

#include "char_double_queue.h"
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

#ifdef __linux__
#include <locale.h>
#include <wchar.h>
void parse_args(int argc, char *argv[], char **image_name, int *chose_image, int *should_invert) {
    if (argc < 2) {
        system("ls ./images > .temp.txt");
        FILE *folder_files = fopen(".temp.txt", "r");
        if (folder_files == NULL) {
            wprintf(L"Usage: %s <image_name = $path> <invert = 0 | 1> \n", argv[0]);
            exit(1);
        }
        CharDoubleQueue *fila_dupla = CharDoubleQueue_alloc();
        CharQueue *fila_char = CharQueue_alloc();
        char c = fgetc(folder_files);
        while (c != EOF) {
            if (c == '\n') {
                if (!CharQueue_is_empty(fila_char)) {
                    CharDoubleQueue_insert(fila_dupla, fila_char);
                    fila_char = CharQueue_alloc();
                }
            } else {
                CharQueue_insert(fila_char, c);
            }
            c = fgetc(folder_files);
        }
        fclose(folder_files);
        int nFiles = CharDoubleQueue_length(fila_dupla);
        char **images = (char **)malloc(sizeof(char *) * nFiles);
        CharQueueNode *CharDoubleQueue_cursor = fila_dupla->first;
        int i = 0;
        while (CharDoubleQueue_cursor != NULL && i < nFiles) {
            char *cursor_file_name = CharQueue_into_new_string(CharDoubleQueue_cursor->fila);
            images[i] = withFolderName("./images", cursor_file_name);
            free(cursor_file_name);
            wprintf(L"%d - %s \n", i + 1, images[i]);
            i++;
            CharDoubleQueue_cursor = CharDoubleQueue_cursor->next;
        }
        CharDoubleQueue_free(fila_dupla);
        int image_index;
        wprintf(L"Choose one of the images above: ");
        scanf("%d", &image_index);
        if (image_index < 1 || image_index > nFiles) {
            wprintf(L"Invalid image index\n");
            exit(1);
        }
        *image_name = newFrom(images[image_index - 1]);
        *chose_image = 1;
        for (int i = 0; i < nFiles; i++) {
            free(images[i]);
        }
        free(images);
    } else {
        *image_name = argv[1];
    }
    *should_invert = 0;
    if (argc >= 3) {
        *should_invert = atoi(argv[2]);
    }
}
#elif _WIN32
void parse_args(int argc, char *argv[], char **image_name, int *chose_image, int *should_invert) {
    if (argc < 2) {
        HANDLE hFind;
        WIN32_FIND_DATA FindData;
        hFind = FindFirstFile("./images/*", &FindData);

        if (hFind == INVALID_HANDLE_VALUE) {
            printf("Usage: %s <image_name = $path> <invert = 0 | 1> \n", argv[0]);
            return 1;
        }

        int nFiles = 1;
        while (FindNextFile(hFind, &FindData)) {
            nFiles++;
        }

        FindClose(hFind);

        hFind = FindFirstFile("./images/*", &FindData);
        char **images = (char **)malloc(sizeof(char *) * nFiles);
        for (int i = 0; i < nFiles; i++) {
            images[i] = withFolderName("./images", FindData.cFileName);
            printf("%d - %s \n", i + 1, FindData.cFileName);
            FindNextFile(hFind, &FindData);
        }

        FindClose(hFind);

        int image_index;
        printf("Choose one of the images above: ");
        scanf("%d", &image_index);
        if (image_index < 1 || image_index > nFiles) {
            printf("Invalid image index\n");
            return 1;
        }
        image_name = newFrom(images[image_index - 1]);
        chose_image = 1;
        for (int i = 0; i < nFiles; i++) {
            free(images[i]);
        }
        free(images);
    } else {
        image_name = argv[1];
    }
    *should_invert = 0;
    if (argc >= 3) {
        *should_invert = atoi(argv[2]);
    }
}
#else
#error "This OS is not supported"
#endif