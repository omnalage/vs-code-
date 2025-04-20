#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define TILE_SIZE 64  // Adjust tile size based on system

typedef struct {
    int **A, **B, **C;
    long int M, N, K;
    int thread_id;
    int num_threads;
} ThreadData;

// Function to initialize matrix
void Initialise_Array(int ***X, long int rows, long int cols) {
    *X = (int **)malloc(rows * sizeof(int *));
    if (*X == NULL) {
        printf("Memory allocation failed in Initialise_Array()!!\n");
        exit(1);
    }

    for (long int i = 0; i < rows; i++) {
        (*X)[i] = (int *)malloc(cols * sizeof(int));
        if ((*X)[i] == NULL) {
            printf("Memory allocation failed in Initialise_Array()!!\n");
            exit(1);
        }
    }

    for (long int i = 0; i < rows; i++) {
        for (long int j = 0; j < cols; j++) {
            (*X)[i][j] = i + j;
        }
    }
}

// Free allocated memory
void Free(int **X, long int rows) {
    for (long int i = 0; i < rows; i++) {
        free(X[i]);
    }
    free(X);
}

// Single-threaded GEMM with tiling/blocking
void Gemm_Tiling(int **A, int **B, int **C, long int M, long int N, long int K) {
    for (long int i = 0; i < M; i++) {
        for (long int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    for (long int ii = 0; ii < M; ii += TILE_SIZE) {
        for (long int jj = 0; jj < N; jj += TILE_SIZE) {
            for (long int kk = 0; kk < K; kk += TILE_SIZE) {
                for (long int i = ii; i < ii + TILE_SIZE && i < M; i++) {
                    for (long int j = jj; j < jj + TILE_SIZE && j < N; j++) {
                        int sum = 0;
                        for (long int k = kk; k < kk + TILE_SIZE && k < K; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
}

// Parallel GEMM with tiling/blocking (using pthreads)
void *Gemm_Tiling_Parallel(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int **A = data->A;
    int **B = data->B;
    int **C = data->C;
    long int M = data->M;
    long int N = data->N;
    long int K = data->K;
    int thread_id = data->thread_id;
    int num_threads = data->num_threads;

    // Divide work among threads by rows
    long int start_row = thread_id * (M / num_threads);
    long int end_row = (thread_id == num_threads - 1) ? M : start_row + (M / num_threads);

    for (long int ii = start_row; ii < end_row; ii += TILE_SIZE) {
        for (long int jj = 0; jj < N; jj += TILE_SIZE) {
            for (long int kk = 0; kk < K; kk += TILE_SIZE) {
                for (long int i = ii; i < ii + TILE_SIZE && i < end_row; i++) {
                    for (long int j = jj; j < jj + TILE_SIZE && j < N; j++) {
                        int sum = 0;
                        for (long int k = kk; k < kk + TILE_SIZE && k < K; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
    pthread_exit(NULL);
}

// Function to measure execution time of provided function
double Measure_Execution_Time(void (*func)(int **, int **, int **, long int, long int, long int), int **A, int **B, int **C, long int M, long int N, long int K) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    func(A, B, C, M, N, K);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    return time_taken;
}

int main() {
    long int M = 500, N = 500, K = 500;
    char ans;
    int num_threads;

    printf("Do you want to enter M, K, N manually? (y/n): ");
    scanf(" %c", &ans);

    if (ans == 'y' || ans == 'Y') {
        printf("Enter the values of M, K, N: ");
        scanf("%ld %ld %ld", &M, &K, &N);
    }

    printf("Enter the number of threads to use (or 0 for max threads): ");
    scanf("%d", &num_threads);

    if (num_threads <= 0) {
        num_threads = 8;
    }

    int **A, **B, **C;

    // Initialize matrices
    Initialise_Array(&A, M, K);
    Initialise_Array(&B, K, N);
    Initialise_Array(&C, M, N);

    // Zero initialize C
    for (long int i = 0; i < M; i++) {
        for (long int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    printf("Gemm_Tiling Serial: %lf seconds\n", Measure_Execution_Time(Gemm_Tiling, A, B, C, M, N, K));

    // Reset C matrix
    for (long int i = 0; i < M; i++) {
        for (long int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    // Create threads for parallel computation
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_threads; i++) {
        thread_data[i] = (ThreadData){A, B, C, M, N, K, i, num_threads};
        pthread_create(&threads[i], NULL, Gemm_Tiling_Parallel, &thread_data[i]);
    }

    // Join threads after computation
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double parallel_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Gemm_Tiling Parallel: %lf seconds\n", parallel_time);

    // Free memory
    Free(A, M);
    Free(B, K);
    Free(C, M);

    return 0;
}