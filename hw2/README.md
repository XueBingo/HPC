# HPC_hw2

## Problem 1

`val_test01.cpp`:  
There are two bugs in the this code.
First, only n * sizeof(int) is allocated. To fix it, I allocated n+1 * sizeof(int).
Second, using delete to free memory. To fix it, I use `free()`.  


`val_test02.cpp`:  
Conditional jump or move depends on uninitialised value(s),
and Use of uninitialised value of size 8.
To be specific, we use some elements in x[] before initialization.
To fix it, I initialed them after allocation.  


## Problem 2
> command: g++ -std=c++11 -O3 -march=native MMult1.cpp && ./a.out  
> 
> machine: crunchy5.cims.nyu.edu | Four AMD Opteron 6272 (2.1 GHz) (64 cores) | 256 GB | CentOS 7


**Timings for various matrix sizes obtained with the blocked version**
> BLOCK_SIZE = 16; -O3 optimization

```bash
 Dimension       Time    Gflop/s       GB/s        Error
        16   2.196562   0.910515 217.083698 4.541851e-05
        64   2.218081   0.901752 134.371502 9.545329e-08
       112   2.191963   0.912706 124.346277 8.956704e-09
       160   2.199330   0.912569 119.665328 1.671651e-09
       208   2.213437   0.910690 116.913740 6.266418e-10
       256   4.064848   0.495287  62.732973 2.655725e-10
       304   2.227025   0.908298 113.976330 1.086846e-10
       352   2.383266   0.841809 104.912834 6.207301e-11
       400   2.434373   0.841284 104.300453 4.047251e-11
       448   2.855440   0.755740  93.308743 2.296474e-11
       496   2.704479   0.812146  99.938394 1.386979e-11
       544   2.742207   0.821911 100.861117 1.250555e-11
       592   2.435374   0.851921 104.301692 6.707523e-12
       640   3.193196   0.656756  80.248760 4.547474e-12
       688   3.111064   0.837426 102.150551 5.229595e-12
       736   2.866577   0.834490 101.641542 4.092726e-12
       784   3.377053   0.856173 104.146724 4.092726e-12
       832   3.016600   0.763681  92.788638 2.216893e-12
       880   3.183774   0.856181 103.920481 2.330580e-12
       928   3.706560   0.862448 104.584410 2.671641e-12
       976   4.329550   0.858948 104.073125 2.444267e-12
      1024   6.728876   0.319144  38.639441 1.080025e-12
      1072   2.897256   0.850408 102.889649 1.193712e-12
      1120   3.362824   0.835565 101.030009 1.421085e-12
      1168   3.767841   0.845797 102.208002 1.421085e-12
      1216   4.815449   0.746782  90.194735 1.705303e-12
      1264   4.744799   0.851243 102.760541 1.648459e-12
      1312   5.372261   0.840765 101.449222 1.762146e-12
      1360   5.983403   0.840811 101.411707 1.762146e-12
      1408   8.549872   0.652948  78.721941 2.046363e-12
      1456   7.304667   0.845111 101.852156 2.273737e-12
      1504   8.094084   0.840632 101.277187 2.103206e-12
      1552   8.807235   0.848918 102.242163 2.273737e-12
      1600  10.948369   0.748239  90.089051 2.330580e-12
      1648  10.509417   0.851771 102.524865 2.330580e-12
      1696  11.570417   0.843254 101.472076 2.614797e-12
      1744  12.585202   0.842964 101.411113 2.557954e-12
      1792  23.565876   0.488383  58.739594 2.557954e-12
      1840  14.798056   0.841935 101.239277 3.012701e-12
      1888  16.006121   0.840911 101.093891 2.842171e-12
      1936  17.067900   0.850288 102.199913 2.842171e-12
      1984  20.892982   0.747575  89.836534 2.785328e-12
```
**Peak FLOP-rate**: 0.912569 Gflop/s  


**BLOCK_SIZE and performance**
> Dimension = 256
```bash
 Dimension       Time    Gflop/s       Error     BLOCK_SIZE
       256   9.647448   0.208684 2.655725e-10        4
       256   7.370546   0.273150 2.401066e-10        8
       256   4.283762   0.469976 2.423803e-10        12
       256   4.010788   0.501963 2.428351e-10        16
       256   9.597267   0.209775 2.532943e-10        20
       256   6.178938   0.325827 2.455636e-10        24
       256   5.320399   0.378405 2.441993e-10        28
       256   3.442285   0.584863 2.405613e-10        32
       256   4.821041   0.417600 2.396519e-10        36
       256   5.403120   0.372612 2.310117e-10        40
       256   3.534860   0.569546 2.328306e-10        44
       256   3.415464   0.589456 2.319211e-10        48
       256   6.921946   0.290853 2.319211e-10        52
       256   6.133741   0.328228 2.391971e-10        56
       256   3.469388   0.580294 2.319211e-10        60
       256   3.175538   0.633992 2.492015e-10        64
       256   4.764436   0.422561 2.428351e-10        68
       256   8.563460   0.235100 2.396519e-10        72
       256   7.162986   0.281065 2.419256e-10        76
       256   7.826451   0.257239 2.455636e-10        80
       256   3.527388   0.570753 2.428351e-10        84
       256   3.391256   0.593664 2.319211e-10        88
       256   3.733892   0.539187 2.373781e-10        92
       256   5.651083   0.356262 2.464731e-10        96
       256   7.127130   0.282479 2.319211e-10        100
       256   3.415078   0.589523 2.319211e-10        104
       256   3.540592   0.568624 2.269189e-10        108
       256   4.044524   0.497776 2.410161e-10        112
       256   6.834958   0.294554 2.319211e-10        116
       256   7.171600   0.280728 2.328306e-10        120
       256   3.659638   0.550127 2.319211e-10        124
       256   3.395928   0.592847 2.455636e-10        128
```
Optimal BLOCK_SIZE = 64

