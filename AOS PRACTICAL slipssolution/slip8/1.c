#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main()
 {
 int fd;
// Open a file for writing (or create it if it 
doesn't exist)
 fd=open("output1.txt", O_WRONLY | O_CREAT 
|O_TRUNC, S_IRUSR | S_IWUSR);
 if(fd==-1)
{
 perror("open");
 exit(1);
}
// Redirect standard output (file descriptor 1) to 
the opened file
 if(dup2(fd,1)==-1)
{
 perror("dup2");
 close(fd);
 exit(1);
}
// Now, anything written to standard output (e.g., 
printf) will go to "output.txt"
printf("This text will be written to the file.\n");
return 0;
}
