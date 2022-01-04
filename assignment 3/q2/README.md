# CSE231 : Operating Systems (Moonson)

This repository contains all my codes for CSE231's assignment 3.

# This contains:
    A single Makefile to build all programs in all subdirectories(Fifo, Message Queue and Socket)

# Each Subdirectory contains:
    1. A header file constants.h with all data struct and constants that I used.
    2. Each variant of P1 and P2 accordingly.

## How to compile
    run make

## How to run
    1. Fifo: cd fifo
            Now run ./p1
            Then run ./p2
        Note: if you try to run ./p2 first, the program can stuck.
    
    2. Message Queue: cd messag  e_queue
                    Now run ./p2
                    Then run ./p1
        Note: if you try to run ./p1 first and then ./p2, the program can stuck.
    3. Socket: cd socket
                Now run ./p2
                Then run ./p1
        Note: if you try to run ./p1 first and then ./p2, the program can stuck.

## How to clean
    go to cd ..
    run make clean

## How the program works

    Used the same approach in every variant to generate random string, to send and receive  informations. The only difference is only in the method I am sending and receive the information. 
    For every varient, I am using two data structure

    struct message {
        int id; //index of the string 
        char string[5]; the string to be sent
    };

    struct response {
        int highest; //highest id sent
    }

    1. Fifo
    I have used two fifos, one for sending to P2 and one to receive
        In Fifo variant, first we prepare the fifo by creating it with required permissions
        inside the a loop we open the fifo for write with required permissions, after this, we write the 5 random strings, to handle this, I created a flag to check whether the first fives strings was already sent or not, if yes, then start sending string from the highest id received from P2  + 1, to the highest id received + 5. If the first fives strings was not sent, start sending from 0 index to 4.

        We are sending a message object, so, before using write() system call, we initialize each field of our message instance, and after all we send the message struct's instance. 

        after sent, as required, we need to close write the fifo, so that the P2 will be able to open and read it.

        Still in P1, after sending the strings, I prompted the P1 to receive through read() system call , a response struct instance, this instance, will be open and read from Fifo 2. 
        and then, as before, I closed the fifo2.
         
        in P2, first we create the Fifo 2, and then prompt the program to receive from P1.
        To send the highest ID, I am storing all of them in integer array and then compare them using a function to get ge highest ID. Afterhand, this id is enqueued to response data struct and sent to P1.
    
    2. Messaque Queue

        In Message queue variant, the approach is almost the same
        We create the messaque queue using mq_open() with required permissions.
        Inside a loop, we open the p2 message queue and send message using mq_send() with desired parameters
        Then we I prompted the P1 to receive message from P2.

        I did the same as fifo for P2, except the use of mq_send() and mq_receive()

    3. Socket
        I have used Packet socket and send a type while writing to some socket. before using and creating the socket, we need to set up its family and the path. I used two sockets, to send and receive packets respectively.
        The approach to send the highest ID is just the same.
