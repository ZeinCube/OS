#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int task1() {
  int x = 100;
  int rc = fork();

  if (rc < 0) {
    // fork failed; exit
    printf("No fork = %d\n", x);
    exit(1);
  } else if (rc == 0) {
    // new process
    x = 300;
    printf("Child x = %d\n", x);
  } else {
    // original process
    waitpid(-1, NULL, WUNTRACED);
    x = 22;
    printf("Parent x = %d\n", x);
  }
  return 0;
}