# CSE231 : Operating Systems (Moonson)

This repository contains all my codes for CSE231's assignment 2.
This contains:

### test.c
### Makefile
### and this document

## How to compile
    run **make**
## How to run
    run ./run file

## How to clean
    run make clean

## How the script works
###  The system Calls
    To implement the system call, I had to make change in the kernel, properly in system calls table, where I defined the system call name, archteture and the system call function.

    In kernel/sys.c file, I implemented the system call function using the SYS_DEFINEX macro, where X define the number of arguments the system call will receive.

    for my solution,  I used to arrays, one source, and one destination, these two arrays will come from the user space.
    Since we need the source array content, I created a tmp in kernel mode, and using __copy_from_user, i transfered the content of array source into the kernel and I stored into tmp, while doing this I checked if the result is not 0, that means if some error (-1) were counted,then return -EFAULT, to say that something went wrong, and if no error were counted, simply just make the operation.

    After successfully copying the content of source array into the tmp, I sent the content of tmp to user space using __copy_to_user.


## TESTS ## 
    To ensure the system call is working fine, I have created a test file,
    where we use the same system call by specifying the system call number (as defined system calls table, 548).
    and by calling the  syscall system call, we passed the system call number and the required argments. I

    