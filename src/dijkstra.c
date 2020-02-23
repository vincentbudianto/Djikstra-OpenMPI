// Copyright www.computing.llnl.gov
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>

int minDistance(int dist[], bool sptSet[], int V) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
}

void dijkstra(int src, int V, int **graph, int *dist) 
{   
    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 
  
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < V - 1; count++) { 
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int u = minDistance(dist, sptSet, V); 
  
        // Mark the picked vertex as processed 
        sptSet[u] = true; 
  
        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < V; v++) 
  
            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v] 
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) 
                dist[v] = dist[u] + graph[u][v]; 
    } 
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc != 2) {
        fprintf(stderr, "Usage: dijkstra <Number of nodes>\n");
        exit(1);
    }

    int nodes = atoi(argv[1]);
    int **matrix = (int **)malloc(nodes * sizeof(int*));
    for(int i = 0; i < nodes; i++) matrix[i] = (int *)malloc(nodes * sizeof(int));
    assert(matrix != NULL);

    if (nodes < 10) {
        printf("Current matrix:\n");
        for (int i=0; i < nodes; i++) {
        for (int j=0; j < nodes; j++) {
            matrix[i][j] = rand() % 200;
            if (matrix[i][j] > 100 || i == j)
            . {
                matrix[i][j] = 0;
            }
        }
        }
        for (int i=0; i < nodes; i++) {
        for (int j=0; j < nodes; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
        }
    }

    int **newmatrix = (int **)malloc(nodes * sizeof(int*));
    for(int i = 0; i < nodes; i++) newmatrix[i] = (int *)malloc(nodes * sizeof(int));

    clock_t begin = clock();
    int numtasks, rank=1;
    MPI_Status Stat;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (int i=rank; i < nodes; i+=numtasks) {
        dijkstra(i, nodes, matrix, newmatrix[i]);
        if (rank != 0){
            MPI_Send(newmatrix[i], nodes, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    }

    // MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i=1; i < nodes && i < nodes; i++) {
            if (i % numtasks != 0) {
                MPI_Recv(newmatrix[i], nodes, MPI_INT, i%numtasks, 1, MPI_COMM_WORLD, &Stat);
            }
        }
        clock_t end = clock();
        if (nodes < 10) {
            printf("New matrix:\n");
            for (int i=0; i < nodes; i++) {
                for (int j=0; j < nodes; j++) {
                    printf("%d ", newmatrix[i][j]);
                }
                printf("\n");
            }
        }
        printf("Solution found in: %.3f seconds\n", ((double)(end - begin) / CLOCKS_PER_SEC));
    }


    for (int i=0; i < nodes; i++) {
        free(matrix[i]);
    }
    free(matrix);
    for (int i=0; i < nodes; i++) {
        free(newmatrix[i]);
    }
    free(newmatrix);
    MPI_Finalize();
}
