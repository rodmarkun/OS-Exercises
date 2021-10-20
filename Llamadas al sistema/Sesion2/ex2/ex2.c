#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/*
Write a program that counts the SIGUSR1 and SIGUSR2 signals it receives. When this 
program receives the SIGTERM signal, it will show the number of signals SIGUSR1 and 
SIGUSR2 received and it will terminate.
*/

static int done_waiting = 0;
int no_SIGUSRONE = 0;
int no_SIGUSRTWO = 0;

static void handler(int signum) {
    printf("Received signal %d\n", signum); fflush(stdout);
    switch (signum)
    {
    case SIGUSR1:
        no_SIGUSRONE++;
        break;
    
    case SIGUSR2:
        no_SIGUSRTWO++;
        break;

    case SIGTERM:
        printf("Number of SIGUSR1 signals: %d, Number of SIGUSR2 signals: %d\n", no_SIGUSRONE, no_SIGUSRTWO);
        done_waiting = 1;
        break;

    default:
        printf("Wrong signal received");
        break;
    }
}

static void my_pause() {
    done_waiting = 0;
    while ( !done_waiting );
}

int main() {
    signal(SIGUSR2, handler);
    signal(SIGUSR1, handler);
    signal(SIGTERM, handler);
    my_pause();
    return (0);
}