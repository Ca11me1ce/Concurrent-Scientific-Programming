# Matrix Matrix Multiplication
### Target: 
* 4 possible implementations of matrix-matrix multiplication (serial, openMP, Cannon-MPI and Summa-MPI) determine when it is advantageous to use each.
### Author: Ca11me1ce

* Given 4 possible implementations of matrix-matrix multiplication (serial, openMP, Cannon-MPI and Summa-MPI) determine when it is advantageous to use each. Find for a range of matrix sizes (NxN) and a range of available processors/nodes (P) which method would perform the fastest.

* You are free to use whatever C source code you find online. However, cite your sources. Copied code without credit will result in zero points.

* Your subroutines should use double precision floating point variables.

* P should be tested from the minimum to the maximum of the open allocation (100 nodes).

* NxN should be pushed to the maximum size.

### File name: matrix_mul.c
* File description: matrix multiplication in serial version and OpenMP version
* Compile Command: 
	```bash
		gcc matrix_mul.c -o matrix_mul.out -fopenmp
  	```
* Running Command: 
	```bash
		./matrix_mul.out <NUM_THREADS> <N>
	```
  
### File name: cannon_mpi.c
* Compile command: 
	```bash
			module load intel
			module load impi/5.1.3
			mpicc cannon_mpi.c -o cannon_mpi.out
	```
      
* Running command: 
	```bash
			mpirun -np <NUM_THREADS> ./cannon_mpi.out
	```		
	* You can change the size of matrix in line 17, just change the value of N(matrix size: N*N)
  
 ### File name: summa_mpi.c
* Compile command: 
	```bash
			module load intel
			module load impi/5.1.3
			mpicc summa_mpi.c -o summa_mpi.out
	```
      
* Running command: 
	```bash
			mpirun -np <NUM_THREADS> ./summa_mpi.out <NODE_NUMBERS> 
	```
