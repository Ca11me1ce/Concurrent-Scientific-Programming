/*
	Author: Ca11me1ce
	Modified Date: Feb 1, 2018
	Running command: $gcc benchmark.c -o benchmark.out
*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

void get_walltime(double* wcTime) {

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);

}

int dummy(double A[], double B[], double C[], double D[]){
	return 0;
}

void test(long unsigned int R, long unsigned int N){
	
	long unsigned int i, j;
	double *A=(double*)malloc(N*sizeof(double));
	double *B=(double*)malloc(N*sizeof(double));
	double *C=(double*)malloc(N*sizeof(double));
	double *D=(double*)malloc(N*sizeof(double));

	double S,E,MFLOPS;
	for(i=1; i<=N; i++){
		A[i]=0.0;
		B[i]=1.0;
		C[i]=2.0;
		D[i]=3.0;
	}

	get_walltime(&S);

	for(j=1; j<=R; j++){
		for(i=1; i<=N;i++){
			A[i]=B[i]+C[i]*D[i];
		}
		if(A[2]<0){
			//break;
			dummy(A,B,C,D);
		}
	}
	
	get_walltime(&E);

	MFLOPS=R*N*2.0/((E-S)*1000000.0);//mega floating-point operations per second
	printf("%lf\t", MFLOPS);
	free(A);
	free(B);
	free(C);
	free(D);

}

int main(){
	printf("when r=10: \n");
	test(10, 10);
	test(10, 100);
	test(10, 1000);
	test(10, 10000);
	test(10, 100000);
	test(10, 1000000);
	test(10, 10000000);

	printf("\nwhen r=100: \n");
	test(100, 10);
	test(100, 100);
	test(100, 1000);
	test(100, 10000);
	test(100, 100000);
	test(100, 1000000);
	test(100, 10000000);

	printf("\nwhen r=1000: \n");
	test(1000, 10);
	test(1000, 100);
	test(1000, 1000);
	test(1000, 10000);
	test(1000, 100000);
	test(1000, 1000000);
	test(1000, 10000000);


	return 0;

}
