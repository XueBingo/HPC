# <center>HPC_hw3</center>

<p align='right'>Bing Xue (bx2109@nyu.edu)</p>

> Repo link: https://github.com/XueBingo/HPC

## 1. OpenMP warm-up

> We assume that `n` is an odd number, that is, there are even numbers of iterations in each loop.

a. 

In the first region, t1 takes task `1`~`n/2-1`, and t2 takes `n/2`~`n-1`. So t1 spends `n/2*(n/2-1)/2`, and t2 spends `(3*n/2-1)*(n/2-1)/2`. So t1 will spend `(n-1)*(n/2-1)/2` waiting for t2.

In the second region, t2 takes task `1`~`n/2-1`, and t1 takes `n/2`~`n-1`. So t2 spends `n/2*(n/2-1)/2`, and t1 spends `(3*n/2-1)*(n/2-1)/2`. So t2 will spend `(n-1)*(n/2-1)/2` waiting for t1.

b.

In the first region, t1 takes task 1, 3, 5, …, n-2, and t2 takes 2, 4, 6, …, n-1. So t1 spends `(n-1)*(n-1)/(2*2)`, and t2 spends `(n+1)*(n-1)/(2*2)`. So t1 will spend `(n-1)/2` waiting for t2.

In the second region, t2 takes task 1, 3, 5, …, n-2, and t1 takes 2, 4, 6, …, n-1. So t2 spends `(n-1)*(n-1)/(2*2)`, and t1 spends `(n+1)*(n-1)/(2*2)`. So t2 will spend `(n-1)/2` waiting for t1.

c.

Yes, compared with `schedule(static)`, it would balance the load dynamically. Once a thread finishes executing its assigned iteration, it will request another iteration from the pool of unassigned iterations. So the waiting time of any thread in any region won’t exceed `n`, which is the longest time taken of a task.

d.

Yes, the `nowait` clause.



## 2. Parallel Scan in OpenMP

> machine: crunchy5.cims.nyu.edu | Four AMD Opteron 6272 (2.1 GHz) (64 cores) | 256 GB | CentOS 7

**Timing:**

num_threads = 2

sequential-scan = 1.142130s
parallel-scan   = 0.426070s
error = 0

num_threads = 3

sequential-scan = 1.129317s
parallel-scan   = 0.366571s
error = 0

num_threads = 4

sequential-scan = 1.125308s
parallel-scan   = 0.239362s
error = 0

|      | sequential-scan | parallel-scan |
| ---- | --------------- | ------------- |
| 2    | 1.142130s       | 0.426070s     |
| 3    | 1.129317s       | 0.366571s     |
| 4    | 1.125308s       | 0.239362s     |



## 3. OpenMP version of 2D Jacobi/Gauss-Seidel smoothing

> machine: crunchy5.cims.nyu.edu | Four AMD Opteron 6272 (2.1 GHz) (64 cores) | 256 GB | CentOS 7

GS variant:
$$
u^{k+1}_{i, j} = \frac{1}{4}(h^2*f_{i, j} + u^{k}_{i-1, j} + u^{k}_{i, j-1} + u^{k}_{i+1, j} + u^{k}_{i, j+1})\\
u^{k+1}_{i, j} = \frac{1}{4}(h^2*f_{i, j} + u^{k+1}_{i-1, j} + u^{k+1}_{i, j-1} + u^{k}_{i+1, j} + u^{k}_{i, j+1})
$$
**Timing:**

```
[bx2109@crunchy5 hw3]$ ./run.sh 
g++ -std=c++11 -O3 -march=native -fopenmp jacobi2D-omp.cpp -o jacobi2D-omp
g++ -std=c++11 -O3 -march=native -fopenmp gs2D-omp.cpp -o gs2D-omp
=============================================
Jacobi
num_threads = 1 N = 1000        h = 0.000999
Elapsed time: 313ms
GS
num_threads = 1 N = 1000        h = 0.000999
Elapsed time: 597ms
=============================================
Jacobi
num_threads = 2 N = 1000        h = 0.000999
Elapsed time: 186ms
GS
num_threads = 2 N = 1000        h = 0.000999
Elapsed time: 318ms
=============================================
Jacobi
num_threads = 4 N = 1000        h = 0.000999
Elapsed time: 74ms
GS
num_threads = 4 N = 1000        h = 0.000999
Elapsed time: 134ms
=============================================
Jacobi
num_threads = 8 N = 1000        h = 0.000999
Elapsed time: 36ms
GS
num_threads = 8 N = 1000        h = 0.000999
Elapsed time: 60ms
=============================================
Jacobi
num_threads = 16        N = 1000        h = 0.000999
Elapsed time: 18ms
GS
num_threads = 16        N = 1000        h = 0.000999
Elapsed time: 28ms
=============================================
Jacobi
num_threads = 32        N = 1000        h = 0.000999
Elapsed time: 15ms
GS
num_threads = 32        N = 1000        h = 0.000999
Elapsed time: 26ms
=============================================
Jacobi
num_threads = 64        N = 1000        h = 0.000999
Elapsed time: 159ms
GS
num_threads = 64        N = 1000        h = 0.000999
Elapsed time: 498ms
=============================================
=============================================
Jacobi
num_threads = 1 N = 10000       h = 0.000100
Elapsed time: 34909ms
GS
num_threads = 1 N = 10000       h = 0.000100
Elapsed time: 69334ms
=============================================
Jacobi
num_threads = 2 N = 10000       h = 0.000100
Elapsed time: 17526ms
GS
num_threads = 2 N = 10000       h = 0.000100
Elapsed time: 33790ms
=============================================
Jacobi
num_threads = 4 N = 10000       h = 0.000100
Elapsed time: 11949ms
GS
num_threads = 4 N = 10000       h = 0.000100
Elapsed time: 18787ms
=============================================
Jacobi
num_threads = 8 N = 10000       h = 0.000100
Elapsed time: 9910ms
GS
num_threads = 8 N = 10000       h = 0.000100
Elapsed time: 18237ms
=============================================
Jacobi
num_threads = 16        N = 10000       h = 0.000100
Elapsed time: 6247ms
GS
num_threads = 16        N = 10000       h = 0.000100
Elapsed time: 10226ms
=============================================
Jacobi
num_threads = 32        N = 10000       h = 0.000100
Elapsed time: 5853ms
GS
num_threads = 32        N = 10000       h = 0.000100
Elapsed time: 9067ms
=============================================
Jacobi
num_threads = 64        N = 10000       h = 0.000100
Elapsed time: 6041ms
GS
num_threads = 64        N = 10000       h = 0.000100
Elapsed time: 9867ms
=============================================
=============================================
```

**Jacobi**

| num_threads\N | 1000  | 10000   |
| ------------- | ----- | ------- |
| 1             | 313ms | 34909ms |
| 2             | 186ms | 17526ms |
| 4             | 74ms  | 11949ms |
| 8             | 36ms  | 9910ms  |
| 16            | 18ms  | 6247ms  |
| 32            | 15ms  | 5853ms  |

**GS**

| num_threads\N | 1000  | 10000   |
| ------------- | ----- | ------- |
| 1             | 597ms | 69334ms |
| 2             | 318ms | 33790ms |
| 4             | 134ms | 18787ms |
| 8             | 60ms  | 18237ms |
| 16            | 28ms  | 10226ms |
| 32            | 26ms  | 9067ms  |