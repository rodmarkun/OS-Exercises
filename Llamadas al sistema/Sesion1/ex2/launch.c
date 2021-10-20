#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <libgen.h>

/*
Realice un programa ./exercise2/launch.c.  Lee de la entrada estándar (mediante la 
función de la biblioteca C scanf) la ruta de un programa y cree un proceso hijo para 
ejecutar dicho programa. Pruebe a lanzar el programa arguments.c de la transparencia 5.
Utilice la función basename de la biblioteca C para extraer de la ruta del fichero 
ejecutable el nombre del mismo.
*/

int main() {
    int status;
    pid_t pid;
    char cadena[50];
    printf ("Introduzca una cadena:\n");
    scanf("%s", cadena);

    if (0 > (pid = fork()))
    {
        perror("Error en fork");
        exit(1);
    }
    if(pid == 0){
        if (0 > execl(cadena, basename(cadena), "param1", "param2", NULL)) {
            fprintf(stderr, "Error en exec %d\n", errno);
            exit(1);
        }
    }
    exit(0);
}