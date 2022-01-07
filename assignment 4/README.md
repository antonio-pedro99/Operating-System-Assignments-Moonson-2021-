# CSE231 : Operating Systems (Moonson)

This repository contains all my codes for CSE231's assignment 4.

# This contains:
    A single Makefile to build test program.

## How to compile
    run make

## How to run
    ./main

## How to clean
    go to cd ..
    run make clean

## How the program works
    System calls implementation

    Writer(), the writer system call will receive 3 arguments, a char pointer representing the string to be written in the queue, the size, and a sem_t struct representing our mutex.

    In kernel, we are using simply a char pointer to represent the queue, it will be initialized everything the writer system call is called from the user space. Inside the writer system call, we define a temporary queue using ``kmalloc``. Then before we enqueue the string in our kernel queue using memcpy, we need to take care about deadlocks and race conditions, for this we used sem_wait() and thread_mutex_lock(), after enqueuing the  string, we unlock the mutex, then using sem_post() to notify the kernel.

    Reader() system call, receive the same number of arguments.

    To dequeue the string, we first use sem_wait() and lock the mutex, and the use copy_to_user to send the queue content to the buff parameter. then unlock the semaphore.
    

   