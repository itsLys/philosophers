#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x  = 0;
pthread_mutex_t mutex;
void* routine(void *ptr)
{
	int i  = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		x++;
		i++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

// first we haveto define a place where store informations about the thread
// always check your threads
int main()
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL))
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL))
		return 2;
	if (pthread_join(t1, NULL))
		return 3;
	if (pthread_join(t2, NULL))
		return 4;
	// WARN: ALWAYS DESTROY 
	pthread_mutex_destroy(&mutex);
	printf("x:	%d\n", x);
}
