#ifndef MANAGER
#define MANAGER
#include<iostream>
class database;

class manager {//管理员类：登录/修改商品信息/上架/下架
private:
	std::string name = "ad";//提前预设的账户
	std::string cipher = "123";//提前预设的密码
	void addGoods(database& shop);//添加商品
	void deleteGoods(database& shop);//删除商品
	void changeGoods(database& shop);//修改商品
public:
	bool judgeName(std::string n) {//判断输入管理员信息是否正确
		if (n == name) return true;
		return false;
	}
	bool judgeCipher(std::string c) {
		if (c == cipher) return true;
		return false;
	}
	void managerPage(database& shop);

};
#endif