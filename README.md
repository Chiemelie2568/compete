
# Concurrent Pipe Communication in C

## Overview

This project demonstrates interprocess communication (IPC) in Linux using an anonymous pipe and multiple processes created with `fork()`.

The program creates four child processes:
- **2 writers** generate random integer values and write their byte representations to the pipe.
- **2 readers** compete to read data from the same pipe.
- **The parent process** waits for the child processes to terminate and reaps them.

The goal is to explore how multiple processes communicate through a shared pipe and how the operating system handles concurrent reads and writes.

## Concepts Demonstrated

- **Anonymous pipes:** Communication between processes through a kernel-managed byte stream.
- **Process creation:** Creating child processes with `fork()`.
- **Concurrent execution:** Multiple processes accessing the same communication channel.
- **Blocking I/O:** Understanding when `read()` may block while waiting for data.
- **File descriptor management:** Closing unused pipe ends to ensure correct EOF behavior.
- **Process synchronization:** Waiting for child processes using `wait()` or `waitpid()`.
- **Process reaping:** Collecting terminated children's status to prevent zombie processes.

## How It Works

1. The parent creates an anonymous pipe.
2. The parent creates two writer processes and two reader processes.
3. Both writers generate random values and write their bytes to the pipe.
4. Both readers read from the shared pipe. Each byte consumed by one reader is no longer available to the other.
5. The parent waits for all children to terminate and reaps them.

## Important Observations

- A pipe is a **byte stream**, not a message queue.
Separate writes are not guaranteed to correspond to separate reads.
- Multiple readers sharing one pipe compete for its data;
the pipe does not broadcast data to every reader.
- The order in which processes execute and write data can vary between runs.
- A blocking `read()` on an empty pipe waits if at least one write-end reference remains open.
- A reader receives EOF when the pipe buffer is empty and all write-end references have been closed.

## Requirements

- Linux or another Unix-like system supporting POSIX pipes and `fork()`.
- A C compiler, such as GCC.
- Standard build tools, if required by the project.

## Build

If the source file is named `main.c`, compile it with:

```bash
clang -Wall -Wextra -Wpedantic -std=c99 -o main main.c
clang -Wall -Wextra -Wpedantic -std=c99 -o write_num write_num.c
clang -Wall -Wextra -Wpedantic -std=c99 -o read_num read_num.c
```

## Run

```bash
./main
```

The output may differ between runs because process scheduling and the timing of
reads and writes are not deterministic.

## Limitations

- The pipe transports a byte stream rather than explicitly framed messages.
- The program's behavior depends on correct file descriptor management and process termination.
- The program is intended as a learning experiment, not a production IPC implementation.

## What I Learned

This project helped me understand how anonymous pipes enable communication between processes,
how multiple readers and writers interact with the same pipe, why blocking I/O occurs, and why
closing unused file descriptors is essential for correct EOF behavior.

