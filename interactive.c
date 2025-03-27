#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

void Exit() {
    exit(0);
}

int ***Load(int ***image, int N, int M, char *path) {
    read_from_bmp(image, N, M, path);
    return image;
}

void Save(int ***image, int N, int M, char *path) {
    write_to_bmp(image, N, M, path);
}

int ***ApplyHorizontal(int ***image, int N, int M) {
    return flip_horizontal(image, N, M);
}

int ***ApplyRotate(int ***image, int N, int M) {
    int ***aux_image = rotate_left(image, N, M);
    image = calloc(M, sizeof(int **));
    if (!image) {
        printf("Alocare esuata!\n");
        exit(0);
    }
    int i = 0, j = 0;
    for (i = 0; i < M; i++) {
        image[i] = calloc(N, sizeof(int *));
        if (!image[i]) {
            printf("Alocare esuata!\n");
            exit(0);
        }
        for (j = 0; j < N; j++) {
            image[i][j] = calloc(3, sizeof(int));
            if (!image[i][j]) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            int k = 0;
            for (k = 0; k < 3; k++) {
                image[i][j][k] = aux_image[i][j][k];
            }
        }
    }
    dezaloc(aux_image, M, N);
    return image;
}

int ***ApplyCrop(int ***image, int *N, int *M, int x, int y, int w, int h) {
    int ***aux_image = crop(image, *N, *M, x, y, h, w);
    image = calloc(h, sizeof(int **));
    if (!image) {
        printf("Alocare esuata!\n");
        exit(0);
    }
    int i = 0, j = 0;
    for (i = 0; i < h; i++) {
        image[i] = calloc(w, sizeof(int *));
        if (!image[i]) {
            printf("Alocare esuata!\n");
            exit(0);
        }
        for (j = 0; j < w; j++) {
            image[i][j] = calloc(3, sizeof(int));
            if (!image[i][j]) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            int k = 0;
            for (k = 0; k < 3; k++) {
                image[i][j][k] = aux_image[i][j][k];
            }
        }
    }
    *N = h;
    *M = w;
    dezaloc(aux_image, *N, *M);
    return image;
}

int ***ApplyExtend(int ***image, int *N, int *M, int rows, int cols, int R, int G, int B) {
    int ***aux_image = extend(image, *N, *M, rows, cols, R, G, B);
    int n = *N + 2 * rows, m = *M + 2 * cols;
    image = calloc(n, sizeof(int **));
    if (!image) {
        printf("Alocare esuata!\n");
        exit(0);
    }
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        image[i] = calloc(m, sizeof(int *));
        if (!image[i]) {
            printf("Alocare esuata!\n");
            exit(0);
        }
        for (j = 0; j < m; j++) {
            image[i][j] = calloc(3, sizeof(int));
            if (!image[i][j]) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            int k = 0;
            for (k = 0; k < 3; k++) {
                image[i][j][k] = aux_image[i][j][k];
            }
        }
    }
    *N = n;
    *M = m;
    dezaloc(aux_image, *N, *M);
    return image;
}

int ***ApplyPaste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y) {
    return paste(image_dst, N_dst, M_dst, image_src, N_src, M_src, x, y);
}

float **CreateFilter(float **filter, int size) {
    int i = 0, j = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            scanf("%f ", &filter[i][j]);
        }
    }
    return filter;
}

int ***ApplyFilter(int ***image, int N, int M, float **filter, int filter_size) {
    return apply_filter(image, N, M, filter, filter_size);
}

void DeleteFilter(Filtered *matrix, int index, int filter_nr) {
    int i = 0;
    for (i = 0; i < matrix[index].size; i++) {
        free(matrix[index].filter[i]);
    }
    free(matrix[index].filter);
    for (i  = index+1; i < filter_nr; i++) {
        matrix[i-1] = matrix[i];
    }
}

void DeleteImage(Indexed *matrix, int index, int index_nr) {
    int i = 0;
    dezaloc(matrix[index].image, matrix[index].N, matrix[index].M);
    for (i  = index+1; i < index_nr; i++) {
        matrix[i-1] = matrix[i];
    }
}

