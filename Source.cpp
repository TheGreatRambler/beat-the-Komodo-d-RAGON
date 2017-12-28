#include <iostream>
#include <string>
#include "item.h"
#include <vector>
#include <cctype>
#include <chrono>
#include <thread>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <algorithm>

using namespace std;

std::string nameOfFile = "save";

std::string errorMessage = "Something has occured. What a shame!";

double money = 0.00;
int difficulty = 10;
int myHealth = 100;
int exploreAmount = 0;
int buyAmount = 0;
bool debtTrue = false;

int komodoDragonHealth = 50;

std::string nameOfPerson[10] = { "Master","Captain","Chief","Lord","Maestro","Commander","Champion","Executive","Top Dog","yourName" };
std::vector <item*> inventory;
std::vector <item*> shopItems{ { new goldingots, new shoes, new sword, new apple, new brownie, new bag, new theRecursiveFruit, new hat, new pie, new car, new shoes, new dog } };

template <class T>
void print(T a) {
	std::cout << a << std::endl;
}
template <class T>
void enter(T &a) {
	std::cin >> a;
}

void loading() {
	std::cout << '-' << std::flush;
	for (int i = 0; i < 3; i++) {
		using namespace std::chrono_literals;
		std::cout << "." << std::flush;
		std::this_thread::sleep_for(1s);
	}
	std::cout << "\n";
}

void health(int a) {
	myHealth += a;
}

void debtHealthLoss() {
	if (debtTrue) {
		health(-(difficulty / 2));
	}
}

std::fstream& gotoLine(std::fstream& file, unsigned int num) {
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore((std::numeric_limits<std::streamsize>::max)() , '\n');
	}
	return file;
}

std::string exePath() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return std::string(string(buffer).substr(0, pos));
}

void save() {
	std::string saveName = "save";
	std::string path = exePath() + "\\" + saveName + ".txt";
	std::ofstream saveFile;
	saveFile.open(path, ios::out | ios::trunc);
	if (saveFile.is_open()) {
		saveFile << money << std::endl;
		saveFile << difficulty << std::endl;
		saveFile << myHealth << std::endl;
		saveFile << exploreAmount << std::endl;
		saveFile << buyAmount << std::endl;
		saveFile << nameOfPerson[9] << std::endl;
		saveFile << komodoDragonHealth << std::endl;
		saveFile << inventory.size() << std::endl;
		for (item* i : inventory) {
			saveFile << i->getName() << std::endl;
		}
		loading();
		saveFile.close();
	}
	else {
		print(errorMessage);
	}
}

void load() {
	std::string saveName = "save";
	std::string line;
	int numberOfItems = 0;
	std::string name = "Apple";
	std::string path = exePath() + "\\" + saveName + ".txt";
	fstream saveFile(path, ios::in);
	if (saveFile.is_open()) {
		for (int i = 1; i < 9; i++) {
			if (i == 1) {
				gotoLine(saveFile, i);
				saveFile >> money;
			}
			else if (i == 2) {
				gotoLine(saveFile, i);
				saveFile >> difficulty;
			}
			else if (i == 3) {
				gotoLine(saveFile, i);
				saveFile >> myHealth;
			}
			else if (i == 4) {
				gotoLine(saveFile, i);
				saveFile >> exploreAmount;
			}
			else if (i == 5) {
				gotoLine(saveFile, i);
				saveFile >> buyAmount;
			}
			else if (i == 6) {
				gotoLine(saveFile, i);
				saveFile >> nameOfPerson[9];
			}
			else if (i == 7) {
				gotoLine(saveFile, i);
				saveFile >> komodoDragonHealth;
			}
			else if (i == 8) {
				gotoLine(saveFile, i);
				saveFile >> numberOfItems;
			}

			else {
				print(errorMessage);
			}

			for (int i = 1; i < numberOfItems; i++) {
				saveFile >> name;
				for (item* i : inventory) {
					if (name == i->getName()) {
						money -= i->getPrice();
						inventory.push_back(i);
					}
				}
			}
		}
		saveFile.close();
	}
	else {
		print(errorMessage);
	}
}

std::string capitalize(std::string str) {
	std::string::iterator it(str.begin());

	if (it != str.end())
		str[0] = toupper((unsigned char)str[0]);

	while (++it != str.end())
	{
		*it = tolower((unsigned char)*it);
	}
	return str;
}

int random (int min, int max){
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do {
        x = rand(); 
    }
    while (x >= RAND_MAX - remainder);
    return min + x % n;
}

std::string nameChoice() {
	std::string name = nameOfPerson[random(0,9)];
	if (name == "yourName") {
		name = nameOfPerson[random(0,9)];
	}
	return name;
}

std::vector <item*> getShopItems() {
	std::vector <item*> shop;
	for (item* i : shopItems) {
		double chance = (double)((random(0,(shopItems.size())-1) + 1)) / 10.0;
		if (chance <= i->getChance()) {
			shop.push_back(i);
		}
	}
	return shop;
}

