#include <iostream>
#include "pair.hpp"

int main() {
	
	{
		ft::pair<int, int> p1 = ft::make_pair(1, 2);
		ft::pair<int, int> p2(1, 2);

		std::cout << "p1 is pair(" << p1.first << ',' << p1.second << ')' << std::endl;
		std::cout << "p2 is pair(" << p2.first << ',' << p2.second << ')' << std::endl;
		std::cout << "p1 == p2 : " << ' ' << (p1 == p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 != p2 : " << ' ' << (p1 != p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 < p2 : " << ' ' << (p1 < p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 > p2 : " << ' ' << (p1 > p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 <= p2 : " << ' ' << (p1 <= p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 >= p2 : " << ' ' << (p1 >= p2 ? "TRUE" : "FALSE") << std::endl;
	}
	std::cout << "======================================" << std::endl;
	{
		ft::pair<int, int> p1 = ft::make_pair(1, 1);
		ft::pair<int, int> p2 = p1;

		std::cout << "p1 is pair(" << p1.first << ',' << p1.second << ')' << std::endl;
		std::cout << "p2 is pair(" << p2.first << ',' << p2.second << ')' << std::endl;
		std::cout << "p1 == p2 : " << ' ' << (p1 == p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 != p2 : " << ' ' << (p1 != p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 < p2 : " << ' ' << (p1 < p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 > p2 : " << ' ' << (p1 > p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 <= p2 : " << ' ' << (p1 <= p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 >= p2 : " << ' ' << (p1 >= p2 ? "TRUE" : "FALSE") << std::endl;
	}
	std::cout << "======================================" << std::endl;
	{
		ft::pair<std::string, int> p1;
		ft::pair<std::string, int> p2("B", 'B');

		p1.first = "A";
		p1.second = 'A';
		std::cout << "p1 is pair(" << p1.first << ',' << p1.second << ')' << std::endl;
		std::cout << "p2 is pair(" << p2.first << ',' << p2.second << ')' << std::endl;
		std::cout << "p1 == p2 : " << ' ' << (p1 == p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 != p2 : " << ' ' << (p1 != p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 < p2 : " << ' ' << (p1 < p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 > p2 : " << ' ' << (p1 > p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 <= p2 : " << ' ' << (p1 <= p2 ? "TRUE" : "FALSE") << std::endl;
		std::cout << "p1 >= p2 : " << ' ' << (p1 >= p2 ? "TRUE" : "FALSE") << std::endl;
	}
	return 0;
}
