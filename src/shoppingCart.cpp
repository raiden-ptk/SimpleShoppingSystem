#include"shoppingCart.h"
#include"database.h"
int shoppingCart::findGood(std::string n) {//查找商品在购物车中位置
	for (int index = 0; index < numOfgoods; index++) {
		if (goods[index].getName() == n) {//找到商品返回下标
			return index;
		}
	}
	return -1;
}

void shoppingCart::showCart() {//展示购物车中的商品
	//system("cls");
	std::cout << "\n------购物车信息------\n" << std::endl;
	if (!numOfgoods) {
		std::cout << "当前购物车为空qwq" << std::endl;
		return;
	}
	std::cout << "\t商品名称\t价格\t描述\t\t数目\t" << std::endl;
	for (int i = 0; i < numOfgoods; i++) {
		std::cout << "|\t" << goods[i].getName() << "\t\t" << goods[i].getPrice() << "\t" << goods[i].getInfo() << "\t\t" << goods[i].getCount() << "\t|" << std::endl;
	}
	std::cout << "\n当前购物总计金额为：" << sumPrice << std::endl;
}

bool shoppingCart::deleteGood(std::string n) {//删除购物车中商品
	int index = findGood(n);
	if (index != -1) {//找到了要删除的商品
		sumPrice -= goods[index].count * goods[index].price;
		for (int i = index + 1; i < numOfgoods; i++) {
			goods[index].count = goods[i].count;
			goods[index].info = goods[i].info;
			goods[index].name = goods[i].name;
			goods[index].number = goods[i].number;
			goods[index].price = goods[i].price;
		}
		numOfgoods--;
		return true;
	}
	else {
		std::cout << "\n您输入的商品不存在,请重新输入" << std::endl;
		return false;
	}
}

void shoppingCart::changeGood(std::string n, int maxCount) {//更改购物车中的信息
	system("cls");
	std::cout << "\n请输入您调整后此商品的购买数量" << std::endl;
	int c;
	while (true) {
		std::cin >> c;
		if (!c) {
			deleteGood(n);
			break;
		}
		else if (c > maxCount) {
			std::cout << "超过当前商品库存数量，请重新输入，当前最大库存为：" << maxCount << std::endl;
		}
		else if (c < 0) {
			std::cout << "您输入的数目不正确，请重新输入" << std::endl;
		}
		else {
			int index = findGood(n);
			sumPrice += (c - goods[index].count) * goods[index].price;
			goods[index].count = c;
			std::cout << "\n已修改！" << std::endl;
			break;
		}
	}
}

void shoppingCart::clear(std::string* test, int c, database& shop) {//商品结算
	system("cls");
	std::cout << "\n\t商品名称\t价格\t描述\t\t数目\t" << std::endl;
	int sump = 0;
	int* reduce = new int[c];//记录要结算的商品的个数
	int* restInshop = new int[c];//记录货架中现有的商品数目

	for (int i = 0; i < c; i++) {//保存货架中现有商品数目
		int index = shop.good_exist(test[i]);
		restInshop[i] = shop.getGood(index).getCount();
	}

	for (int i = 0; i < c; i++) {
		int index = findGood(test[i]);
		if (index != -1 && goods[index].getCount() <= restInshop[i]) {//如果在购物车中找到了要结算的商品，且商品仍足够，则展示其信息
			std::cout << "|\t" << goods[index].getName() << "\t\t" << goods[index].getPrice() << "\t" << goods[index].getInfo() << "\t\t" << goods[index].getCount() << "\t|" << std::endl;
			reduce[i] = goods[index].getCount();
			sump += goods[index].price * goods[index].count;
		}
		else if (index != -1 && goods[index].getCount() > restInshop[i]) {//如果在购物车中找到了要结算的商品，但是货架中剩余的商品不足
			std::cout << "商品" << goods[index].getName() << "库存不足，现剩余" << restInshop[i] << "件，请修改购买数目";
			return;
		}
		else {
			std::cout << "\n您输入的商品信息含有错误，请重试" << std::endl;
			return;
		}
	}
	std::cout << "\n当前选择结算的商品总计金额为：" << sump << std::endl;

	int q = -1;//券码使用
	if (haveCode> 0) {
		std::cout << "\n您现在拥有优惠券，可以输入券码使用" << std::endl;
		std::string b_button;
		while (true) {
			std::cout << "\n是否使用优惠券？(Y/N)" << std::endl;
			std::cin >> b_button;
			if (b_button == "Y") {
				std::cout << "\n请输入券码：" << std::endl;
				std::string code;
				std::cin >> code;
				q = shop.code_exist(code);
				if (q == -1) std::cout << "\n您输入的券码不是有效券码" << std::endl;
				else if(q < 100) {
					haveCode--;//拥有的优惠券数减一
					break;
				}
				else if (q > 100) {
					if (sump < q - q % 100) {//不满足满减条件
						std::cout << "\n抱歉，"<<", 该券为满"<<q -q%100<<"减"<<q%100<<"元满减券" <<",您购物总价不满足该券要求的满减条件" << std::endl;
					}
					else {
						haveCode--;//拥有的优惠券数减一
						break;
					}
				}
			}
			else if (b_button == "N") {
				break;
			}
			else std::cout << "\n请输入正确选项" << std::endl;
		}
	}
	std::cout << "\n您确认结算吗？(Y/N)";
	if (q == -1) std::cout << ",当前选择结算的商品总计金额为：" << sump << std::endl;//未使用或者未成功使用
	else if(q<100)std::cout << ",当前选择结算的商品总计金额为：" << sump << "-" << q << "=" << ((sump - q)>0?(sump-q):0 )<< "元" << std::endl;//成功使用随机券
	else if (q > 100) {
		std::cout <<",使用满"<<q -q%100<<"减"<<q%100<<"元满减券后" << ", 当前选择结算的商品总计金额为：" << sump << " - " << q % 100 << " = " << ((sump - q % 100)>0?(sump-q%100):0) << "元" << std::endl;//成功使用满减券
	}

	std::string s;
	std::cin >> s;
	while (true) {
		if (s == "Y") {//确认结算
			for (int i = 0; i < c; i++) {
				int index = findGood(test[i]);
				history.save(goods[index].getName(), goods[index].getPrice(), goods[index].getInfo(), goods[index].getCount());
				//保存入购买记录
				deleteGood(test[i]);
				shop.reduceGood(test[i], reduce[i]);
			}
			break;
		}
		else if (s == "N") return;
		else std::cout << "\n请输入正确选项" << std::endl;
	}
	std::cout << "\n结算成功！" << std::endl;
}

bool shoppingCart::saveCart() {//保存购物车中商品
	std::ofstream ofs;
	std::string filename = owner + "_Cart.txt";
	ofs.open(filename, std::ios::out);
	for (int i = 0; i < numOfgoods; i++) {
		//std::cout << "|\t" << goods[i].getName() << "\t\t" << goods[i].getPrice() << "\t" << goods[i].getInfo() << "\t\t" << goods[i].getCount() << "\t|" << std::endl;
		ofs << goods[i].getName() << ' ' << goods[i].getPrice() << ' ' << goods[i].getInfo() << ' ' << goods[i].getCount() << std::endl;
	}
	ofs.close();
	return true;
}

bool shoppingCart::cart_Init() {//初始化购物车
	std::ifstream ifs;
	std::string filename = owner + "_Cart.txt";
	ifs.open(filename, std::ios::in);

	std::string n, info;
	int p, c;

	while (ifs >> n && ifs >> p && ifs >> info && ifs >> c) {
		good g(n, p, info, c);
		setGood(g, c);
	}
	ifs.close();
	return true;
}