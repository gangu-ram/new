#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() 
{
 pid_t child_pid, wpid;
 int status;
 child_pid = fork();
 if (child_pid == 0)
 {
 
 printf("Child process (PID: %d)
 is running.\n", getpid());
 
 sleep(2);
 
 exit(50);
 } 
 else if (child_pid > 0)
 {
 
 printf("Parent process (PID: %d) 
 is waiting for the child 
 to terminate.\n", getpid());
 wpid = wait(&status);
 if (wpid == -1) 
 {
 perror("wait");
 exit(1);
 }
 if (WIFEXITED(status)) 
 {
 printf("Child process (PID: %d) 
 exited with status: %d\n", 
 wpid, WEXITSTATUS(status));
 } 
 else
 {
 printf("Child process (PID: %d) 
 did not exit normally.\n", wpid);
 }
 }
 else 
 {
 perror("fork");
 exit(1);
 }
 return 0;
}
