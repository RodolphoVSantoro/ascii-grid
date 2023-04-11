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

void set_grid_color(Grid_Color* grid, Reduced_Color reduced_color, int i, int j, rgb local_average) {
    unsigned char average_red = reduced_color.red / reduced_color.number_of_pixels;
    unsigned char average_green = reduced_color.green / reduced_color.number_of_pixels;
    unsigned char average_blue = reduced_color.blue / reduced_color.number_of_pixels;
    int local_average_color = (local_average.red + local_average.green + local_average.blue) / 3;
    grid[i + j * GRID_HEIGHT].red = average_red > local_average_color;
    grid[i + j * GRID_HEIGHT].green = average_green > local_average_color;
    grid[i + j * GRID_HEIGHT].blue = average_blue > local_average_color;
    grid[i + j * GRID_HEIGHT].intensity = map_to_grid_intensity(reduced_color);
}

rgb compute_regional_average(PPM* imagem, int i_start, int j_start, int i_end, int j_end) {
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

Grid_Color* grid_image_init(int image_height, int image_width, PPM* imagem) {
    Grid_Color* grid = (Grid_Color*)malloc(sizeof(Grid_Color) * GRID_SIZE);

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

int getLength(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char* newFrom(char* str) {
    int string_length = getLength(str);
    char* newStr = (char*)malloc(sizeof(char) * (string_length + 1));
    int i;
    for (i = 0; i < string_length; i++) {
        newStr[i] = str[i];
    }
    newStr[i] = '\0';
    return newStr;
}

char* withFolderName(char* folder_name, char* file_name) {
    int folder_name_length = getLength(folder_name);
    int file_name_length = getLength(file_name);
    char* newStr = (char*)malloc(sizeof(char) * (folder_name_length + file_name_length + 2));
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

#ifdef _WIN32
int main(int argc, char* argv[]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char* image_name = NULL;
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
        char** images = (char**)malloc(sizeof(char*) * nFiles);
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
    PPM* imagem = PPM_from_image(image_name);
    if (chosen_image) {
        free(image_name);
    }
    if (invert) {
        efeito_aplica_negativo(&imagem);
    }
    int image_height = imagem->cabecalho->tamanho->altura;
    int image_width = imagem->cabecalho->tamanho->largura;

    Grid_Color* grid = grid_image_init(image_height, image_width, imagem);
    grid_draw(hConsole, grid);

    free(grid);
    PPM_libera(imagem);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}
#else
#error "Operational system not supported"
#endif