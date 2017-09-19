#include <stdio.h>
#include <stdlib.h>

int  main( int argc,const char *argv[] )
{

  int nums = ("%d\n", atoi(argv[1]));
  int counter = 0;

  while (counter < nums){
    printf("%d\n",(counter+1)*7);
    counter++ ;
  }

  return EXIT_SUCCESS;
}


