#include <ctime>
#include <iostream>

#include "Geometry.hpp"

double branching_smallest_of_3(double arr[])
{
	if (arr[0] < arr[1])
	{
		if (arr[0] < arr[2]) return arr[0];
		else return arr[2];
	}
	else
	{
		if (arr[1] < arr[2]) return arr[1];
		else return arr[2];
	}
}

int ret[] = {0, 2, 1, 1, 0, 2, 0};
double non_branching_smallest_of_3(double arr[])
{
	int ie1 = arr[0] < arr[1];
	int ie2 = arr[1] < arr[2];
	int ie3 = arr[2] < arr[0];
	int ie = (ie1 << 2) | (ie2 << 1) | ie3;
	return arr[ret[ie]];
}

int main()
{
	float a = 1.0;
	std::cout << (a + FLT_EPSILON > a) << std::endl;
	std::cout << (100 * a + FLT_EPSILON > 100 * a);
	getchar();
	geo::triangle t;
	t.a.x = 1.1f;
	t.b.x = 3.1f;
	t.c.x = 2.1f;
	std::cout << geo::tri_minx(t);
	getchar();
	std::cout << "mofo" << std::endl;
	clock_t begin = clock();
	srand(0);
	for(int i = 0; i < 10000000; i++)
	{
		double arr[3];
		arr[0]  = (rand() % 1000) / 10.0;
		arr[1]  = (rand() % 1000) / 10.0;
		arr[2]  = (rand() % 1000) / 10.0;
		double res = non_branching_smallest_of_3(arr);
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << elapsed_secs << std::endl;
	std::cout << "mofo" << std::endl;
	begin = clock();
	srand(0);
	for(int i = 0; i < 10000000; i++)
	{
		double arr[3];
		arr[0]  = (rand() % 1000) / 10.0;
		arr[1]  = (rand() % 1000) / 10.0;
		arr[2]  = (rand() % 1000) / 10.0;
		double res = non_branching_smallest_of_3(arr);
	}
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << elapsed_secs << std::endl;
	getchar();
	return 0;
}
