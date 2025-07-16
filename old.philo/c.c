#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *winner = NULL;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *routine(void *arg)
{
    int id = *(int *)arg;

    // Randomize small delay
    usleep(rand() % 1000);

    pthread_mutex_lock(&lock);
    if (winner == NULL)
    {
        if (id == 2)
            winner = "thread 2";
        else
            winner = "thread 1";
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t th[2];
    int id1 = 1, id2 = 2;

    srand(time(NULL)); // Seed randomness

	pthread_create(&th[0], NULL, routine, &id1);
	pthread_create(&th[1], NULL, routine, &id2);

    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);

    printf("Winner: %s\n", winner);

    pthread_mutex_destroy(&lock);
    return 0;
}
