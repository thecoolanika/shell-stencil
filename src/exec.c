#include "exec.h"

#include <stdlib.h> // for malloc, realloc, and free
#include <unistd.h> // for fork

void exec_init(char *environment) {
    env = environment;
}

void exec_cleanup() {
    env = NULL;
}

pid_t execute_process(const char *command, char **argv) {
    pid_t proc = fork();

    if (proc == -1) {
        return -1;
    }

    if (proc == 0) {
        char *envp[] = { env, NULL };

        execve(argv[0], argv, envp);
        exit(EXIT_FAILURE);
    }

    return proc;
}

