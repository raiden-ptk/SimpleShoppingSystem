#ifndef GOOD
#define GOOD
#include<iostream>

class good {//��Ʒ��
	friend class manager;
	friend class shoppingCart;
	friend class database;
private:
	int number = 0;//���
	std::string name = "good";//����
	int price = 99999;//�۸�
	int count = 0;//���
	std::string info = "empty";//����
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