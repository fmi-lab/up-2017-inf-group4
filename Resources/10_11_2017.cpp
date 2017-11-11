#include <iostream>


int main()
{
	{
		int a = 5, b = -10;

		{
			int t = a;
			a = b;
			b = t;
		}
		{
			a = a + b;
			b = a - b;
			a = a - b;
		}
		{
			a ^= b;
			b ^= a;
			a ^= b;
		}
	}
	{
		int number;
		std::cin >> number;
		int temp = 1;
		int newNumber = 0;

		while (number > 0)
		{
			int lastDigit = number % 10;
			number /= 10;

			if (lastDigit % 2 == 0)
			{
				newNumber += lastDigit*temp;
				temp *= 10;
			}
		}
		std::cout << newNumber;

	}

	return 0;
}