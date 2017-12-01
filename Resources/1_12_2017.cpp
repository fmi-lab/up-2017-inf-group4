#include <iostream>

int get_min_index(int *a, int l, int r)
{
	int min = l;
	++l;

	while (l <= r)
	{
		if (a[l] < a[min])
			min = l;

		++l;
	}
	return l;
}

void swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

void sort(int *a, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		int id = get_min_index(a, i, n - 1);
		swap(a[i], a[id]);
	}
}

int main()
{
	int a = 6;
	int&b = a, d, z;
	//int&x; -грешка
	std::cout << a << std::endl;
	++a;
	std::cout << b << std::endl;
	++b;
	std::cout << a << std::endl;

	return 0;
}