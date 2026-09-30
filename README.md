# Shell-Based Database Manager

## Project Description

Shell-Based Database Manager is a lightweight terminal-based database management system developed using C/C++ and Linux system programming concepts.

The project aims to provide database operations through a custom command-line shell without depending on a heavy external database server.

## Week 1 Features

- Interactive command-line REPL
- Linux development environment
- C-based implementation
- Makefile-based build system
- Git version control
- GitHub repository setup

## Expected Outcomes

- Develop a lightweight shell-integrated database manager.
- Support database operations through a command-line interface.
- Use Linux/POSIX system calls for low-level file operations.
- Implement safe multi-process access using file locking.
- Use memory mapping and IPC for efficient database operations.
- Understand OS-level storage, memory and process management.

## Build

make

## Run

make run

## Week 2 Features

- Dynamic command input
- Memory allocation using malloc()
- Automatic buffer expansion using realloc()
- Proper memory cleanup using free()

## Week 3 Features

- Command parsing using strtok()
- Dynamic argv[] construction
- Modular parser implementation
- Ready for process execution with execvp()

## Week 4 Features

- Process creation using fork()
- Command execution using execvp()
- Parent-child synchronization using waitpid()
- Error handling using perror()
- Execution of real Linux commands
- Process management integrated with the shell
