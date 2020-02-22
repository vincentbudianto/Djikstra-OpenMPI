/* NIM/Nama    : 13517020 / T. Antra Oksidian Tafly || 13517137 / Vincent Budianto
 * Date        : 28 February 2020
 * Topic       : OpenMPI - Djikstra Algorithm
 * Description : Parallel implementations of the dijkstra algorithm with OpenMPI */

// Library
// #include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/********************* Adjacency List Structure *********************/
// A structure to represent an adjacency list node
struct AdjListNode
{
  int dest;
  int cost;
  struct AdjListNode *next;
};

// A structure to represent an adjacency list
struct AdjList
{
  struct AdjListNode *head;
};

// A utility function to create a new adjacency list node
struct AdjListNode *newAdjListNode(int dest, int cost)
{
  struct AdjListNode *newNode;

  newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
  newNode->dest = dest;
  newNode->cost = cost;
  newNode->next = NULL;

  return newNode;
};

/********************* Graph Structure *********************/
// A structure to represent a graph
struct Graph
{
  int N;
  struct AdjList *array;
};

// A utility function that creates a graph of N nodes
struct Graph *createGraph(int N)
{
  int i;
  struct Graph *graph;

  graph = (struct Graph *)malloc(sizeof(struct Graph));
  graph->N = N;

  // Create an array of adjacency lists
  graph->array = (struct AdjList *)malloc(N * sizeof(struct AdjList));

  // Initialize each adjacency list as empty by making head as NULL
  for (i = 0; i < N; ++i)
  {
    graph->array[i].head = NULL;
  }

  return graph;
};

// Adds an edge to an undirected graph
void addEdge(struct Graph *graph, int src, int dest, int cost)
{
  struct AdjListNode *newNode;

  // Add an edge from source to destination
  newNode = newAdjListNode(dest, cost);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  // Add an edge from destination to source
  newNode = newAdjListNode(src, cost);
  newNode->next = graph->array[dest].head;
  graph->array[dest].head = newNode;
}

// A utility function to generate graph
void buildGraph(struct Graph *graph, int N)
{
  int cost;
  int src;
  int dest;

  for (src = 0; src < (N - 1); src++)
  {
    for (dest = (src + 1); dest < N; dest++)
    {
      // Set path cost
      cost = rand();

      if (cost > 0)
      {
        addEdge(graph, src, dest, cost);
      }
    }
  }
}

// A utility function to print the adjacency list representation of graph
void printGraph(struct Graph *graph)
{
  int n;

  for (n = 0; n < graph->N; ++n)
  {
    struct AdjListNode *pCrawl = graph->array[n].head;
    printf("\n Node %d\n head", (n + 1));
    while (pCrawl)
    {
      printf("  -->  %d (%d)", (pCrawl->dest + 1), pCrawl->cost);
      pCrawl = pCrawl->next;
    }
    printf("\n");
  }
}

/********************* Main Program *********************/
int main(int argc, char *argv[])
{
  // Set rand() seed
  // srand(13517020);
  /* total cost <= 0
     size | total
     100  |    0
     500  |    4
     1000 |   18
     5000 |  380
  */
  srand(13517137);
  /* total cost <= 0
     size | total
     100  |    0
     500  |    2
     1000 |   13
     5000 |  360
  */

  if (argc == 2)
  {
    printf("OpenMPI - Djikstra Algorithm\n\n");

    /********************* Generating Graph *********************/
    // Number of nodes in a graph
    long N = strtol(argv[1], NULL, 10);

    // Initiate graph
    struct Graph *graph = createGraph(N);

    // Build graph
    buildGraph(graph, N);

    // print the adjacency list representation of the above graph
    printGraph(graph);

    return 0;
  }
  else
  {
    printf("error: missing command line arguments\n");

    return 1;
  }
}