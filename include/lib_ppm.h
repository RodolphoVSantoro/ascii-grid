#ifndef PPM_H
#define PPM_H

typedef unsigned char uchar;

struct RGB {
    uchar red, green, blue;
};
typedef struct RGB rgb;
struct DIM2D {
    int largura;
    int altura;
};
typedef struct DIM2D Dimensao2D;

enum BMPKEY {
    Key_BM = 1,
    Key_BW = 2,
    Key_PPM = 3,
    Key_BMP = 6
};
typedef enum BMPKEY BMPKey;
struct PPMHEADER {
    Dimensao2D *tamanho;
    int channelRange;
    BMPKey tipoBMP;
};
typedef struct PPMHEADER PPMHeader;

struct PPM {
    PPMHeader *cabecalho;
    rgb **pixel;
};
typedef struct PPM PPM;

PPM *PPM_leitura(const char *fname);
void PPM_libera(PPM *imagem);
void efeito_aplica_negativo(PPM **imagem);
PPM *PPM_from_image(const char *fname);
#endif
