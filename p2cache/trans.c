/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void trans_simple_2(int M, int N, int A[N][M], int B[M][N]);
void trans_simple_44(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that
 *     you will be graded on the assignment. Do not change the
 *     description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
  if ((M==32)&&(N==64)){
    trans_simple_44(M, N, A, B);
  }
  else {
    trans_simple_2(M, N, A, B);
  }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/* Header comment */
char trans_simple_desc[] = "first try 32 x 32";
void trans_simple(int M, int N, int A[N][M], int B[M][N])
{
	int i, j;
	int h, v;
	int tmp;
	
	for (i = 0; i < N; i+=8){
		for (j = 0; j < M; j+=8){
			
			/*block 3 */
			for (h = i + 7; (h>(i+3))&&h<M; h--){
				for (v = j + 3; (v>=j)&&v<N; v--){
					B[v][h] = A[h][v];
				}
			}

			/*block 4*/
			for (h = i + 7; (h>(i+3))&&h<M; h--){
				for (v = j + 4; (v<=(j+7))&&v<N; v++){
					B[v-4][h-4] = A[h][v];
				}
			}
			/*block 2*/
			for (h = i; (h<=(i+3))&&h<M; h++){
				for (v = j + 4; (v<=(j+7))&&v<N; v++){
					B[v][h] = A[h][v];
				}
			}
			/*block 1*/
			for (h = i; (h<=(i+3))&&h<M; h++){
				for (v = j; (v<=(j+3))&&v<N; v++){
					B[v+4][h+4] = A[h][v];
				}
			}
			/*swap*/
			for (h=i; (h<=(i+3))&&h<M; h++){
				for (v = j; (v<=(j+3))&&v<N; v++){
					tmp = B[h+4+(j-i)][v+4+(i-j)];
					B[h+4+(j-i)][v+4+(i-j)] = B[h+(j-i)][v+(i-j)];
					B[h+(j-i)][v+(i-j)] = tmp;
				}
			}
		}
	}

}


/* Header comment */
char trans_simple_desc_1[] = "first try 32 x 64";
void trans_simple_1(int M, int N, int A[N][M], int B[M][N]){
  
        int i, j;
        int h, v;
        int tmp;
	int tmp2;

        for (i = 0; i < 32; i+=8){
                for (j = 0; j < M; j+=8){

                        /*block 3 */
                        for (h = i + 7; (h>(i+3))&&h<M; h--){
                                for (v = j + 3; (v>=j)&&v<32; v--){
                                        B[v][h] = A[h][v];
                                }
                        }

                        /*block 4*/
                        for (h = i + 7; (h>(i+3))&&h<M; h--){
                                for (v = j + 4; (v<=(j+7))&&v<32; v++){
                                        B[v-4][h-4] = A[h][v];
                                }
                        }
                        /*block 2*/
                        for (h = i; (h<=(i+3))&&h<M; h++){
                                for (v = j + 4; (v<=(j+7))&&v<32; v++){
                                        B[v][h] = A[h][v];
                                }
                        }
                        /*block 1*/
                        for (h = i; (h<=(i+3))&&h<M; h++){
                                for (v = j; (v<=(j+3))&&v<32; v++){
                                        B[v+4][h+4] = A[h][v];
                                }
                        }
                        /*swap*/
                        for (h=i; (h<=(i+3))&&h<M; h++){
                                for (v = j; (v<=(j+3))&&v<32; v++){
                                        tmp = B[h+4+(j-i)][v+4+(i-j)];
                                        B[h+4+(j-i)][v+4+(i-j)] = B[h+(j-i)][v+(i-j)];
                                        B[h+(j-i)][v+(i-j)] = tmp;
                                }
                        }
			/*block 7*/
			for (h = i + 7; (h>(i+3))&&h<M; h--){
				for (v = j + 11; (v>=(j+8))&&v<N; v--){
					B[v][h] = A[h][v];
				}
			}
			/*block 8*/
			for (h = i + 7; (h>(i+3))&&h<M; h--){
				for (v = j + 12; (v<=(j+15))&&v<N; v++){
					B[v-4][h-4] = A[h][v];
				}
			}
			/*block 6*/
			for (h = i; (h<=(i+3))&&h<M; h++){
				for (v = j +12; (v<=(j+15))&&v<N; v++){
					B[v][h] = A[h][v];
				}
			}
			/*block 5*/
			for (h = i; (h<=(i+3))&&h<M; h++){
				for (v = j + 8; (v<=(j+11))&&v<N; v++){
					B[v+4][h+4] = A[h][v];
				}
			}
			/*swap*/
			for (h = i; (h<=(i+3))&&h<M; h++){
				for (v = j; (v<=(j+3))&&v<32; v++){
					tmp2 = B[h+12+(j-i)][v+12+(i-j)];
					B[h+12+(j-i)][v+12+(i-j)] = B[h+8+(j-i)][v+8+(i-j)];
					B[h+8+(j-i)][v+8+(i-j)] = tmp2;
				}
			}
                }
        }

}


/* Header comment */
char trans_simple_desc_2[] = "try for squares";
void trans_simple_2(int M, int N, int A[N][M], int B[M][N]){
  int cblock, i, j, r, c, idx, tmp;
  
  int isdiagonal = 0;

  if (N == 32)
  {
    cblock = 8;
  }
  else
  {
    cblock = 4;
  }
  
  for (i = 0; i < N; i += cblock)
  {
    for (j = 0; j < M; j += cblock)
    {
      for (r = i; r < i + cblock; r++)
      {
	for (c = j; c < j + cblock; c ++)
	{
	  if (r != c)
	  {
	    B[c][r] = A[r][c];
	  }
	  else
	  {
	    tmp = A[r][c];
	    idx = r;
	    isdiagonal = 1;
	  }
	}
	if (isdiagonal == 1)
	{
	  B[idx][idx] = tmp;
	  isdiagonal = 0;
	}
      }
    }

  }

}	

/* Header comment */
char trans_simple_desc_3[] = "try for non squares";
void trans_simple_3(int M, int N, int A[N][M], int B[M][N])
{

  int cblock = 4;
  int i, j, r, c, tmp, idx;
  int isdiagonal;

  for (i = 0; i < N; i += cblock)
  {
    for (j = 0; j < M; j += cblock)
    {
      for (r = i; (r < i+cblock)&&(r<N); r++)
      {
	for (c = j; (c < j + cblock)&&(c<M); c++)
	{
	  if (r != c)
	  {
	    B[c][r] = A[r][c];
	  }
	  else
	  {
	    tmp = A[r][c];
	    idx = r;
	    isdiagonal = 1;
	  }
	}
	if (isdiagonal == 1)
	{
	  B[idx][idx] = tmp;
	  isdiagonal = 0;
	}
      }
    }
  }
}

char trans_simple_desc_44[] = "try for nonsquares2222";
void trans_simple_44(int M, int N, int A[N][M], int B[M][N]){

  int cblock = 8;
  int i, j, r;

  for (i = 0; i < N; i += cblock)
  {
    for (j = 0; j < M; j++)
    {
      for (r = i; r < i+cblock; r++)
      {
            B[j][r] = A[r][j];
          }
        }
      }
    }


/* Header comment */
char trans_simple_desc_4[] = "try for nonsquares2222";
void trans_simple_4(int M, int N, int A[N][M], int B[M][N])
{
  int i, j, r, c, tmp;

  int idx;
  int isdiagonal = 0;
  int cblock = 8;


  for (i = 0; i < M; i += cblock)
  {
    for (j = 0; j < M; j += cblock)
    {
      for (r = i; r < i + cblock; r++)
      {
        for (c = j; c < j + cblock; c ++)
        {
          if (r != c)
          {
            B[c][r] = A[r][c];
          }
          else
          {
            tmp = A[r][c];
            idx = r;
            isdiagonal = 1;
          }
        }
        if (isdiagonal == 1)
        {
          B[idx][idx] = tmp;
          isdiagonal = 0;
        }
      }
    }
  }

  for (i = 32; i < N; i += cblock)
  {
    for (j = 0; j < M; j += cblock)
    {
      for (r = i; r < i + cblock; r++)
      {
        for (c = j; c < j + cblock; c ++)
        {
          if (r != c)
          {
            B[c][r] = A[r][c];
          }
          else
          {
            tmp = A[r][c];
            idx = r;
            isdiagonal = 1;
          }
        }
        if (isdiagonal == 1)
        {
          B[idx][idx] = tmp;
          isdiagonal = 0;
        }
      }
    }
  }
}



/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

    registerTransFunction(trans_simple, trans_simple_desc);

    registerTransFunction(trans_simple_1, trans_simple_desc_1);

    registerTransFunction(trans_simple_2, trans_simple_desc_2);

    registerTransFunction(trans_simple_3, trans_simple_desc_3);

    registerTransFunction(trans_simple_4, trans_simple_desc_4);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

