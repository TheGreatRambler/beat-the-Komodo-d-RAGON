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
#include <cwchar>
#include <windows.h>
#include <math.h>

using namespace std;

std::string nameOfFile = "save";

std::string errorMessage = "Something has occured. What a shame!";

double money = 0.00;
int difficulty = 10;
int myHealth = 100;
int exploreAmount = 0;
int buyAmount = 0;
int komododragonkillamount = 0;
bool debtTrue = false;
int healthamounttillrunaway = 10;
int strength = 5;
int numoftimescheatingstore = 0;
int totalPoints = 0;
int numoftimescheatingtillkickedout = 10;

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

void changeFontInfo() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_BOLD;
	std::wcscpy(cfi.FaceName, L"Courier New");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void loading() {
	for (int i = 0; i < 3; i++) {
		std::cout << "." << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << "\n";
}

void calctotalpoints() {
	totalPoints = exploreAmount + buyAmount + (int)(myHealth / 10) + komododragonkillamount * 5 * difficulty - numoftimescheatingstore * 3;
}

void health(int a) {
	myHealth += a;
}

void debtHealthLoss() {
	if (debtTrue) {
		health(-(round(difficulty * -money / 50)));
	}
}

std::fstream& gotoLine(std::fstream& file, unsigned int num) {
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}
	return file;
}

std::string exePath() {
	std:string file_path = __FILE__;
	std::string dir_path = file_path.substr(0, file_path.rfind("\\"));
	return dir_path;
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
		saveFile << komododragonkillamount << std::endl;
		saveFile << healthamounttillrunaway << std::endl;
		saveFile << nameOfPerson[9] << std::endl;
		saveFile << komodoDragonHealth << std::endl;
		saveFile << inventory.size() << std::endl;
		saveFile << numoftimescheatingstore << std::endl;
		for (item* i : inventory) {
			saveFile << i->getName() << std::endl;
		}
		loading();
		saveFile.close();
		std::cout << "Your save file is saved at " << path << std::endl;
	}
	else {
		print(errorMessage);
	}
}

