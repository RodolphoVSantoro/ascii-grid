#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define GRID_HEIGHT 60
#define GRID_WIDTH 230
#define GRID_SIZE (GRID_HEIGHT * GRID_WIDTH)

#include "lib_ppm.h"

enum bool { false,
            true };
typedef enum bool bool;

struct REDUCED_COLOR {
    int red;
    int green;
    int blue;
    int number_of_pixels;
};
typedef struct REDUCED_COLOR Reduced_Color;

struct GRID_COLOR {
    bool red;
    bool green;
    bool blue;
    int intensity;
};
typedef struct GRID_COLOR Grid_Color;

unsigned char intensity_map[4] = {176, 177, 178, 219};

int map_to_grid_intensity(Reduced_Color color) {
    int red = color.red / color.number_of_pixels;
    int green = color.green / color.number_of_pixels;
    int blue = color.blue / color.number_of_pixels;
    int grey = (red + green + blue) / 3;
    int small_grey = grey / 64;

    return intensity_map[small_grey];
}

Reduced_Color get_grid_color(int i, int j, int image_height, int height_ratio, int image_width, int width_ratio, PPM* imagem) {
    Reduced_Color reduced_color = {0, 0, 0, 0};

    for (int k = i * height_ratio; k < (i + 1) * height_ratio; k++) {
        for (int l = j * width_ratio; l < (j + 1) * width_ratio; l++) {
            if (l >= image_width) {
                break;
            }
            reduced_color.red += imagem->pixel[k][l].red;
            reduced_color.green += imagem->pixel[k][l].green;
            reduced_color.blue += imagem->pixel[k][l].blue;
            reduced_color.number_of_pixels++;
        }
        if (k >= image_height) {
            break;
        }
    }

    return reduced_color;
}

void set_grid_color(Grid_Color* grid, Reduced_Color reduced_color, int i, int j) {
    unsigned char average_red = reduced_color.red / reduced_color.number_of_pixels;
    unsigned char average_green = reduced_color.green / reduced_color.number_of_pixels;
    unsigned char average_blue = reduced_color.blue / reduced_color.number_of_pixels;
    grid[i + j * GRID_HEIGHT].red = average_red > 51;
    grid[i + j * GRID_HEIGHT].green = average_green > 51;
    grid[i + j * GRID_HEIGHT].blue = average_blue > 51;
    grid[i + j * GRID_HEIGHT].intensity = map_to_grid_intensity(reduced_color);
}

Grid_Color* grid_image_init(int image_height, int image_width, PPM* imagem) {
    Grid_Color* grid = (Grid_Color*)malloc(sizeof(Grid_Color) * GRID_SIZE);

    int height_ratio = image_height / GRID_HEIGHT;
    int width_ratio = image_width / GRID_WIDTH;
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            Reduced_Color reduced_color = get_grid_color(i, j, image_height, height_ratio, image_width, width_ratio, imagem);
            set_grid_color(grid, reduced_color, i, j);
        }
    }
    return grid;
}

void setColor(HANDLE hConsole, Grid_Color grid_color) {
    WORD color = 0;
    if (grid_color.red) {
        color = color | FOREGROUND_RED;
    }
    if (grid_color.green) {
        color = color | FOREGROUND_GREEN;
    }
    if (grid_color.blue) {
        color = color | FOREGROUND_BLUE;
    }

    SetConsoleTextAttribute(hConsole, color);
}

void grid_draw(HANDLE hConsole, Grid_Color* grid) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            setColor(hConsole, grid[i + j * GRID_HEIGHT]);
            printf("%c", grid[i + j * GRID_HEIGHT].intensity);
            // for (int sleep = 0; sleep < 1000000; sleep++)
            //   ;
        }
        printf("\n");
    }
}

void list_ascii() {
    for (int i = 33; i <= 256; i++) {
        printf("%d: %c\n", i, i);
    }
}

int main(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    PPM* imagem = PPM_leitura("images/hk.ppm");
    // efeito_aplica_negativo(&imagem);
    int image_height = imagem->cabecalho->tamanho->altura;
    int image_width = imagem->cabecalho->tamanho->largura;

    Grid_Color* grid = grid_image_init(image_height, image_width, imagem);
    grid_draw(hConsole, grid);

    free(grid);
    PPM_libera(imagem);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}
