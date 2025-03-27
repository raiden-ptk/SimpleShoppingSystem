#include"Record.h"
#pragma warning(disable : 4996)
void Record::show() {
        std::cout << "请选择时间段：" << std::endl;
        std::cout << "1. 1分钟" << std::endl;
        std::cout << "2. 1小时" << std::endl;
        std::cout << "3. 1天" << std::endl;

        int choice;
        std::cin >> choice;

        time_t nowtime;
        time(&nowtime);
        tm* p = localtime(&nowtime);//获取当前时间

        if (choice == 1) {
            int count = 0;
            std::cout << "\n在过去1min内购买的商品：" << std::endl;
            std::cout << "\t商品名称\t价格\t描述\t\t数目\t" << std::endl;
            for (const auto& entry : data) {
                if (p->tm_min-entry.min<=1&&p->tm_min-entry.min>=0) {
                    count++;
                    std::cout << "|\t" << entry.name << "\t\t" << entry.price << "\t" << entry.info << "\t\t" << entry.cnt << "\t|"
                        << entry.year << ':' << entry.month
                        << ':' << entry.day << ' ' << entry.hour << ':' << entry.min << std::endl;
                }
            }
            if (count == 0) std::cout << "\n未找到购买记录" << std::endl;
        }
        else if (choice == 2) {
            int count = 0;
            std::cout << "\n在过去1hour内购买的商品：" << std::endl;
            std::cout << "\t商品名称\t价格\t描述\t\t数目\t" << std::endl;
            for (const auto& entry : data) {
                if (p->tm_hour - entry.hour <= 1 && p->tm_hour - entry.hour >= 0) {
                    count++;
                    std::cout << "|\t" <<entry.name<< "\t\t" << entry.price << "\t" <<entry.info << "\t\t" <<entry.cnt << "\t|"
                        <<entry.year << ':' << entry.month
                        << ':' << entry.day << ' ' << entry.hour << ':' << entry.min << std::endl;
                }
            }
            if (count == 0) std::cout << "\n未找到购买记录" << std::endl;
        }
        else if (choice == 3) {
            int count = 0;
            std::cout << "\n在过去1day内购买的商品：" << std::endl;
            std::cout << "\t商品名称\t价格\t描述\t\t数目\t" << std::endl;
            for (const auto& entry : data) {
                if (p->tm_mday - entry.day <= 1 && p->tm_mday - entry.day >= 0) {
                    count++;
                    std::cout << "|\t" << entry.name << "\t\t" << entry.price << "\t" << entry.info << "\t\t" << entry.cnt << "\t|"
                        << entry.year << ':' << entry.month
                        << ':' << entry.day << ' ' << entry.hour << ':' << entry.min << std::endl;
                }
            }
            if (count == 0) std::cout << "\n未找到购买记录" << std::endl;
        }
}

void Record::save(std::string name, int price, std::string info, int cnt) {
    Entry entry;
    //保存商品信息
    entry.name = name;
    entry.price = price;
    entry.info = info;
    entry.cnt = cnt;
    //保存时间信息
    time_t nowtime;
    time(&nowtime);
    tm* p = localtime(&nowtime);
    entry.year = p->tm_year + 1900;
    entry.month = p->tm_mon + 1;
    entry.day = p->tm_mday;
    entry.hour = p->tm_hour;
    entry.min = p->tm_min;
    data.push_back(entry);//存入数组
    std::ofstream ofs(filename, std::ios::binary|std::ios::app);
    ofs << name << ' ' << price << ' ' << info << ' ' << cnt << ' ' << entry.year << ' ' << entry.month << ' ' << entry.day << ' ' << entry.hour << ' ' << entry.min << std::endl;


}

void Record::load() {
        data.clear();
        std::ifstream in(filename, std::ios::binary);
        std::string n, inf;
        int p, c;//记录购买商品信息
        int y, m, d, h, mi;//记录购买商品时间
        while (in >>n>>p>>inf>>c>> y >> m>>d>>h>>mi) {//name/price/info/count/year/month/day/hour/min顺序读取
            Entry entry;
            entry.name = n;//依次存入记录
            entry.price = p;
            entry.info = inf;
            entry.cnt = c;
            entry.year = y;
            entry.month = m;
            entry.hour = h;
            entry.day = d;
            entry.min = mi;
            data.push_back(entry);
        }
        in.close();
}