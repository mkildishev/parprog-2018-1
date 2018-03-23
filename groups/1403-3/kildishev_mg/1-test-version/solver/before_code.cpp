#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <omp.h>
void dijksta_alg(int* graph, int n, int start);
void write_in_file(int* graph, int n,double time, const char* name)
{
	FILE *matr = NULL;
	matr = fopen(name, "wb");
	if (matr == NULL)
	{
		printf("Error opening file");
	}
	fwrite(&n, sizeof(int), 1, matr);
	fwrite(graph, sizeof(int), n, matr);
	fwrite(&time, sizeof(double), 1, matr);

	fclose(matr);
}

int* read_from_file(const char * a, int& t)
{

	FILE *matr = NULL;
	matr = fopen(a, "rb");
	int n;

	fread(&n, sizeof(n), 1, matr);
	t = n;
	int* graph = new int[n*n];

	fread(graph, sizeof(int), n*n, matr);
	fclose(matr);

	return graph;
}

int main(int argc, char * argv[])
{
	char* eman = NULL;
	char* pans = NULL;
	char* tans = NULL;
	int st;
	if (argc > 1)
	{
		eman = argv[1];
		pans = argv[2];
		st = atoi(argv[3]);

	}
	int* graph = NULL;
	int n = 0;
	graph = read_from_file(eman, n);

	for (int k = 0; k < n; k++)
	{
		for (int m = 0; m < n; m++)
			std::cout << graph[(k*(n)) + m] << " ";

		std::cout << "\n";
	}
	std::cout << "\n";
	double time = omp_get_wtime();
	dijksta_alg(graph, n, st);
	time = omp_get_wtime() - time;

	int* ans = new int[n];

	for (int i = 0; i < n; i++)
	{
		ans[i] = graph[i*(n+1)];
		std::cout << graph[i*(n+1)] << " ";
	}
	
	write_in_file(ans, n,time, pans);
}

