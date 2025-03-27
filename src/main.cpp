#include<iostream>
#include"database.h"
int main() {
	database shop;//一个商店的数据库
	shop.database_Init();
	while (true) {
		system("cls");
		std::cout << "\n------西电购物系统首页------" << std::endl;
		std::cout << "\n[A]用户注册" << std::endl;
		std::cout << "[B]用户登录" << std::endl;
		std::cout << "[C]浏览商品" << std::endl;
		std::cout << "[D]管理员选项" << std::endl;
		std::cout << "[E]退出" << std::endl;
		std::cout << "\n请选择您的操作：" << std::endl;

		std::string button;
		std::cin >> button;

		if (button == "A") {//进行用户注册
			shop.conSignUp();
		}
		else if (button == "B") {//用户登录
			shop.conSignIn();
		}
		else if (button == "C") {//浏览商品
			shop.showGoods();
		}
		else if (button == "D") {//管理员选项
			shop.manSignIn();
		}
		else if (button == "E") {
			break;
		}
		else {
			std::cout << "您提供的服务选项有误，请重新尝试QwQ" << std::endl;
		}
		Sleep(700);
	}
}