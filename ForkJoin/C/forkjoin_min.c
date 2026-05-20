#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE      100
#define THRESHOLD  10

typedef struct {
    int *array;
    int  lo;
    int  hi;
    int  result;
} MinTask;

void *compute_min(void *arg) {
    MinTask *task = (MinTask *)arg;

    if (task->hi - task->lo < THRESHOLD) {
        int min = task->array[task->lo];
        for (int i = task->lo; i < task->hi; i++)
            if (task->array[i] < min)
                min = task->array[i];
        task->result = min;
        return NULL;
    }

    int mid = (task->lo + task->hi) / 2;

    MinTask left  = { task->array, task->lo, mid, 0 };
    MinTask right = { task->array, mid, task->hi, 0 };

    pthread_t tid;
    pthread_create(&tid, NULL, compute_min, &left);
    compute_min(&right);
    pthread_join(tid, NULL);

    task->result = left.result < right.result ? left.result : right.result;
    return NULL;
}

int main(void) {
    int data[SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
        data[i] = rand() % 100;

    printf("Searching minimum from:\n");
    for (int i = 0; i < SIZE; i++) {
        if (i % 10 == 0) printf("\n");
        printf("%2d ", data[i]);
    }
    printf("\n");

    MinTask root = { data, 0, SIZE, 0 };
    compute_min(&root);

    printf("\nResult is %d\n", root.result);
    return 0;
}
