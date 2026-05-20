#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 3

int sMat[SIZE][SIZE];
int rMat[SIZE][SIZE];

typedef struct {
    int row;
} ThreadArg;

void *compute_row(void *arg) {
    int row = ((ThreadArg *)arg)->row;
    for (int col = 0; col < SIZE; col++)
        for (int k = 0; k < SIZE; k++)
            rMat[row][col] += sMat[row][k] * sMat[k][col];
    return NULL;
}

int main(void) {
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            sMat[i][j] = rand() % 10;

    printf("Source matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", sMat[i][j]);
        printf("\n");
    }

    pthread_t threads[SIZE];
    ThreadArg args[SIZE];

    for (int i = 0; i < SIZE; i++) {
        args[i].row = i;
        pthread_create(&threads[i], NULL, compute_row, &args[i]);
    }

    for (int i = 0; i < SIZE; i++)
        pthread_join(threads[i], NULL);

    printf("\nResult (squared):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", rMat[i][j]);
        printf("\n");
    }

    return 0;
}
