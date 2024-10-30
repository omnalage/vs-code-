#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 10  // Fixed buffer size

// Global variables (set through user input)
int M, K, N;            // Matrix dimensions
int PRODUCERS, CONSUMERS; // Number of producer and consumer threads
int TARGET_COUNT;        // Number of matrices to process
int TILE_SIZE = 32;      // Tile size for matrix multiplication

// Bounded buffer data structures
double **buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// Matrices and processed counter
double *B, *C;
int matrices_processed = 0;
pthread_mutex_t process_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to generate random matrices
double *generate_random_matrix(int rows, int cols) {
    double *matrix = (double *)aligned_alloc(64, rows * cols * sizeof(double)); // Cache-aligned memory
    for (int i = 0; i < rows * cols; ++i) {
        matrix[i] = (double)(rand() % 10);
    }
    return matrix;
}

// Tiled matrix multiplication function for cache optimization
void multiply_tiled(double *A, double *B, double *C, int start_row, int end_row) {
    for (int i = start_row; i < end_row; i += TILE_SIZE) {
        for (int j = 0; j < N; j += TILE_SIZE) {
            for (int k = 0; k < K; k += TILE_SIZE) {
                // Perform multiplication on the current tile
                for (int ii = i; ii < i + TILE_SIZE && ii < M; ++ii) {
                    for (int jj = j; jj < j + TILE_SIZE && jj < N; ++jj) {
                        double sum = C[ii * N + jj];
                        for (int kk = k; kk < k + TILE_SIZE && kk < K; ++kk) {
                            sum += A[ii * K + kk] * B[kk * N + jj];
                        }
                        C[ii * N + jj] = sum;
                    }
                }
            }
        }
    }
}

// Consumer thread function
void *consumer(void *arg) {
    while (1) {
        double **matrices;

        // Retrieve matrices from buffer
        pthread_mutex_lock(&buffer_mutex);
        while (count == 0) {
            pthread_cond_wait(&not_empty, &buffer_mutex);
        }
        matrices = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&buffer_mutex);

        // Perform matrix multiplication
        multiply_tiled(matrices[0], B, C, 0, M);

        // Free allocated memory
        free(matrices[0]);
        free(matrices);

        // Track processed matrices
        pthread_mutex_lock(&process_mutex);
        matrices_processed++;
        if (matrices_processed >= TARGET_COUNT) {
            pthread_mutex_unlock(&process_mutex);
            break;
        }
        pthread_mutex_unlock(&process_mutex);
    }
    return NULL;
}

// Producer thread function
void *producer(void *arg) {
    while (1) {
        // Generate random matrix and add to buffer
        double *matrix = generate_random_matrix(M, K);
        double **matrices = (double **)malloc(2 * sizeof(double *));
        matrices[0] = matrix;
        matrices[1] = B;  // Shared matrix B

        // Insert matrices into buffer
        pthread_mutex_lock(&buffer_mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &buffer_mutex);
        }
        buffer[in] = matrices;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&buffer_mutex);
    }
    return NULL;
}

int main() {
    // User input for matrix dimensions and threads
    printf("Enter matrix dimensions (M K N): ");
    scanf("%d %d %d", &M, &K, &N);

    printf("Enter number of producers: ");
    scanf("%d/n", &PRODUCERS);

    printf("Enter number of consumers: ");
    scanf("%d", &CONSUMERS);

    printf("Enter target number of matrices to process: ");
    scanf("%d", &TARGET_COUNT);

    printf("Enter tile size for multiplication : ");
    scanf("%d", &TILE_SIZE);

    // Seed the random number generator
    srand(time(NULL));

    // Allocate memory for matrices
    B = generate_random_matrix(K, N);
    C = (double *)aligned_alloc(64, M * N * sizeof(double));  // Cache-aligned memory

    // Create producer and consumer threads
    pthread_t producer_threads[PRODUCERS], consumer_threads[CONSUMERS];

    for (int i = 0; i < PRODUCERS; ++i) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }
    for (int i = 0; i < CONSUMERS; ++i) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    // Wait for all consumers to finish
    for (int i = 0; i < CONSUMERS; ++i) {
        pthread_join(consumer_threads[i], NULL);
    }

    // Cancel producer threads (optional)
    for (int i = 0; i < PRODUCERS; ++i) {
        pthread_cancel(producer_threads[i]);
    }
    // Free allocated memory
    free(B);
    free(C);

    printf("Matrix multiplication completed with %d matrices processed.\n", matrices_processed);
    return 0;
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>
// #include <time.h>

// // Bounded buffer settings
// #define BUFFER_SIZE 10 // Fixed buffer size

