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

class database {//数据库类，用于保存所有信息
	friend class manager;//对管理员开放
private:
	consumer consumers[maxnum];//保存所有顾客
	good goods[maxnum];//保存所有商品
	manager man;//保存一个管理员
	int numOfconsu = 0;//现有顾客的数量
	int numOfgoods = 0;//现有商品的数量
	const int numOfman = 1;//有且仅有一个管理员
	std::string code_ran[5] = { "bh150021037","bh528728347","bh462427648","bh283738110","EOC" };//预设随机券的券码
	std::string code_lim[5] = { "ml51093930","ml66872680","ml40056740","ml78111961","EOC" };//预设满减券的券码
public:
	database() {

	}
	bool consu_exist(long long p);//判断一个用户是否已经注册
	int good_exist(std::string name);//判断一个商品是否存在，若存在返回其下标
	bool setConsumer(long long p, std::string n, std::string c);//添加用户
	consumer& getConsumer(long long p);//拿出一个用户
	manager& getManager() {//拿出管理员
		return man;
	}
	good& getGood(int i) {//拿出商品
		return goods[i];
	}
	int getNumOfGoods() {//返回商品数量
		return numOfgoods;
	}
	void conSignUp();//用户注册
	void conSignIn();//用户登录
	void manSignIn();//管理员登录
	void showGoods();//浏览商品
	void reduceGood(std::string n, int c);//减少库存
	int code_exist(std::string c);//验证券码是否正确
	bool database_Init();//初始化购物系统
};
#endif