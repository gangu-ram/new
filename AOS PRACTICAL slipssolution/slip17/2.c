#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void sigint_handler(int signum) 
{
}
void sigquit_handler(int signum)
{
}
int main()
{
 signal(SIGINT,sigint_handler);
 signal(SIGQUIT,sigquit_handler);
 int pipe_fd[2];
 pid_t child1,child2;
 if(pipe(pipe_fd)==-1)
 {
 perror("pipe");
 exit(EXIT_FAILURE);
 }
 child1=fork();
 if(child1==-1)
 {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if(child1==0)
 {
 close(pipe_fd[0]);
 dup2(pipe_fd[1],STDOUT_FILENO);
 close(pipe_fd[1]);
 execlp("ls","ls","-l",NULL);
 perror("exec ls");
 exit(EXIT_FAILURE);
 }
else
 {
 child2=fork();
 if(child2==-1)
 {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if(child2==0)
 {
 close(pipe_fd[1]);
 dup2(pipe_fd[0],STDIN_FILENO);
 close(pipe_fd[0]);
 execlp("wc","wc","-l",NULL);
 perror("exec wc");
 exit(EXIT_FAILURE);
 }
 else
 {
 close(pipe_fd[0]);
 close(pipe_fd[1]);
 wait(NULL);
 wait(NULL);
 }
 }
 return 0;
}
