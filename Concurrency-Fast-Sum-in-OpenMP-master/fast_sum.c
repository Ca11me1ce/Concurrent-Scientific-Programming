/*
@	sum.c
@	**You can use running shell to compile and run this code with different N values and p values
@	**More details, please see runing shell file I provided in same folder
@
@	**Compile command: $gcc -o sum sum.c -fopenmp -lm
@	**Run command: $./sum N_value NUM_THREADS
@
@	Author: Ca11me1ce
@	Modified Date: Feb 14, 2018

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>

//#define  NUM_THREADS 2


double ver1_fast_sum(double *pd_input, int i_N, int NUM_THREADS);
double ver2_fast_sum(double *pd_input, int i_N, int NUM_THREADS);
void get_walltime(double* wcTime);

int main(int argc, char *argv[]){
	if(argc!=3){
		printf("Invalid Parameter.\nPlease enter valid paramenter to run the command e.g.($./sum 100000 4).\nSee running command in the beginning of this file.\nThere is a run_shell enclosed\n");
		return -1;
	}
	int N=atoi(argv[1]);
	int NUM_THREADS=atoi(argv[2]);
	int i;
	double sum;
	double d_s, d_e;
	double d_s1, d_e1;

	double *sum_array=(double*)malloc(N*sizeof(double));//allocate memory for array

	//asign value to array
	for(i=0; i<N; i++){
		sum_array[i]=2.0;
	}

	printf("N =\t%d\n", N);
	printf("The number of process: \t%d\n", NUM_THREADS);

	//call ver2_fast_sum
	get_walltime(&d_s);//start time
	sum=ver2_fast_sum(sum_array,N,NUM_THREADS);
	get_walltime(&d_e);//end time

	printf("sum of fast_sum is \t%lf\n", sum);
	printf("ver2 fast_sum time is: \t%lf\n", d_e-d_s);	

	//call ver1_fast_sum
	get_walltime(&d_s1);//start time
	sum=ver1_fast_sum(sum_array,N,NUM_THREADS);
	get_walltime(&d_e1);//end time
	printf("ver1 fast_sum time is: \t%lf\n", d_e1-d_s1);	

	free(sum_array);

	return 0;

}

/** 

 * @brief Calculate the sum of an array

 * @param pd_input - input pointer to array of data to be summed

 * @param i_N - input size of array to be summed

 * @return sum of array

 */
double ver2_fast_sum(double *pd_input, int i_N, int NUM_THREADS){

	omp_set_num_threads(NUM_THREADS);  
	double sum;
	long long sum_mp[NUM_THREADS]; 
	int i_t;

//OpenMP 
#pragma omp parallel  
	{  
		int id=omp_get_thread_num();  
		int tmp=0;  
#pragma omp for  

		for(i_t=0; i_t<i_N; i_t++){  
			tmp+=pd_input[i_t];  
		}  
		sum_mp[id]=tmp;  
	}  


	int i;
	for(i=0; i<NUM_THREADS; i++){  
		sum+=sum_mp[i];  
	}
	
	return sum;

}

double ver1_fast_sum(double *pd_input, int i_N, int NUM_THREADS){

	omp_set_num_threads(NUM_THREADS);
	int i;
	double sum;
	long long tmp_array[NUM_THREADS];

#pragma omp parallel
	{
		int id=omp_get_thread_num();
		int tmp=0;

		for(i=0; i<i_N; i++){
			tmp+=pd_input[i];		
		}
		tmp_array[id]=tmp;

	}

//PRAM Algorithm
	int h, k;
	for(h=1; h<log((double)NUM_THREADS); h++){
		for(k=0; k<((double)NUM_THREADS/pow(2, h)); k++){
			tmp_array[k]=tmp_array[2*k-1]+tmp_array[2*k];
		}
	}


	sum=tmp_array[1];
	return sum;
		

}

//get time
void get_walltime(double* wcTime) {

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);

}




