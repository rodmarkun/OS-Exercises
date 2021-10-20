#include <stdio.h>                
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_HIJOS 3

/*
Realice un programa denominado ./exercise3/four.c . Creará cuatro procesos, A, B, C y D, 
de forma que A sea padre de B, B sea padre de C, y C sea padre de D. D debe invocar la 
llamada al sistema execl para mutar en el nuevo proceso ps, de modo que la salida en 
pantalla muestre la relación de parentesco entre los cuatro procesos. Utilice man ps.¡
*/

int main(int argc, char **argv)
{
    int statval, i = 0; 
    pid_t pid;

    printf("Soy el proceso A y soy %d\n", getpid());
    while(i < NUM_HIJOS){
        if((pid = fork()) == 0){
            if(0 > pid){
                perror("Error en fork");
                exit(1);
            }
            printf("Soy el proceso %d y soy hijo de %d\n", getpid(), getppid());
            i++;
            if(i == NUM_HIJOS){
                execl("/bin/ps", "ps", NULL);
            }
        }
        else {
            wait(&statval);
            break;
        }
    }

    return 0;
} 