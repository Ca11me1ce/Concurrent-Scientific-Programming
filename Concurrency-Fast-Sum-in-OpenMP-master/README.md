# Concurrency Fast Sum in OpenMP

1) Answer the following questions:<br>
> A) A work-efficient PRAM algorithm requires W(n) = O(n log n) and T(n) = O(log2 n). For what values of p does the algorithm achieve optimal speedup?<br>
> B) Rank the following in the increasing order of how expensive they would be inside a loop (with a billion iterations and approx. 10 instructions/iteration).<br>

>> 1. A floating point add<br>
>> 2. exp(x)<br>
>> 3. OpenMP critical region<br>
>> 4. A floating point divide<br>
>> 5. OpenMP atomic pragma<br>

2) Implement two versions of a summation algorithm discussed in Parallel Algorithm Design and Analysis.pptx using OpenMP on the ACI-ICS cluster.<br>
    The first version must implement the PRAM binary-tree summation using only:<br>
    ```c
        #pragma omp parallel
        omp_get_num_threads()
        omp_get_thread_num()
        omp_set_thread_num()
    ```
You CANNOT use the for reduction call.<br>
The second version should implement a partitioning based summation algorithm. For this implementation, you can use everything taught so far.<br>
Use this as the summation routine declaration:<br>
```c
/** 

 * @brief Calculate the sum of an array

 * @param pd_input - input pointer to array of data to be summed

 * @param i_N - input size of array to be summed

 * @return sum of array

 */

double fast_sum(double *pd_input, int i_N);
```
Assume the size of the array and the number of processors available are independent variables (i.e. 'N' can be really big and 'p' can be less than optimal).<br>
Benchmark the routine for various sizes of N and various values of p.<br>
Relate the results to Amdahl's Law and Brent's Theorem.<br>
Test ranges for N and p should be of reasonable size.<br>
