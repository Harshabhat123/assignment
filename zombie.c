// making of a zombie process
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t child_id;
    child_id=fork();
    if(child_id>0)
    {
        sleep(60);
        //parent process sleeps 
    }
    else
    {
        exit(0);
        //child terminates
    }

}