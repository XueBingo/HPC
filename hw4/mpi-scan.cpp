#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <iostream>
#include <string.h>


// Scan A array and write result into prefix_sum array;
// use long data type to avoid overflow
void scan_seq(long* prefix_sum, const long* A, long n) {
  if (n == 0) return;
  prefix_sum[0] = 0;
  for (long i = 1; i < n; i++) {
    prefix_sum[i] = prefix_sum[i-1] + A[i-1];
  }
}

void scan_mpi(long* B, long* A, long N, int rank, int size) {

  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);
  printf("Rank %d/%d running on %s.\n", rank, size, processor_name);
  /////
  MPI_Barrier(MPI_COMM_WORLD);

  long n = N / size;

  long* local_in = (long*) malloc(n * sizeof(long));
  long* local_out = (long*) malloc(n * sizeof(long));
  // distributes the elements of the input array A to size processes in the MPI \
  communicator MPI_COMM_WORLD, where each process receives a subarray of n elements.
  MPI_Scatter(A, n, MPI_LONG, local_in, n, MPI_LONG, 0, MPI_COMM_WORLD);

  local_out[0] = local_in[0];
  for (long i = 1; i < n; i++) {
    local_out[i] = local_out[i-1] + local_in[i];
  }
  long* offset_arr = (long*) malloc(size * sizeof(long));

  // gathers the last element of the partial prefix sums computed by each process \
  into the array offset_arr in all processes in the MPI communicator MPI_COMM_WORLD.
  MPI_Allgather(local_out+n-1, 1, MPI_LONG, offset_arr, 1, MPI_LONG, MPI_COMM_WORLD);

  long offset = 0;
  for(int i = 0; i < rank; i++){
    offset += offset_arr[i];
  }

  for(int i = 0; i < n; i++){
    local_out[i] += offset;
  }

  // gathers the partial prefix sums computed by each process into the array B1 \
  in the root process (rank 0) 
  MPI_Gather(local_out, n, MPI_LONG, &(B[1]), n, MPI_LONG, 0, MPI_COMM_WORLD);

  free(local_in);
  free(local_out);
  free(offset_arr);

  MPI_Barrier(MPI_COMM_WORLD);

//////
}

int main(int argc, char *argv[]) {
  long N = 48000000;
  int rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long* A;
  long* B1;
  long* B0;

  if (rank == 0) {
    A = (long*) malloc(N * sizeof(long));
    B0 = (long*) malloc(N * sizeof(long));
    B1 = (long*) calloc((N+1),sizeof(long));
    for(long i = 0; i < N; i++) A[i] = rand();
    scan_seq(B0, A, N);
  }

  scan_mpi(B1, A, N, rank, size);

  if (rank == 0) {
    long err = 0;
    for (long i = 0; i < N; i++) err = std::max(err, std::abs(B0[i] - B1[i]));
    printf("error = %ld\n", err);

    free(B0);
    free(B1);
    free(A);
  }

  MPI_Finalize();

  return 0;
}