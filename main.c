
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1

#define MAXV 10

int main() {
    int fd[2];

    if (pipe(fd) < 0) {
        fprintf(stderr, "Pipe Error");
        exit(EXIT_FAILURE);
    }

    char read_fd[MAXV], write_fd[MAXV];
    sprintf(read_fd, "%d", fd[READ_END]);
    sprintf(write_fd, "%d", fd[WRITE_END]);

    // created 4 processes.
    for (int i=0; i<4; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork Failed\n");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // case 0 and 1 are writing, while 2 and reading are reading.
            switch(i) {
                case 0:
                    close(fd[READ_END]);  // closing the read end
                    printf("Process %d Writing\n", i);
                    execlp("./write_num", "write_num", write_fd, (char *)NULL);
                    break;
                case 1:
                    close(fd[READ_END]);  // closing the read end
                    printf("Process %d Writing\n", i);
                    execlp("./write_num", "write_num", write_fd, (char *)NULL);
                    break;
                case 2:
                    close(fd[WRITE_END]);  // closing the write end
                    printf("Process %d Reading\n", i);
                    execlp("./read_num", "read_num", read_fd, (char *)NULL);
                    break;
                case 3:
                    close(fd[WRITE_END]);  // closing the write end
                    printf("Process %d Reading\n", i);
                    execlp("./read_num", "read_num", read_fd, (char *)NULL);
                    break;
            }
            // control shouldn't reach here.
            perror("Exec Error");
            exit(EXIT_FAILURE);
        }
    }

    // reape all child processes
    close(fd[READ_END]);
    close(fd[WRITE_END]);
    for (int i=0; i<4; i++)
        wait(NULL);
    printf("Parent process has just reaped all child processes\n");
    return 0;
}

