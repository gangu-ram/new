//write a c program to display all the files from current directory which are created in a particular month

#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>
 int main()
{
 struct tm target_time;
 char target_month[10];
 int target_year;
 
 //get month and year you want to filter for
 printf("enter the month (1-12):");
 scanf("%d",&target_time.tm_mon);
 target_time.tm_mon--;
 printf("enter the year(e.g., 2023):");
 scanf("%d",&target_year);
 //creating a string representation of the target month and year
 snprintf(target_month, 10, "%04d-%02d",target_year, target_time.tm_mon +1);
 //open the current directory
 DIR *dir= opendir(".");
 if(dir ==NULL)
 {
  perror("error opening directroy");
  return 1;
 }
struct dirent *entry;
struct stat file_info;
//iterate through the files in the directrory
while((entry =readdir(dir))!=NULL)
{
if(stat(entry->d_name, &file_info)==0)
{
struct tm *creation_time=localtime(&file_info.st_ctime);
//check if the file was created in the target month and year
char file_month[10];
snprintf(file_month, 10, "%04d-%02d", creation_time->tm_year +1900, creation_time->tm_mon +1);
if(strcmp(file_month, target_month)==0)
{
 printf("%s\n", entry->d_name);
}
}
}
closedir(dir);
return 0;
}