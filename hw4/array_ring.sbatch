#!/bin/bash

#SBATCH --job-name=array_ring
#SBATCH --output=array_ring.out
#SBATCH --nodes=4
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=16GB
#SBATCH --verbose

mpirun ./array_ring 10000