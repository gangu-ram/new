#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
int main(int argc,char * argv[])
{
 if(argc!=2)
 {
 fprintf(stderr,"Usage:%s<filename>\n",argv[0]);
 return 1;
 }
 const char *filename=argv[1];
 struct stat fileStat;
 if(stat(filename,&fileStat)==-1)
 {
 perror("stat");
 return 1;
 }
 printf("Type Of File: ");
 
 if(S_ISREG(fileStat.st_mode))
 printf("Regular file\n");
 else if(S_ISDIR(fileStat.st_mode))
 printf("Directory\n");
 else if(S_ISLNK(fileStat.st_mode))
 printf("Symbolic link\n");
 else if(S_ISCHR(fileStat.st_mode))
 printf("Character device\n");
 else if(S_ISBLK(fileStat.st_mode))
 printf("Block device\n");
 else if(S_ISFIFO(fileStat.st_mode))
 printf("FIFO/Named pipe\n");
 else
 printf("Unkonwn");
return 0;
}
