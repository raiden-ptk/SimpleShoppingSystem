#include"database.h"
void database::showGoods() {//展示货架信息
	system("cls");
	std::cout << "\n------商品信息------\n" << std::endl;
	if (!numOfgoods) {
		std::cout << "当前货架为空qwq" << std::endl;
		return;
	}
	std::cout << "\t商品名称\t价格\t描述\t\t库存\t" << std::endl;
	for (int i = 0; i < numOfgoods; i++) {
		std::cout << "|\t" << goods[i].getName() << "\t\t" << goods[i].getPrice() << "\t" << goods[i].getInfo() << "\t\t" << goods[i].getCount() << "\t|" << std::endl;
	}
}

bool database::consu_exist(long long p) {//查找一个用户是否已经存在
	for (int i = 0; i < numOfconsu; i++) {
		if (p == consumers[i].getPhone()) {
			return true;
		}
	}
	return false;
}

int database::good_exist(std::string name) {//查找一份商品是否已经存在
	for (int i = 0; i < numOfgoods; i++) {
		if (name == goods[i].getName()) {
			return i;//返回商品位置
		}
	}
	return -1;
}

int database::code_exist(std::string c) {//验证券码是否正确，若正确返回优惠金额
	int rad = rand() % 9 + 2;//取得2到10之间的随机数
	for (int i = 0; code_ran[i] != "EOC"; i++) {//先在随机券中进行检索
		if (c == code_ran[i]) return code_ran[i][rad] - '0';//通过随机数对应字符与'0'的差值确定券的金额
	}
	for (int i = 0; code_lim[i] != "EOC"; i++) {//再在满减券中进行检索
		if (c == code_lim[i]) return (code_lim[i][2] - '0') * 100 + (code_lim[i][8] - '0') * 10;
	}
	return -1;//没有找到对应券码
}

void database::reduceGood(std::string n, int c) {//减少某件商品的库存
	int index = good_exist(n);
	goods[index].count -= c;
}

bool database::setConsumer(long long p, std::string n, std::string c) {//加入一个用户
	if (consu_exist(p)) return false;
	consumers[numOfconsu].setPhone(p);
	consumers[numOfconsu].setName(n);
	consumers[numOfconsu].setCipher(c);

	//向文件中保存一个用户
	std::ofstream ofs;
	ofs.open(CONSUMERFILE, std::ios::out|std::ios::app);
	ofs << p << ' ' << n << ' ' << c << ' ' << std::endl;

	numOfconsu++;
	return true;
}

bool database::database_Init() {//系统初始化
	std::ifstream ifs;//用户信息初始化
	ifs.open(CONSUMERFILE, std::ios::in);
	long long p;
	std::string n, c;

	while (ifs >> p && ifs >> n && ifs >> c) {
		consumers[numOfconsu].setPhone(p);
		consumers[numOfconsu].setName(n);
		consumers[numOfconsu].setCipher(c);
		consumers[numOfconsu].cartInit();//用户购物车初始化
		numOfconsu++;
	}

	ifs.close();

	//商品信息初始化
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

consumer& database::getConsumer(long long p) {//拿出一个用户
	for (int i = 0; i < numOfconsu; i++) {
		if (p == consumers[i].getPhone()) {
			return consumers[i];
		}
	}
}

void database::conSignUp() {//用户注册
	long long p;
	long long min = 10000000000;
	long long max = 99999999999;
	std::string n, c;
	system("cls");
	std::cout << "\n------用户注册------" << std::endl;
	while (true) {
		std::cout << "请输入您的电话号码：" << std::endl;
		std::cin >> p;
		if (p<min || p>max) {
			std::cout << "\n您输入的号码长度有误，请重新尝试" << std::endl;
		}
		else break;
	}
	std::cout << "请输入您的用户名：" << std::endl;
	std::cin >> n;
	std::cout << "请输入您的密码：" << std::endl;
	std::cin >> c;
	if (setConsumer(p, n, c)) {
		std::cout << "\n用户注册成功！" << std::endl;
	}
	else std::cout << "\n用户已经存在！" << std::endl;
}

void database::conSignIn() {//用户登录
	system("cls");
	std::cout << "\n请输入您的电话号码：" << std::endl;
	long long p;
	int i = 3;//输入密码次数
	std::string c;
	std::cin >> p;
	if (consu_exist(p)) {
		consumer& temp = getConsumer(p);//为其创建一个用户对象
		for (i; i > 0;) {
			std::cout << "请输入您的密码：" << std::endl;
			std::cin >> c;
			if (temp.judgeCipher(c)) {
				std::cout << "\n登陆成功！" << std::endl;
				//随机派送优惠券
				//int rad = rand() % 10;//生成0-9之间的随机数
				int rad = 7;
				if (rad < 4) {
					temp.haveCode();//用户获得优惠券
					std::cout << "\nLucky!恭喜您获得随机数额的优惠券一张，券码为：" << code_ran[rad] << "请尽快使用哦！" << std::endl;
				}
				else if (rad >= 4) {
					temp.haveCode();//用户获得优惠券
					std::string code_l = code_lim[rad % 4];
					std::cout << "\nLucky!恭喜您获得满"<<(code_l[2]-'0')*100 << "减"<<(code_l[8]-'0')*10<< "券一张，券码为：" << code_l << "请尽快使用哦！" << std::endl;
				}
				break;
			}
			else std::cout << "\n您输入的密码有误，您还有：" << --i << "次机会" << std::endl;
		}
		if (i > 0) {//登陆成功
			temp.consumerPage(*(this));//则唤起用户页面
		}
		else {
			std::cout << "\n密码输入错误次数过多，您的账户已被冻结" << std::endl;
		}
	}
	else std::cout << "\n您的账户不存在，请先进行注册" << std::endl;
}

void database::manSignIn() {//管理员登陆
	system("cls");
	manager& m = getManager();
	std::cout << "\n请输入管理员账号：" << std::endl;
	int i = 3;//输入密码次数
	std::string n, c;
	std::cin >> n;
	if (m.judgeName(n)) {//如果正确输入了管理员账号
		for (i; i > 0;) {
			std::cout << "请输入管理员账户的密码：" << std::endl;
			std::cin >> c;
			if (m.judgeCipher(c)) {
				std::cout << "\n登陆成功！" << std::endl;
				break;
			}
			else std::cout << "\n您输入的密码有误，您还有：" << --i << "次机会" << std::endl;
		}
		if (i > 0) {//登陆成功了,则唤起管理员界面
			m.managerPage(*(this));
		}
		else {//登录未成功
			std::cout << "\n密码输入错误次数过多，您的账户已被冻结" << std::endl;
		}
	}
	else std::cout << "\n您输入的管理员账号不存在！" << std::endl;
}