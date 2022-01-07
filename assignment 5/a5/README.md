# CSE231 : Operating Systems (Moonson)

# Name: Antonio Pedro
# Roll Number: 2020028

This repository contains all my codes for CSE231's assignment 5(Bonus).

# This contains:
    A single Makefile to build all programs.

## How to compile
    run make

## How to run
    1. Program 1:
            run ./p1
            run ./p2
     
    2. Program 2: 
            run ./p2
            run ./p1
    3. Program 3: 
            run ./p2
            Then run ./p1

## How to clean
    go to cd ..
    run make clean

## How the program works
    Program 1:

    This is the basic implementation of the dinning problem(solved), to solve, we use mutex and semaphores.
    There are five forks, and each philosopher will have access of two fork in his left and right, to eat the same philosopher must be hungry and check if both forks forks are available.

    We have used thread to simulate the philosophers, and each thread will use the same resource, in this case each element inside the forks array.
    
    I used functions like sem_post(), sem_wait() in order to take fork and put fork respectively.

    Program 2:

    Now, if we have assume that the philosopher needs only one fork and access to one of the 4 sauces bowls to eat, there will be deadlock yes.

    In order to solve this deadlock, we have just reduce the number of bowls, and everytime the philosopher will take a fork, he will also take the bowl.

    We have used thread to simulate the philosophers, and each thread will use the same resource, in this case each element inside the forks array.
    
    I used functions like sem_post(), sem_wait() in order to take fork and put fork respectively.

    
    Program 3:

    Now, if we have assume that the philosopher needs both fork and access to one of the 4 sauces bowls to eat, there wont be any deadlocks, since we will have the same number of bowls availabe for every philosopher.

    In order to solve this deadlock, we have just reduce the number of bowls, and everytime the philosopher will take a fork, he will also take the bowl.

    We have used thread to simulate the philosophers, and each thread will use the same resource, in this case each element inside the forks array.
    
    I used functions like sem_post(), sem_wait() in order to take fork and put fork respectively.


