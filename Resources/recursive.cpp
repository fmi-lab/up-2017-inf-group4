#include <iostream>
#include <random>
#include <algorithm>

/*

recursive(аргументи1)
{
	

дъно => if(израз1)
	    {
			return израз2
		}

	..........

	recursive(аргументи2)

	.........................


	recursive(аргументи3)

	и т.н.
}

*/

unsigned fib(unsigned n)
{
	/*if (n < 2) return n;

	return fib(n - 1) + fib(n - 2);*/

	return n < 2 ? n : fib(n - 1) + fib(n - 2);
}

unsigned fact_it(unsigned n)
{
	unsigned res = 1;

	while (n)
	{
		res *= n;
		--n;
	}

	return res;
}

unsigned fact(unsigned n)
{
	/*if (n == 0) return 1;

	return n*fact(n - 1);*/

	return n == 0 ? 1 : n * fact(n - 1);
}

int sum_it(const int *begin, const int *end)
{
	int sum = 0;

	while (begin < end)
	{
		sum += *begin;
		++begin;
	}

	return sum;
}

int sum(const int *begin, const int *end)
{
	/*if (begin >= end) return 0;

	return *begin + sum(begin + 1, end);*/

	return begin >= end ? 0 : *begin + sum(begin + 1, end);
}

int get_min_element_index_it(const int *begin, const int *end)
{
	int min_element_index = 0;

	for (const int *i = begin + 1; i < end; ++i)
	{
		/*begin[min_element_index] == *(begin + min_element_index)*/

		if (*i < *(begin + min_element_index))
			min_element_index = i - begin;
	}
	
	return min_element_index;
}

void selection_sort_it(int *begin, int *end)
{
	for (int *p = begin; p < end; ++p)
	{
		/*int min_element_index = get_min_element_index_it(begin, end);
		std::swap(*p, *(begin + min_element_index));*/
		std::swap(*p, *(begin + get_min_element_index_it(begin, end)));
	}
}

int get_min_element_index(const int *begin, const int *end)
{
	if (begin  >= end)    return -1;

	int min_element_index = get_min_element_index(begin + 1, end) + 1;

	/*if (min_element_index == -1 || *begin < min_element_index) 
		return 0;

	return min_element_index;*/

	return *begin < *(begin + min_element_index) ? 0 : min_element_index;
}

void selection_sort(int *begin, int *end)
{
	if (begin >= end) return;

	std::swap(*begin, *(begin + get_min_element_index(begin, end)));

	selection_sort(begin + 1, end);
}

int product_it(const int *begin, const int *end)
{
	int prod = 1;

	while (begin < end && prod)
	{
		prod *= *begin;
		++begin;
	}

	return prod;
}

int product(const int *begin, const int *end)
{
	/*if (begin >= end) return 1;

	return *begin + prouct(begin + 1, end);*/

	return begin >= end ? 1 : *begin * product(begin + 1, end);
}

int accum_it(const int *begin, const int *end, int null_value, int(*pF)(const int, const int))
{
	while (begin < end)
	{
		null_value = pF(null_value, *begin);

		++begin;
	}

	return null_value;
}

int accum(const int *begin, const int *end, int null_value, int(*pF)(const int, const int))
{
	/*if (begin >= end) return null_value;

	return accum(begin + 1, end, pF(null_value, *begin), pF);*/

	return begin >= end ? null_value : accum(begin + 1, end, pF(null_value, *begin), pF);
}

int op_sum(const int lhs, const int rhs)
{
	return lhs + rhs;
}

int op_product(const int lhs, const int rhs)
{
	return lhs * rhs;
}

int op_min(const int lhs, const int rhs)
{
	return lhs < rhs ? lhs : rhs;
}

int op_max(const int lhs, const int rhs)
{
	return lhs > rhs ? lhs : rhs;
}

void print(const int *begin, const int *end)
{
	if (begin >= end)
	{
		std::cout << std::endl;
		return;
	}

	std::cout << *begin << " ";
	print(begin + 1, end);
}

void init(int *begin, int *end)
{
	if (begin >= end) return;

	*begin = rand() % 101;

	init(begin + 1, end);
}

const int row = 10;
const int col = 10;
char lab[row][col + 1] = { ".*........",
						   ".*..***...",
						   ".****.*...",
						   "......*.*.",
						   "......*.*.",
						   "........*.",
						   ".********.",
						   ".*..*.....",
						   ".**.*.****",
						   "....*....." };


int main()
{
	const int size = 16;
	int arr[size];
	int *end = arr + size;

	init(arr, end);
	print(arr, end);
	std::cout << sum(arr, end) << std::endl;
	std::cout << sum_it(arr, end) << std::endl;
	std::cout << product(arr, end) << std::endl;
	std::cout << product_it(arr, end) << std::endl;
	
	std::cout << accum(arr, end, 0, op_sum) << std::endl;
	std::cout << accum(arr, end, 1, op_product) << std::endl;
	std::cout << accum(arr, end, 100000, op_min) << std::endl;
	std::cout << accum(arr, end, -100000, op_max) << std::endl;
	std::cout << accum(arr + 1, end, *arr, op_min) << std::endl;
	std::cout << accum(arr + 1, end, *arr, op_max) << std::endl;
	selection_sort(arr, end);
	print(arr, end);

	return 0;
}