#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int task3() {
    int rc = fork();

    if (rc == 0) // child process
    {
        printf("Hello World!\n");
        execl("/bin/ls", "/bin/ls", "-l", NULL);
    } else if (rc > 0) { //parent process
        wait(NULL);
        printf("I am parent process\n");
    } else { //error
        printf("Error occurred during fork()\n");
    }
    return 0;
}