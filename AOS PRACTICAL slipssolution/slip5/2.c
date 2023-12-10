#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main() 
{
 int pipefd[2];
 pid_t child_pid;
 if (pipe(pipefd) == -1) 
 {
 perror("Pipe creation failed");
 exit(EXIT_FAILURE);
 }
 child_pid = fork();
 if (child_pid == -1) 
 {
 perror("fork failed ");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) 
 {
 
 close(pipefd[0]); 
 char *messages[] =
 {
 "Message1= Hello World",
 "Message2= Hello SPPU",
 "Message2= Linux is Funny",
 };
 for (int i = 0; i < 3; i++) 
 {
 write(pipefd[1], messages[i], strlen(messages[i]));
 write(pipefd[1], "\n", 1); 
 }
 close(pipefd[1]);
 exit(EXIT_SUCCESS);
 } 
else 
{
 
 close(pipefd[1]); 
 char buffer[100];
 ssize_t bytes_read;
 while ((bytes_read = read(pipefd[0],
 buffer, sizeof(buffer))) > 0)
 {
 buffer[bytes_read] = '\0';
 printf("Parent received: %s", buffer);
 }
 close(pipefd[0]);
 }
 //wait(NULL); 
 return 0;
}
