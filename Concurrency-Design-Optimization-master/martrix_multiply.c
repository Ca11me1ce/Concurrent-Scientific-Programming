//compile command: 
//$gcc -O3 martrix_multiply.c -o martrix_multiply; ./martrix_multiply

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void get_walltime(double* wcTime) {

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);

}

void original_test(double *a, double *b, double *c, int N){
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			c[i]=c[i]+(*(a+i*N+j))*b[j];
		}
	}

	//printf("The answer of original test is: %lf\n", c[1] );

}

void outer_loop_unrolling(double *a, double *b, double *c, int N){
	int i, j;
	for(i=0; i<N; i+=2){
		for(j=0; j<N; j++){
			c[i]=c[i]+(*(a+i*N+j))*b[j];
			c[i+1]=c[i+1]+(*(a+(i+1)*N+j))*b[j];
		}
	}
	//printf("The answer of outer test is: %lf\n", c[1] );
}

void spatial_blocking(double *a, double *b, double *c, int N){
	int bs=10;
	int nb=N/bs;
	int i, j, k;
	for(k=0; k<nb; k++){
		for(i=0; i<N; i++){
			for(j=(k-1)*bs; j<k*bs; j++){
				c[i]=c[i]+(*(a+i*N+j))*b[j];
			}
		}
	}

	//printf("The answer of blocking test is: %lf\n", c[1] );
}

int assign_value(int N){

	double d_s, d_e;
	int i, j;

	int R=1000;

	//because the max N-value is 1000, this declaration is ok;
	double c[N];   //*c=(double*)malloc(N*sizeof(double));
	double b[N];   //*b=(double*)malloc(N*sizeof(double));
	double a[N][N];

//array initialize
	for(i=0; i<N; i++){
		c[i]=1.0;
	}

	for(j=0; j<N; j++){
		b[j]=2.0;
	}
	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			a[i][j]=3.0;
		}
	}

//N value
	printf("|When N=%d \t\t\t|              |\n", N);

	//original test
	get_walltime(&d_s);

	for(i=0; i<R; i++){
		original_test(*a, b, c, N);
	}
	
	get_walltime(&d_e);

	printf("|original test: \t\t|   %lf   |\n", d_e-d_s);

	//outer loop unrolling
	get_walltime(&d_s);

	for(i=0; i<R; i++){
		outer_loop_unrolling(*a, b, c, N);
	}
	
	get_walltime(&d_e);

	printf("|outer loop unrolling test: \t|   %lf   |\n", d_e-d_s);

	//spatial blocking
	get_walltime(&d_s);

	for(i=0; i<R; i++){
		spatial_blocking(*a, b, c, N);
	}
	
	get_walltime(&d_e);

	printf("|spatial blocking test: \t|   %lf   |\n", d_e-d_s);

	return 0;


}


int main(){
	
	//N=10
	printf("|----------------------------------------------|\n");
	assign_value(10);
	printf("|----------------------------------------------|\n");
	//N=100
	assign_value(100);
	printf("|----------------------------------------------|\n");
	//N=1000
	assign_value(1000);
	printf("|----------------------------------------------|\n");

	return 0;


		
}

