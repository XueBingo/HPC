#!/bin/bash

make

# loop over input sizes

for num_node in 2048 4096; do
  echo "============================================="
  for num_thread in 1 2 4 6 8 12 16 32 64; do
    ./floyd_warshall -n $num_node -t $num_thread
    echo "============================================="
  done
done

make clean