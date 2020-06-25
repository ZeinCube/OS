#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int task7() {
    int rc = fork();

    if (rc == 0) // child process
    {
        printf("child\n");
        close(STDOUT_FILENO);
        printf("print from child process\n");
    } else if (rc > 0) {
        wait(NULL);
        printf("print from parent process\n");
    } else {
        printf("Error\n");
    }
    return 0;
}