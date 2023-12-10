#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#define Buffer_Size 256
int main()
 {
 int pipe_fd[2];
// File descriptors for the pipe| 0-read,1-write
pid_t child_pid;
 char write_message[Buffer_Size]=
 "Hello, Child procces!";
 char read_message[Buffer_Size];
 // Create the pipe
 if(pipe(pipe_fd)==-1)
 {
 perror("pipe creation failed");
 exit(EXIT_FAILURE);
 }
 //fork a child process
 if((child_pid=fork())==-1)
 {
 perror("fork failed");
 exit(EXIT_FAILURE);
 }
 if(child_pid==0)
 {
 //this is the child process
 // Close the write end of the pipe since the child 
will read from it
 close(pipe_fd[1]);
 //read from pipe
ssize_t bytes_read
=read(pipe_fd[0],read_message,sizeof(read_message));
 if(bytes_read== -1)
 {
 perror("Read from pipe failed");
 exit(EXIT_FAILURE);
 }
 printf("Child received:%s\n",read_message);
 //close the read end of pipe
 close(pipe_fd[0]);
 }
 else
 {
 // This is the parent process
// Close the read end of the pipe since the 
parent will write to it
 close(pipe_fd[0]);
 //write to the pipe
 ssize_t bytes_written=
write(pipe_fd[1],write_message,strlen(write_message) 
+1);
 if(bytes_written== -1)
 {
 perror("write to pipe failed");
 exit(EXIT_FAILURE);
 }
 printf("Parent wrote:%s\n",write_message);
 // Close the write end of the pipe
 close(pipe_fd[1]);
 //wait for child to finish
 wait(NULL);
 }
 return 0;
 
 