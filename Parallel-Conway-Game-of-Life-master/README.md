# Parallel Conway's Game of Life
### Editor: Ca11me1ce
The parallel version and serial version of the game of life. The parallel version is in CUDA parallel API.

* Parallel Version:
	* Modified Time: 6:42 PM April 4, 2018<br>
	* Running Command for Parallel: Make sure the USE_MPI is open
  	```bash
			module load intel
			module load impi/5.1.3
			mpicc -o parallel_run gameoflife_parallel.c
			mpirun -np <num_threads> ./parallel_run <m> <k>
	```
          
* Serial Version Game of Life
	* Run Command: 
	```bash
			gcc gameoflife_serial.c -o serial_run
			./serial_run <m> <k>
	```
### What is Conway's Game of Life?
Wiki: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