int main(int argc, char **argv)
{

	srand(time(NULL));
	print("Welcome to the game!");
	while (1 == 1) {

		std::string option = "Hi. I don't know what I'm doing. I'm an empty variable. Yayy.";
		print("What would you like to do, " + nameChoice() + "?");
		enter(option);

		if (option == "buy") {
			bool repeatTrue = true;
			while (repeatTrue) {
				repeatTrue = false;
				std::string choice = "Hello,how are you doing?";
				std::cout << "Welcome to Friendly Market 2.0! What would you like to purchase? You have " << money << "$." << std::endl;
				std::vector <item*> shop = getShopItems();
				for (item* i : shop) {
					std::cout << i->getName() << " - " << i->getDescription() << " - " << i->getPrice() << "$ - " << i->getPicture() << std::endl;
				}
				enter(choice);
				loading();
				for (item* i : shop) {
					if (capitalize(choice) == i->getName()) {
						money -= i->getPrice();
						inventory.push_back(i);
						buyAmount += 1;
						std::cout << "You purchased a " << i->getName() << " for " << i->getPrice() << "$. You now have " << money << "$." << std::endl;
						print("Would you like to purchase something else?");
						std::string buyTrue = "no";
						enter(buyTrue);
						if (buyTrue == "yes" || buyTrue == "yeah" || buyTrue == "yep" || buyTrue == "definitely!") {
							repeatTrue = true;
						}
						else if (buyTrue == "no" || buyTrue == "nope" || buyTrue == "nah") {
							print("Thank you for shopping at Friendly Market 2.0!");
						}
						else {
							print("Nobody likes it when you refuse to answer a honest question.");
						}
					}
				}
			}
		}
		else if (option == "explore") {
			print("You are taking a walk outside.");
			loading();

			int findOrFight = random(1,difficulty);
			if (findOrFight <= 5) {
				double chance = (double)((random(0,9) + 1)) / 10.0;
				int itemFound = random(0,(shopItems.size())-1);
				if (chance <= shopItems[itemFound]->getChance()) {
					print("You found something!");
					inventory.push_back(shopItems[itemFound]);
					std::cout << "You have found a " << shopItems[itemFound]->getName() << " on the ground." << std::endl;
					print("Congrats!");
				} else {
					print("Unfortunately, you have not found anything. It has been a uneventful day.");
				}

			} else if (findOrFight >= 6) {
				print("Oh no! A Komodo d-RAGON has been found!");
				loading();
				print("Time to fight!");
				bool defeated = false;
				while (defeated == false) {
					int enemyHealth = (komodoDragonHealth / 10) * random(1, 10);
					std::string chosenObject = "Something useful, I would suppose.";
					print("What item would you like to use to fight the Komodo d-RAGON?");
					for (item* i : inventory) {
						std::cout << i->getName() << " - " << i->getDamage() << std::endl;
					}
					enter(chosenObject);
					loading();
					for (auto hurtVec = inventory.begin(); hurtVec != inventory.end(); ++hurtVec) {
						if (capitalize(chosenObject) == (*hurtVec)->getName()) {
							int damage = ((*hurtVec)->getDamage()) * random(1, 3);
							int hurt = (difficulty * random(1, 3));
							std::cout << "Your " << (*hurtVec)->getName() << " has wounded the Komodo d-RAGON by " << damage << " health points.";
							std::cout << " In retalitation, the Komodo d-RAGON has wounded you by " << hurt << " health points.";
							enemyHealth -= damage;
							myHealth -= hurt;
							if ((*hurtVec)->keepAfterFight() == false) {
								inventory.erase(hurtVec);
							}
							else {
								//HA, HA. NOTHING
							}
							print("/n");
							break;
						}
						else {
							++hurtVec;
						}
					}

					if (enemyHealth <= 0) {
						print("congratulations! You have beat the Komodo d-RAGON!");
						defeated = true;
					}
				}
				int healthLost = -(random(1,4) * random(1,difficulty));
				std::cout << "You fought valiantly, but you have lost a LOT of health. You have lost " << -(healthLost) << " health points from the Komodo d-RAGON!" << std::endl;
				print("Better luck next time!");
			}

			health(-(random(0,difficulty)));
			exploreAmount += 1;
		}
		else if (option == "health") {
			std::cout << "You have " << myHealth << " health points.";
			print("/n");
		}
		else if (option == "eat") {
			bool repeatTrue = true;
			while (repeatTrue) {
			std::string itemToEat = "Dirt, if you're lucky...";
			print("What would you like to eat?");
			for (item* i : inventory) {
				std::cout << i->getName() << " - " << i->getDescription() << " - " << i->getRegeneration() << std::endl;
			}
			enter(itemToEat);
			loading();
			for (auto eatVec = inventory.begin(); eatVec != inventory.end(); ++eatVec) {
				if (capitalize(itemToEat) == (*eatVec)->getName()) {
					health((*eatVec)->getRegeneration());
					std::cout << "Your " << (*eatVec)->getName() << " has given you " << (*eatVec)->getRegeneration() << " health points.";
					inventory.erase(eatVec);
					print("/n");
					break;
				}
				else {
					++eatVec;
				}
			}
			print("Would you like to eat something else?");
			std::string buyTrue = "no";
			enter(buyTrue);
			if (buyTrue == "yes" || buyTrue == "yeah" || buyTrue == "yep" || buyTrue == "definitely!") {
				repeatTrue = true;
			}
			else if (buyTrue == "no" || buyTrue == "nope" || buyTrue == "nah") {
				repeatTrue = false;
				print("Ok.");
			}
			else {
				print("Nobody likes it when you refuse to answer a honest question.");
			}
			}

		}
		else if (option == "items") {
			for (item* i : inventory) {
				std::cout << i->getName() << " - " << i->getDescription() << " - " << i->getPicture() << std::endl;
			}
		}
		else if (option == "exit") {
			std::string exitTrue = "no";
			print("Do you REALLY want to exit? Yes, or no?");
			enter(exitTrue);
			if (exitTrue == "yes" || exitTrue == "yeah" || exitTrue == "yep" || exitTrue == "definitely!") {
				loading();
				break;
			}
			else if (exitTrue == "no" || exitTrue == "nope" || exitTrue == "nah") {
				loading();
				print("Ok.");
			}
			else {
				print("Nobody likes it when you refuse to answer a honest question.");
			}
		}
		else if (option == "name") {
			print("Give me a nickname, if you please.");
			enter(nameOfPerson[9]);
			loading();
		}
		else if (option == "work") {
			print("You are working at Walmart today.");
			loading();
			double earnings = random(0,50);
			std::cout << "You earned " << earnings << "$" << std::endl;
			money += earnings;
			std::cout << "You have " << money << "$" << std::endl;
			health(-(random(0,15)));
		}
		else if (option == "whatever") {
			print("You have to do better than that!");
			print("Maybe next time I'll understand.");
		}
		else if (option == "help") {
			print("Here are the available commands:");
			print("buy: purchase items");
			print("explore: go walking outside, and discover something pleasent, or something worse...");
			print("items: view your inventory");
			print("eat: have a snack");
			print("work: get some money");
			print("name: change your name");
			print("wallet: view your money");
			print("difficulty: change difficulty");
			print("health: view your health");
			print("stats: view your statistics");
			print("save: save your game");
			print("open: open your game");
			print("exit: quit the game");
		}
		else if (option == "wallet") {
			std::cout << "You have " << money << "$" << std::endl;
		}
		else if (option == "stats") {
			std::cout << "You have explored " << exploreAmount << " times." << std::endl;
			std::cout << "You have bought " << exploreAmount << " items." << std::endl;
		}
		else if (option == "save") {
			save();
		}
		else if (option == "open") {
			load();
		}
		else if (option == "difficulty") {
			std::string choice = "Man, if only it were easier...";
			print("Would you like to play easy, medium, or hard?");
			enter(choice);
			if (choice == "easy") {
				if (myHealth >= 100) {
					myHealth = 100;
					difficulty = 10;
					komodoDragonHealth = 50;
					print("Okey dokey.");
				}
				else {
					print("It's too late to change. Get some more health, and I'll consider it.");
				}
			} else if (choice == "medium") {
				if (myHealth >= 75) {
					difficulty = 20;
					myHealth = 75;
					komodoDragonHealth = 60;
					print("Okey dokey.");
				}
				else {
					print("It's too late to change. Get some more health, and I'll consider it.");
				}
			} else if (choice == "hard") {
				if (myHealth >= 50) {
					difficulty = 35;
					myHealth = 50;
					komodoDragonHealth = 75;
					print("Okey dokey.");
				}
				else {
					print("It's too late to change. Get some more health, and I'll consider it.");
				}
			} else {
				print("Sorry, I couldn't hear that. My ears are bad.");
			}
		}
		else {
			print("You can't do that. We run a tight boat here. There isn't any anarchy here. You should be ashamed. How can you live this way? Your family should have disowned you long ago.");
		}

		if (myHealth <= 0) {
			std::string exitTrue = "no";
			loading();
			print("You didn't feed yourself. You have died. Congratulations for making it this far.");
			loading();
			print("Would you like to play again?");
			enter(exitTrue);
			if (exitTrue == "yes" || exitTrue == "yeah" || exitTrue == "yep" || exitTrue == "definitely!") {
				loading();
				print("Yay. I'm excited.");
			}
			else if (exitTrue == "no" || exitTrue == "nope" || exitTrue == "nah") {
				loading();
				break;
			}
			else {
				print("Nobody likes it when you refuse to answer a honest question.");
				loading();
				break;
			}

		}

		if (money < 0) {
			print("You're in debt. you should probably do something about that...");
			debtTrue = true;
		} else if (money >= 0) {
			debtTrue = false;
		}

		debtHealthLoss();
	}
}
