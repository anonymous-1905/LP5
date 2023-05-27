#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void bfs_sequential(int **edges,int v,int sv)
{
	queue<int> pv;
	bool * visited=new bool [v];
	int i,cv;
	for(i=0;i<v;i++)
	{
		visited[i]=false;
	}
	pv.push(sv);
	visited[sv]=true;
	while(!pv.empty())
	{
		int cv=pv.front();
		pv.pop();
		cout<<" "<<cv;
		for(i=0;i<v;i++)
		{
			if(i==cv)
			{
				continue;
			}
			if(edges[cv][i]==1 && !visited[i])
			{
				pv.push(i);
				visited[i]=true;
			}
		}
		
	}
	delete [] visited;
}


void bfs_parallel(int **edges,int v,int sv)
{
	queue<int> pv;
	bool * visited=new bool [v];
	int i,cv;
	for(i=0;i<v;i++)
	{
		visited[i]=false;
	}
	pv.push(sv);
	visited[sv]=true;
	while(!pv.empty())
	{
		int cv=pv.front();
		pv.pop();
		cout<<" "<<cv;
		#pragma omp parallel for
		for(i=0;i<v;i++)
		{
			if(i==cv)
			{
				continue;
			}
			if(edges[cv][i]==1 && !visited[i])
			{
				pv.push(i);
				visited[i]=true;
			}
		}
		
	}
	delete [] visited;
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

    //Measure the performance of sequential dfs
    cout<<"sequential bfs"<<endl;
    double startSeq = omp_get_wtime();
    bfs_sequential(graph, numNodes, 0);
    double endSeq = omp_get_wtime();
    double seqDuration = endSeq - startSeq;
    
    
    //Measure the performance of parallel dfs
    cout<<"\nparallel bfs"<<endl;
    double startParallel = omp_get_wtime();
    bfs_parallel(graph, numNodes, 0);
    double endParallel = omp_get_wtime();
    double parallelDuration = endParallel - startParallel;
    
    cout << "\nSequential Bfs Time: " << seqDuration << " seconds" <<endl;
    cout << "Parallel Bfs Time: " << parallelDuration << " seconds" <<endl;
    return 0;
}
