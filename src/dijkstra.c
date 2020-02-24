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
    {
        if ((sptSet[v] == false) && (dist[v] <= min))
        {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void dijkstra(int src, int V, int **graph, int *dist)
{
    // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized
    bool sptSet[V];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX, sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
        {
            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to  v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && (dist[u] != INT_MAX) && (dist[u] + graph[u][v] < dist[v]))
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    // Set rand() seed
    srand(13517020);
    /* total cost == 0
     size | total
     100  |    0
     500  |    4
     1000 |   18
     3000 |  135
     5000 |  380
	*/
    // srand(13517137);
    /* total cost == 0
     size | total
     100  |    0
     500  |    2
     1000 |   13
     3000 |  126
     5000 |  360
  	*/

    if (argc != 2)
    {
        fprintf(stderr, "error: missing command line arguments\n");
        exit(1);
    }
    else
    {
        // Inititate graph
        long nodes = atoi(argv[1]);
        long **matrix = (long **)malloc(nodes * sizeof(long *));

        for (int i = 0; i < nodes; i++)
        {
            matrix[i] = (long *)malloc(nodes * sizeof(long));
        }

        assert(matrix != NULL);

        // Build graph
        for (int i = 0; i < nodes; i++)
        {
            for (int j = 0; j < nodes; j++)
            {
                if (i == j)
                {
                    matrix[i][j] = 0;
                }
                else
                {
                    matrix[i][j] = rand();
                }
            }
        }

        long **newmatrix = (long **)malloc(nodes * sizeof(long *));

        for (int i = 0; i < nodes; i++)
        {
            newmatrix[i] = (long *)malloc(nodes * sizeof(long));
        }

        // Dijkstra Algorithm
        clock_t begin = clock();
        int numtasks, rank = 1;
        MPI_Status Stat;
        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        // Parallel Algorithm
        if (numtasks > 1)
        {
            int runners = numtasks - 1;

            if (rank != 0)
            {
                for (int i = rank - 1; i < nodes; i += runners)
                {
                    dijkstra(i, nodes, matrix, newmatrix[i]);
                    MPI_Send(newmatrix[i], nodes, MPI_INT, 0, i, MPI_COMM_WORLD);
                }
            }
            else
            {
                for (int i = 0; i < nodes; i++)
                {
                    MPI_Recv(newmatrix[i], nodes, MPI_INT, i % runners + 1, i, MPI_COMM_WORLD, &Stat);
                }

                clock_t end = clock();

                // Write to file
                FILE *fp;
                fp = fopen("~/out/old_matrix.txt", "w");
                fprintf(fp, "Old matrix:\n");

                for (int i = 0; i < nodes; i++)
                {
                    for (int j = 0; j < nodes; j++)
                    {
                        fprintf(fp, "%d ", matrix[i][j]);
                    }

                    fprintf(fp, "\n");
                }

                fclose(fp);

                fp = fopen("~/out/result.txt", "w");
                fprintf(fp, "New matrix:\n");

                for (int i = 0; i < nodes; i++)
                {
                    for (int j = 0; j < nodes; j++)
                    {
                        fprintf(fp, "%d ", newmatrix[i][j]);
                    }

                    fprintf(fp, "\n");
                }

                fprintf(fp, "Solution found in: %.3f microseconds\n", ((double)(end - begin) / CLOCKS_PER_SEC) * 1000000);
                fclose(fp);
            }
        }
        // Serial Algorithm
        else
        {
            for (int i = 0; i < nodes; i++)
            {
                dijkstra(i, nodes, matrix, newmatrix[i]);
            }

            clock_t end = clock();

            // Write to file
            FILE *fp;
            fp = fopen("~/out/old_matrix.txt", "w");
            fprintf(fp, "Old matrix:\n");

            for (int i = 0; i < nodes; i++)
            {
                for (int j = 0; j < nodes; j++)
                {
                    fprintf(fp, "%d ", matrix[i][j]);
                }

                fprintf(fp, "\n");
            }

            fclose(fp);

            fp = fopen("~/out/result.txt", "w");
            fprintf(fp, "New matrix:\n");

            for (int i = 0; i < nodes; i++)
            {
                for (int j = 0; j < nodes; j++)
                {
                    fprintf(fp, "%d ", newmatrix[i][j]);
                }

                fprintf(fp, "\n");
            }

            fprintf(fp, "Solution found in: %.3f microseconds\n", ((double)(end - begin) / CLOCKS_PER_SEC) * 1000000);
            fclose(fp);
        }

        MPI_Finalize();

        // Dealocation
        for (int i = 0; i < nodes; i++)
        {
            free(matrix[i]);
        }

        free(matrix);

        for (int i = 0; i < nodes; i++)
        {
            free(newmatrix[i]);
        }

        free(newmatrix);
    }
    return 0;
}
