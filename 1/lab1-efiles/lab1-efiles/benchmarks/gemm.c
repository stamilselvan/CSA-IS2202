#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/* ripped from simics/src/inclue/magic_instruction.h */
#define MY_MAGIC(n) do {                                   \
        __asm__ __volatile__ ("sethi " #n ", %g0");                      \
} while (0)

#define MAGIC_BREAKPOINT MY_MAGIC(0x40000)

typedef double real;

/* Column-major matrices */
#define A(row,column) _A[(row) + ldA*(column)]
#define B(row,column) _B[(row) + ldB*(column)]
#define C(row,column) _C[(row) + ldC*(column)]

#define ARRAY_SIZE 16384
#define SQ_DIM_SIZE 128
#define BLOCK_DIM_SIZE 4

void gemm(int M, int N, int K, real alpha, real* _A, int ldA,
	  real* _B, int ldB, real beta, real* _C, int ldC) {
  int m, n, k;
  for(n = 0; n < N; n++) {
    for(m = 0; m < M; m++) {
      real C_mn = beta * C(m,n);
      for(k = 0; k < K; k++)
	C_mn += alpha*A(m,k)*B(k,n);
      C(m,n) = C_mn;
    }
  }
}

void blocked_gemm(int M, int N, int K, real alpha, real* _A, int ldA,
		  real* _B, int ldB, real beta, real* _C, int ldC,
		  int bM, int bN, int bK) {
  int bm, bn, bk, m, n, k, cM, cN, cK;

  for(bn = 0; bn < N; bn += bN) {
    cN = (bn+bN) < N ? (bn+bN) : N ;
    for(bm = 0; bm < M; bm += bM) {
      cM = (bm+bM) < M ? (bm+bM) : M ;
      for(bk = 0; bk < K; bk += bK) {
	cK = (bk+bK) < K ? (bk+bK) : K ;
	for(n = bn; n < cN; n++) {
	  for(m = bm; m < cM; m++) {
	    real Cmn = beta*C(m,n);
	    for(k = bk; k < cK; k ++)
	      Cmn += alpha*A(m,k)*B(k,n);
	    C(m,n) = Cmn;
	  }
	}
      }
    }
  }
}

int main(int argc, char* argv[]){

  real _A[ARRAY_SIZE];
  real _B[ARRAY_SIZE];
  real _C[ARRAY_SIZE] = {0};
  
  real alpha = 1;
  real beta = 1;

  int ldA = SQ_DIM_SIZE;
  int ldB = SQ_DIM_SIZE;
  int ldC = SQ_DIM_SIZE;

  int M = SQ_DIM_SIZE;
  int N = SQ_DIM_SIZE;
  int K = SQ_DIM_SIZE;
	
  int i = 0;

  int bM = BLOCK_DIM_SIZE;
  int bN = BLOCK_DIM_SIZE;
  int bK = BLOCK_DIM_SIZE;


  //fill arrays
  for(i = 0; i < ARRAY_SIZE; i++){
    _A[i] = rand();
    _B[i] = rand();
  }

  MAGIC_BREAKPOINT;
  
  blocked_gemm(M, N, K, alpha, _A, ldA, _B, ldB, beta, _C, ldC, bM, bN, bK);
  
  MAGIC_BREAKPOINT;
}
