#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h> //for unint64_t
#include <string.h>


typedef uint64_t uint64;

int generate_rand(uint64 *num);
void sigAlrmHandler(int sig, siginfo_t *info, void *context);

pid_t s1_pid;

void sigAlrmHandler(int sig, siginfo_t *info, void *context) {
   union sigval sv; //signal's value to be sent
   uint64 rand_num = 0;
   int s = generate_rand(&rand_num);
   
   printf("SR is Sending signal to s1 %d...\n", s1_pid);

   if (!s) {
      printf("Maybe RDRAND is not working...\n");
   }

  // printf("RDRAND = %llu\n",  (unsigned long long ) rand_num);
   sv.sival_int = (int)rand_num;
   sigqueue(s1_pid, SIGTERM, sv);  
   exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]) {
  
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


int generate_rand(uint64 *r)
{
   unsigned char aux;
   int res;
   __asm__ volatile("rdrand %0;" "setc %1": "=r"(*r), "=qm"(aux));

   res = (int) aux;
   return res;
}

