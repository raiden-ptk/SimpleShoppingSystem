#include"manager.h"
#include"database.h"
void manager::managerPage(database& shop) {//管理员操作页面
	while (true) {
		system("cls");
		std::cout << "\n------管理员登陆中------" << std::endl;
		std::cout << "\n[A]添加商品" << std::endl;
		std::cout << "[B]删除商品" << std::endl;
		std::cout << "[C]修改商品" << std::endl;
		std::cout << "[D]返回首页" << std::endl;
		std::cout << "\n请选择您的操作：" << std::endl;
		std::string man_button;
		std::cin >> man_button;
		if (man_button == "A") {//用户浏览商品
			addGoods(shop);
		}
		else if (man_button == "B") {//用户购买商品
			deleteGoods(shop);
		}
		else if (man_button == "C") {//用户修改密码
			changeGoods(shop);
		}
		else if (man_button == "D") {//退出用户页面
			break;
		}
		else {
			std::cout << "\n您输入的操作不存在，请重新尝试" << std::endl;
		}
		Sleep(500);
	}
}

void manager::addGoods(database& shop) {//管理员添加商品
	system("cls");
	std::string n, inf;
	int p, plus;
	std::cout << "\n请输入您要添加的商品的信息：" << std::endl;
	std::cout << "请输入商品名称：" << std::endl;
	std::cin >> n;
	int flag = shop.good_exist(n);
	if (flag != -1) {
		std::cout << "\n商品已经存在，是否添加库存？" << std::endl;
		std::cout << "[A]是" << std::endl;
		std::cout << "[B]否" << std::endl;
		std::string choice;
		std::cin >> choice;
		if (choice == "A") {
			std::cout << "请输入加入库存的数量:" << std::endl;
			std::cin >> plus;
			shop.goods[flag].count += plus;
			std::cout << "添加成功！" << std::endl;
			return;
		}
		else if (choice == "B") {

		}
		else std::cout << "无效操作" << std::endl;
	}
	std::cout << "请输入商品价格：" << std::endl;
	std::cin >> p;
	std::cout << "请输入商品描述：" << std::endl;
	std::cin >> inf;
	std::cout << "请输入商品数量：" << std::endl;
	std::cin >> plus;

	shop.goods[shop.numOfgoods].name = n;
	shop.goods[shop.numOfgoods].price = p;
	shop.goods[shop.numOfgoods].info = inf;
	shop.goods[shop.numOfgoods].count += plus;
	shop.numOfgoods++;
	std::cout << "\n商品添加完成！" << std::endl;
}

void manager::deleteGoods(database& shop) {//管理员删除商品
	system("cls");
	std::cout << "\n当今库存为:\n" << std::endl;
	shop.showGoods();
	std::cout << "\n请输入您要删除的商品的名称：" << std::endl;
	std::string name;
	std::cin >> name;
	int index = shop.good_exist(name);
	if (index != -1) {
		for (int i = index + 1; i < shop.numOfgoods; i++) {
			shop.goods[index].count = shop.goods[i].count;
			shop.goods[index].info = shop.goods[i].info;
			shop.goods[index].name = shop.goods[i].name;
			shop.goods[index].number = shop.goods[i].number;
			shop.goods[index].price = shop.goods[i].price;
		}
		shop.numOfgoods--;
		std::cout << "\n当今库存为:\n" << std::endl;
		shop.showGoods();
	}
	else {
		std::cout << "\n您输入的商品不存在，请重试" << std::endl;
	}
}

void manager::changeGoods(database& shop) {//管理员修改商品信息
	system("cls");
	std::cout << "\n当今库存为:\n" << std::endl;
	shop.showGoods();
	std::cout << "\n请输入您要修改的商品的名称：" << std::endl;
	std::string n;
	std::cin >> n;
	int index = shop.good_exist(n);
	if (index != -1) {
		while (true) {
			std::cout << "\n[A]修改商品名称" << std::endl;
			std::cout << "[B]修改商品价格" << std::endl;
			std::cout << "[C]修改描述" << std::endl;
			std::cout << "[D]修改数量" << std::endl;
			std::cout << "[E]结束该商品修改" << std::endl;
			std::cout << "\n请选择您的操作：" << std::endl;
			std::string chg_button;
			std::cin >> chg_button;
			if (chg_button == "A") {
				std::string new_name;
				std::cout << "\n请输入修改后名称:" << std::endl;
				std::cin >> new_name;
				shop.goods[index].name = new_name;
			}
			else if (chg_button == "B") {
				int new_price;
				std::cout << "\n请输入修改后价格:" << std::endl;
				std::cin >> new_price;
				shop.goods[index].price = new_price;
			}
			else if (chg_button == "C") {
				std::string new_info;
				std::cout << "\n请输入修改后描述:" << std::endl;
				std::cin >> new_info;
				shop.goods[index].info = new_info;
			}
			else if (chg_button == "D") {
				int new_count;
				std::cout << "\n请输入修改后数量:" << std::endl;
				std::cin >> new_count;
				shop.goods[index].count = new_count;
			}
			else if (chg_button == "E") break;
			else std::cout << "\n您输入的操作不存在，请重新尝试" << std::endl;
			std::cout << "\n当今库存为:\n" << std::endl;
			shop.showGoods();
		}
	}
	else {
		std::cout << "\n您输入的商品不存在，请重新尝试" << std::endl;
	}
}