#include <iostream>
#include <algorithm>

int problem1()
{
	int n;
	std::cin >> n;

	if (n < 0)
		std::cout << "error" << std::endl;
	else if (n < 3)
		std::cout << "yes" << std::endl;
	
	else
	{
		int a, b, c;
		std::cin >> a >> b;
		n -= 2;

		while (n--)
		{
			std::cin >> c;

			if ((b >= a&&b >= c) || (b <= a&&b <= c))
			{
				a = b;
				b = c;
			}
			else
			{
				std::cout << "no" << std::endl;
				return 0;
			}
		}
		std::cout << "yes" << std::endl;
	}
	return 0;
}

int problem2()
{
	unsigned n,left_bit=1,count=0;
	bool one_zero = 1;
	std::cin >> n;

	while (n >= left_bit)
		left_bit <<= 1;//умножение по 2

	left_bit >>= 1;//деление на 2

	//n&1 -> true (n is odd) false (n is even)

	while (left_bit)
	{
		if (n&left_bit)//текущия бит е 1
		{
			count = (one_zero ? count + 1 : 1);
			one_zero = 1;

			if ((count & 1) == 0)
				n &= (~left_bit);//правим текущич бит 0
		}
		else
		{
			count = (one_zero ? 1 :count + 1);
			one_zero = 0;
			if ((count & 1) == 0)
				n |= left_bit;//правим текущич бит 1
		}

		left_bit >>= 1;
	}
	std::cout << n << std::endl;

	return 0;
}

#define TO_STR(x) #x

int problem3()
{
	const bool attack = true;
	const bool defend = !attack;

	int tokens = 0;

	const int player_default_damage = 10,
			  player_default_armor = 25,
			  player_default_luck = 5,
			  player_default_magic = 5,
			  player_default_health = 100,

			  monster_default_health = 50,
			  monster_default_damage = 5,
			  monster_default_armor = 5,
			  monster_default_luck = 0,
			  monster_level_experience = 2;

	int player_health_cap = player_default_health;

	int level = 0;
	char ch;

	int player_health = player_default_health,
		player_damage = player_default_damage,
		player_armor = player_default_armor,
		player_luck = player_default_luck,
		player_magic = player_default_magic;

	while (true)
	{
		std::cout << TO_STR(level) << " " << level << std::endl;

		int monster_health = monster_default_health + (level*monster_level_experience),
			monster_damage = monster_default_damage + (level*monster_level_experience),
			monster_armor =  monster_default_armor + (level*monster_level_experience),
			monster_luck =   monster_default_luck + (level*monster_level_experience);

		while (true)
		{
			std::cin >> ch;

			switch (ch)
			{
			case 'I':
				std::cout << TO_STR(player_health) << " " << player_health << std::endl;
				std::cout << TO_STR(player_damage) << " " << player_damage << std::endl;
				std::cout << TO_STR(player_armor) << " " << player_armor << std::endl;
				std::cout << TO_STR(player_luck) << " " << player_luck << std::endl;
				std::cout << TO_STR(player_magic) << " " << player_magic << std::endl;
				std::cout << std::endl;
				std::cout << TO_STR(monster_health) << " " << monster_health << std::endl;
				std::cout << TO_STR(monster_damage) << " " << monster_damage << std::endl;
				std::cout << TO_STR(monster_armor) << " " << monster_armor << std::endl;
				std::cout << TO_STR(monster_luck) << " " << monster_luck << std::endl;
				break;
			case 'A':
				ch = rand() % 2;
				std::cout << "monster" << " " <<(ch==attack?"attack":"defend")<< std::endl;

				if (ch == attack)
				{
					monster_health -= ((rand() % 101) < player_luck ? 2 : 1)*player_damage;
					player_health -= ((rand() % 101) < monster_luck ? 2 : 1)*monster_damage;
				}
				else
				{
					if ((rand() % 101) > monster_luck)
						monster_health -= ((rand() % 101)<player_luck ? 2 : 1)*((player_damage*(100 - std::max(100,monster_armor / 2)))/100);
				}
				break;
			case 'D':
				ch = rand() % 2;
				std::cout << "monster" << " " << (ch==attack ? "attack" : "defend") << std::endl;

				if (ch == attack)
				{
					if ((rand() % 101) > player_luck)
						player_health -= ((rand()%101)<monster_luck?2:1)*((monster_damage*(100 - std::max(100,player_armor / 2)))/100);
					else
					{
						monster_damage /= 2;
						std::cout << "successful protection" << std::endl;
						std::cout << TO_STR(monster_damage) << " " << monster_damage << std::endl;
					}
				}

				break;
			case 'P':
				if (player_magic)
				{
					--player_magic;

					player_health =player_health_cap;
				}
				break;
			case 'X':
				return 0;
			default:
				std::cout << "Invalid command" << std::endl;
				std::cout << "I - show stats" << std::endl;
				std::cout << "A - attack" << std::endl;
				std::cout << "D - defend" << std::endl;
				std::cout << "P - Potion" << std::endl;
				std::cout << "X - exit" << std::endl;
				break;
			}
			if (player_health <= 0)
			{
				std::cout << "you died" << std::endl;
				tokens += level;
				level = 0;
				break;
			}
			else if(monster_health<=0)
			{
				std::cout << "monster died" << std::endl;
				if (rand() % 2)
				{
					++player_magic;
					std::cout << "you win magic potion" << std::endl;
				}
				std::cout << "choose five skills" << std::endl;
				std::cout << "H, A, D or L" << std::endl;
				int n = 5;
				while (n--)
				{
					do
					{
						std::cin >> ch;
					} while (ch != 'H' && ch != 'D' && ch != 'A' && ch != 'L');

					if (ch == 'H') ++player_health_cap;
					else if (ch == 'D') ++player_damage;
					else if (ch == 'A') ++player_armor;
					else ++player_luck;
				}

				player_health = player_health_cap;
				++level;
				break;
			}
			std::cout << TO_STR(player_health) << " " << player_health << std::endl;
			std::cout << TO_STR(monster_health) << " " << monster_health << std::endl;
			std::cout << std::endl;
		}

		if (level==0)
		{
			if (tokens / 5 < 1)
				std::cout << "you need to buy a new token" << std::endl;
			
			else
			{
				std::cout << "you are entitled to free play" << std::endl;
				tokens -= 5;
			}
			std::cout << "Y or N" << std::endl;

			do
			{
				std::cin >> ch;

				if (ch == 'N') return 0;

			} while (ch != 'Y');
		}
	}

	return 0;
}

int main()
{
	return problem2();
}