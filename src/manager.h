#ifndef MANAGER
#define MANAGER
#include<iostream>
class database;

class manager {//����Ա�ࣺ��¼/�޸���Ʒ��Ϣ/�ϼ�/�¼�
private:
	std::string name = "ad";//��ǰԤ����˻�
	std::string cipher = "123";//��ǰԤ�������
	void addGoods(database& shop);//�����Ʒ
	void deleteGoods(database& shop);//ɾ����Ʒ
	void changeGoods(database& shop);//�޸���Ʒ
public:
	bool judgeName(std::string n) {//�ж��������Ա��Ϣ�Ƿ���ȷ
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