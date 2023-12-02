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
    int chose_image = 0;
    int should_invert = 0;

    parse_args(argc, argv, &image_name, &chose_image, &should_invert);

    printf("Opening image: %s\n", image_name);
    PPM *imagem = PPM_from_image(image_name);
    if (chose_image) {
        free(image_name);
    }
    if (should_invert) {
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
    int chose_image = 0;
    int should_invert = 0;

    parse_args(argc, argv, &image_name, &chose_image, &should_invert);

    wprintf(L"Opening image: %s\n", image_name);
    PPM *imagem = PPM_from_image(image_name);
    if (chose_image) {
        free(image_name);
    }

    if (should_invert) {
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