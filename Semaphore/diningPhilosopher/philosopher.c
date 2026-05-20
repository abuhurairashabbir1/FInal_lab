#include "dp_header.h"

int main(int argc, char *argv[])
{
    int sem_id, id;
    int left, right;
    struct sembuf pick, put;
    union semun arg;
    unsigned short forks[N];

    if (argc != 2) {
        printf("Usage: %s <philosopher_id (0-%d)>\n", argv[0], N - 1);
        exit(1);
    }

    id = atoi(argv[1]);
    if (id < 0 || id >= N) {
        printf("Philosopher ID must be between 0 and %d\n", N - 1);
        exit(1);
    }

    left  = id;
    right = (id + 1) % N;

    /* deadlock prevention: last philosopher picks up right fork first */
    if (id == N - 1) {
        int tmp = left;
        left  = right;
        right = tmp;
    }

    sem_id = semget(SEMKEY, N, 0666);
    if (sem_id < 0) {
        perror("Cannot get semaphore");
        exit(1);
    }

    /* show current fork status */
    arg.array = forks;
    semctl(sem_id, 0, GETALL, arg);
    printf("Philosopher %d: Fork status: ", id);
    for (int i = 0; i < N; i++)
        printf("Fork%d=%d ", i, arg.array[i]);
    printf("\n");

    printf("Philosopher %d is thinking...\n", id);
    sleep(1);

    /* pick up left fork */
    pick.sem_num = left;
    pick.sem_op  = -1;
    pick.sem_flg = 0;
    printf("Philosopher %d waiting for fork %d (left)...\n", id, left);
    if (semop(sem_id, &pick, 1) < 0) {
        perror("semop pick left");
        exit(1);
    }
    printf("Philosopher %d picked up fork %d (left)\n", id, left);

    /* pick up right fork */
    pick.sem_num = right;
    pick.sem_op  = -1;
    pick.sem_flg = 0;
    printf("Philosopher %d waiting for fork %d (right)...\n", id, right);
    if (semop(sem_id, &pick, 1) < 0) {
        perror("semop pick right");
        exit(1);
    }
    printf("Philosopher %d picked up fork %d (right)\n", id, right);

    printf("Philosopher %d is EATING!\n", id);
    sleep(2);

    /* put down both forks */
    put.sem_num = left;
    put.sem_op  = 1;
    put.sem_flg = 0;
    semop(sem_id, &put, 1);

    put.sem_num = right;
    semop(sem_id, &put, 1);

    printf("Philosopher %d finished eating, released forks %d and %d\n", id, left, right);

    /* show updated fork status */
    semctl(sem_id, 0, GETALL, arg);
    printf("Philosopher %d: Fork status now: ", id);
    for (int i = 0; i < N; i++)
        printf("Fork%d=%d ", i, arg.array[i]);
    printf("\n");

    return 0;
}
