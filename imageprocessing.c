#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

void Swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void dezaloc(int ***image, int N, int M) {
    int i = 0, j = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
}

// Task 1
int ***flip_horizontal(int ***image, int N, int M) {
    int i = 0, j = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M / 2; j++) {
            Swap(&image[i][j][0], &image[i][M-j-1][0]);
            Swap(&image[i][j][1], &image[i][M-j-1][1]);
            Swap(&image[i][j][2], &image[i][M-j-1][2]);
        }
    }
    return image;
}

// Task 2
int ***rotate_left(int ***image, int N, int M) {
    int ***aux_image = calloc(M, sizeof(int **));
    if (!aux_image) {
        printf("Alocare esuata!\n");
        exit(0);
    }
    int i = 0, j = 0;
    for (i = 0; i < M; i++) {
        aux_image[i] = calloc(N, sizeof(int *));
        if (!aux_image[i]) {
            printf("Alocare esuata!\n");
            exit(0);
        }
        for (j = 0; j < N; j++) {
            aux_image[i][j] = calloc(3, sizeof(int));
            if (!aux_image[i][j]) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            int k = 0;
            for (k = 0; k < 3; k++) {
                aux_image[i][j][k] = image[j][M-i-1][k];
            }
        }
    }
    dezaloc(image, N, M);
    return aux_image;
}

// Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***aux_image = calloc(h, sizeof(int **));
    if (!aux_image) {
        printf("Alocare esuata!\n");
        exit(0);
    }
    int i = 0, j = 0;
    for (i = 0; i < h; i++) {
        aux_image[i] = calloc(w, sizeof(int *));
        if (!aux_image[i]) {
            printf("Alocare esuata!\n");
            exit(0);
        }
        for (j = 0; j < w; j++) {
            aux_image[i][j] = calloc(3, sizeof(int));
            if (!aux_image[i][j]) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            int k = 0;
            for (k = 0; k < 3; k++) {
                aux_image[i][j][k] = image[i+y][j+x][k];
            }
        }
    }
    dezaloc(image, N, M);
    return aux_image;
}

// Task 4
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int n = N + 2 * rows, m = M + 2 * cols;
    int ***aux_image = calloc(n, sizeof(int **));
    if (!aux_image) {
        printf("Alocare esuata!\n");
        exit(0);
    }
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        aux_image[i] = calloc(m, sizeof(int *));
        if (!aux_image[i]) {
            printf("Alocare esuata!\n");
            exit(0);
        }
        for (j = 0; j < m; j++) {
            aux_image[i][j] = calloc(3, sizeof(int));
            if (!aux_image[i][j]) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            if (i >= rows && i < rows + N && j >= cols && j < cols + M) {
                int k = 0;
                for (k = 0; k < 3; k++) {
                    aux_image[i][j][k] = image[i-rows][j-cols][k];
                }
            } else {
                aux_image[i][j][0] = new_R;
                aux_image[i][j][1] = new_G;
                aux_image[i][j][2] = new_B;
            }
        }
    }
    dezaloc(image, N, M);
    return aux_image;
}

// Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y) {
    int i = 0, j = 0;
    for (i = y; i < N_dst && i < y + N_src; i++) {
        for (j = x; j < M_dst && j < x + M_src; j++) {
            int k = 0;
            for (k = 0; k < 3; k++) {
                image_dst[i][j][k] = image_src[i-y][j-x][k];
            }
        }
    }
    return image_dst;
}

// Task 6
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    const int MAX_LIM = 255, MIN_LIM = 0;
    int ***aux_image = calloc(N, sizeof(int **));
    if (!aux_image) {
        printf("Alocare esuata!\n");
        exit(0);
    }
    int i = 0, j = 0, k = 0;
    for (i = 0; i < N; i++) {
        aux_image[i] = calloc(M, sizeof(int *));
        if (!aux_image[i]) {
            printf("Alocare esuata!\n");
            exit(0);
        }
        for (j = 0; j < M; j++) {
            aux_image[i][j] = calloc(3, sizeof(int));
            if (!aux_image[i][j]) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            for (k = 0; k < 3; k++) {
                int x = 0, y = 0, l = filter_size / 2;
                float val = 0;
                for (y = -l; y <= l; y++) {
                    if (i + y < 0 || i + y >= N) {
                        continue;
                    } else {
                        for (x = -l; x <= l; x++) {
                            if (j + x < 0 || j + x >= M) {
                                continue;
                            }
                            val += (float)image[i+y][j+x][k] * filter[l+y][l+x];
                        }
                    }
                }
                aux_image[i][j][k] = (int) val;
                if (aux_image[i][j][k] < MIN_LIM) {
                    aux_image[i][j][k] = MIN_LIM;
                } else if (aux_image[i][j][k] > MAX_LIM) {
                    aux_image[i][j][k] = MAX_LIM;
                }
            }
        }
    }
    dezaloc(image, N, M);
    return aux_image;
}
