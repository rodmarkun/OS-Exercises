#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
while(argc--)
printf("%s ", *argv++); 
printf("\n");  
exit(EXIT_SUCCESS);
}