#!/bin/bash


make

for N in 1000 10000; do
  echo "============================================="
  for num_thread in 1 2 4 8 16 32 64; do
    ./jacobi2D-omp $num_thread $N
    ./gs2D-omp $num_thread $N
    echo "============================================="
  done
done
