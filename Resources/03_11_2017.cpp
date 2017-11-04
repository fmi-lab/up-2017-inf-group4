#include <iostream>

int main()
{
	{
		int num, pos, dig;
		std::cin >> num >> pos >> dig;

		int count_digs = 0;
		int temp = num;

		while (temp)//temp!=0
		{
			++count_digs;
			temp /= 10;
		}

		pos = count_digs - pos - 1;

		int pow = 1;

		while (pos--) pow *= 10;

		num -= ((num / pow) % 10)*pow;
		num += dig*pow;
		std::cout << num << std::endl;
	}

	{
		//програма, която чете едни число в десетично борйна система
		// и го отпечатва на екрана в обратен ред (за улеснение)
		// в произволна бройна система (отново за улеснение ще работи само при база 2,3,4 .. 10
		unsigned number_system = 10,num;
		std::cin >> num;

		if (num == 0)
		{
			std::cout << 0;
		}
		while (num)
		{
			std::cout << (num % number_system);
			num /= number_system;
		}
	}


	return 0;
}