#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
using namespace std;
int main(int argc, char** argv)
{
/* Make sure the command line is correct */
if (argc < 2)
{
cout << "FILE NAME missing\n";
exit(1);
}
/* Open the specified file */
int openfd = open(argv[1], O_RDWR);
int closefd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);

if (openfd < 0)
{
cout << "\n" << "input file cannot be opened" << "\n";
exit(1);
}
if (closefd < 0)
{
cout << "\n" << "output file cannot be opened" << "\n";
exit(1);
}


struct stat stats;
if (stat(argv[1], &stats) == 0)
cout << endl << "file size " << stats.st_size;
else
cout << "Unable to get file properties.\n";
/* Get the page size  */
int fileSize = stats.st_size;
int pagesize = getpagesize();
cout << endl << "page size is " << pagesize << "\n";
/* map the file into memory */

  lseek(outFd, filesize - 1, SEEK_SET);
  lseek(outFd, 0, SEEK_SET);

while(fileSize > 0){
    if(fileSize < pagesize){
        pagesize = fileSize;
        fileSize = 0;
    }else
    fileSize -= pagesize;
}


char* data = (char*)mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, 
openfd, 0);
/* Did the mapping succeed ? */
if (!data)
{
cout << "\n" << "mapping did not succeed" << "\n";
exit(1);
}
/* Print the whole file character-by-character */
for (int fIndex = 0; fIndex < pagesize; ++fIndex)
{
cout << data[fIndex];
}
cout << endl;
/* Write a string to the mapped region */
char* mapped =(char*)mmap(NULL, pagesize,PROT_READ | PROT_WRITE | MAP_SHARED, closefd, 0);
if (!mapped){
    cout <<"\n" << "mapping did not succeed" << "\n";
    exit(1);
}

/* memcpy(data, "Hello world, this is a test\n", sizeof("Hello world, this is a 
test"));*/
/* Unmap the shared memory region */
memcpy(mapped, data, pagesize);
munmap(mapped, pagesize);
munmap(data, pagesize);
lseek(openfd, pagesize, SEEK_SET);
lseek(closefd, pagesize, SEEK_SET)


/* Close the file */
close(openfd);
close(closefd);

return 0;
}
