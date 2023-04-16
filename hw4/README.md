# <center>HPC_hw4</center>

<p align='right'>Bing Xue (bx2109@nyu.edu)</p>

> Repo link: https://github.com/XueBingo/HPC

## 1. Greene network test.

```
Rank 0 running on gr034.hpc.nyu.edu.
Rank 1 running on gr035.hpc.nyu.edu.
pingpong latency: 1.931160e-04 ms
pingpong bandwidth: 1.106704e+01 GB/s
```

## 2. MPI ring communication.
*int_ring*
> setting: N = 10, number of process = 4
```
Final sum: 60
```
The final sum correspnd to the calculated result: $(0+3)*4/2*10 = 60$.

> setting: N = 10000, number of process = 4
```
Rank 0 running on cm013.hpc.nyu.edu.
Rank 1 running on cm014.hpc.nyu.edu.
Rank 2 running on cm015.hpc.nyu.edu.
Rank 3 running on cm029.hpc.nyu.edu.
Final sum: 60000
int_ring latency for a ring: 1.019798e-02 ms
```

*array_ring*
> setting: N = 10000, number of process = 4
array_ring latency for a ring: 6.711538e-01 ms
Bandwidth: 11919.770785 MB/s



