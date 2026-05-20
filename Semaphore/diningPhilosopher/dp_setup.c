#include "dp_header.h"

int main(void)
{
    int sem_id;
    union semun arg;
    unsigned short forks[N];

    sem_id = semget(SEMKEY, N, IPC_CREAT | IPC_EXCL | 0666);
    if (sem_id < 0) {
        perror("Cannot create semaphore");
        exit(1);
    }

    /* each fork starts as available (1) */
    for (int i = 0; i < N; i++)
        forks[i] = 1;

    arg.array = forks;
    if (semctl(sem_id, 0, SETALL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Semaphore set created. %d forks initialized to 1 (available).\n", N);
    return 0;
}
