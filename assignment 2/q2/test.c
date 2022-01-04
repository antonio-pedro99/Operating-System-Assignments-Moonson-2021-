#define ROW 2
#define COL 3

#include <unistd.h>
#include <stdio.h>

int main(){
  double a1[ROW][COL] = {{2.3, 5.6, 50.2}, {10.32, 20.5, 15.9}};
  double a2[ROW][COL];
  int size = ROW * COL;

  printf("Calling the system call ...\n");
  
  syscall(548, size, *a1, *a2);


 for (int i = 0; i <  ROW; i++) {
      for (int j = 0; j < COL; j++) {
        printf("%2.f ", (float)a2[i][j]);
      }
      printf("\n");
  } 
  return 0;
}
