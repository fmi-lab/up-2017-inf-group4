#include <iostream>

void print(unsigned long long x)
{
	std::cout << ((x>>24)&(0xFF)) << ".";
	std::cout << ((x >> 16)&(0xFF)) << ".";
	std::cout << ((x >> 8)&(0xFF)) << ".";
	std::cout << (x & 0xFF);
}

int main()
{
	unsigned long long IP=0,offset,input;

	std::cin >> input;
	IP |= (input << 24);

	std::cin >> input;
	IP |= (input << 16);

	std::cin >> input;
	IP |= (input << 8);

	std::cin >> input;
	IP |= input;
	
	std::cin >> offset;

	std::cout << "IP" << std::endl;
	print(IP);
	std::cout<<"/"<<offset<< std::endl;
	offset = 32 - offset;

	unsigned long long netmask = ~(0ULL);
	netmask ^= (1ULL << offset) - 1;

	unsigned long long address = (IP&netmask);
	std::cout << "address" << std::endl;
	print(address);
	std::cout << std::endl;

	std::cout << "netmask" << std::endl;
	print(netmask);
	std::cout << std::endl;

	unsigned long long broadcast = (IP | (~netmask));
	std::cout << "broadcast" << std::endl;
	print(broadcast);
	std::cout << std::endl;
}