#ifndef INTEROP_RS_H
#define INTEROP_RS_H
typedef unsigned char u8;
typedef unsigned int u32;

struct RUST_RGB {
    u8 red;
    u8 green;
    u8 blue;
};
typedef struct RUST_RGB rust_rgb;

struct IMAGE {
    rust_rgb** pixels;
    u32 width;
    u32 height;
};
typedef struct IMAGE Image;

Image load_image(const char* path);
void drop_image(Image image);
#endif
/*-------------------HOW TO USE-------------------*/
/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    Image image = load_image("./red.png");

    printf("%d", image.pixels[0][0].red);
    printf("%d\n", image.width);
    printf("%d\n", image.height);

    drop_image(image);
}
*/