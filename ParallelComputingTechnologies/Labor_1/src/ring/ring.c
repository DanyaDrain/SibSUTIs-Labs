#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>

#define BITE 1
#define KILOBYTE 1024
#define MEGABYTE 1024 * 1024

void ring(int size, int rank, int count, MPI_Datatype datatype, FILE *log_file); //Функция обмена сообщениями внутри буффера

int main(int argc, char **argv) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    FILE *log = NULL;
    if (rank == 0) {
        log = fopen("results.txt", "a");
        if (!log) {
            fprintf(stderr, "Cannot open results_ring.txt for writing\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    ring(size, rank, BITE, MPI_CHAR, log);
    ring(size, rank, KILOBYTE, MPI_CHAR, log);
    ring(size, rank, MEGABYTE, MPI_CHAR, log);
 
    if (log) {
        fclose(log);
    }

    MPI_Finalize();
    return 0;
}

void ring(int size, int rank, int count, MPI_Datatype datatype, FILE *log_file){
    int right = (rank + 1) % size;
    int left = (rank - 1 + size) % size;
    char *buf = (char *)malloc(count * sizeof(char));
    char fill = (char)('A' + (rank % 26));
    for (int i = 0; i < count; i++) { buf[i] = fill; }  
    MPI_Barrier(MPI_COMM_WORLD);
    double start, end , time;
    if (rank == 0) { start = MPI_Wtime(); }
    for(int i = 0; i < size - 1; i++){
        if(rank % 2 == 0){
            MPI_Send(buf, count, datatype, right, 0, MPI_COMM_WORLD);
            MPI_Recv(buf, count, datatype, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            MPI_Recv(buf, count, datatype, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(buf, count, datatype, right, 0, MPI_COMM_WORLD);
        }
    }
    if(rank == 0) {
        end = MPI_Wtime();
        time = end - start;
        fprintf(log_file, "Процесс = %d, Размер = %d, время = %.9f\n", rank, count, time);
    }
    free(buf);
}