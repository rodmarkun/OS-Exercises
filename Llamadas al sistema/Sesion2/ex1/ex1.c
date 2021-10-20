#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/*
Write a program that waits for the arrival of a signal with pause. If it receives either the 
SIGUSR1 or the SIGINT signal then the program must write the name of the author and 
terminate
*/

static void handler() {
    printf("Pablo Rodriguez"); fflush(stdout);
}

int main() {
    signal(SIGINT, handler);
    signal(SIGUSR1, handler);
    pause();
    return (0);
}