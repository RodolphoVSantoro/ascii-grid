#include "ascii_grid.h"

#include <stdio.h>
#include <stdlib.h>

#include "interop_rs.h"
#include "lib_ppm.h"
#ifdef _WIN32
#include <windows.h>
const unsigned char intensity_map[4] = {176, 177, 178, 219};
int map_to_grid_intensity(Reduced_Color color) {
    int red = color.red / color.number_of_pixels;
    int green = color.green / color.number_of_pixels;
    int blue = color.blue / color.number_of_pixels;
    int grey = (red + green + blue) / 3;
    int small_grey = grey / 64;

    return intensity_map[small_grey];
}

void set_grid_color(Grid_Color *grid, Reduced_Color reduced_color, int i, int j, rgb local_average) {
    unsigned char average_red = reduced_color.red / reduced_color.number_of_pixels;
    unsigned char average_green = reduced_color.green / reduced_color.number_of_pixels;
    unsigned char average_blue = reduced_color.blue / reduced_color.number_of_pixels;
    int local_average_color = (local_average.red + local_average.green + local_average.blue) / 3;
    grid[i + j * GRID_HEIGHT].red = average_red > local_average_color;
    grid[i + j * GRID_HEIGHT].green = average_green > local_average_color;
    grid[i + j * GRID_HEIGHT].blue = average_blue > local_average_color;
    grid[i + j * GRID_HEIGHT].intensity = map_to_grid_intensity(reduced_color);
}

rgb compute_regional_average(PPM *imagem, int i_start, int j_start, int i_end, int j_end) {
    Reduced_Color total_average = {0, 0, 0, 0};
    if (i_start < 0) {
        i_start = 0;
    }
    if (j_start < 0) {
        j_start = 0;
    }
    for (int i = i_start; i < i_end && i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = j_start; j < j_end && j < imagem->cabecalho->tamanho->largura; j++) {
            total_average.red += imagem->pixel[i][j].red;
            total_average.green += imagem->pixel[i][j].green;
            total_average.blue += imagem->pixel[i][j].blue;
            total_average.number_of_pixels++;
        }
    }
    total_average.red /= total_average.number_of_pixels;
    total_average.green /= total_average.number_of_pixels;
    total_average.blue /= total_average.number_of_pixels;

    return (rgb){total_average.red, total_average.green, total_average.blue};
}

Reduced_Color get_grid_color(int i, int j, int image_height, int height_ratio, int image_width, int width_ratio, PPM *imagem) {
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

Grid_Color *grid_image_init(int image_height, int image_width, PPM *imagem) {
    Grid_Color *grid = (Grid_Color *)malloc(sizeof(Grid_Color) * GRID_SIZE);

    int height_ratio = image_height / GRID_HEIGHT;
    int width_ratio = image_width / GRID_WIDTH;
    int square_size;
    if (height_ratio < width_ratio) {
        square_size = height_ratio * 10;
    } else {
        square_size = width_ratio * 10;
    }
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            Reduced_Color reduced_color = get_grid_color(i, j, image_height, height_ratio, image_width, width_ratio, imagem);
            rgb regional_average = compute_regional_average(imagem, i * height_ratio - square_size, j * width_ratio - square_size, i * height_ratio + square_size, j * width_ratio + square_size);
            set_grid_color(grid, reduced_color, i, j, regional_average);
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

void grid_draw(HANDLE hConsole, Grid_Color *grid) {
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
#endif
#ifdef __linux__
#include <locale.h>
#include <wchar.h>

void printColor(Grid_Color grid_color) {
    int red = grid_color.red;
    int green = grid_color.green;
    int blue = grid_color.blue;

    // opaque square
    int unicode = 0x2588;
    // diamond
    // int unicode = 0x1FBBF;
    // smol person
    // int unicode = 0x1FBB2;
    // square with more transparency
    // int unicode = 0x2592;
    wprintf(L"\x1B[38;2;%d;%d;%dm%lc", red, green, blue, unicode);
}
void grid_draw(Grid_Color *grid) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            printColor(grid[i + j * GRID_HEIGHT]);
        }
        wprintf(L"\n");
    }
}
Grid_Color *grid_image_init(int image_height, int image_width, PPM *imagem) {
    Grid_Color *grid = (Grid_Color *)malloc(sizeof(Grid_Color) * GRID_SIZE);

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

Reduced_Color get_grid_color(int i, int j, int image_height, int height_ratio, int image_width, int width_ratio, PPM *imagem) {
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

void set_grid_color(Grid_Color *grid, Reduced_Color reduced_color, int i, int j) {
    unsigned char average_red = reduced_color.red / reduced_color.number_of_pixels;
    unsigned char average_green = reduced_color.green / reduced_color.number_of_pixels;
    unsigned char average_blue = reduced_color.blue / reduced_color.number_of_pixels;
    grid[i + j * GRID_HEIGHT].red = average_red;
    grid[i + j * GRID_HEIGHT].green = average_green;
    grid[i + j * GRID_HEIGHT].blue = average_blue;
}

#endif
