#ifndef GOOD
#define GOOD
#include<iostream>

class good {//商品类
	friend class manager;
	friend class shoppingCart;
	friend class database;
private:
	int number = 0;//编号
	std::string name = "good";//名称
	int price = 99999;//价格
	int count = 0;//库存
	std::string info = "empty";//描述
public:
	good() {

	}
	good(std::string n, int p, std::string fo, int c) {
		name = n;
		price = p;
		info = fo;
		count = c;
	}
	std::string getName() {
		return name;
	}
	int getPrice() {
		return price;
	}
	int getCount() {
		return count;
	}
	std::string getInfo() {
		return info;
	}
};
#endif