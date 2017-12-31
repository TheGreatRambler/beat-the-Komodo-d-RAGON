#pragma once
#pragma once
#include <string>

class item {
public:
	virtual double getPrice() = 0;
	virtual double getChance() = 0;
	virtual int getRegeneration() = 0;
	virtual int getDamage() = 0;
	virtual int id() = 0;
	virtual bool keepAfterFight() = 0;
	virtual std::string getDescription() = 0;
	virtual std::string getType() = 0;
	virtual std::string getPicture() = 0;
	virtual std::string getName() = 0;
};

class misc : public item {
	virtual std::string getType() {
		return "miscellaneous";
	}
	virtual bool keepAfterFight() {
		return 1;
	}
};
class food : public item {
	virtual std::string getType() {
		return "food";
	}
	virtual bool keepAfterFight() {
		return 0;
	}
};
class tool : public item {
	virtual std::string getType() {
		return "tool";
	}
	virtual bool keepAfterFight() {
		return 1;
	}
};
class clothing : public item {
	virtual std::string getType() {
		return "clothing";
	}
	virtual bool keepAfterFight() {
		return 1;
	}
};
class pet : public item {
	virtual std::string getType() {
		return "pet";
	}
	virtual bool keepAfterFight() {
		return 1;
	}
};

class goldingots : public misc {
public:
	virtual std::string getName() {
		return "Goldingot";
	}
	virtual double getPrice() {
		return 100000000000.01;
	}
	virtual std::string getDescription() {
		return "Don't even try.";
	}
	virtual std::string getPicture() {
		return "[_]";
	}
	virtual double getChance() {
		return 0.1;
	}
	virtual int getRegeneration() {
		return 9001;
	}
	virtual int getDamage() {
		return 100;
	}
	virtual int id() {
		return 1;
	}
};
class shoes : public clothing {
public:
	virtual std::string getName() {
		return "Shoes";
	}
	virtual double getPrice() {
		return 70.00;
	}
	virtual std::string getDescription() {
		return "Good for running. Gives a slight speed boost.";
	}
	virtual std::string getPicture() {
		return "_||_";
	}
	virtual double getChance() {
		return 0.7;
	}
	virtual int getRegeneration() {
		return 1;
	}
	virtual int getDamage() {
		return 5;
	}
	virtual int id() {
		return 2;
	}
};
class sword : public tool {
public:
	virtual std::string getName() {
		return "Sword";
	}
	virtual double getPrice() {
		return 100.00;
	}
	virtual std::string getDescription() {
		return "Use to protect yourself.";
	}
	virtual std::string getPicture() {
		return "!";
	}
	virtual double getChance() {
		return 0.5;
	}
	virtual int getRegeneration() {
		return -10;
	}
	virtual int getDamage() {
		return 40;
	}
	virtual int id() {
		return 3;
	}
};
class apple : public food {
public:
	virtual std::string getName() {
		return "Apple";
	}
	virtual double getPrice() {
		return 2.00;
	}
	virtual std::string getDescription() {
		return "Stay happy and healthy!©";
	}
	virtual std::string getPicture() {
		return "`O";
	}
	virtual double getChance() {
		return 1.0;
	}
	virtual int getRegeneration() {
		return 5;
	}
	virtual int getDamage() {
		return -2;
	}
	virtual int id() {
		return 4;
	}
};
class brownie : public food {
public:
	virtual std::string getName() {
		return "Brownie";
	}
	virtual double getPrice() {
		return 7.00;
	}
	virtual std::string getDescription() {
		return "Gives a speed boost due to your hyperactivity!";
	}
	virtual std::string getPicture() {
		return "==";
	}
	virtual double getChance() {
		return 0.3;
	}
	virtual int getRegeneration() {
		return 10;
	}
	virtual int getDamage() {
		return -5;
	}
	virtual int id() {
		return 5;
	}
};
class bag : public misc {
public:
	virtual std::string getName() {
		return "Bag";
	}
	virtual double getPrice() {
		return 30.00;
	}
	virtual std::string getDescription() {
		return "Adds extra storage to your inventory.";
	}
	virtual std::string getPicture() {
		return "[O]";
	}
	virtual double getChance() {
		return 1.0;
	}
	virtual int getRegeneration() {
		return 1;
	}
	virtual int getDamage() {
		return 15;
	}
	virtual int id() {
		return 6;
	}
};
class theRecursiveFruit : public food {
public:
	virtual std::string getName() {
		return "Therecursivefruit";
	}
	virtual double getPrice() {
		return 5.00;
	}
	virtual std::string getDescription() {
		return "Get ready for some recursive beauty...";
	}
	virtual std::string getPicture() {
		return "%^&*(";
	}
	virtual double getChance() {
		return 1.0;
	}
	virtual int getRegeneration() {
		return -50;
	}
	virtual int getDamage() {
		return 7;
	}
	virtual int id() {
		return 7;
	}
};
class hat : public misc {
public:
	virtual std::string getName() {
		return "Hat";
	}
	virtual double getPrice() {
		return 20.00;
	}
	virtual std::string getDescription() {
		return "Wear it with pride.";
	}
	virtual std::string getPicture() {
		return "-^-";
	}
	virtual double getChance() {
		return 0.8;
	}
	virtual int getRegeneration() {
		return 1;
	}
	virtual int getDamage() {
		return 4;
	}
	virtual int id() {
		return 8;
	}
};
class pie : public food {
public:
	virtual std::string getName() {
		return "Pie";
	}
	virtual double getPrice() {
		return 10.00;
	}
	virtual std::string getDescription() {
		return "One food to rule them all.";
	}
	virtual std::string getPicture() {
		return "(<)";
	}
	virtual double getChance() {
		return 0.4;
	}
	virtual int getRegeneration() {
		return 20;
	}
	virtual int getDamage() {
		return -20;
	}
	virtual int id() {
		return 9;
	}
};
class car : public misc {
public:
	virtual std::string getName() {
		return "Car";
	}
	virtual double getPrice() {
		return 1000.00;
	}
	virtual std::string getDescription() {
		return "Get around in style.";
	}
	virtual std::string getPicture() {
		return ".<>.";
	}
	virtual double getChance() {
		return 0.2;
	}
	virtual int getRegeneration() {
		return -90;
	}
	virtual int getDamage() {
		return 100;
	}
	virtual int id() {
		return 10;
	}
};
class dog : public pet {
public:
	virtual std::string getName() {
		return "Dog";
	}
	virtual double getPrice() {
		return 200.00;
	}
	virtual std::string getDescription() {
		return "Have a friend.";
	}
	virtual std::string getPicture() {
		return ",<>,*";
	}
	virtual double getChance() {
		return 0.4;
	}
	virtual int getRegeneration() {
		return 50;
	}
	virtual int getDamage() {
		return 100;
	}
	virtual int id() {
		return 11;
	}
};
