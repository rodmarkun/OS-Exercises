#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


/*
Crear un programa denominado duo.c. 
El programa crea un proceso A que crea un hijo B. B crea el directorio denominado contenedor con permisos 0700 y 
dentro de contenedor el fichero denominado dueto. (3 puntos)
A escribe en dueto el carácter ASCII a seguido del carácter nulo (0x00), y B el carácter ASCII b. (3 puntos)
Sincronizar la escritura mediante señales de modo que el contenido final de dueto sea la cadena “ba“. (3 puntos)
Finalmente, A debe leer esta cadena y escribirla en pantalla. (1 punto)
Nota: En C el código ASCII de la letra a es 'a'. Por ejemplo:
char letra = 'a';
*/

int turno = 0; // 0 = B, 1 = A

static void  handler() {
    printf("Turno cambiado\n");
    turno = 1;
}

void pausaA(){
    while(turno == 0);
}

int main(){
    pid_t pid;
    int f_b, f_a, i;
    char letra_a[] = {'a', 0x00};
    char letra_b = 'b';
    char buffer[3];
    printf("Soy el proceso A con pid: %d\n", getpid());
    if(0 > (pid = fork())){
        perror("Error en fork");
        exit(1);
    }
    if(pid == 0){
        printf("Soy el proceso B con pid: %d\n", getpid());
        mkdir("./contenedor", 0700);
        if(0 > (f_b = creat("./contenedor/dueto", 0666))){
            perror("Error en creat");
            exit(1);
        }
        if(0 > (write(f_b, &letra_b, 1))){
            perror("Error al escribir con B");
            exit(1);
        }
        close(f_b);
        kill(getppid(), SIGUSR1);
        exit(0);
    }
    else{
        signal(SIGUSR1, handler);
        pausaA();
        if(0 > (f_a = open("./contenedor/dueto", O_WRONLY | O_APPEND, 0666))){
            perror("Error en open");
            exit(1);
        }
        if(0 > (write(f_a, &letra_a, 2))){
            perror("Error al escribir con A");
            exit(1);
        }
        close(f_a);
        if(0 > (f_a = open("./contenedor/dueto", O_RDONLY, 0666))){
            perror("Error en open");
            exit(1);
        }
        if(0 > (read(f_a, buffer, 3))){
            perror("Error en read");
            exit(1);
        }
        for(i = 0; i < 3; i++){
            printf("%c", buffer[i]);
        }
        printf("\n");
    }
    return 0;
}