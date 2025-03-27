#include"shoppingCart.h"
#include"database.h"
int shoppingCart::findGood(std::string n) {//������Ʒ�ڹ��ﳵ��λ��
	for (int index = 0; index < numOfgoods; index++) {
		if (goods[index].getName() == n) {//�ҵ���Ʒ�����±�
			return index;
		}
	}
	return -1;
}

void shoppingCart::showCart() {//չʾ���ﳵ�е���Ʒ
	//system("cls");
	std::cout << "\n------���ﳵ��Ϣ------\n" << std::endl;
	if (!numOfgoods) {
		std::cout << "��ǰ���ﳵΪ��qwq" << std::endl;
		return;
	}
	std::cout << "\t��Ʒ����\t�۸�\t����\t\t��Ŀ\t" << std::endl;
	for (int i = 0; i < numOfgoods; i++) {
		std::cout << "|\t" << goods[i].getName() << "\t\t" << goods[i].getPrice() << "\t" << goods[i].getInfo() << "\t\t" << goods[i].getCount() << "\t|" << std::endl;
	}
	std::cout << "\n��ǰ�����ܼƽ��Ϊ��" << sumPrice << std::endl;
}

bool shoppingCart::deleteGood(std::string n) {//ɾ�����ﳵ����Ʒ
	int index = findGood(n);
	if (index != -1) {//�ҵ���Ҫɾ������Ʒ
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
		std::cout << "\n���������Ʒ������,����������" << std::endl;
		return false;
	}
}

void shoppingCart::changeGood(std::string n, int maxCount) {//���Ĺ��ﳵ�е���Ϣ
	system("cls");
	std::cout << "\n�����������������Ʒ�Ĺ�������" << std::endl;
	int c;
	while (true) {
		std::cin >> c;
		if (!c) {
			deleteGood(n);
			break;
		}
		else if (c > maxCount) {
			std::cout << "������ǰ��Ʒ������������������룬��ǰ�����Ϊ��" << maxCount << std::endl;
		}
		else if (c < 0) {
			std::cout << "���������Ŀ����ȷ������������" << std::endl;
		}
		else {
			int index = findGood(n);
			sumPrice += (c - goods[index].count) * goods[index].price;
			goods[index].count = c;
			std::cout << "\n���޸ģ�" << std::endl;
			break;
		}
	}
}

void shoppingCart::clear(std::string* test, int c, database& shop) {//��Ʒ����
	system("cls");
	std::cout << "\n\t��Ʒ����\t�۸�\t����\t\t��Ŀ\t" << std::endl;
	int sump = 0;
	int* reduce = new int[c];//��¼Ҫ�������Ʒ�ĸ���
	int* restInshop = new int[c];//��¼���������е���Ʒ��Ŀ

	for (int i = 0; i < c; i++) {//���������������Ʒ��Ŀ
		int index = shop.good_exist(test[i]);
		restInshop[i] = shop.getGood(index).getCount();
	}

	for (int i = 0; i < c; i++) {
		int index = findGood(test[i]);
		if (index != -1 && goods[index].getCount() <= restInshop[i]) {//����ڹ��ﳵ���ҵ���Ҫ�������Ʒ������Ʒ���㹻����չʾ����Ϣ
			std::cout << "|\t" << goods[index].getName() << "\t\t" << goods[index].getPrice() << "\t" << goods[index].getInfo() << "\t\t" << goods[index].getCount() << "\t|" << std::endl;
			reduce[i] = goods[index].getCount();
			sump += goods[index].price * goods[index].count;
		}
		else if (index != -1 && goods[index].getCount() > restInshop[i]) {//����ڹ��ﳵ���ҵ���Ҫ�������Ʒ�����ǻ�����ʣ�����Ʒ����
			std::cout << "��Ʒ" << goods[index].getName() << "��治�㣬��ʣ��" << restInshop[i] << "�������޸Ĺ�����Ŀ";
			return;
		}
		else {
			std::cout << "\n���������Ʒ��Ϣ���д���������" << std::endl;
			return;
		}
	}
	std::cout << "\n��ǰѡ��������Ʒ�ܼƽ��Ϊ��" << sump << std::endl;

	int q = -1;//ȯ��ʹ��
	if (haveCode> 0) {
		std::cout << "\n������ӵ���Ż�ȯ����������ȯ��ʹ��" << std::endl;
		std::string b_button;
		while (true) {
			std::cout << "\n�Ƿ�ʹ���Ż�ȯ��(Y/N)" << std::endl;
			std::cin >> b_button;
			if (b_button == "Y") {
				std::cout << "\n������ȯ�룺" << std::endl;
				std::string code;
				std::cin >> code;
				q = shop.code_exist(code);
				if (q == -1) std::cout << "\n�������ȯ�벻����Чȯ��" << std::endl;
				else if(q < 100) {
					haveCode--;//ӵ�е��Ż�ȯ����һ
					break;
				}
				else if (q > 100) {
					if (sump < q - q % 100) {//��������������
						std::cout << "\n��Ǹ��"<<", ��ȯΪ��"<<q -q%100<<"��"<<q%100<<"Ԫ����ȯ" <<",�������ܼ۲������ȯҪ�����������" << std::endl;
					}
					else {
						haveCode--;//ӵ�е��Ż�ȯ����һ
						break;
					}
				}
			}
			else if (b_button == "N") {
				break;
			}
			else std::cout << "\n��������ȷѡ��" << std::endl;
		}
	}
	std::cout << "\n��ȷ�Ͻ�����(Y/N)";
	if (q == -1) std::cout << ",��ǰѡ��������Ʒ�ܼƽ��Ϊ��" << sump << std::endl;//δʹ�û���δ�ɹ�ʹ��
	else if(q<100)std::cout << ",��ǰѡ��������Ʒ�ܼƽ��Ϊ��" << sump << "-" << q << "=" << ((sump - q)>0?(sump-q):0 )<< "Ԫ" << std::endl;//�ɹ�ʹ�����ȯ
	else if (q > 100) {
		std::cout <<",ʹ����"<<q -q%100<<"��"<<q%100<<"Ԫ����ȯ��" << ", ��ǰѡ��������Ʒ�ܼƽ��Ϊ��" << sump << " - " << q % 100 << " = " << ((sump - q % 100)>0?(sump-q%100):0) << "Ԫ" << std::endl;//�ɹ�ʹ������ȯ
	}

	std::string s;
	std::cin >> s;
	while (true) {
		if (s == "Y") {//ȷ�Ͻ���
			for (int i = 0; i < c; i++) {
				int index = findGood(test[i]);
				history.save(goods[index].getName(), goods[index].getPrice(), goods[index].getInfo(), goods[index].getCount());
				//�����빺���¼
				deleteGood(test[i]);
				shop.reduceGood(test[i], reduce[i]);
			}
			break;
		}
		else if (s == "N") return;
		else std::cout << "\n��������ȷѡ��" << std::endl;
	}
	std::cout << "\n����ɹ���" << std::endl;
}

bool shoppingCart::saveCart() {//���湺�ﳵ����Ʒ
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

bool shoppingCart::cart_Init() {//��ʼ�����ﳵ
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