#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned int u32;

struct person {
    u8** name;
    u8 age;
};
typedef struct person Person;

struct RGB {
    u8 red;
    u8 green;
    u8 blue;
};
typedef struct RGB rgb;

struct IMAGE {
    rgb** pixels;
    u32 width;
    u32 height;
};
typedef struct IMAGE Image;

Image load_image(const u8* path);
int add_numbers(int n1, int n2);
Person add(u8** name, u8 n2);

void free_image(Image image) {
    for (u32 i = 0; i < image.width; i++) {
        printf("%d ", i);
        free(image.pixels[i]);
    }
    free(image.pixels);
}

int main() {
    const u8* path = (u8*)"./bin/red.png";
    Image image = load_image(path);

    printf("%d", image.pixels[0][0].red);

    free_image(image);

    // printf("%d", add_numbers(1, 2));

    // u8** img = (u8**) malloc(sizeof(u8*) * 10);

    // for (int i = 0; i < 10; i++) {
    //     img[i] = (u8*) malloc(sizeof(u8) * 10);

    //     for (int j = 0; j < 10; j++) {
    //         img[i][j] = i * j;
    //     }
    // }

    // Person person = add(img, 10);

    // for (int i = 0; i < 10; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         printf("%d ", person.name[i][j]);
    //     }
    //     printf("\n");
    // }

    // for (int i = 0; i < 10; i++) {
    //     free(img[i]);
    // }

    // free(img);
}