## Problem 3

> `_mm256_set1_pd` is an intrinsic function in Intel's Intrinsics, which is used to set all elements of a 256-bit vector of double-precision floating-point values to the same value.  
`_mm256_mul_pd` is used to multiply two 256-bit vectors of double-precision floating-point values element-wise.  
`_mm256_load_pd` is used to load 256-bit vectors of double-precision floating-point values from memory.  
`_mm256_add_pd` is used to add two 256-bit vectors of double-precision floating-point values element-wise.  
`_mm256_store_pd`  is an intrinsic function in Intel's Intrinsics, used to store 256-bit vectors of double-precision floating-point values to memory.

I do the AVX part of `sin4_intrin()` by adding 4 more terms. Now the accuracy is 12-digits.
```bash
Reference time: 52.5995
Taylor time:    3.3379      Error: 6.928125e-12
Intrin time:    2.5354      Error: 6.928125e-12
Vector time:    2.2838      Error: 2.454130e-03
```

## Problem 4
> Processor: Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz

compute.cpp: Report timings and study the latency of other functions such as sqrt, sin, cos (as outlined at the bottom of the file). Try to run with different compiler optimization flags and report timings.  

-O3 optimization
```
mult-add
0.900234 seconds
division
3.145639 seconds
sqrt
3.133709 seconds
sin
10.830236 seconds
```

-O0 optimization
```
mult-add
2.921078 seconds
division
4.264271 seconds
sqrt
5.994306 seconds
sin
13.603349 seconds
```

compute-vec.cpp Read the code and report timings for the vectorized code. Try to explain the different timings (it’s OK if these explanations aren’t fully correct).  

```
time = 0.907615
flop-rate = 8.813893 Gflop/s

time = 1.783758
flop-rate = 4.484887 Gflop/s

time = 1.774972
flop-rate = 4.507089 Gflop/s
```
`compute_fn0()` uses simple for loop (implicit vectorization) to compute.  
`compute_fn1()` uses intrinsic vectorization to compute.  
`compute_fn2()` uses a wrapper class Vec that provides a more abstract interface to SIMD operations. So its timing is close to fn1.  
fn0 is the fastest, maybe thanks to complier's optimization. The performance of fn1 and fn2 may due to the overheads of intrinsic vectorization and Vec.  

compute-vec-pipe.cpp Measure and report the performance of the code for different M as outlined in the comment at the bottom of the file. Summarize your observations.

M = 1
```
time = 0.904538
flop-rate = 8.843910 Gflop/s

time = 1.799325
flop-rate = 4.446089 Gflop/s

time = 1.776413
flop-rate = 4.503436 Gflop/s
```

M = 2
```
time = 1.030388
flop-rate = 15.527538 Gflop/s

time = 1.802190
flop-rate = 8.878024 Gflop/s

time = 1.781046
flop-rate = 8.983427 Gflop/s
```

M = 3
```
time = 2.367103
flop-rate = 10.138798 Gflop/s

time = 1.791521
flop-rate = 13.396359 Gflop/s

time = 1.782760
flop-rate = 13.462194 Gflop/s
```

M = 4
```
time = 4.025008
flop-rate = 7.950188 Gflop/s

time = 1.797150
flop-rate = 17.805864 Gflop/s

time = 1.783830
flop-rate = 17.938820 Gflop/s
```

M = 8
```
time = 2.240452
flop-rate = 28.565199 Gflop/s

time = 2.040176
flop-rate = 31.369658 Gflop/s

time = 2.050045
flop-rate = 31.218666 Gflop/s
```

M = 16
```
time = 7.594753
flop-rate = 16.853657 Gflop/s

time = 3.801349
flop-rate = 33.672167 Gflop/s

time = 3.795872
flop-rate = 33.720760 Gflop/s
```

M = 32
```
time = 28.494053
flop-rate = 8.984263 Gflop/s

time = 28.435303
flop-rate = 9.002889 Gflop/s

time = 28.495653
flop-rate = 8.983823 Gflop/s
```

M = 64
```
time = 56.997868
flop-rate = 8.982786 Gflop/s

time = 56.953074
flop-rate = 8.989855 Gflop/s

time = 56.833921
flop-rate = 9.008703 Gflop/s
```

When M is small(1, 2), fn0 is the fastest. Because there isn't enough parallelism to fill the pipeline. And the overhead may result in a worse performance.  
When M = 4, 8, 16, fn1 and fn2 benifit from pipeliening, thus much faster than fn0.  
M is too large(32, 16) then the computation cannot fit in registers and the data pills to the L1 cache resulting in slower execution. So the speed of these 3 functions are pretty close.