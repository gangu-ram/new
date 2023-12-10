#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char * argv[])
{
 int i;
 if(argc<2)
 {
 fprintf(stderr,"Usage:%s<filename>\n",argv[0]);
 return 1;
 }
 
 struct stat fileStat;
for(i=1;i<argc;i++)
{
 if(stat(argv[i],&fileStat)==-1)
 {
 perror("stat");
 return 1;
 }
 else
 {
 printf("Inode of file %s is 
%d\n",argv[i],(long)fileStat.st_ino);
 
 } 
}
return 0;
}
