#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdint.h> 
#include <limits.h>

typedef uint64_t uint64;

int getTimeStamp();
void sigAlrmHandler(int sig, siginfo_t *info, void *context);
pid_t s1_pid;

void sigAlrmHandler(int sig, siginfo_t *info, void *context) {
  union sigval sv; //signal's value to be sent
  uint64 res = (unsigned long long) getTimeStamp();
 
  printf("ST is Sending signal to s1 %d...\n", s1_pid);
 // printf("TIMESTAMP = %llu\n", (unsigned long long ) res);
  sv.sival_int = (int) res;
  sigqueue(s1_pid, SIGTERM, sv); 
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
  struct sigaction act;
  struct itimerval itv;
   
   sscanf(argv[1], "%d", &s1_pid); //convert the string pid of s1 into integer

   sigemptyset(&act.sa_mask);
   act.sa_sigaction = sigAlrmHandler;
   act.sa_flags = SA_RESTART;

   if (sigaction(SIGALRM, &act, NULL) == -1) {
      perror("signaction");
   }

   itv.it_value.tv_sec = 1; //each every second
   itv.it_value.tv_usec = itv.it_interval.tv_sec = itv.it_interval.tv_usec = 0;

   if (setitimer(ITIMER_REAL, &itv, NULL) == -1) {
      perror("setitimer");
   } 


  for (;;) sleep(10);
  usleep(10000);
  return 0;
}

int getTimeStamp()
{
  unsigned int _up, _down;
  asm volatile("rdtscp" : "=a"(_up), "=d"(_down));
  return (int) ((uint64)high) | (((uint64)low) << 32);
}