// // Global variables (set through terminal input)
// int M, K, N; // Matrix dimensions
// int PRODUCERS, CONSUMERS; // Number of producer and consumer threads
// int TARGET_COUNT; // Number of matrices to process

// // Bounded buffer data structures
// double **buffer[BUFFER_SIZE];
// int in = 0, out = 0, count = 0;
// pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
// pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// // Matrix used for multiplication
// double *B, *C;
// int matrices_processed = 0;
// pthread_mutex_t process_mutex = PTHREAD_MUTEX_INITIALIZER;

// // Function to generate a random matrix
// double *generate_random_matrix(int rows, int cols) {
//     double *matrix = (double *)malloc(rows * cols * sizeof(double));
//     for (int i = 0; i < rows * cols; ++i) {
//         matrix[i] = (double)(rand() % 10);
//     }
//     return matrix;
// }

// // Matrix multiplication function
// void multiply_matrices(double *A, double *B, double *C, int start_row, int end_row) {
//     for (int i = start_row; i < end_row; ++i) {
//         for (int j = 0; j < N; ++j) {
//             double sum = 0;
//             for (int k = 0; k < K; ++k) {
//                 sum += A[i * K + k] * B[k * N + j];
//             }
//             C[i * N + j] = sum;
//         }
//     }
// }

// // Consumer thread function
// void *consumer(void *arg) {
//     while (1) {
//         double **matrices;

//         // Retrieve matrix pair from the buffer
//         pthread_mutex_lock(&buffer_mutex);
//         while (count == 0) {
//             pthread_cond_wait(&not_empty, &buffer_mutex);
//         }
//         matrices = buffer[out];
//         out = (out + 1) % BUFFER_SIZE;
//         count--;
//         pthread_cond_signal(&not_full);
//         pthread_mutex_unlock(&buffer_mutex);

//         // Perform multiplication
//         multiply_matrices(matrices[0], B, C, 0, M);

//         // Free the matrices after use
//         free(matrices[0]);
//         free(matrices);

//         // Increment processed matrices count
//         pthread_mutex_lock(&process_mutex);
//         matrices_processed++;
//         if (matrices_processed >= TARGET_COUNT) {
//             pthread_mutex_unlock(&process_mutex);
//             break;
//         }
//         pthread_mutex_unlock(&process_mutex);
//     }
//     return NULL;
// }

// // Producer thread function
// void *producer(void *arg) {
//     while (1) {
//         double *matrix = generate_random_matrix(M, K);
//         double **matrices = (double **)malloc(2 * sizeof(double *));
//         matrices[0] = matrix;
//         matrices[1] = B;

//         // Insert into the buffer
//         pthread_mutex_lock(&buffer_mutex);
//         while (count == BUFFER_SIZE) {
//             pthread_cond_wait(&not_full, &buffer_mutex);
//         }
//         buffer[in] = matrices;
//         in = (in + 1) % BUFFER_SIZE;
//         count++;
//         pthread_cond_signal(&not_empty);
//         pthread_mutex_unlock(&buffer_mutex);
//     }
//     return NULL;
// }

// int main() {
//     // Get input from the user
//     printf("Enter matrix dimensions (M K N): ");
//     scanf("%d %d %d", &M, &K, &N);

//     printf("Enter number of producers: ");
//     scanf("%d", &PRODUCERS);

//     printf("Enter number of consumers: ");
//     scanf("%d", &CONSUMERS);

//     printf("Enter target number of matrices to process: ");
//     scanf("%d", &TARGET_COUNT);

//     // Seed the random number generator
//     srand(time(NULL));

//     // Allocate memory for matrices
//     B = generate_random_matrix(K, N);
//     C = (double *)calloc(M * N, sizeof(double));

//     // Create producer and consumer threads
//     pthread_t producer_threads[PRODUCERS], consumer_threads[CONSUMERS];

//     for (int i = 0; i < PRODUCERS; ++i) {
//         pthread_create(&producer_threads[i], NULL, producer, NULL);
//     }
//     for (int i = 0; i < CONSUMERS; ++i) {
//         pthread_create(&consumer_threads[i], NULL, consumer, NULL);
//     }

//     // Wait for all consumers to complete
//     for (int i = 0; i < CONSUMERS; ++i) {
//         pthread_join(consumer_threads[i], NULL);
//     }

//     // Terminate all producers (optional, they run indefinitely)
//     for (int i = 0; i < PRODUCERS; ++i) {
//         pthread_cancel(producer_threads[i]);
//     }

//     // Clean up and free allocated memory
//     free(B);
//     free(C);

