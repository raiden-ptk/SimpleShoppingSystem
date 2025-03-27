#pragma once
#ifndef DATABASE
#define DATABASE

class consumer;
#include"consumer.h"
#include"good.h"
#include"manager.h"
#include<fstream>
#define CONSUMERFILE "consumers.txt"
#define GOODSFILE "goods.txt"

class database {//���ݿ��࣬���ڱ���������Ϣ
	friend class manager;//�Թ���Ա����
private:
	consumer consumers[maxnum];//�������й˿�
	good goods[maxnum];//����������Ʒ
	manager man;//����һ������Ա
	int numOfconsu = 0;//���й˿͵�����
	int numOfgoods = 0;//������Ʒ������
	const int numOfman = 1;//���ҽ���һ������Ա
	std::string code_ran[5] = { "bh150021037","bh528728347","bh462427648","bh283738110","EOC" };//Ԥ�����ȯ��ȯ��
	std::string code_lim[5] = { "ml51093930","ml66872680","ml40056740","ml78111961","EOC" };//Ԥ������ȯ��ȯ��
public:
	database() {

	}
	bool consu_exist(long long p);//�ж�һ���û��Ƿ��Ѿ�ע��
	int good_exist(std::string name);//�ж�һ����Ʒ�Ƿ���ڣ������ڷ������±�
	bool setConsumer(long long p, std::string n, std::string c);//����û�
	consumer& getConsumer(long long p);//�ó�һ���û�
	manager& getManager() {//�ó�����Ա
		return man;
	}
	good& getGood(int i) {//�ó���Ʒ
		return goods[i];
	}
	int getNumOfGoods() {//������Ʒ����
		return numOfgoods;
	}
	void conSignUp();//�û�ע��
	void conSignIn();//�û���¼
	void manSignIn();//����Ա��¼
	void showGoods();//�����Ʒ
	void reduceGood(std::string n, int c);//���ٿ��
	int code_exist(std::string c);//��֤ȯ���Ƿ���ȷ
	bool database_Init();//��ʼ������ϵͳ
};
#endif