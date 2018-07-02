# Concurrency Benchmark
### Author: Ca11me1ce
This is a test benchmark for concurrent programming.<br>
Running command: 
```bash
gcc benchmark.c -o benchmark.out
```

1) Convert the following pseudo code to C/C++ (vector triad benchmark from chapter 1 of the book) Run this code on your own personal development platform as well as the ACI-ICS cluster. 
```fortran
double precision, dimension(N) :: A,B,C,D

double precision :: S,E,MFLOPS

do i=1,N   // fill arrays with data

     A(i) = 0.d0;B(i) = 1.d0

     C(i) = 2.d0; D(i) = 3.d0

enddo

call get_walltime(S)  // get start time

do j=1,R

     do i=1,N

           A(i) = B(i) + C(i) * D(i)  // 3 loads, 1 store

      enddo

      if(A(2).lt.0) call dummy(A,B,C,D) // prevent loop interchange

enddo

call get_walltime(E) // get end time stamp

MFLOPS = R*N*2.d0/((E-S)*1.d6) // calculate MFLOPS
```

Use the following routine for get_wall_time()
```c
#include <sys/time.h>

void get_walltime(double* wcTime) {

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}
```

2) Modify values for R and N. Observe the results. Fix R to some value and generate a plot for N that best summarizes your observations. (MFPLOS vs. N). 

3) Your homework submisison should be a zip file containing two files: a pdf write-up and a zip of your code. The short write-up should be 1-2 pages (including a graph) discussing the findings of your benchmarks. Be sure to include relevant information about your development platform (processor, RAM, OS, compiler). 
