#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("CHILD started. ");
        if (argc == 1) {
            printf("No arguments provided. Terminating child.\n");
            exit(0);
        } else if (argc == 2) {
            printf("One argument provided. Calling execlp(), never to return (sniff)\n");
            execlp(argv[1], argv[1], NULL);
            perror("execlp failed\n"); // If exec fails
            exit(1);
        } else {
            printf("More than one argument provided. Calling execvp(), never to return (sniff)\n");
            execvp(argv[1], &argv[1]);
            perror("execvp failed\n"); // If exec fails
            exit(1);
        }
    } else {
        // Parent process
        printf("PARENT started, now waiting for process ID#%d\n", pid);
        int status;
        waitpid(pid, &status, 0);
        printf("PARENT resumed. Child exit code of %d. Now terminating parent\n", WEXITSTATUS(status));
    }

    return 0;
}
