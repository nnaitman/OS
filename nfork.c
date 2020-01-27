/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
#include <stdlib.h>
/* Pour fprintf() */
#include <stdio.h>
/* Pour fork() */
#include <unistd.h>
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>
/* Pour le temps*/
#include <sys/time.h>
#inclue <time.h>



int nFork (int nbProcess){
    int i;
    for (i=0; i < nbProcess; i++){
        switch (fork()){
            case -1: return -1;
            case 0: return 0;
        }
    }
    return 0;
}

int main(int argc, char ** args){
    pid_t pid;
    struct timeval start, stop;

    if (argc < 2){
        fprintf(stderr, "usage: %s <command>\n", &args);
        exit(1);
    }

/*top depart */

    gettimeofday(&start, 0);
    switch (pid = fork()){
        case -1:

            perror(" fork failed");
            exit(2);

        case 0:

            execvp(args[1], args+1);
            exit(0);

        default:
            waitpid (pid, 0,0);
            gettimeofday(&stop, 0);

        printf("time: %f ns \n", (stop.tv_usec - start.tv_usec + 1000000.0 * (stop.tv_usec - start.tv_usec)))/1000;
    }
}


