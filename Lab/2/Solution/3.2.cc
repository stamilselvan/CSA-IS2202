#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/* ripped from simics/src/inclue/magic_instruction.h */
#define MY_MAGIC(n) do {                                   \
        __asm__ __volatile__ ("sethi " #n ", %g0");                      \
} while (0)

#define MAGIC_BREAKPOINT MY_MAGIC(0x40000)

#define ARRAY_SIZE 65536

int main(int argc, char* argv[]){

	double A[ARRAY_SIZE], B[ARRAY_SIZE], C[ARRAY_SIZE];
	int i,j,k;
	//fill arrays
	  for(i = 0; i < ARRAY_SIZE; i++){
	    A[i] = rand();
	    B[i] = rand();
	    C[i] = rand();
	  }

	  MAGIC_BREAKPOINT;
	while(1){
	  for(i = 3; i < ARRAY_SIZE; i++){
		  A[i] = A[i-3] + A[i-2] * A[i-1] + A[i+1];
		  B[i] = A[i] * B[i-1] + B[i-2] + B[i-2] + B[i+1];
		  C[i] = A[i+1] + B[i] + C[i-1] + C[i-2] + C[i-3] + C[i+1];

		  if(!(i%4)){
			  for(j=6230; j<7255; j=j+33){
				  A[j-2] = B[j*3+i];
				  for(k=j*2;k<j*5;k=k+35){
					  C[k-j] = C[k+j];
					  B[k-3] = A[k]+C[k-j];
				  }
			  }
		  }

	  }
	}
}
