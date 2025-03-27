#include"consumer.h"
#include"database.h"
void consumer::consumerPage(database& shop) {//生成用户页面
	while (true) {
		//system("cls");
		std::cout << "\n------用户：" << getName() << "登陆中------" << std::endl;
		std::cout << "\n[A]浏览商品" << std::endl;
		std::cout << "[B]购买商品" << std::endl;
		std::cout << "[C]修改密码" << std::endl;
		std::cout << "[D]查询商品" << std::endl;
		std::cout << "[E]我的购物车" << std::endl;
		std::cout << "[F]退出登录" << std::endl;
		std::cout << "\n请选择您的操作：" << std::endl;
		std::string cu_button;
		std::cin >> cu_button;
		if (cu_button == "A") {//用户浏览商品
			lookGoods(shop);
		}
		else if (cu_button == "B") {//用户购买商品
			buyGoods(shop);
		}
		else if (cu_button == "C") {//用户修改密码
			changeCipher();
		}
		else if (cu_button == "D") {//用户查询商品
			searchGoods(shop);
		}
		else if (cu_button == "E") {//查看购物车
			myCart(shop);
		}
		else if (cu_button == "F") {//退出用户页面
			//退出登录前，将购物车保存
			cart.saveCart();
			break;
		}
		else std::cout << "\n您输入的操作不存在，请重新尝试" << std::endl;
		Sleep(500);
	}
}

void consumer::lookGoods(database& shop) {//用户浏览商品
	shop.showGoods();
}

void consumer::buyGoods(database& shop) {//用户购买商品
	//std::cout << "敬请期待" << std::endl;
	system("cls");
	shop.showGoods();
	while (true) {
		std::string n;
		int c;
		std::cout << "\n请输入要添加进购物车中的商品名称，输入q退出" << std::endl;
		std::cout << "商品名称：";
		std::cin >> n;
		int index = shop.good_exist(n);
		if (n == "q") break;
		if (index == -1) {
			std::cout << "\n您输入的商品不存在，请重试" << std::endl;
			continue;
		}
		while (true) {
			std::cout << "购买数量：";
			std::cin >> c;
			if (c > shop.getGood(index).getCount()) {
				std::cout << "\n超过库存容量，请重试" << std::endl;
				continue;
			}
			break;
		}
		cart.setGood(shop.getGood(index), c);
		std::cout << "\n商品已添加入购物车中！" << std::endl;
	}
}

void consumer::changeCipher() {//用户修改密码
	system("cls");
	while (true) {
		std::string new_c_1, new_c_2;
		std::cout << "\n请输入新密码：" << std::endl;
		std::cin >> new_c_1;
		std::cout << "请确认新密码：" << std::endl;
		std::cin >> new_c_2;
		if (new_c_1 == new_c_2) {
			setCipher(new_c_1);
			std::cout << "\n密码已经修改完成！" << std::endl;
			break;
		}
		else {
			std::cout << "\n两次输入不一致，请重新输入" << std::endl;
		}
	}
}

void consumer::searchGoods(database& shop) {//用户查询商品
	system("cls");
	std::string key;
	std::cout << "\n请输入您要查询的商品的名称或关键字：";
	std::cin >> key;
	std::cout << "\n------相关商品为------" << std::endl;
	std::cout << "\n\t商品名称\t价格\t描述\t\t库存\t" << std::endl;
	int j = 0, num = shop.getNumOfGoods(), flag = 0;
	for (j; j < num; j++) {
		good& temp = shop.getGood(j);
		if (key == temp.getName()) {
			std::cout << "|\t" << temp.getName() << "\t\t" << temp.getPrice() << "\t" << temp.getInfo() << "\t\t" << temp.getCount() << "\t|" << std::endl;
			flag++;
			break;
		}
	}
	if (j == num) {//如果没有与用户输入名称完全一样的商品，则输出相关的商品
		for (int i = 0; i < num; i++) {
			good& temp = shop.getGood(i);
			if (match(key, temp.getName())) {
				std::cout << "|\t" << temp.getName() << "\t\t" << temp.getPrice() << "\t" << temp.getInfo() << "\t\t" << temp.getCount() << "\t|" << std::endl;
				flag++;//标志
			}
		}
	}
	if (!flag) std::cout << "抱歉，暂时没有这种商品qwq" << std::endl;
}

void consumer::myCart(database& shop) {//用户购物车页面
	while (true) {
		//system("cls");
		cart.history.load();
		std::cout << "\n------ " << getName() << "的购物车------" << std::endl;
		cart.showCart();
		std::cout << "\n[A]删除购物车中商品" << std::endl;
		std::cout << "[B]修改商品购买数量" << std::endl;
		std::cout << "[C]结算商品" << std::endl;
		std::cout << "[D]查看历史记录商品" << std::endl;
		std::cout << "[E]退出购物车" << std::endl;
		std::cout << "\n请选择您的操作：" << std::endl;
		std::string car_button;
		std::cin >> car_button;
		if (car_button == "A") {//删除预购商品
			std::cout << "\n请输入您预删除的商品名称：" << std::endl;
			std::string n;
			std::cin >> n;
			bool flag = cart.deleteGood(n);
			if (flag == true) std::cout << "已删除！" << std::endl;
		}
		else if (car_button == "B") {//修改预购商品数量
			std::cout << "\n请输入您预修改的商品名称：" << std::endl;
			std::string n;
			std::cin >> n;
			int index = shop.good_exist(n);//找到库存中的商品信息
			cart.changeGood(n, shop.getGood(index).getCount());
		}
		else if (car_button == "C") {//结算商品
			std::cout << "\n请输入您预结算的商品名称，以空格分开,输入q结束" << std::endl;
			std::string test[maxnum]; int i;
			for (i = 0; ; i++) {
				std::cin >> test[i];
				if (test[i] == "q") break;
			}
			cart.clear(test, i, shop);
		}
		else if (car_button == "D") {//查看历史记录
			cart.showHistory();
		}
		else if (car_button == "E") {//退出用户购物车
			break;
		}
		else std::cout << "\n您输入的操作不存在，请重新尝试" << std::endl;
		Sleep(300);
	}
}