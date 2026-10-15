
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/random.h>
#include <sys/types.h>

#define MAXV 20

char str_rand();
ssize_t WRITE(int fd, const void *buf, size_t count);

int main(int argc, char *argv[]) {
    char buf[MAXV];
    int fd, i;

    pid_t pid;

    if (argc != 2) {
        fprintf(stderr, "Expected a file descriptor: %s [fd]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (sscanf(argv[1], "%d", &fd) != 1) {
        fprintf(stderr, "Can't convert %s to an integer\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // polute buf with random numbers.
    for (int j=0; j<4; j++)
        buf[j] = str_rand();

    i = 0;
    pid = getpid();
    while(i<4 && WRITE(fd, &buf[i], 1))
        printf("%d Just Wrote %c\n", pid, buf[i++]);
    return 0;
}

// returns a single random digit
char str_rand() {
    int number;

    ssize_t n = getrandom(&number, 1, 0);

    if (n != 1) {
        perror("getrandom");
        exit(EXIT_FAILURE);
    }

    number %= 10;

    return number + '0';
}

ssize_t WRITE(int fd, const void *buf, size_t count) {
    ssize_t byte_written = write(fd, buf, count);
    if (byte_written < 0) {
        perror("Write Error");
        exit(EXIT_FAILURE);
    }
    return byte_written;
}

