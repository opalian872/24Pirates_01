#include <iostream>
#include <string>


//해당 함수는 게임 초기 이후로 등장하지 않기 때문에 Player 클래스에 포함하지 않고 외부 함수로 분류해 두었습니다.

void PlayerMaking(std::string& playerName, int& maxHp, int& hp, int& attack, int& defense, int& exp, int& gold, bool& playerCondition)
{
	maxHp = 200;
	hp = maxHp;
	attack = 30;
	defense = 0;
	exp = 0;
	gold = 0;
	playerCondition = true;

	std::cout << "Enter Player Name : ";
	std::cin >> playerName;
	std::cout << std::endl;
	std::cout << "Player's HP : " << hp << "/" << maxHp << std::endl;
	std::cout << "Player's attack : " << attack << std::endl;
	std::cout << "Player's defense : " << defense << std::endl;
	std::cout << "Player's exp : " << exp << std::endl;
	std::cout << "Player's gold : " << gold << std::endl;
}