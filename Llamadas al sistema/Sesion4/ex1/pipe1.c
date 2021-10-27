#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
Modifique pipe0.c como pipe1.c de modo que el proceso A escribe en la 
pipe la secuencia 1, 2, 3, 4, ..., 10. El proceso B lee la secuencia de la pipe 
y la escribe en pantalla
*/

int main()
{
    int fd[2], nbytes, i, dato;
    pid_t childpid;

    pipe(fd);
    if((childpid = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    if(childpid == 0) {
        /* Child process closes up input side */
        close(fd[1]);
        /* Read in a string from the pipe */
        for(i = 0; i < 10; i++){
            nbytes = read(fd[0], &dato, sizeof(int));
            printf("Received int: %d\n", dato);
        }
    }

    else {
        /* Parent process closes up output side */
        close(fd[0]);
        /* Send "string" through the output side of pipe */
        for(i = 1; i <= 10; i++){
            write(fd[1], &i, sizeof(int));
        }
        exit(0);
    }
}