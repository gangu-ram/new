#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void childProcess() 
{
 while (1)
 {
 printf("Child process is running..../n");
 sleep(1);
 }
}
int main() 
{
pid_t child_pid;
//Create a child process
child_pid = fork();
if (child_pid < 0)
{
 perror("Fork Failed");
 exit(1);
 }
 
 if (child_pid == 0)
{
 // This is the child process
 childProcess();
 } 
else 
{
 printf("Parent created child process with PID: 
%d\n", child_pid);
 sleep(2);
 
 printf("Suspending the child process...\n");
 kill(child_pid, SIGSTOP);
 sleep(2); 
 
 printf("Resuming the child process...\n");
 kill(child_pid, SIGCONT);
 sleep(2);
 
 printf("Terminating the child process...\n");
 kill(child_pid, SIGTERM);
 }
 
 return 0;
} 