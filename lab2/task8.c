#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static int task8() {
    int file_descriptor[2];
    char buf[100];

    if (pipe(file_descriptor) == -1) {
        exit(EXIT_FAILURE);
    }
    int pr1 = fork();
    if (pr1 == 0) {
        close(file_descriptor[0]);
        char msg1[] = "hello";
        write(file_descriptor[1], msg1, 5);
        close(file_descriptor[1]);
    } else {
        wait(NULL);
        int cpid2 = fork();
        if (cpid2 == 0) {
            read(file_descriptor[0], buf, 5);
            printf("%s", buf);
        }
    }
    return 0;
}