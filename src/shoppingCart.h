#ifndef SHOPPINGCART
#define SHOPPINGCART
#define maxnum 100
#include"good.h"
#include"Record.h"
class database;

class shoppingCart {//购物车类
	friend class consumer;
private:
	std::string owner="nobody";
	good goods[maxnum];//购买的商品信息
	int numOfgoods = 0;//购物车中商品数目
	int sumPrice = 0;//购物车商品总价格
	int haveCode = 0;//拥有的优惠券数
	Record history;//购物记录
public:
	void setOwner(std::string n) {
		owner = n;
		history.filename = n + "_history.txt";
	}
	shoppingCart() {

	}
	int findGood(std::string n);//在购物车中查找商品
	void showCart();//展示购物车信息
	void setGood(good g, int c) {//向购物车中存入商品
		goods[numOfgoods].name = g.name;
		goods[numOfgoods].count = c;
		goods[numOfgoods].info = g.info;
		goods[numOfgoods].number = g.number;
		goods[numOfgoods].price = g.price;
		sumPrice += c * g.price;
		numOfgoods++;
	}
	bool deleteGood(std::string n);//删除购物车中商品
	void changeGood(std::string n, int maxCount);//修改
	void clear(std::string* test, int c, database& shop);//结算购物车中商品
	void setCode() {//添加优惠券
		haveCode++;
	}
	bool saveCart();
	bool cart_Init();
	void showHistory() {
		history.show();
	}
};
#endif