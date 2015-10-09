#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

sig_atomic_t child_exit_status;
void clean_up_child_process ()//int signal_number
{
/* Clean up the child process. */
int status;
wait (&status);
/* Store its exit status in a global variable.*/
child_exit_status = status;
}

int main ()
{
/* Handle SIGCHLD by calling clean_up_child_process. */
 pid_t pid;
 pid=fork();
 if(pid>0)
 {
    printf("\nparent executing..!!");
 }
 else
 {
 struct sigaction sigchld_action;
 sigchld_action.sa_handler = &clean_up_child_process;
 printf("\nchild terminating..!!"); 
 sigaction (SIGCHLD, &sigchld_action, NULL);
 printf("\nparent executing..!!");
 }
}