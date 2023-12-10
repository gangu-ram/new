#include<stdio.h>
int main()
 {
 // Open a file for writing, this will redirect
 standard output to the file.
 FILE *file=freopen("output.txt", "w", stdout);
 if(file==NULL)
 {
perror("freopen");
return 1;
 }
 printf("This text will be written to the file.\n");
 // Close the file to restore standard output.
 fclose(file);
 return 0;
}
 /*
 ./a.out
 cat output.txt
 This text will be written to the file.
 */
