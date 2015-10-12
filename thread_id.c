#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
void* thread_function (void* arg)
{
printf("child thread pid is %d\n", (int) getpid ());
return NULL;
}

int main ()
{
pthread_t thread;
printf ("main thread pid is %d\n", (int) getpid ());
pthread_create (&thread, NULL, &thread_function, NULL);
pthread_join(thread,NULL);
return 0;
}