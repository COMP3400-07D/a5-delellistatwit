#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 2) 
    {
        fprintf(stderr, "USAGE: partc FILEIN\n");
        return 1;
    }

    char* input_file = argv[1];
    int pipefd[2];

    if (pipe(pipefd) < 0) 
    {
        perror("pipe");
        return 2;
    }

    pid_t pid = fork();
    if (pid < 0) 
    {
        perror("fork");
        return 2;
    }

    if (pid > 0) 
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
            perror("dup2");
            close(pipefd[1]);
            return 2;
        }
        close(pipefd[1]);

        char* parta_args[] = {"./parta", input_file, NULL};
        execv("./parta", parta_args);

        perror("execv parta failed");
        return 2;
    } else 
    {
        close(pipefd[1]);

        if (dup2(pipefd[0], STDIN_FILENO) < 0) 
        {
            perror("dup2");
            close(pipefd[0]);
            return 2;
        }
        close(pipefd[0]);

        char* sort_args[] = {"sort", "-t,", "-k2", "-n", NULL};
        execvp("sort", sort_args);

        perror("execvp sort failed");
        return 2;
    }

    return 0;
}
