# CSE231 : Operating Systems (Moonson)

This repository contains all my codes for CSE231's assignment 2.
This contains:

### main.c
### Makefile
### sr.c
### st.c

## How to compile
    run **make**
    go to /build folder
## How to run
    **Note** : Running E1 and E2 separately will cause the program to throw segmentation fault.
    run ./run file

## How to clean
    go to cd ..
    run make clean

## How the script works
### main.c file
    We create 3 processess(beside the parent):
    S1, SR, ST

    S1 - Receive SIGTERM signal from external program by Process ID, and print the data sent along with the signal.
        We receive this signal and some data each time the S1 process receive  SIGTERM signal sent by SR and ST.
        code -> main.c file lines 42 - 47

        1. at this point, we used sigemptyset(&action.sa_mask), this manipulate the signals that are data objects that let a process keep track of groups of signals.

        2. at this point, we register the signal handler

        3. at this point, we used SA_RESTART flag to restart everytime the process got a signal, and SA_SIGINFO to allow the process receive also a data from sigqueue

        In lines 14 - 26 we define the handler function, this function will be called everytime S1 Process receive a signal, and it will print the data sent by SR and ST.

    SR - Read some RANDOM number from the CPU each 1s and send the same to S1 along with SIGTERM signal.

        In lines 19-34, we define a sigalrm handler, everythime this process get a SIGALRM sent automatically by setitimer() in each every 1s, the sigalrm handler will send the random number and SIG term signal to S1 process, using sigqueue.

        In lines 45-47, we prepare the process to receive signal, we use SA_RESTART to restart the process everytime it get a signal.
        
    SR and ST will comunicate with S1 process using signals.
        We use sigqueue to send a signal and a integer value to S1 process.
        lines 25-26 in sr.c and lines 31-32 in st.c file.

        In SR, we read the timestamp of the CPU and cast it to int and pass to sv.sival_int in both files.

## Note ## Please, run the code more than one time to test it at all/

    