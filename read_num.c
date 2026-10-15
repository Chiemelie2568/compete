
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXV 20

ssize_t READ(int fd, void *buf, size_t count);

int main(int argc, char *argv[]) {
    char buf[MAXV];
    int fd;
    int i=0;

    if (argc != 2) {
        fprintf(stderr, "Expected a file descriptor: %s [fd]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (sscanf(argv[1], "%d", &fd) != 1) {
        fprintf(stderr, "Can't convert %s to an integer\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (READ(fd, &buf[i], 1)) {i++;}
    buf[i] = '\0';

    printf("I just READ %d bytes\n", i);
    int len = strlen(buf);
    for(int j=0; j<len; j++)
        printf("%c ", buf[j]);
    printf("\n");
    return 0;
}

ssize_t READ(int fd, void *buf, size_t count) {
    ssize_t byte_read = read(fd, buf, count);
    if (byte_read == -1) {
        perror("Error while reading");
        close(fd);
        exit(EXIT_FAILURE);
    }
    return byte_read;
}


