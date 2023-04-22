#ifndef ASCII_GRID_H
#define ASCII_GRID_H
#include <stdlib.h>

#include "lib_ppm.h"
#ifdef _WIN32
#define GRID_HEIGHT 60
#define GRID_WIDTH 230
#define GRID_SIZE (GRID_HEIGHT * GRID_WIDTH)

enum bool {
    false,
    true
};
typedef enum bool bool;

struct GRID_COLOR {
    bool red;
    bool green;
    bool blue;
    int intensity;
};

typedef struct GRID_COLOR Grid_Color;

extern const unsigned char intensity_map[4];
#endif

#ifdef __linux__
#define GRID_HEIGHT 993
#define GRID_WIDTH 1400
#define GRID_SIZE (GRID_HEIGHT * GRID_WIDTH)
struct GRID_COLOR {
    int red;
    int green;
    int blue;
};
typedef struct GRID_COLOR Grid_Color;
#endif

struct REDUCED_COLOR {
    int red;
    int green;
    int blue;
    int number_of_pixels;
};
typedef struct REDUCED_COLOR Reduced_Color;

Grid_Color *grid_image_init(int image_height, int image_width, PPM *imagem);
Reduced_Color get_grid_color(int i, int j, int image_height, int height_ratio, int image_width, int width_ratio, PPM *imagem);
int map_to_grid_intensity(Reduced_Color color);
#ifdef _WIN32
void setColor(HANDLE hConsole, Grid_Color grid_color);
void grid_draw(HANDLE hConsole, Grid_Color *grid);
void set_grid_color(Grid_Color *grid, Reduced_Color reduced_color, int i, int j, rgb local_average);
#endif
#ifdef __linux__
void printColor(Grid_Color grid_color);
void grid_draw(Grid_Color *grid);
void set_grid_color(Grid_Color *grid, Reduced_Color reduced_color, int i, int j);
#endif

#endif