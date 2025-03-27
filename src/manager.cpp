#include"manager.h"
#include"database.h"
void manager::managerPage(database& shop) {//����Ա����ҳ��
	while (true) {
		system("cls");
		std::cout << "\n------����Ա��½��------" << std::endl;
		std::cout << "\n[A]�����Ʒ" << std::endl;
		std::cout << "[B]ɾ����Ʒ" << std::endl;
		std::cout << "[C]�޸���Ʒ" << std::endl;
		std::cout << "[D]������ҳ" << std::endl;
		std::cout << "\n��ѡ�����Ĳ�����" << std::endl;
		std::string man_button;
		std::cin >> man_button;
		if (man_button == "A") {//�û������Ʒ
			addGoods(shop);
		}
		else if (man_button == "B") {//�û�������Ʒ
			deleteGoods(shop);
		}
		else if (man_button == "C") {//�û��޸�����
			changeGoods(shop);
		}
		else if (man_button == "D") {//�˳��û�ҳ��
			break;
		}
		else {
			std::cout << "\n������Ĳ��������ڣ������³���" << std::endl;
		}
		Sleep(500);
	}
}

void manager::addGoods(database& shop) {//����Ա�����Ʒ
	system("cls");
	std::string n, inf;
	int p, plus;
	std::cout << "\n��������Ҫ��ӵ���Ʒ����Ϣ��" << std::endl;
	std::cout << "��������Ʒ���ƣ�" << std::endl;
	std::cin >> n;
	int flag = shop.good_exist(n);
	if (flag != -1) {
		std::cout << "\n��Ʒ�Ѿ����ڣ��Ƿ���ӿ�棿" << std::endl;
		std::cout << "[A]��" << std::endl;
		std::cout << "[B]��" << std::endl;
		std::string choice;
		std::cin >> choice;
		if (choice == "A") {
			std::cout << "����������������:" << std::endl;
			std::cin >> plus;
			shop.goods[flag].count += plus;
			std::cout << "��ӳɹ���" << std::endl;
			return;
		}
		else if (choice == "B") {

		}
		else std::cout << "��Ч����" << std::endl;
	}
	std::cout << "��������Ʒ�۸�" << std::endl;
	std::cin >> p;
	std::cout << "��������Ʒ������" << std::endl;
	std::cin >> inf;
	std::cout << "��������Ʒ������" << std::endl;
	std::cin >> plus;

	shop.goods[shop.numOfgoods].name = n;
	shop.goods[shop.numOfgoods].price = p;
	shop.goods[shop.numOfgoods].info = inf;
	shop.goods[shop.numOfgoods].count += plus;
	shop.numOfgoods++;
	std::cout << "\n��Ʒ�����ɣ�" << std::endl;
}

void manager::deleteGoods(database& shop) {//����Աɾ����Ʒ
	system("cls");
	std::cout << "\n������Ϊ:\n" << std::endl;
	shop.showGoods();
	std::cout << "\n��������Ҫɾ������Ʒ�����ƣ�" << std::endl;
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
		std::cout << "\n������Ϊ:\n" << std::endl;
		shop.showGoods();
	}
	else {
		std::cout << "\n���������Ʒ�����ڣ�������" << std::endl;
	}
}

void manager::changeGoods(database& shop) {//����Ա�޸���Ʒ��Ϣ
	system("cls");
	std::cout << "\n������Ϊ:\n" << std::endl;
	shop.showGoods();
	std::cout << "\n��������Ҫ�޸ĵ���Ʒ�����ƣ�" << std::endl;
	std::string n;
	std::cin >> n;
	int index = shop.good_exist(n);
	if (index != -1) {
		while (true) {
			std::cout << "\n[A]�޸���Ʒ����" << std::endl;
			std::cout << "[B]�޸���Ʒ�۸�" << std::endl;
			std::cout << "[C]�޸�����" << std::endl;
			std::cout << "[D]�޸�����" << std::endl;
			std::cout << "[E]��������Ʒ�޸�" << std::endl;
			std::cout << "\n��ѡ�����Ĳ�����" << std::endl;
			std::string chg_button;
			std::cin >> chg_button;
			if (chg_button == "A") {
				std::string new_name;
				std::cout << "\n�������޸ĺ�����:" << std::endl;
				std::cin >> new_name;
				shop.goods[index].name = new_name;
			}
			else if (chg_button == "B") {
				int new_price;
				std::cout << "\n�������޸ĺ�۸�:" << std::endl;
				std::cin >> new_price;
				shop.goods[index].price = new_price;
			}
			else if (chg_button == "C") {
				std::string new_info;
				std::cout << "\n�������޸ĺ�����:" << std::endl;
				std::cin >> new_info;
				shop.goods[index].info = new_info;
			}
			else if (chg_button == "D") {
				int new_count;
				std::cout << "\n�������޸ĺ�����:" << std::endl;
				std::cin >> new_count;
				shop.goods[index].count = new_count;
			}
			else if (chg_button == "E") break;
			else std::cout << "\n������Ĳ��������ڣ������³���" << std::endl;
			std::cout << "\n������Ϊ:\n" << std::endl;
			shop.showGoods();
		}
	}
	else {
		std::cout << "\n���������Ʒ�����ڣ������³���" << std::endl;
	}
}