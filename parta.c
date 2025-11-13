#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];

    if (argc != 2) 
    {
        fprintf(stderr, "USAGE: parta FILEIN\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) 
    {
        fprintf(stderr, "ERROR: %s not found\n", argv[1]);
        return 2;
    }

    int upper = 0;
    int lower = 0;
    int number = 0;
    int space = 0;
    int others = 0;

    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, BUFSIZE)) > 0) 
    {
        for (ssize_t i = 0; i < bytes_read; i++) 
        {
            unsigned char c = buffer[i];
            if (isupper(c)) 
            {
                upper++;
            } 
            else if (islower(c)) 
            {
                lower++;
            } 
            else if (isdigit(c)) 
            {
                number++;
            } 
            else if (isspace(c)) 
            {
                space++;
            } 
            else 
            {
                others++;
            }
        }
    }

    if (bytes_read < 0) 
    {
        fprintf(stderr, "ERROR: %s could not be read\n", argv[1]);
        close(fd);
        return 2;
    }

    close(fd);

    printf("Upper,%d\n", upper);
    printf("Lower,%d\n", lower);
    printf("Number,%d\n", number);
    printf("Space,%d\n", space);
    printf("Other,%d\n", others);

    return 0;
}
