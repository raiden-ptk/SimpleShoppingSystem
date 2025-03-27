#include"consumer.h"
#include"database.h"
void consumer::consumerPage(database& shop) {//�����û�ҳ��
	while (true) {
		//system("cls");
		std::cout << "\n------�û���" << getName() << "��½��------" << std::endl;
		std::cout << "\n[A]�����Ʒ" << std::endl;
		std::cout << "[B]������Ʒ" << std::endl;
		std::cout << "[C]�޸�����" << std::endl;
		std::cout << "[D]��ѯ��Ʒ" << std::endl;
		std::cout << "[E]�ҵĹ��ﳵ" << std::endl;
		std::cout << "[F]�˳���¼" << std::endl;
		std::cout << "\n��ѡ�����Ĳ�����" << std::endl;
		std::string cu_button;
		std::cin >> cu_button;
		if (cu_button == "A") {//�û������Ʒ
			lookGoods(shop);
		}
		else if (cu_button == "B") {//�û�������Ʒ
			buyGoods(shop);
		}
		else if (cu_button == "C") {//�û��޸�����
			changeCipher();
		}
		else if (cu_button == "D") {//�û���ѯ��Ʒ
			searchGoods(shop);
		}
		else if (cu_button == "E") {//�鿴���ﳵ
			myCart(shop);
		}
		else if (cu_button == "F") {//�˳��û�ҳ��
			//�˳���¼ǰ�������ﳵ����
			cart.saveCart();
			break;
		}
		else std::cout << "\n������Ĳ��������ڣ������³���" << std::endl;
		Sleep(500);
	}
}

void consumer::lookGoods(database& shop) {//�û������Ʒ
	shop.showGoods();
}

void consumer::buyGoods(database& shop) {//�û�������Ʒ
	//std::cout << "�����ڴ�" << std::endl;
	system("cls");
	shop.showGoods();
	while (true) {
		std::string n;
		int c;
		std::cout << "\n������Ҫ��ӽ����ﳵ�е���Ʒ���ƣ�����q�˳�" << std::endl;
		std::cout << "��Ʒ���ƣ�";
		std::cin >> n;
		int index = shop.good_exist(n);
		if (n == "q") break;
		if (index == -1) {
			std::cout << "\n���������Ʒ�����ڣ�������" << std::endl;
			continue;
		}
		while (true) {
			std::cout << "����������";
			std::cin >> c;
			if (c > shop.getGood(index).getCount()) {
				std::cout << "\n�������������������" << std::endl;
				continue;
			}
			break;
		}
		cart.setGood(shop.getGood(index), c);
		std::cout << "\n��Ʒ������빺�ﳵ�У�" << std::endl;
	}
}

void consumer::changeCipher() {//�û��޸�����
	system("cls");
	while (true) {
		std::string new_c_1, new_c_2;
		std::cout << "\n�����������룺" << std::endl;
		std::cin >> new_c_1;
		std::cout << "��ȷ�������룺" << std::endl;
		std::cin >> new_c_2;
		if (new_c_1 == new_c_2) {
			setCipher(new_c_1);
			std::cout << "\n�����Ѿ��޸���ɣ�" << std::endl;
			break;
		}
		else {
			std::cout << "\n�������벻һ�£�����������" << std::endl;
		}
	}
}

void consumer::searchGoods(database& shop) {//�û���ѯ��Ʒ
	system("cls");
	std::string key;
	std::cout << "\n��������Ҫ��ѯ����Ʒ�����ƻ�ؼ��֣�";
	std::cin >> key;
	std::cout << "\n------�����ƷΪ------" << std::endl;
	std::cout << "\n\t��Ʒ����\t�۸�\t����\t\t���\t" << std::endl;
	int j = 0, num = shop.getNumOfGoods(), flag = 0;
	for (j; j < num; j++) {
		good& temp = shop.getGood(j);
		if (key == temp.getName()) {
			std::cout << "|\t" << temp.getName() << "\t\t" << temp.getPrice() << "\t" << temp.getInfo() << "\t\t" << temp.getCount() << "\t|" << std::endl;
			flag++;
			break;
		}
	}
	if (j == num) {//���û�����û�����������ȫһ������Ʒ���������ص���Ʒ
		for (int i = 0; i < num; i++) {
			good& temp = shop.getGood(i);
			if (match(key, temp.getName())) {
				std::cout << "|\t" << temp.getName() << "\t\t" << temp.getPrice() << "\t" << temp.getInfo() << "\t\t" << temp.getCount() << "\t|" << std::endl;
				flag++;//��־
			}
		}
	}
	if (!flag) std::cout << "��Ǹ����ʱû��������Ʒqwq" << std::endl;
}

void consumer::myCart(database& shop) {//�û����ﳵҳ��
	while (true) {
		//system("cls");
		cart.history.load();
		std::cout << "\n------ " << getName() << "�Ĺ��ﳵ------" << std::endl;
		cart.showCart();
		std::cout << "\n[A]ɾ�����ﳵ����Ʒ" << std::endl;
		std::cout << "[B]�޸���Ʒ��������" << std::endl;
		std::cout << "[C]������Ʒ" << std::endl;
		std::cout << "[D]�鿴��ʷ��¼��Ʒ" << std::endl;
		std::cout << "[E]�˳����ﳵ" << std::endl;
		std::cout << "\n��ѡ�����Ĳ�����" << std::endl;
		std::string car_button;
		std::cin >> car_button;
		if (car_button == "A") {//ɾ��Ԥ����Ʒ
			std::cout << "\n��������Ԥɾ������Ʒ���ƣ�" << std::endl;
			std::string n;
			std::cin >> n;
			bool flag = cart.deleteGood(n);
			if (flag == true) std::cout << "��ɾ����" << std::endl;
		}
		else if (car_button == "B") {//�޸�Ԥ����Ʒ����
			std::cout << "\n��������Ԥ�޸ĵ���Ʒ���ƣ�" << std::endl;
			std::string n;
			std::cin >> n;
			int index = shop.good_exist(n);//�ҵ�����е���Ʒ��Ϣ
			cart.changeGood(n, shop.getGood(index).getCount());
		}
		else if (car_button == "C") {//������Ʒ
			std::cout << "\n��������Ԥ�������Ʒ���ƣ��Կո�ֿ�,����q����" << std::endl;
			std::string test[maxnum]; int i;
			for (i = 0; ; i++) {
				std::cin >> test[i];
				if (test[i] == "q") break;
			}
			cart.clear(test, i, shop);
		}
		else if (car_button == "D") {//�鿴��ʷ��¼
			cart.showHistory();
		}
		else if (car_button == "E") {//�˳��û����ﳵ
			break;
		}
		else std::cout << "\n������Ĳ��������ڣ������³���" << std::endl;
		Sleep(300);
	}
}