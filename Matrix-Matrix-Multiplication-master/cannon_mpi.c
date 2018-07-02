/*
	Author: Ca11me1ce
	Modified Date:

	File name: cannon_mpi.c
	Compile command: $module load intel
			$module load impi/5.1.3
			$mpicc cannon_mpi.c -o cannon_mpi.out
	Running command: $mpirun -np <NUM_THREADS> ./cannon_mpi.out
			
	You can change the size of matrix in line 17, just change the value of N(matrix size: N*N)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

#define N 10

int data_set(double *a, double *b, double *c);
void get_walltime(double* wcTime);

int main(int argc,char *argv[])
{
   int rank,size;
	int row=0,column=0;
	int count=0,i=0,j=0,k=0;
 //  char ch;
  // double *A,*B,*C,
	double a=0,b=0,c=0,n;

	double *A=(double*)malloc(N*N*sizeof(double));
	double *B=(double*)malloc(N*N*sizeof(double));
	double *C=(double*)malloc(N*N*sizeof(double));

	data_set(A,B,C);



  // FILE *fp;
   MPI_Init(NULL,NULL);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank); 

   MPI_Bcast(&row,1,MPI_INT,0,MPI_COMM_WORLD);
	int periods[2];
    periods[0]=1; //both vertical and horizontal movement; 
	 periods[1]=1;

	int dims[2];
    dims[0]=row;
	    dims[1]=0;
   int coords[2]; /* 2 Dimension topology so 2 coordinates */
   int right=0, left=0, down=0, up=0;    // neighbor ranks
   MPI_Comm cart_comm;
   MPI_Cart_create(MPI_COMM_WORLD,2,dims,periods,0,&cart_comm );
   MPI_Scatter(A,1,MPI_FLOAT,&a,1,MPI_FLOAT,0,cart_comm);
   MPI_Scatter(B,1,MPI_FLOAT,&b,1,MPI_FLOAT,0,cart_comm);
   MPI_Comm_rank(cart_comm,&rank);
   MPI_Cart_coords(cart_comm,rank,2,coords);
   MPI_Cart_shift(cart_comm, 1, coords[0], &left,&right);
   MPI_Cart_shift(cart_comm, 0, coords[1], &up,&down);
   MPI_Sendrecv_replace(&a,1,MPI_FLOAT,left,11,right,11,cart_comm,MPI_STATUS_IGNORE);
   MPI_Sendrecv_replace(&b,1,MPI_FLOAT,up,11,down,11,cart_comm,MPI_STATUS_IGNORE);
   c = c + a*b;
   for(i=1;i<row;i++)
   {
     MPI_Cart_shift(cart_comm, 1, 1, &left,&right);
     MPI_Cart_shift(cart_comm, 0, 1, &up,&down);
     MPI_Sendrecv_replace(&a,1,MPI_FLOAT,left,11,right,11,cart_comm,MPI_STATUS_IGNORE);
     MPI_Sendrecv_replace(&b,1,MPI_FLOAT,up,11,down,11,cart_comm,MPI_STATUS_IGNORE);
     c = c + a*b;
   }
  // C=(float*)calloc(sizeof(float),row*row);
   MPI_Gather(&c,1,MPI_FLOAT,C,1,MPI_FLOAT,0,cart_comm);
   if(rank==0)
   {
      k=0; 
      printf("\nA * B:\n");
      for(i=0;i<row;i++)
      {
         for(j=0;j<row;j++)
         {
            printf("%f\t",C[k]);
            k++;
         }    
         printf("\n");
      }
   }
   MPI_Finalize();
	return 0;

}

int data_set(double *a, double *b, double *c){
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			a[i*N+j]=2.0;
			b[i*N+j]=3.0;
			c[i*N+j]=0.0;
		}
	}
	return 0;


}

void get_walltime(double* wcTime){

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);

}
