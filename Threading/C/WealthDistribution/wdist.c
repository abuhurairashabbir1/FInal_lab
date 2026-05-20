#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Please provide: number_of_Players initial_balance cut_Off_Value zakat_on_off\n");
        return 1;
    }

    int numPlayers    = atoi(argv[1]);
    int initialBalance = atoi(argv[2]);
    int cutOffValue   = atoi(argv[3]);
    int zakat         = atoi(argv[4]);
    int rounds        = 0;

    int *balances = malloc(numPlayers * sizeof(int));
    if (!balances) { perror("malloc"); return 1; }

    srand(time(NULL));

    for (int i = 0; i < numPlayers; i++)
        balances[i] = initialBalance;

    while (numPlayers > 1) {
        for (int i = 0; i < numPlayers; i++) {
            if (balances[i] < cutOffValue && zakat == 0)
                continue;

            int opponent;
            do {
                opponent = rand() % numPlayers;
            } while (opponent == i || balances[opponent] < cutOffValue);

            int betAmount = (balances[i] < balances[opponent] ? balances[i] : balances[opponent]) / 5;

            if (rand() % 2) {
                balances[i]        += betAmount;
                balances[opponent] -= betAmount;
            } else {
                balances[i]        -= betAmount;
                balances[opponent] += betAmount;
            }

            printf("Player %d (%d) vs Player %d (%d)\n",
                   i, balances[i], opponent, balances[opponent]);
        }

        printf("This was round# %d\n", ++rounds);

        if (zakat == 1) {
            int poor = -1, rich = 0, max = 0;
            for (int i = 0; i < numPlayers; i++)
                if (balances[i] <= cutOffValue) { poor = i; break; }

            if (poor != -1) {
                for (int i = 0; i < numPlayers; i++)
                    if (balances[i] > max) { max = balances[i]; rich = i; }

                int calc_zakat = (int)(balances[rich] * 0.025);
                balances[poor] += calc_zakat;
                balances[rich] -= calc_zakat;
                printf("Zakat = %d was transferred from Player %d to %d\n",
                       calc_zakat, rich, poor);
            }
        } else {
            int remaining = 0;
            for (int i = 0; i < numPlayers; i++) {
                if (balances[i] >= cutOffValue) {
                    balances[remaining++] = balances[i];
                } else {
                    printf("Player %d eliminated with balance %d\n", i, balances[i]);
                }
            }
            numPlayers = remaining;
        }
    }

    printf("Game finished after %d rounds\n", rounds);
    free(balances);
    return 0;
}
