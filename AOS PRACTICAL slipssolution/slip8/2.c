#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() 
{
 int pipefd[2];
 if (pipe(pipefd) == -1) 
 {
 perror("pipe");
 exit(1);
 }
 pid_t ls_pid, wc_pid;
 // Fork a child process to run 'ls -l'
 if ((ls_pid = fork()) == 0) 
 {
 close(pipefd[0]); 
 dup2(pipefd[1], 1); 
 close(pipefd[1]); 
 // Execute 'ls -l'
 execlp("ls", "ls", "-l", NULL);
 perror("execlp ls");
 exit(1);
 
 } 
 
 else if (ls_pid < 0) 
 {
 perror("fork ls");
 exit(1);
 
 }
 
 if ((wc_pid = fork()) == 0) 
 
 {
 close(pipefd[1]); 
// Close the write end of the pipe
 dup2(pipefd[0], 0); 
// Redirect stdin to the pipe
 close(pipefd[0]); 
// Close the duplicated read end of the pipe
 
// Execute 'wc -l'
 
 execlp("wc", "wc", "-l", NULL);
 perror("execlp wc");
 exit(1);
 } 
 else if (wc_pid < 0) 
 {
 perror("fork wc");
 exit(1);
 }
// Close both ends of the pipe in the parent process
close(pipefd[0]);
close(pipefd[1]);
 // Wait for the child processes to complete
 waitpid(ls_pid, NULL, 0);
 waitpid(wc_pid, NULL, 0);
 return 0;
}
