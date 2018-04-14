#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ostream>
#include <algorithm>
#include <vector>
#include <omp.h>

void dijksta_alg(int* graph,int n, int start, int thread_count)
{
	std::vector<int> min_pret(n);
	graph[start*n+start] = 0;
	bool* v = new bool[n];
	for (int i = 0; i < n; i++)
		v[i] = false;
	int cur = start, next_cur = start;
	int count = 0;
	int temp_min;
	while (count < n)
	{
		temp_min = INT_MAX;

		cur = next_cur;

		#pragma omp parallel for num_threads(thread_count) schedule(guided)
			for (int i = 0; i < n; i++)
			{
				if ((cur != i) && (graph[cur*n + i] != 0) && !v[i])
				{
					if (graph[i*n + i] > graph[cur*n + i] + graph[cur*n + cur])
						graph[i*n + i] = graph[cur*n + i] + graph[cur*n + cur];
				}
				if (!v[i])
					min_pret[i] = graph[i*n + i];

			}
			min_pret[cur] = INT_MAX;
			next_cur = std::min_element(min_pret.begin(), min_pret.end()) - min_pret.begin();
			count++;
			v[cur] = true;
	}
}