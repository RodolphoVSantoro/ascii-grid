#include <stdio.h>
#include <stdlib.h>

#include "ascii_grid.h"
#include "char_double_queue.h"
#include "char_queue.h"
#include "folder_string.h"
#include "lib_ppm.h"

#ifdef _WIN32
#include <windows.h>
#else
#ifdef __linux__
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#endif

#ifdef _WIN32
int main(int argc, char *argv[]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char *image_name = NULL;
    int chosen_image = 0;
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
        chosen_image = 1;
        for (int i = 0; i < nFiles; i++) {
            free(images[i]);
        }
        free(images);
    } else {
        image_name = argv[1];
    }
    int invert = 0;
    if (argc >= 3) {
        invert = atoi(argv[2]);
    }
    printf("Opening image: %s\n", image_name);
    PPM *imagem = PPM_from_image(image_name);
    if (chosen_image) {
        free(image_name);
    }
    if (invert) {
        efeito_aplica_negativo(&imagem);
    }
    int image_height = imagem->cabecalho->tamanho->altura;
    int image_width = imagem->cabecalho->tamanho->largura;

    Grid_Color *grid = grid_image_init(image_height, image_width, imagem);
    grid_draw(hConsole, grid);

    free(grid);
    PPM_libera(imagem);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}
#else
#ifdef __linux__
#include <locale.h>
#include <wchar.h>
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    char *image_name = NULL;
    int chosen_image = 0;
    if (argc < 2) {
        system("ls ./images > .temp.txt");
        FILE *fp = fopen(".temp.txt", "r");
        if (fp == NULL) {
            wprintf(L"Usage: %s <image_name = $path> <invert = 0 | 1> \n", argv[0]);
            return 1;
        }
        CharDoubleQueue *fila_dupla = CharDoubleQueue_alloc();
        CharQueue *fila_char = CharQueue_alloc();
        char c = fgetc(fp);
        while (c != EOF) {
            if (c == '\n') {
                if (!CharQueue_is_empty(fila_char)) {
                    CharDoubleQueue_insert(fila_dupla, fila_char);
                    fila_char = CharQueue_alloc();
                }
            } else {
                CharQueue_insert(fila_char, c);
            }
            c = fgetc(fp);
        }
        fclose(fp);
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
            return 1;
        }
        image_name = newFrom(images[image_index - 1]);
        chosen_image = 1;
        for (int i = 0; i < nFiles; i++) {
            free(images[i]);
        }
        free(images);
    } else {
        image_name = argv[1];
    }
    int invert = 0;
    if (argc >= 3) {
        invert = atoi(argv[2]);
    }
    wprintf(L"Opening image: %s\n", image_name);
    PPM *imagem = PPM_from_image(image_name);
    if (chosen_image) {
        free(image_name);
    }
    if (invert) {
        efeito_aplica_negativo(&imagem);
    }
    int image_height = imagem->cabecalho->tamanho->altura;
    int image_width = imagem->cabecalho->tamanho->largura;

    Grid_Color *grid = grid_image_init(image_height, image_width, imagem);
    grid_draw(grid);

    free(grid);
    PPM_libera(imagem);
    return 0;
}
#else
#error "Operational system not supported"
#endif
#endif