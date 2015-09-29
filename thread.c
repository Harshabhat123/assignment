#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* hi()
{
    int i;
    for(i=0;i<20;i++)
    printf("%d-hi\n",i);
}
void* hello()
{
 printf("hello\n");
}
int main()
{
    pthread_t id;
    pthread_t id1;
    pthread_create(&id,NULL,hi,NULL);
    pthread_join(id,NULL);
    pthread_create(&id1,NULL,hello,NULL);
    pthread_join(id1,NULL);
    printf("hi harsha\n");
}