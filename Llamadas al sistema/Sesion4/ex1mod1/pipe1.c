#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
Modifique el ejercicio 1 de la sesión según el esquema de la figura:
de modo que el proceso B se convierta en un servidor de eco, es decir, sin escribir nada en 
pantalla, B escribe en la segunda pipe la secuencia numérica que recibe por la primera 
pipe. Es el proceso A el que escribe en pantalla la secuencia que lee de la pipe
*/

int main()
{
    int fdwrite[2], fdread[2], nbytes, i, dato;
    pid_t childpid;

    pipe(fdwrite);
    pipe(fdread);
    if((childpid = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    if(childpid == 0) {
        /* Child process closes up input side */
        close(fdwrite[1]);
        close(fdread[0]); //Close output on reader
        /* Read in a string from the pipe */
        for(i = 0; i < 10; i++){
            nbytes = read(fdwrite[0], &dato, sizeof(int));
            write(fdread[1], &dato, sizeof(int));
        }
    }

    else {
        /* Parent process closes up output side */
        close(fdwrite[0]);
        close(fdread[1]); // Close input on reader
        /* Send "string" through the output side of pipe */
        for(i = 1; i <= 10; i++){
            write(fdwrite[1], &i, sizeof(int));
        }
        for(i = 0; i < 10; i++){
            nbytes = read(fdread[0], &dato, sizeof(int));
            printf("A ha leido el entero: %d\n", dato);
        }
        exit(0);
    }
}