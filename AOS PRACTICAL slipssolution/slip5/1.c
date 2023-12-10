#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
int main()
{
char search[20];
int count=0;
DIR *dir;
struct dirent *entry;
dir=opendir(".");
if(dir==NULL)
{
perror("opendir");
return 1;
}
printf("Names of files in current
 directory:\n");
while((entry=readdir(dir))!=NULL)
{
 if(strcmp(".",entry->d_name)!=0 
 && strcmp(entry->d_name,"..")!=0 )
{
printf("%s\n",entry->d_name);
count++;
}
}
printf("\nNo. of files in current
 directory:%d\n",count);
closedir(dir);
return 0;
}