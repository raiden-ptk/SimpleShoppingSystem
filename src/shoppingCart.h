#ifndef SHOPPINGCART
#define SHOPPINGCART
#define maxnum 100
#include"good.h"
#include"Record.h"
class database;

class shoppingCart {//���ﳵ��
	friend class consumer;
private:
	std::string owner="nobody";
	good goods[maxnum];//�������Ʒ��Ϣ
	int numOfgoods = 0;//���ﳵ����Ʒ��Ŀ
	int sumPrice = 0;//���ﳵ��Ʒ�ܼ۸�
	int haveCode = 0;//ӵ�е��Ż�ȯ��
	Record history;//�����¼
public:
	void setOwner(std::string n) {
		owner = n;
		history.filename = n + "_history.txt";
	}
	shoppingCart() {

	}
	int findGood(std::string n);//�ڹ��ﳵ�в�����Ʒ
	void showCart();//չʾ���ﳵ��Ϣ
	void setGood(good g, int c) {//���ﳵ�д�����Ʒ
		goods[numOfgoods].name = g.name;
		goods[numOfgoods].count = c;
		goods[numOfgoods].info = g.info;
		goods[numOfgoods].number = g.number;
		goods[numOfgoods].price = g.price;
		sumPrice += c * g.price;
		numOfgoods++;
	}
	bool deleteGood(std::string n);//ɾ�����ﳵ����Ʒ
	void changeGood(std::string n, int maxCount);//�޸�
	void clear(std::string* test, int c, database& shop);//���㹺�ﳵ����Ʒ
	void setCode() {//����Ż�ȯ
		haveCode++;
	}
	bool saveCart();
	bool cart_Init();
	void showHistory() {
		history.show();
	}
};
#endif