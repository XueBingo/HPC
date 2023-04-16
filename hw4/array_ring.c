#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE (2 * 1024 * 1024)/sizeof(int) // 2 MB

int main(int argc, char** argv) {
    int rank, size, tag, n, i, sum, recv;
    int* sendbuf = (int*) malloc(sizeof(int) * ARRAY_SIZE);
    int* recvbuf = (int*) malloc(sizeof(int) * ARRAY_SIZE);
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc > 1) {
        n = atoi(argv[1]);
    } else {
        n = 10;
    }

    tag = 0;

    double tt = MPI_Wtime();
    for (i = 0; i < n; i++) {
        if (rank == 0) {
            MPI_Send(sendbuf, ARRAY_SIZE, MPI_INT, 1, tag, MPI_COMM_WORLD);
            MPI_Recv(sendbuf, ARRAY_SIZE, MPI_INT, size - 1, tag, MPI_COMM_WORLD, &status);
        } else {
            MPI_Recv(sendbuf, ARRAY_SIZE, MPI_INT, rank - 1, tag, MPI_COMM_WORLD, &status);
            if (rank == size - 1) {
                MPI_Send(sendbuf, ARRAY_SIZE, MPI_INT, 0, tag, MPI_COMM_WORLD);
            } else {
                MPI_Send(sendbuf, ARRAY_SIZE, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);
            }
        }
    }
    tt = MPI_Wtime() - tt;

    if (rank == 0) {
        printf("array_ring latency for a ring: %e ms\n", tt/n * 1000);
        printf("Bandwidth: %f MB/s\n", (double) (ARRAY_SIZE * sizeof(int) * size * atoi(argv[1])) / (tt * 1024 * 1024));
    }

    MPI_Finalize();

    return 0;
}
