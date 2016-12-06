#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* runner(void*);	// Pre-definition of the runnable task for the threads
int sum;		// This data is shared by the threads

int main(int argc, char const **argv)
{
	pthread_t tid;		// Thread identifier
	pthread_attr_t attr;	// Set of thread attributes

	if(argc != 2)
	{
		printf("usage: a.out <integer value>\n");
		return -1;
	}

	if(atoi(argv[1]) < 0)
	{
		printf("%d must be greater than zero.\n", atoi(argv[1]));
		return -1;
	}

	pthread_attr_init(&attr);	// Default attributes

	// Create the thread. At this point the thread begins to execute
	pthread_create(&tid, &attr, &runner, argv[1]);

	// Wait for the thread to finish
	pthread_join(tid, NULL);

	return 0;
}

// On ly the threads have control in this functions
void* runner(void *param)
{
	int i, upper = atoi(param);
	sum = 0;

	for (i = 0; i <= upper; ++i)
		sum += i;

	printf("Sum: %d\n", sum);

	// Thread finishes
	pthread_exit(0);
}
