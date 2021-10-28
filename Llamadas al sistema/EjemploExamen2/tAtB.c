#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>

int espera = 1; // 0 - No espera / 1 - Espera
int esperaHijo = 1; // 0 - No espera / 1 - Espera

void esperaPrincipal(){
    while(espera);
}

void esperaHijoPrincipal(){
    while(esperaHijo);
}

void crearFicheroTA(){
    printf("El hilo A comienza su ejecución\n");
    int fd;
    char pid_proceso = getpid() + '0';
    if(0 > (fd = creat("./original", 0700))){
        perror("Error en creat original");
        exit(1);
    }
    if(0 > write(fd, &pid_proceso, sizeof(pid_proceso))){
        perror("Error en write en crearFicheroTA");
        exit(1);
    }
    close(fd);
    printf("El hilo tA ha terminado su trabajo\n");
    espera = 0;
}

void crearCopia(int pipefd[]){
    printf("tB comienza su ejecución\n");
    int fd;
    int i;
    char c;

    if(0 > (fd = creat("./copia", 0700))){
        perror("Error en creat copia");
        exit(1);
    }
    close(pipefd[1]); // Close input

    for(i = 0; i < 10; i++){
        read(pipefd[0], &c, sizeof(char));
        printf("Received: %c\n", c);
        write(fd, &c, 1);
    }
    close(fd);
    printf("tB termina su ejecución\n");
}

int main(){

    int fd, pipefd[2];
    pid_t pid;
    char buffer[10];
    int i;

    // Escribir nombre del autor
    printf("Rodríguez Martín, Pablo\n");

    pthread_t tA;
    pthread_create(&tA, NULL, (void *)crearFicheroTA, NULL);
    printf("El hilo principal procede a esperar\n");
    pthread_join(tA, NULL);
    printf("El hilo principal reanuda su ejecución\n");

    pipe(pipefd);

    if(0 > (pid = fork())){
        perror("Error en fork");
        exit(1);
    }
    if(pid == 0){
        // Hijo
        pthread_t tB;
        pthread_create(&tB, NULL, (void *)crearCopia, pipefd);
        pthread_join(tB, NULL);
    }
    else{
        // Padre
        printf("tMain procede a leer el contenido del fichero\n");
        fd = open("./original", O_RDONLY, 0700);
        if(0 > (read(fd, buffer, 10))){
            perror("Error en read");
            exit(1);
        }
        close(pipefd[0]); // Close Output
        for(i = 1; i <= 10; i++){
            write(pipefd[1], &buffer[i], sizeof(buffer[i]));
        }
        printf("tMain ha terminado su cometido y procede a esperar a su hijo\n");
    }

}