#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, tag, n, i, sum, recv;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    printf("Rank %d running on %s.\n", rank, processor_name);


    if (argc > 1) {
        n = atoi(argv[1]);
    } else {
        n = 10;
    }

    tag = 0;
    sum = 0;

    double tt = MPI_Wtime();
    for (i = 0; i < n; i++) {
        if (rank == 0) {
            MPI_Send(&sum, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
            MPI_Recv(&recv, 1, MPI_INT, size - 1, tag, MPI_COMM_WORLD, &status);
            sum = recv;
        } else {
            MPI_Recv(&recv, 1, MPI_INT, rank - 1, tag, MPI_COMM_WORLD, &status);
            sum = recv + rank;
            if (rank == size - 1) {
                MPI_Send(&sum, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
            } else {
                MPI_Send(&sum, 1, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);
            }
        }
    }
    tt = MPI_Wtime() - tt;

    if (rank == 0) {
        printf("Final sum: %d\n", sum);
        printf("int_ring latency for a ring: %e ms\n", tt/n * 1000);
    }

    MPI_Finalize();

    return 0;
}
