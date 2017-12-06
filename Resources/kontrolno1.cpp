#include <iostream>
#include <iomanip>

const double eps = 1e-4;

double mabs(double n)
{
	return n < 0 ? -n : n;
}

bool is_zero(double n)
{
	return mabs(n) < eps;
}


void read_array(double arr[], unsigned n)
{
	for(unsigned i = 0; i < n; ++i)
		std::cin >> arr[i];
}

void print(double arr[], unsigned n)
{
	//отпечатва само 3 знака след десетичката запетая
	std::cout << std::fixed << std::setprecision(3);

	for(unsigned i = 0; i < n; ++i)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

double sum_array(double arr[], unsigned n)
{
	double sum = 0.0;
	for(unsigned i = 0; i < n; ++i)
		sum += arr[i];
	
	return sum;
}

void swap(double& a, double& b)
{
	double t = a;
	a = b;
	b = t;
}

unsigned get_min_index(double a[], unsigned begin, unsigned n)
{
	unsigned min = begin;
	
	for(unsigned i = begin + 1; i < n; ++i)
	{
		if(a[min] > a[i])
			min = i;
	}
	
	return min;
}

void sort(double a[], unsigned n)
{
	for (unsigned i = 0; i < n - 1; ++i)
	{
		unsigned id = get_min_index(a, i, n);
		swap(a[i], a[id]);
	}
}

double calc_det(double a1, double a2, double b1, double b2)
{
	return (a1 * b2) - (b1 * a2); 
}

void problem1()
{
	double a[3], b[3];
	
	do{
		read_array(a, 3);
	}while(is_zero(a[0]) && is_zero(a[1]));
	
	do{
		read_array(b, 3);
	}while(is_zero(b[0]) && is_zero(b[1]));

	double A = calc_det(a[0], a[1], b[0], b[1]);

	if(is_zero(A))
	{
		if (is_zero(calc_det(a[1], a[2], b[1], b[2])))
			std::cout << "coincide" << std::endl;
		else
			std::cout << "parallel" << std::endl;
	}
	else
	{
		double B = calc_det(a[1], a[2], b[1], b[2]);
		double C = calc_det(a[2], a[0], b[2], b[0]);
		double x = B / A;
		double y = C / A;

		std::cout << std::fixed << std::setprecision(3);
		std::cout << x << " " << y << std::endl;
	}
}

unsigned cnt_digits(unsigned n)
{
	if(n == 0) return 1;
	
	unsigned res = 0;
	
	while(n != 0)
	{
		++res;
		n /= 10;
	}
	return res;
}

unsigned mpow(unsigned x, unsigned n)
{
	unsigned res = 1;
	while(n--)
		res *= x;
	
	return res;
}

unsigned digit_on_pos(unsigned number, unsigned pos)
{
	return ( number / mpow(10, pos - 1) ) % 10;
}

void right_to_left(unsigned number, unsigned pos, unsigned digit)
{
	unsigned p = mpow(10, pos - 1);
	number -= p * digit_on_pos(number, pos);
	number += p * digit;
	
	std::cout << number << std::endl;
}

void left_to_right(unsigned number, unsigned pos, unsigned digit)
{
	//изразявам(трансформирам) позицията
	//погледната отляво надясно
	//за да изпозлвам предното решение
	unsigned digs = cnt_digits(number);
	pos = digs - pos + 1;
	
	right_to_left(number, pos, digit);
}

void problem2()
{
	unsigned number, pos, digit;
	std::cin >> number >> pos >> digit;

	left_to_right(number, pos, digit);
}

unsigned read_size(unsigned limit)
{
	unsigned n;
	do
	{
		std::cin >> n;
	}while(n >= limit || n == 0);
	
	return n;
}

const unsigned SIZE = 5000;

void problem3()
{
	double arr[SIZE];
	unsigned n = read_size(SIZE);
	
	for(unsigned i = 0; i < n; ++i)
	{
		do
		{
			std::cin >> arr[i];
		}while( mabs(arr[i]) > 1e5);
	}
	
	double average = sum_array(arr, n) / n;
	
	unsigned cnt = 1;
	unsigned read = 1;  // индекс за четене в масива
	unsigned write = 1; // индекс за запис в масива
	
	while(read < n)
	{
		if(!is_zero(arr[read - 1] - arr[read]))
		{
			if (cnt > 2)
			{
				write -= cnt;
				arr[write] = average;
				++write;
			}
			cnt = 1;
		}
		else
		{
			++cnt;
		}
		arr[write] = arr[read];
		++read;
		++write;
	}
	if (cnt > 2)
	{
		write -= cnt;
		arr[write] = average;
		++write;
	}

	n = write;
	print(arr, n);
}

const unsigned MATRIX_SIZE = 200;

void read_matrix(double mat[][MATRIX_SIZE], unsigned n, unsigned m)
{
	for(unsigned i = 0; i < n; ++i)
		read_array(mat[i], m);
}

bool equal_arrays(double arr1[], double arr2[], unsigned m)
{
	for(unsigned i = 0; i < m; ++i)
	{
		if(!is_zero(arr1[i] - arr2[i]))
			return false;
	}
	return true;
}

void init_false(bool mark[], unsigned n)
{
	for (unsigned i = 0; i < n; ++i)
		mark[i] = false;
}

void problem4a()
{
	double mat[MATRIX_SIZE][MATRIX_SIZE];
	unsigned n = read_size(MATRIX_SIZE);
	unsigned m = read_size(MATRIX_SIZE);

	read_matrix(mat, n, m);

	bool mark[MATRIX_SIZE];

	bool two_equal_rows = false;

	for (unsigned r1 = 0; r1 < n; ++r1)
	{
		for (unsigned r2 = r1 + 1; r2 < n; ++r2)
		{
			bool match = true;
			init_false(mark, m);

			for (unsigned pos1 = 0; pos1 < m && match; ++pos1)
			{
				match = false;

				for (unsigned pos2 = 0; pos2 < m && !match; ++pos2)
				{
					if (!mark[pos2] && is_zero(mat[r1][pos1] - mat[r2][pos2]))
					{
						mark[pos2] = match = true;
					}
				}
			}

			if (match)
			{
				two_equal_rows = true;
				print(mat[r1], m);
				print(mat[r2], m);
				std::cout << std::endl;
			}
		}
	}

	if (two_equal_rows == false)
		std::cout << "“No such rows" << std::endl;
}

//И в двете решения на 4б си чупя(променям) входните данни, което е лоша практика
void problem4b_1()
{
	double mat[MATRIX_SIZE][MATRIX_SIZE];
	unsigned n = read_size(MATRIX_SIZE),
			 m = read_size(MATRIX_SIZE);

	read_matrix(mat, n, m);
	
	for(unsigned i = 0; i < n; ++i)
		sort(mat[i], m);
	
	bool two_equal_rows = false;
	
	for(unsigned i = 0; i < n; ++i)
	{
		for(unsigned j = i + 1; j < n; ++j)
		{
			if(equal_arrays(mat[i], mat[j], m))
			{
				std::cout << i + 1 << " " << j + 1 << std::endl;
				two_equal_rows = true;
			}
		}
	}
	if(two_equal_rows == false)
		std::cout << 0 << std::endl;
}

void problem4b_2()
{
	double mat[MATRIX_SIZE][MATRIX_SIZE];
	unsigned n = read_size(MATRIX_SIZE),
			 m = read_size(MATRIX_SIZE);
	
	read_matrix(mat, n, m);
	
	bool two_equal_rows = false;
	
	for(unsigned r1 = 0; r1 < n; ++r1)
	{
		for(unsigned r2 = r1 + 1; r2 < n; ++r2)
		{
			bool match = true;
			
			for(unsigned pos1 = 0; pos1 < m && match; ++pos1)
			{
				match = false;
				
				for(unsigned pos2 = pos1; pos2 < m && !match; ++pos2)
				{
					if(is_zero(mat[r1][pos1] - mat[r2][pos2]))
					{
						match = true;
						swap(mat[r2][pos1], mat[r2][pos2]);
						//гарантираме си, че след позиция "pos1" в ред "r2"
						//имаме само "необработени" елементи
					}
				}
			}
			
			if(match)
			{
				two_equal_rows = true;
				std::cout << r1 + 1 << " " << r2 + 1 << std::endl;
			}
		}
	}
	
	if(two_equal_rows == false)
		std::cout << 0 << std::endl;
}

int main()
{
	problem1();
	return 0;
}