int main() {
    Filtered *f_matrix = calloc(1, sizeof(Filtered));
    Indexed *matrix = calloc(1, sizeof(Indexed));
    if (!matrix) {
        printf("Alocare esuata!\n");
        exit(0);
    }
    int index_nr = 0, filter_nr = 0;
    const int SIZE_PATH = 100;
    char *cmd = calloc(SIZE_PATH, sizeof(char));
    while (1) {
        scanf("%s", cmd);

        if (strcmp(cmd, "e") == 0) {
            int i = 0;
            for (i = 0; i < index_nr; i++) {
                dezaloc(matrix[i].image, matrix[i].N, matrix[i].M);
            }
            free(matrix);
            for (i = 0; i < filter_nr; i++) {
                int j = 0;
                for (j = 0; j < f_matrix[i].size; j++) {
                    free(f_matrix[i].filter[j]);
                }
                free(f_matrix[i].filter);
            }
            free(f_matrix);
            free(cmd);
            Exit();
        } else if (strcmp(cmd, "l") == 0) {
            int N = 0, M = 0, i = 0, j = 0;
            char *path = calloc(SIZE_PATH, sizeof(char));
            scanf("%d %d %s ", &N, &M, path);
            Indexed *aux = realloc(matrix, (index_nr+1) * sizeof(Indexed));
            if (!aux) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            aux[index_nr].N = N;
            aux[index_nr].M = M;
            aux[index_nr].image = calloc(N, sizeof(int **));
            if (!aux[index_nr].image) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            for (i = 0; i < N; i++) {
                aux[index_nr].image[i] = calloc(M, sizeof(int *));
                if (!aux[index_nr].image[i]) {
                    printf("Alocare esuata!\n");
                    exit(0);
                }
                for (j = 0; j < M; j++) {
                    aux[index_nr].image[i][j] = calloc(3, sizeof(int));
                    if (!aux[index_nr].image[i][j]) {
                        printf("Alocare esuata!\n");
                        exit(0);
                    }
                }
            }
            matrix = aux;
            matrix[index_nr].image = Load(matrix[index_nr].image, N, M, path);
            index_nr++;
            free(path);
            continue;
        } else if (strcmp(cmd, "s") == 0) {
            int index = 0;
            char *path = calloc(SIZE_PATH, sizeof(char));
            scanf("%d %s", &index, path);
            Save(matrix[index].image, matrix[index].N, matrix[index].M, path);
            free(path);
            continue;
        } else if (strcmp(cmd, "ah") == 0) {
            int index = 0;
            scanf("%d", &index);
            matrix[index].image = ApplyHorizontal(matrix[index].image, matrix[index].N, matrix[index].M);
            continue;
        } else if (strcmp(cmd, "ar") == 0) {
            int index = 0;
            scanf("%d", &index);
            matrix[index].image = ApplyRotate(matrix[index].image, matrix[index].N, matrix[index].M);
            Swap(&matrix[index].N, &matrix[index].M);
            continue;
        } else if (strcmp(cmd, "ac") == 0) {
            int index = 0, x = 0, y = 0, w = 0, h = 0;
            scanf("%d %d %d %d %d", &index, &x, &y, &w, &h);
            matrix[index].image = ApplyCrop(matrix[index].image, &matrix[index].N, &matrix[index].M, x, y, w, h);
            continue;
        } else if (strcmp(cmd, "ae") == 0) {
            int index = 0, rows = 0, cols = 0, R = 0, G = 0, B = 0;
            scanf("%d %d %d %d %d %d", &index, &rows, &cols, &R, &G, &B);
            matrix[index].image = ApplyExtend(matrix[index].image, &matrix[index].N, &matrix[index].M,
                                              rows, cols, R, G, B);
            continue;
        } else if (strcmp(cmd, "ap") == 0) {
            int index_dst = 0, index_src = 0, x = 0, y = 0;
            scanf("%d %d %d %d", &index_dst, &index_src, &x, &y);
            matrix[index_dst].image = ApplyPaste(matrix[index_dst].image, matrix[index_dst].N,
                                                 matrix[index_dst].M, matrix[index_src].image,
                                                 matrix[index_src].N, matrix[index_src].M, x, y);
            continue;
        } else if (strcmp(cmd, "cf") == 0) {
            int size = 0;
            scanf("%d ", &size);
            Filtered *aux = realloc(f_matrix, (filter_nr+1) * sizeof(Filtered));
            if (!aux) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            aux[filter_nr].size = size;
            aux[filter_nr].filter = calloc(size, sizeof(float *));
            if (!aux[filter_nr].filter) {
                printf("Alocare esuata!\n");
                exit(0);
            }
            int i = 0;
            for (i = 0; i < size; i++) {
                aux[filter_nr].filter[i] = calloc(size, sizeof(float));
                if (!aux[filter_nr].filter[i]) {
                    printf("Alocare esuata!\n");
                    exit(0);
                }
            }
            f_matrix = aux;
            f_matrix[filter_nr].filter = CreateFilter(f_matrix[filter_nr].filter, size);
            filter_nr++;
            continue;
        } else if (strcmp(cmd, "af") == 0) {
            int index_img = 0, index_filter = 0;
            scanf("%d %d", &index_img, &index_filter);
            matrix[index_img].image = ApplyFilter(matrix[index_img].image, matrix[index_img].N, matrix[index_img].M,
                                                  f_matrix[index_filter].filter, f_matrix[index_filter].size);
        } else if (strcmp(cmd, "df") == 0) {
            int index_filter = 0;
            scanf("%d", &index_filter);
            DeleteFilter(f_matrix, index_filter, filter_nr);
            filter_nr--;
            continue;
        } else if (strcmp(cmd, "di") == 0) {
            int index_img = 0;
            scanf("%d", &index_img);
            DeleteImage(matrix, index_img, index_nr);
            index_nr--;
            continue;
        }
    }
    return 0;
}
