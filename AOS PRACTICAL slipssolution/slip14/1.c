#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
int main()
{
 int search;
 printf("Enter Bytes:");
 scanf("%d",&search);
 DIR *dir;
 struct dirent *entry;
 struct stat fileStat;
 
 dir=opendir(".");
 if(dir==NULL)
 {
 perror("opendir");
 return 1;
 }
 printf("files that has size greater than 
 %d:\n",search);
 while((entry=readdir(dir))!=NULL)
 {
 if(entry->d_type==DT_REG)
 {
 if(stat(entry->d_name,&fileStat)==-1)
 {
 perror("stat");
 return 1;
 }
 else
 {
 if((int)fileStat.st_size>search)
 {
 printf("%-25s \t %10d\n",entry
 ->d_name,(int)fileStat.st_size);
}
 
 } 
 }
 }
 
 closedir(dir);
 return 0;
 }