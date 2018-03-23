#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>

using namespace std;

default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution <int> distribution(1, 1e4);


int* generate_tree_graph(int* graph, int n, int dim)
{
	if (n < dim-1) {
		cout << "ERROR";
		return NULL;
	}
		
	int elem_count = n*n;
	int count = 0;
	graph = new int[elem_count];
	for (int i = 0; i < n*n; i++)
	{
		graph[i] = 0;
	}
		
	for (int i = 0; i < n; i++)
	{
		graph[i * n + i] = INT_MAX;
	}
	int st = 1; 
	while (count < (n+1 / dim) )
	{
		
		for (int i = 0; i < dim; i++)
		{
			int v = (count*n+count+st);
			if (v <= (n)*(count+1)-1)
			{
				graph[v] = distribution(generator);
				graph[(st + count)*n + count] = graph[v];
			}
			
			if (dim - 1 != i)
				st++;
		}
		count++;
	}
	return graph;
}

int* generate_random_graph(int* graph, int n)
{
	int elem_count = n*n;
	int count = 0;
	graph = new int[elem_count];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == i)
				graph[i * n + i] = INT_MAX;
			else
				graph[i*n + j] = graph[j*n + i] = distribution(generator);
		}
	}
	return graph;
}

int main(int argc, char * argv[])
{
	int* graph = NULL;
	int type, n, dim;

	char* eman = NULL;
	if (argc > 1)
	{
		type = atoi(argv[1]);
		eman = argv[2];
		n = atoi(argv[3]);
		if (type == 1)
			dim = atoi(argv[4]);

	}

	if (type == 1)
		graph = generate_tree_graph(graph, n, dim);
	else
		graph = generate_random_graph(graph, n);

	FILE *matr = NULL;
	matr = fopen(eman, "wb");
	if (matr == NULL)
	{
		printf("Error opening file");
	}
	fwrite(&n, sizeof(int), 1, matr);
	fwrite(graph, sizeof(int), n*n, matr);

	fclose(matr);

}