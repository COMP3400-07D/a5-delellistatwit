#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 3)
    {
        fprintf(stderr, "USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    char* input_file = argv[1];
    char* output_file = argv[2];

    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0770);

    if (fd < 0) 
    {
        fprintf(stderr, "ERROR: could not open %s\n", output_file);
        return 2;
    }

    if (dup2(fd, STDOUT_FILENO) < 0) 
    {
        fprintf(stderr, "ERROR: could not redirect STDOUT\n");
        close(fd);
        return 2;
    }
    close(fd);

    printf("Category,Count\n");
    fflush(stdout);

    char* parta_args[] = {"./parta", input_file, NULL};

    int eret = execv("./parta", parta_args);

    fprintf(stderr, "ERROR: execv failed\n");
    return 2;
}