#!/bin/bash

#SBATCH --job-name=int_ring
#SBATCH --output=int_ring.out
#SBATCH --nodes=4
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=16GB

mpirun ./int_ring 10000