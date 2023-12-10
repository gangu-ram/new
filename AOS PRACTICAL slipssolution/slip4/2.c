#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include<signal.h>
void childSingalHandler(int signum)
 {
 if (signum == SIGHUP)
 {
 printf("Child: Received SIGHUP/n");
 } 
 else if (signum == SIGINT)
 {
 printf("Child: Received SIGHUP/n");
 } 
 else if (signum == SIGQUIT)
 {
 printf("Child: Received SIGQUIT/n"); 
 printf("See You Daddy !!!/n"); 
 exit(0);
 }
 } 
int main()
{
 pid_t child_pid;
 child_pid = fork();
 
 if(child_pid == -1)
 {
 perror ("Fork Failed");
 exit(1);
 }
 else if (child_pid == 0) 
 {
 
 signal(SIGHUP, childSingalHandler); 
 signal(SIGINT, childSingalHandler);
 signal(SIGQUIT, childSingalHandler);
 
 while (1)
 {
 sleep(1);
 }
 } 
 else
 {
 for(int i = 1; i<= 15; i++)
 {
 if(i % 3 == 0) 
 {
 
 kill(child_pid,(i<=9) ? SIGHUP : SIGINT);
 
 }
 sleep(1);
 }
 kill(child_pid, SIGQUIT);
 wait(NULL);
 printf("Parent: Child process terminated./n");
 }
return 0;
}