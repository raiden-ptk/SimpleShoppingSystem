#include"database.h"
void database::showGoods() {//չʾ������Ϣ
	system("cls");
	std::cout << "\n------��Ʒ��Ϣ------\n" << std::endl;
	if (!numOfgoods) {
		std::cout << "��ǰ����Ϊ��qwq" << std::endl;
		return;
	}
	std::cout << "\t��Ʒ����\t�۸�\t����\t\t���\t" << std::endl;
	for (int i = 0; i < numOfgoods; i++) {
		std::cout << "|\t" << goods[i].getName() << "\t\t" << goods[i].getPrice() << "\t" << goods[i].getInfo() << "\t\t" << goods[i].getCount() << "\t|" << std::endl;
	}
}

bool database::consu_exist(long long p) {//����һ���û��Ƿ��Ѿ�����
	for (int i = 0; i < numOfconsu; i++) {
		if (p == consumers[i].getPhone()) {
			return true;
		}
	}
	return false;
}

int database::good_exist(std::string name) {//����һ����Ʒ�Ƿ��Ѿ�����
	for (int i = 0; i < numOfgoods; i++) {
		if (name == goods[i].getName()) {
			return i;//������Ʒλ��
		}
	}
	return -1;
}

int database::code_exist(std::string c) {//��֤ȯ���Ƿ���ȷ������ȷ�����Żݽ��
	int rad = rand() % 9 + 2;//ȡ��2��10֮��������
	for (int i = 0; code_ran[i] != "EOC"; i++) {//�������ȯ�н��м���
		if (c == code_ran[i]) return code_ran[i][rad] - '0';//ͨ���������Ӧ�ַ���'0'�Ĳ�ֵȷ��ȯ�Ľ��
	}
	for (int i = 0; code_lim[i] != "EOC"; i++) {//��������ȯ�н��м���
		if (c == code_lim[i]) return (code_lim[i][2] - '0') * 100 + (code_lim[i][8] - '0') * 10;
	}
	return -1;//û���ҵ���Ӧȯ��
}

void database::reduceGood(std::string n, int c) {//����ĳ����Ʒ�Ŀ��
	int index = good_exist(n);
	goods[index].count -= c;
}

bool database::setConsumer(long long p, std::string n, std::string c) {//����һ���û�
	if (consu_exist(p)) return false;
	consumers[numOfconsu].setPhone(p);
	consumers[numOfconsu].setName(n);
	consumers[numOfconsu].setCipher(c);

	//���ļ��б���һ���û�
	std::ofstream ofs;
	ofs.open(CONSUMERFILE, std::ios::out|std::ios::app);
	ofs << p << ' ' << n << ' ' << c << ' ' << std::endl;

	numOfconsu++;
	return true;
}

bool database::database_Init() {//ϵͳ��ʼ��
	std::ifstream ifs;//�û���Ϣ��ʼ��
	ifs.open(CONSUMERFILE, std::ios::in);
	long long p;
	std::string n, c;

	while (ifs >> p && ifs >> n && ifs >> c) {
		consumers[numOfconsu].setPhone(p);
		consumers[numOfconsu].setName(n);
		consumers[numOfconsu].setCipher(c);
		consumers[numOfconsu].cartInit();//�û����ﳵ��ʼ��
		numOfconsu++;
	}

	ifs.close();

	//��Ʒ��Ϣ��ʼ��
	ifs.open(GOODSFILE, std::ios::in);
	std::string name, info;
	int price, count;

	while (ifs >> name && ifs >> price && ifs >> info && ifs >> count) {
		goods[numOfgoods].name = name;
		goods[numOfgoods].price = price;
		goods[numOfgoods].info = info;
		goods[numOfgoods].count = count;
		numOfgoods++;
	}


	return true;
}

consumer& database::getConsumer(long long p) {//�ó�һ���û�
	for (int i = 0; i < numOfconsu; i++) {
		if (p == consumers[i].getPhone()) {
			return consumers[i];
		}
	}
}

void database::conSignUp() {//�û�ע��
	long long p;
	long long min = 10000000000;
	long long max = 99999999999;
	std::string n, c;
	system("cls");
	std::cout << "\n------�û�ע��------" << std::endl;
	while (true) {
		std::cout << "���������ĵ绰���룺" << std::endl;
		std::cin >> p;
		if (p<min || p>max) {
			std::cout << "\n������ĺ��볤�����������³���" << std::endl;
		}
		else break;
	}
	std::cout << "�����������û�����" << std::endl;
	std::cin >> n;
	std::cout << "�������������룺" << std::endl;
	std::cin >> c;
	if (setConsumer(p, n, c)) {
		std::cout << "\n�û�ע��ɹ���" << std::endl;
	}
	else std::cout << "\n�û��Ѿ����ڣ�" << std::endl;
}

void database::conSignIn() {//�û���¼
	system("cls");
	std::cout << "\n���������ĵ绰���룺" << std::endl;
	long long p;
	int i = 3;//�����������
	std::string c;
	std::cin >> p;
	if (consu_exist(p)) {
		consumer& temp = getConsumer(p);//Ϊ�䴴��һ���û�����
		for (i; i > 0;) {
			std::cout << "�������������룺" << std::endl;
			std::cin >> c;
			if (temp.judgeCipher(c)) {
				std::cout << "\n��½�ɹ���" << std::endl;
				//��������Ż�ȯ
				//int rad = rand() % 10;//����0-9֮��������
				int rad = 7;
				if (rad < 4) {
					temp.haveCode();//�û�����Ż�ȯ
					std::cout << "\nLucky!��ϲ��������������Ż�ȯһ�ţ�ȯ��Ϊ��" << code_ran[rad] << "�뾡��ʹ��Ŷ��" << std::endl;
				}
				else if (rad >= 4) {
					temp.haveCode();//�û�����Ż�ȯ
					std::string code_l = code_lim[rad % 4];
					std::cout << "\nLucky!��ϲ�������"<<(code_l[2]-'0')*100 << "��"<<(code_l[8]-'0')*10<< "ȯһ�ţ�ȯ��Ϊ��" << code_l << "�뾡��ʹ��Ŷ��" << std::endl;
				}
				break;
			}
			else std::cout << "\n��������������������У�" << --i << "�λ���" << std::endl;
		}
		if (i > 0) {//��½�ɹ�
			temp.consumerPage(*(this));//�����û�ҳ��
		}
		else {
			std::cout << "\n�����������������࣬�����˻��ѱ�����" << std::endl;
		}
	}
	else std::cout << "\n�����˻������ڣ����Ƚ���ע��" << std::endl;
}

void database::manSignIn() {//����Ա��½
	system("cls");
	manager& m = getManager();
	std::cout << "\n���������Ա�˺ţ�" << std::endl;
	int i = 3;//�����������
	std::string n, c;
	std::cin >> n;
	if (m.judgeName(n)) {//�����ȷ�����˹���Ա�˺�
		for (i; i > 0;) {
			std::cout << "���������Ա�˻������룺" << std::endl;
			std::cin >> c;
			if (m.judgeCipher(c)) {
				std::cout << "\n��½�ɹ���" << std::endl;
				break;
			}
			else std::cout << "\n��������������������У�" << --i << "�λ���" << std::endl;
		}
		if (i > 0) {//��½�ɹ���,�������Ա����
			m.managerPage(*(this));
		}
		else {//��¼δ�ɹ�
			std::cout << "\n�����������������࣬�����˻��ѱ�����" << std::endl;
		}
	}
	else std::cout << "\n������Ĺ���Ա�˺Ų����ڣ�" << std::endl;
}