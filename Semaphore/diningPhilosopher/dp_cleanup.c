#include "dp_header.h"

int main(void)
{
    int sem_id = semget(SEMKEY, N, 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(1);
    }
    if (semctl(sem_id, 0, IPC_RMID) < 0) {
        perror("semctl IPC_RMID");
        exit(1);
    }
    printf("Semaphore set removed.\n");
    return 0;
}
