#!/bin/bash

#SBATCH --job-name=mpi-scan
#SBATCH --output=mpi-scan.out
#SBATCH --nodes=4
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=16GB
#SBATCH --verbose

module purge
module load amber/openmpi/intel/20.06

mpirun ./mpi-scan