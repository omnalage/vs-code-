#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_CAPACITY 5
#define MATRIX_DIMENSION 500
#define TARGET_MATRIX_COUNT 10

typedef struct {
    int **matrix1;
    int **matrix2;
} MatrixPair;

// Circular buffer for storing matrix pairs
MatrixPair buffer[BUFFER_CAPACITY];
int buffer_count = 0, buffer_in = 0, buffer_out = 0;
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;
int produced_matrices = 0;
int processed_matrices = 0;

// Function to allocate a matrix
int **allocate_matrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to populate a matrix with random numbers
void fill_random_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void free_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Producer thread function to generate random matrices
void *producer_thread(void *arg) {
    while (1) {
        int **mat1 = allocate_matrix(MATRIX_DIMENSION);
        int **mat2 = allocate_matrix(MATRIX_DIMENSION);
        fill_random_matrix(mat1, MATRIX_DIMENSION);
        fill_random_matrix(mat2, MATRIX_DIMENSION);

        pthread_mutex_lock(&buffer_mutex);

        // Wait if the buffer is full
        while (buffer_count == BUFFER_CAPACITY) {
            pthread_cond_wait(&buffer_not_full, &buffer_mutex);
        }

        // Add the matrix pair to the buffer
        buffer[buffer_in].matrix1 = mat1;
        buffer[buffer_in].matrix2 = mat2;
        buffer_in = (buffer_in + 1) % BUFFER_CAPACITY;
        buffer_count++;

        produced_matrices++;
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&buffer_mutex);

        if (produced_matrices >= TARGET_MATRIX_COUNT) break;
    }
    return NULL;
}

// Consumer thread function to retrieve matrices and multiply them
void *consumer_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&buffer_mutex);

        // Wait if the buffer is empty
        while (buffer_count == 0 && processed_matrices < TARGET_MATRIX_COUNT) {
            pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
        }

        if (processed_matrices >= TARGET_MATRIX_COUNT) {
            pthread_mutex_unlock(&buffer_mutex);
            break;
        }

        // Retrieve a matrix pair from the buffer
        MatrixPair matrices = buffer[buffer_out];
        buffer_out = (buffer_out + 1) % BUFFER_CAPACITY;
        buffer_count--;

        processed_matrices++;
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&buffer_mutex);

        // Perform matrix multiplication
        int **result = allocate_matrix(MATRIX_DIMENSION);
        for (int i = 0; i < MATRIX_DIMENSION; i++) {
            for (int j = 0; j < MATRIX_DIMENSION; j++) {
                result[i][j] = 0;
                for (int k = 0; k < MATRIX_DIMENSION; k++) {
                    result[i][j] += matrices.matrix1[i][k] * matrices.matrix2[k][j];
                }
            }
        }

        // Clean up memory for the matrices
        free_matrix(matrices.matrix1, MATRIX_DIMENSION);
        free_matrix(matrices.matrix2, MATRIX_DIMENSION);
        free_matrix(result, MATRIX_DIMENSION);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t producer_threads[2], consumer_threads[2];

    // Create producer and consumer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&producer_threads[i], NULL, producer_thread, NULL);
        pthread_create(&consumer_threads[i], NULL, consumer_thread, NULL);
    }

    // Wait for producer and consumer threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(producer_threads[i], NULL);
        pthread_join(consumer_threads[i], NULL);
    }

    printf("All matrix pairs have been processed.\n");

    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&buffer_not_full);
    pthread_cond_destroy(&buffer_not_empty);

    return 0;
}
