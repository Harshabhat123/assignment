#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
void* abc(void* z)
{
    int i;
    for(i=0;i<10;i++)
    printf("%d-hi\n",i);
    printf("hi .. hw are you..:%d\n",z);
}

int main()
{
    pthread_t id;
    pthread_create(&id,NULL,abc,(void *)6);
    pthread_join(id,NULL);
    printf("hello world..!!\n");
}