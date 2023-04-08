#include "lib_ppm.h"

#include <stdio.h>
#include <stdlib.h>

FILE *fopen_or_crash(char fname[], char modo[]) {
    FILE *arquivo = fopen(fname, modo);
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo %s\n", fname);
        exit(1);
    }
    return arquivo;
}

int string_compara(char *string1, char *string2) {
    int i;
    for (i = 0; string1[i] != 0 && string2[i] != 0; i++) {
        if (string1[i] < string2[i]) {
            return -1;
        } else if (string1[i] > string2[i]) {
            return 1;
        }
    }
    if (string1[i] == string2[i]) {
        return 0;
    } else if (string2[i] != 0) {
        return -1;
    } else {
        return 1;
    }
}

void PPM_pula_comentarios(FILE *arquivo) {
    int c;
    while ((c = fgetc(arquivo)) == '#' || c == ' ' || c == '\n') {
        if (c == '#') {
            while ((c = fgetc(arquivo)) != '\n' && c != EOF)
                ;
        } else {
            while (((c = fgetc(arquivo)) == '\n' || c == ' ') && c != EOF)
                ;
            ungetc(c, arquivo);
        }
    }
    ungetc(c, arquivo);
}

PPMHeader *PPMHeader_cria(int altura, int largura, int channelRange, BMPKey tipoBMP) {
    PPMHeader *cabecalho = (PPMHeader *)malloc(sizeof(*cabecalho));
    if (cabecalho == NULL) {
        printf("Erro ao alocar cabecalho\n");
        exit(1);
    }
    cabecalho->tamanho = (Dimensao2D *)malloc(sizeof(*cabecalho->tamanho));
    if (cabecalho->tamanho == NULL) {
        printf("Erro ao alocar cabecalho\n");
        exit(1);
    }

    cabecalho->tamanho->altura = altura;
    cabecalho->tamanho->largura = largura;
    cabecalho->channelRange = channelRange;
    cabecalho->tipoBMP = tipoBMP;
    return cabecalho;
}

void Dimensao2D_libera(Dimensao2D *dimensao) {
    free(dimensao);
    dimensao = NULL;
}

void PPMHeader_libera(PPMHeader *cabecalho) {
    Dimensao2D_libera(cabecalho->tamanho);
    cabecalho->tamanho = NULL;
    free(cabecalho);
    cabecalho = NULL;
}

PPM *PPM_cria() {
    PPM *imagem = (PPM *)malloc(sizeof(*imagem));
    if (imagem == NULL) {
        printf("Erro ao alocar imagem\n");
        exit(1);
    }

    imagem->cabecalho = PPMHeader_cria(0, 0, 255, Key_PPM);
    if (imagem->cabecalho == NULL) {
        printf("Erro ao alocar imagem\n");
        exit(1);
    }

    imagem->pixel = NULL;

    return imagem;
}

rgb **rgb2d_malloc(Dimensao2D tamanho) {
    rgb **Pixel2D = (rgb **)malloc(tamanho.altura * sizeof(*Pixel2D));
    if (Pixel2D == NULL) {
        printf("Falha ao alocar pixels\n");
        exit(1);
    }
    for (int i = 0; i < tamanho.altura; i++) {
        Pixel2D[i] = (rgb *)calloc(tamanho.largura, sizeof(**Pixel2D));
        if (Pixel2D[i] == NULL) {
            printf("Falha ao alocar pixels\n");
            exit(1);
        }
    }
    return Pixel2D;
}

void rgb2d_libera(rgb **pixel, Dimensao2D tamanho) {
    if (pixel == NULL) {
        return;
    }
    for (int i = 0; i < tamanho.altura; i++) {
        free(pixel[i]);
        pixel[i] = NULL;
    }
    free(pixel);
    pixel = NULL;
}

void PPM_libera(PPM *imagem) {
    rgb2d_libera(imagem->pixel, *imagem->cabecalho->tamanho);
    PPMHeader_libera(imagem->cabecalho);
    imagem->cabecalho = NULL;
    free(imagem);
    imagem = NULL;
}

PPM *PPM_leitura(const char *fname) {
    FILE *arquivo = fopen_or_crash((char *)fname, "r");

    int largura;
    int altura;
    int channelRange;
    char tipo[3];
    fscanf(arquivo, "%s", tipo);
    if (string_compara(tipo, "P3") != 0) {
        printf("O arquivo nao e um ppm");
        fclose(arquivo);
        arquivo = NULL;
        exit(1);
    }
    PPM_pula_comentarios(arquivo);

    fscanf(arquivo, "%d %d", &largura, &altura);
    fscanf(arquivo, "%d", &channelRange);
    BMPKey key = Key_PPM;
    PPM *imagem = PPM_cria();
    imagem->cabecalho = PPMHeader_cria(altura, largura, channelRange, key);
    imagem->pixel = rgb2d_malloc(*imagem->cabecalho->tamanho);

    int red, green, blue;
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            fscanf(arquivo, "%d", &red);
            imagem->pixel[i][j].red = red;
            fscanf(arquivo, "%d", &green);
            imagem->pixel[i][j].green = green;
            fscanf(arquivo, "%d", &blue);
            imagem->pixel[i][j].blue = blue;
        }
    }
    fclose(arquivo);
    arquivo = NULL;
    return imagem;
}

void efeito_aplica_negativo(PPM **imagem) {
    for (int i = 0; i < (*imagem)->cabecalho->tamanho->altura; i++)
        for (int j = 0; j < (*imagem)->cabecalho->tamanho->largura; j++) {
            (*imagem)->pixel[i][j].red = 255 - (*imagem)->pixel[i][j].red;
            (*imagem)->pixel[i][j].green = 255 - (*imagem)->pixel[i][j].green;
            (*imagem)->pixel[i][j].blue = 255 - (*imagem)->pixel[i][j].blue;
        }
}