#ifndef CONSUMER
#define CONSUMER
class shoppingCart;
#include<iostream>
#include<Windows.h>
#include"shoppingCart.h"
#include"tools.h"

class consumer {//�û���
private:
	shoppingCart cart;//���ﳵ
	long long phone = 123456;//�û��ĵ绰����
	std::string name = "name";//�û���
	std::string cipher = "cipher";//�û�����
	void changeCipher();//�޸�����
	void buyGoods(database& shop);//������Ʒ
	void searchGoods(database& shop);//�û�������Ʒ
	void myCart(database& shop);//�鿴���ﳵ
public:
	consumer(std::string n, std::string c) :name(n), cipher(c) {};//����һ���û��˻�
	consumer() {

	}
	bool setPhone(long long p) {
		phone = p;
		return true;
	}
	bool setName(std::string n) {
		cart.setOwner(n);
		name = n;
		return true;
	}
	bool setCipher(std::string c) {
		cipher = c;
		return true;
	}
	long long getPhone() {
		return phone;
	}
	std::string getName() {
		return name;
	}
	bool judgeCipher(std::string c) {//�ж������Ƿ���ȷ
		if (c == cipher) return true;
		return false;
	}
	void consumerPage(database& shop);//�����û�����
	void lookGoods(database& shop);//�����Ʒ
	void haveCode() {//�����Ż�ȯ
		cart.setCode();
	}
	bool cartInit() {//���ﳵ��ʼ��
		cart.cart_Init();
		return true;
	}
};

#endif