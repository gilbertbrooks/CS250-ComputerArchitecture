#include<stdio.h>
#include<stdlib.h>

int recurse(int n){

  if (n == 0) {
    return 2;
  }

  return (3*(n-1)+recurse(n-1)+1);
}

int main(int argc, const char * argv[]){

  int r = atoi(argv[1]);
  int rRecursed = recurse(r);
  
  printf("%d\n",rRecursed);
  return EXIT_SUCCESS; 

}
