#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
    int i;
    pid_t id, id1;
    printf("\nhi..process id is:%d\n",(int)getpid());
    printf("\nhi..parent process id is:%d\n",(int)getppid());
    system("ls");
    id1=fork();
    
    if(id1!=0)
    {
        printf("\nforked child id in parent process:%d\n",(int)id1);
    }
    else
        printf("\nchild process\n");
        char *parmList[] = {""};
         execvp("ls",parmList);
}