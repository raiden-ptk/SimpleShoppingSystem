#ifndef CONSUMER
#define CONSUMER
class shoppingCart;
#include<iostream>
#include<Windows.h>
#include"shoppingCart.h"
#include"tools.h"

class consumer {//用户类
private:
	shoppingCart cart;//购物车
	long long phone = 123456;//用户的电话号码
	std::string name = "name";//用户名
	std::string cipher = "cipher";//用户密码
	void changeCipher();//修改密码
	void buyGoods(database& shop);//购买商品
	void searchGoods(database& shop);//用户查找商品
	void myCart(database& shop);//查看购物车
public:
	consumer(std::string n, std::string c) :name(n), cipher(c) {};//创建一个用户账户
	consumer() {

	}
	bool setPhone(long long p) {
		phone = p;
		return true;
	}
	bool setName(std::string n) {
		cart.setOwner(n);
		name = n;
		return true;
	}
	bool setCipher(std::string c) {
		cipher = c;
		return true;
	}
	long long getPhone() {
		return phone;
	}
	std::string getName() {
		return name;
	}
	bool judgeCipher(std::string c) {//判断密码是否正确
		if (c == cipher) return true;
		return false;
	}
	void consumerPage(database& shop);//唤起用户界面
	void lookGoods(database& shop);//浏览商品
	void haveCode() {//设置优惠券
		cart.setCode();
	}
	bool cartInit() {//购物车初始化
		cart.cart_Init();
		return true;
	}
};

#endif