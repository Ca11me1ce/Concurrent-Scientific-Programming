# Concurrency Design Optimization

1) Suppose you are programming a processor with an add latency of 3 clock cycles and a multiply latency of 5 cycles. It is also given that this processor can complete one add and one multiply instruction every clock cycle, when instructions are fully pipelined. Consider the following loop:<br>
```c
for (i=0; i<m; i++) {

A[i] = B[i] * C[i] + D[i] + i;

}
```

> * Assuming the program is executed as-is (i.e. no pipelining), what is the lower bound on execution time (in clock cycles) based on the math performed?

> * How can you exploit more instruction level parallelism in this program? What changes do you propose?

> * Assuming you can pipeline the adds and multiplies, what would be the lower bound on execution time in clock cycles for the arithmetic?

2) Get the supplied code hw02_slow_code.cpp<br>
Identify possible optimizations. Implement optimizations and evaluate the results.<br>
Assume vd_s and vi_v potentially contain values in the full dynamic range of their respective data types.<br>

3) Implement a matrix-vector multiply from slide 10 of the DataAccessOptimization slide set. Benchmark performance for N = 10, 100 and 1000. Implement and benchmark both the outer loop unrolling and spatial blocking optimizations.<br>

4) Optional<br>
Determine the fastest single core for an optimized version of the following routine:<br>
```c
benchFunc(float *A, float *B, int N, int M)

{

for (i = 0; i < N-M; i++)

{

  B[i] = 0;

  for (j = 0; j < M; j++)

     B[i] += A[i+j];

  B[i] /= M;

}

}
```

Use N = 100000, M = 256; Assume N and M are not fixed. You may have to run this over several iterations (R = 1000) to get an accurate benchmark measurement. Submit your code and the results from running on the ACI cluster. The best routines will be run for verification of accuracy and performance. Routines that do not accurately perform the calculation will be disqualified. The best performing routine will receive the 2 points.<br>


Your project assignment should be a tar or zip file containing two files, a pdf and a tar.gz of your source code.<br>
Provide the answers to part 1 and a short writeup for parts 2 and 3 in the pdf document.<br>

For part 2, include optimizations identified and tried. Include performance results.<br>
For part 3, document your findings. Include a graph of the results.<br>
For part 4, submit your code, compile command and performance results.<br>