//     printf("Matrix multiplication completed with %d matrices processed.\n", matrices_processed);
//     return 0;
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>
// #include <time.h>

// #define M 500 // Number of rows in matrix A
// #define K 500 // Number of columns in matrix A and rows in matrix B
// #define N 500 // Number of columns in matrix B

// #define BUFFER_SIZE 10 // Size of the bounded buffer
// #define PRODUCERS 2 // Number of producer threads
// #define CONSUMERS 2 // Number of consumer threads
// #define TARGET_COUNT 20 // Number of matrices to process

// // Bounded buffer data structures
// double **buffer[BUFFER_SIZE];
// int in = 0, out = 0, count = 0;
// pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
// pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// // Matrix to be used in multiplication
// double *B, *C;

// // Track processed matrices
// int matrices_processed = 0;
// pthread_mutex_t process_mutex = PTHREAD_MUTEX_INITIALIZER;

// // Function to generate random matrices
// double *generate_random_matrix(int rows, int cols) {
//     double *matrix = (double *)malloc(rows * cols * sizeof(double));
//     for (int i = 0; i < rows * cols; ++i) {
//         matrix[i] = (double)(rand() % 10);
//     }
//     return matrix;
// }

// // Matrix multiplication function
// void multiply_matrices(double *A, double *B, double *C, int start_row, int end_row) {
//     for (int i = start_row; i < end_row; ++i) {
//         for (int j = 0; j < N; ++j) {
//             double sum = 0;
//             for (int k = 0; k < K; ++k) {
//                 sum += A[i * K + k] * B[k * N + j];
//             }
//             C[i * N + j] = sum;
//         }
//     }
// }

// // Thread function for consumer
// void *consumer(void *arg) {
//     while (1) {
//         double **matrices;

//         // Retrieve matrix pair from the buffer
//         pthread_mutex_lock(&buffer_mutex);
//         while (count == 0) {
//             pthread_cond_wait(&not_empty, &buffer_mutex);
//         }
//         matrices = buffer[out];
//         out = (out + 1) % BUFFER_SIZE;
//         count--;
//         pthread_cond_signal(&not_full);
//         pthread_mutex_unlock(&buffer_mutex);

//         // Perform multiplication
//         multiply_matrices(matrices[0], B, C, 0, M);

//         // Free the matrices after use
//         free(matrices[0]);
//         free(matrices);

//         // Increment processed matrices count
//         pthread_mutex_lock(&process_mutex);
//         matrices_processed++;
//         if (matrices_processed >= TARGET_COUNT) {
//             pthread_mutex_unlock(&process_mutex);
//             break;
//         }
//         pthread_mutex_unlock(&process_mutex);
//     }
//     return NULL;
// }

// // Thread function for producer
// void *producer(void *arg) {
//     while (1) {
//         // Generate a random matrix
//         double *matrix = generate_random_matrix(M, K);
//         double **matrices = (double **)malloc(2 * sizeof(double *));
//         matrices[0] = matrix;
//         matrices[1] = B; // Use the global B matrix

//         // Insert into the buffer
//         pthread_mutex_lock(&buffer_mutex);
//         while (count == BUFFER_SIZE) {
//             pthread_cond_wait(&not_full, &buffer_mutex);
//         }
//         buffer[in] = matrices;
//         in = (in + 1) % BUFFER_SIZE;
//         count++;
//         pthread_cond_signal(&not_empty);
//         pthread_mutex_unlock(&buffer_mutex);
//     }
//     return NULL;
// }

// int main() {
//     srand(time(NULL)); // Seed the random number generator

//     // Allocate memory for matrices
//     B = generate_random_matrix(K, N);
//     C = (double *)calloc(M * N, sizeof(double));

//     // Create producer and consumer threads
//     pthread_t producer_threads[PRODUCERS], consumer_threads[CONSUMERS];

//     for (int i = 0; i < PRODUCERS; ++i) {
//         pthread_create(&producer_threads[i], NULL, producer, NULL);
//     }
//     for (int i = 0; i < CONSUMERS; ++i) {
//         pthread_create(&consumer_threads[i], NULL, consumer, NULL);
//     }

//     // Wait for all consumers to complete
//     for (int i = 0; i < CONSUMERS; ++i) {
//         pthread_join(consumer_threads[i], NULL);
//     }

//     // Terminate all producers (not strictly necessary if they run indefinitely)
//     for (int i = 0; i < PRODUCERS; ++i) {
//         pthread_cancel(producer_threads[i]);
//     }

//     // Clean up and free allocated memory
//     free(B);
//     free(C);

//     printf("Matrix multiplication completed with %d matrices processed.\n", matrices_processed);
//     return 0;
// }