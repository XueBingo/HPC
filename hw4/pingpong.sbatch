#!/bin/bash

#SBATCH --job-name=pingpong
#SBATCH --output=pingpong.out
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=2GB

mpirun ./pingpong 0 1