void load() {
	inventory.clear();
	std::string saveName = "save";
	std::string line;
	int numberOfItems = 0;
	std::string name = "Apple";
	std::string path = exePath() + "\\" + saveName + ".txt";
	fstream saveFile(path, ios::in);
	if (saveFile.is_open()) {
		for (int i = 1; i < 10; i++) {
			if (i == 1) {
				gotoLine(saveFile, i) >> money;
			}
			else if (i == 2) {
				gotoLine(saveFile, i) >> difficulty;
			}
			else if (i == 3) {
				gotoLine(saveFile, i) >> myHealth;
			}
			else if (i == 4) {
				gotoLine(saveFile, i) >> exploreAmount;
			}
			else if (i == 5) {
				gotoLine(saveFile, i) >> buyAmount;
			}
			else if (i == 6) {
				gotoLine(saveFile, i) >> komododragonkillamount;
			}
			else if (i == 7) {
				gotoLine(saveFile, i) >> healthamounttillrunaway;
			}
			else if (i == 8) {
				gotoLine(saveFile, i) >> nameOfPerson[9];
			}
			else if (i == 9) {
				gotoLine(saveFile, i) >> komodoDragonHealth;
			}
			else if (i == 10) {
				gotoLine(saveFile, i) >> numberOfItems;
			}
			else if (i == 11) {
				gotoLine(saveFile, i) >> numoftimescheatingstore;
			}

			for (int i = 12; i < numberOfItems; i++) {
				saveFile >> name;
				for (item* i : inventory) {
					if (name == i->getName()) {
						inventory.push_back(i);
					}
				}
			}
		}
		saveFile.close();
		print("File opened. Variables initialized.");
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

int random(int min, int max) {
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);
	return min + x % n;
}

std::string nameChoice() {
	std::string name = nameOfPerson[random(0, 9)];
	if (name == "yourName") {
		name = nameOfPerson[random(0, 9)];
	}
	return name;
}

std::vector <item*> getShopItems() {
	std::vector <item*> shop;
	for (item* i : shopItems) {
		double chance = (double)((random(0, (shopItems.size()) - 1) + 1)) / 10.0;
		if (chance <= i->getChance()) {
shop.push_back(i);
		}
	}
	return shop;
}

bool eatItem(std::string item) {
	bool theitemexists = false;
	for (auto eatVec = inventory.begin(); eatVec != inventory.end(); ++eatVec) {
		if (capitalize(item) == (*eatVec)->getName()) {
			theitemexists = true;
			health((*eatVec)->getRegeneration());
			inventory.erase(eatVec);
			break;
		}
	}
	return theitemexists;
}

int main(int argc, char **argv)
{

	srand(time(NULL));
	changeFontInfo();
	print("Welcome to the game! Enter 'help' to learn the commands.");
	while (1 == 1) {

		std::string option = "Hi. I don't know what I'm doing. I'm an empty variable. Yayy.";
		print("What would you like to do, " + nameChoice() + "?");
		enter(option);

		if (option == "buy") {
			if (numoftimescheatingstore < numoftimescheatingtillkickedout) {
				bool repeatTrue = true;
				while (repeatTrue) {
					repeatTrue = false;
					std::string choice = "Hello, how are you doing?";
					std::cout << "Welcome to Friendly Market 2.0! Would you like to purchase anything? You have " << money << "$." << std::endl;
					std::vector <item*> shop = getShopItems();
					std::string decision;
					for (item* i : shop) {
						std::cout << i->getName() << " - " << i->getDescription() << " - " << i->getPrice() << "$ - " << i->getPicture() << std::endl;
					}
					enter(decision);
					if (decision == "no" || decision == "nope" || decision == "nah") {
						print("Thank you for visiting the Friendly Market 2.0! Hope you'll buy something next time! (or we will kick you out...)");
						break;
					}
					else if (decision == "yes" || decision == "yeah" || decision == "yep" || decision == "definitely!") {
						print("Good choice! What would you like to purchase?");
					}
					else {
						print("Get that gum out of your mouth. I can't even hear what you're saying!");
						break;
					}
					enter(choice);
					bool theitemexists = false;
					for (item* i : shop) {
						if (capitalize(choice) == i->getName()) {

							// You can cheat the store out of a ton of money. See if you can find the edge case

							theitemexists = true;
							if ((double)(money) + 100 <= (double)(i->getPrice())) {
								print("Dude, look at your wallet for a second.");
								std::cout << "You only have " << money << "$. Try again." << std::endl;
								break;
							}

							int quant = 0;
							int successfulbuys = 0;
							int unsuccessfulbuys = 0;

							std::cout << "How many " << i->getName() << "s would you like to purchase?" << std::endl;
							enter(quant);
							if (quant == 1) {
								print("Just one? Our deals are top notch! C'mon... how many?");
								enter(quant);
								if (quant == 1) {
									print("Fine, you win.");
								}
							}
							else if (quant == 0) {
								print("Dude. Not cool. How about you try working here! See how it feels!");
								break;
							}
							loading();

							for (int d = 0; d < quant; d++) {
								if (numoftimescheatingstore < numoftimescheatingtillkickedout) {
									if (money - i->getPrice() >= 0) {
										money -= i->getPrice();
										inventory.push_back(i);
										buyAmount += 1;
										successfulbuys++;
									}
									else {
										money -= i->getPrice();
										inventory.push_back(i);
										buyAmount += 1;
										numoftimescheatingstore++;
										unsuccessfulbuys++;
									}
								}
								else {
									print("You tried to cheat me ... one too many times! Leave!");
									print("       ___ ");
									print("      /. .\\");
									print("      |/^\\|");
									print("      \\___/");
									print("      *-|-*");
									print("       / \\ ");
									print("      -----");
									print("");
									print("");
									print("");
									print("");
									print("");
									print("      we are the *friendliest* market there is...");
									print("");
									print("");
									print("");
									print("");
									break;
								}
							}

							
							std::cout << "You purchased " << quant << " " << i->getName() << "s for " << i->getPrice() * quant << "$. You now have " << money << "$." << std::endl;
							if (unsuccessfulbuys > 0) {
								loading();
								print("Wait one second!");
								loading();
								print("You tried to cheat me!");
								loading();
								print("Don't you ever try to buy on credit again. Out of our store, out!!!!");
								break;
							}
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

					if (theitemexists == false) {
						print("Let me check our warehouse... Nope. We do not carry that item. Sorry.");
					}
				}
			}
			else {
				print("You attemped one too many shoplifts, you little crook!");
			}
		}
		else if (option == "explore") {
			print("You are taking a walk outside.");
			loading();

			int findOrFight = random(1, difficulty);
			if (findOrFight <= 5) {
				double chance = (double)((random(0, 9) + 1)) / 10.0;
				int itemFound = random(0, (shopItems.size()) - 1);
				if (chance <= shopItems[itemFound]->getChance()) {
					print("You found something!");
					inventory.push_back(shopItems[itemFound]);
					std::cout << "You have found a " << shopItems[itemFound]->getName() << " on the ground." << std::endl;
					print("Congrats!");
				}
				else {
					print("Unfortunately, you have not found anything. It has been a uneventful day.");
				}

			}
			else if (findOrFight >= 6) {
				print("Oh no! A Komodo d-RAGON has been found!");
				loading();
				print("Time to fight!");
				int healthLost = 0;
				bool defeated = false;
				while (defeated == false) {
					int enemyHealth = (komodoDragonHealth / 10) * random(1, 10);
					std::string chosenObject;
					print("What item would you like to use to fight the Komodo d-RAGON?");
					for (item* i : inventory) {
						std::cout << i->getName() << " - " << i->getDamage() << std::endl;
					}
					if (inventory.size() == 0) {
						using namespace std::chrono_literals;
						print("There's nothing here \\('_')/");
						loading();
						print("You can still use your hands!!!!!");
						print("Oh");
						std::this_thread::sleep_for(1s);
						print("Oh-Oh");
						std::this_thread::sleep_for(1s);
						print("Oh-Oh-Oh");
						std::this_thread::sleep_for(1s);
						print("Oh-Oh-Oh-Oh!");
						std::this_thread::sleep_for(1s);
						int damage = strength + random(1, 5);
						int hurt = (difficulty * random(1, 3));
						std::cout << "Your valiant attempt has wounded the Komodo d-RAGON by " << damage << " health points. It still has " << enemyHealth << " health points." << std::endl;
						std::cout << "In retalitation, the Komodo d-RAGON has wounded you by " << hurt << " health points. You still have " << myHealth << " health points." << std::endl;
						healthLost += hurt;
						enemyHealth -= damage;
						health(-hurt);
					}
					else {
						enter(chosenObject);
						loading();
						bool itemexists = false;
						for (auto hurtVec = inventory.begin(); hurtVec != inventory.end(); ++hurtVec) {
							if (capitalize(chosenObject) == (*hurtVec)->getName()) {
								itemexists = true;
								int damage = ((*hurtVec)->getDamage()) * random(1, 3);
								int hurt = (difficulty * random(1, 3));
								std::cout << "Your " << (*hurtVec)->getName() << " has wounded the Komodo d-RAGON by " << damage << " health points. It still has " << enemyHealth << " health points." << std::endl;
								std::cout << " In retalitation, the Komodo d-RAGON has wounded you by " << hurt << " health points. You still have " << myHealth << " health points." << std::endl;
								healthLost += hurt;
								enemyHealth -= damage;
								health(-hurt);
								if ((*hurtVec)->keepAfterFight() == false) {
									inventory.erase(hurtVec);
								}
								break;
							}
						}

						if (itemexists == false) {
							int hurt = (difficulty * random(1, 3));
							health(-hurt);
							std::cout << "You can't use that! The Komodo d-RAGON thought you were hillarious and wounded you by " << hurt << " health points because humor is not his forte.";
							healthLost += hurt;
						}
					}


					if (enemyHealth <= 0) {
						print("congratulations! You have beat the Komodo d-RAGON!");
						defeated = true;
						++komododragonkillamount;
					}
					if (myHealth <= healthamounttillrunaway) {
						print("NO! You are nearly dead. ESCAPE!");
						defeated = true;
					}
				}
				std::cout << "You fought valiantly, but you have lost a LOT of health. You have lost " << healthLost << " health points from the Komodo d-RAGON!" << std::endl;
				print("Better luck next time!");
			}

			health(-(random(0, difficulty)));
			exploreAmount += 1;
		}
		else if (option == "eat") {
			if (inventory.size() != 0) {
				bool repeatTrue = true;
				while (repeatTrue) {
					std::string itemToEat;
					print("What would you like to eat?");
					for (item* i : inventory) {
						std::cout << i->getName() << " - " << i->getDescription() << " - " << i->getRegeneration() << std::endl;
					}
					enter(itemToEat);
					int quantity = 1;
					int healthbefore = myHealth;
					int successfuleats = 0;
					int unsuccessfuleats = 0;
					print("How many?");
					enter(quantity);
					if (quantity == 1) {
						print("Just one? Ok, as you wish.");
					}
					else if (quantity == 0) {
						print("Man, what are you doing?!");
						break;
					}
					loading();
					for (int x = 0; x < quantity; x++) {
						if (eatItem(itemToEat)) {
							successfuleats++;
						}
						else {
							unsuccessfuleats++;
						}
					}

					if (unsuccessfuleats == quantity) {
						print("You dont have that item in your inventory!");
					} else if (unsuccessfuleats >= 1) {
						std::cout << "You only had " << successfuleats << " of that item." << std::endl;
						std::cout << "The food has given you " << myHealth - healthbefore << ". You now have " << myHealth << " health points." << std::endl;
					}
					else {
						std::cout << "The food has given you " << myHealth - healthbefore << ". You now have " << myHealth << " health points." << std::endl;
					}
					print("Would you like to eat anything else?");
					std::string buyTrue;
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
			else {
				print("You dont have anything to eat. Sorry.");
			}
		}
		else if (option == "items") {
			if (inventory.size() != 0) {
				for (item* i : inventory) {
					std::cout << i->getName() << " - " << i->getDescription() << " - " << i->getPicture() << std::endl;
				}
			}
			else {
				print("All I see in your pockets is the dust and grime that implies a poor man.");
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
			double earnings = random(0, strength * 10);
			std::cout << "You earned " << earnings << "$" << std::endl;
			money += earnings;
			std::cout << "You have " << money << "$" << std::endl;
			health(-(random(0, 20 - strength)));
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
			print("difficulty: change difficulty");
			print("stats: view your statistics");
			print("save: save your game");
			print("open: open your game");
			print("exit: quit the game");
		}
		else if (option == "stats") {
			std::cout << "You have explored " << exploreAmount << " times." << std::endl;
			std::cout << "You have bought " << buyAmount << " items." << std::endl;
			std::cout << "You have " << money << "$." << std::endl;
			std::cout << "You have " << myHealth << " health points." << std::endl;
			std::cout << "You have killed " << komododragonkillamount << " Komodo d-RAGONs." << std::endl;
			std::cout << "You have " << strength << " strength points." << std::endl;
			std::cout << "You have cheated the store " << numoftimescheatingstore << " times." << std::endl;
			std::cout << std::endl << "You have " << totalPoints << " total points." << std::endl;
		}
		else if (option == "save") {
			loading();
			save();
		}
		else if (option == "open") {
			loading();
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
					healthamounttillrunaway = 10;
					strength = 5;
					print("Okey dokey.");
				}
				else {
					print("It's too late to change. Get some more health, and I'll consider it.");
				}
			}
			else if (choice == "medium") {
				if (myHealth >= 75) {
					difficulty = 20;
					myHealth = 75;
					komodoDragonHealth = 60;
					healthamounttillrunaway = 5;
					strength = 3;
					print("Okey dokey.");
				}
				else {
					print("It's too late to change. Get some more health, and I'll consider it.");
				}
			}
			else if (choice == "hard") {
				if (myHealth >= 50) {
					difficulty = 35;
					myHealth = 50;
					komodoDragonHealth = 75;
					healthamounttillrunaway = 1;
					strength = 2;
					print("Okey dokey.");
				}
				else {
					print("It's too late to change. Get some more health, and I'll consider it.");
				}
			}
			else {
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
		else if (myHealth <= 15) {
			print("You have less than 15 health points. You should probably factor that into your calculations.");
		}

		if (money < 0) {
			print("You're in debt. you should probably do something about that...");
			debtTrue = true;
		}
		else if (money >= 0) {
			debtTrue = false;
		}

		debtHealthLoss();
		calctotalpoints();
	}
}
