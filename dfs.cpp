#include <iostream>
#include <omp.h>

using namespace std;

void dfs_sequential(int **edges,int v,int sv,int* visitedv)
{
	cout << "Node " << sv << " is visited." << endl;
	visitedv[sv]=1;
	for(int i=0;i<v;i++)
	{
		if(i==sv)
		{
			continue;
		}
		if(edges[sv][i]==1)
		{
			if(visitedv[i]==1)
			{
				continue;
			}	
			dfs_sequential(edges,v,i,visitedv);
		}
	}
	
}
void dfs_parallel(int **edges,int v,int sv,int* visitedv)
{
	cout << "Node " << sv << " is visited." << endl;
	visitedv[sv]=1;
	#pragma omp parallel for
	for(int i=0;i<v;i++)
	{
		if(i==sv)
		{
			continue;
		}
		if(edges[sv][i]==1)
		{
			if(visitedv[i]==1)
			{
				continue;
			}	
			dfs_parallel(edges,v,i,visitedv);
		}
	}
	
}
int main() {
    int numNodes;
    cout << "Enter the number of nodes in the graph: ";
    cin >> numNodes;

    // Create a dynamically allocated 2D array for the graph
    int** graph = new int*[numNodes];
    for (int i = 0; i < numNodes; i++) {
        graph[i] = new int[numNodes];
    }

    // Initialize the graph
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graph[i][j] = 0;  // Initialize all elements to 0
        }
    }

    // Take input for the graph
    int numEdges;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges (format: node1 node2):" << endl;
    for (int i = 0; i < numEdges; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        graph[node1][node2] = 1;
        graph[node2][node1] = 1;  // Assuming an undirected graph
    }

    // Create a visited array to keep track of visited nodes
    int* visited=new int[numNodes];
    for(int i=0;i<numNodes;i++)
    {
	visited[i]=0;
    }
    
    //Measure the performance of sequential dfs
    cout<<"sequential dfs"<<endl;
    double startSeq = omp_get_wtime();
    dfs_sequential(graph, numNodes, 0, visited);
    double endSeq = omp_get_wtime();
    double seqDuration = endSeq - startSeq;
    
    for(int i=0;i<numNodes;i++)
    {
	visited[i]=0;
    }
    
    //Measure the performance of parallel dfs
    cout<<"\nparallel dfs"<<endl;
    double startParallel = omp_get_wtime();
    dfs_parallel(graph, numNodes, 0, visited);
    double endParallel = omp_get_wtime();
    double parallelDuration = endParallel - startParallel;
    
    cout <<endl;

    cout << "Sequential Bubble Sort Time: " << seqDuration << " seconds" <<endl;
    cout << "Parallel Bubble Sort Time: " << parallelDuration << " seconds" <<endl;
    
/*

    // Clean up dynamically allocated memory
    for (int i = 0; i < numNodes; i++) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] visited;
*/
    return 0;
}

