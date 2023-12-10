#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char * argv[])
 {
 if(argc<2)
 {
 fprintf(stderr,"Usage:
 %s<filename>\n",argv[0]);
 return 1;
 }
 const char *filename=argv[1];
 if(access(filename,F_OK)==0)
 {
 printf("%s is present in current 
 directory\n",filename);
 }
 else
 printf("%s is not present in current
 directory\n",filename);
 return 0;
}
