#include"Record.h"
#pragma warning(disable : 4996)
void Record::show() {
        std::cout << "��ѡ��ʱ��Σ�" << std::endl;
        std::cout << "1. 1����" << std::endl;
        std::cout << "2. 1Сʱ" << std::endl;
        std::cout << "3. 1��" << std::endl;

        int choice;
        std::cin >> choice;

        time_t nowtime;
        time(&nowtime);
        tm* p = localtime(&nowtime);//��ȡ��ǰʱ��

        if (choice == 1) {
            int count = 0;
            std::cout << "\n�ڹ�ȥ1min�ڹ������Ʒ��" << std::endl;
            std::cout << "\t��Ʒ����\t�۸�\t����\t\t��Ŀ\t" << std::endl;
            for (const auto& entry : data) {
                if (p->tm_min-entry.min<=1&&p->tm_min-entry.min>=0) {
                    count++;
                    std::cout << "|\t" << entry.name << "\t\t" << entry.price << "\t" << entry.info << "\t\t" << entry.cnt << "\t|"
                        << entry.year << ':' << entry.month
                        << ':' << entry.day << ' ' << entry.hour << ':' << entry.min << std::endl;
                }
            }
            if (count == 0) std::cout << "\nδ�ҵ������¼" << std::endl;
        }
        else if (choice == 2) {
            int count = 0;
            std::cout << "\n�ڹ�ȥ1hour�ڹ������Ʒ��" << std::endl;
            std::cout << "\t��Ʒ����\t�۸�\t����\t\t��Ŀ\t" << std::endl;
            for (const auto& entry : data) {
                if (p->tm_hour - entry.hour <= 1 && p->tm_hour - entry.hour >= 0) {
                    count++;
                    std::cout << "|\t" <<entry.name<< "\t\t" << entry.price << "\t" <<entry.info << "\t\t" <<entry.cnt << "\t|"
                        <<entry.year << ':' << entry.month
                        << ':' << entry.day << ' ' << entry.hour << ':' << entry.min << std::endl;
                }
            }
            if (count == 0) std::cout << "\nδ�ҵ������¼" << std::endl;
        }
        else if (choice == 3) {
            int count = 0;
            std::cout << "\n�ڹ�ȥ1day�ڹ������Ʒ��" << std::endl;
            std::cout << "\t��Ʒ����\t�۸�\t����\t\t��Ŀ\t" << std::endl;
            for (const auto& entry : data) {
                if (p->tm_mday - entry.day <= 1 && p->tm_mday - entry.day >= 0) {
                    count++;
                    std::cout << "|\t" << entry.name << "\t\t" << entry.price << "\t" << entry.info << "\t\t" << entry.cnt << "\t|"
                        << entry.year << ':' << entry.month
                        << ':' << entry.day << ' ' << entry.hour << ':' << entry.min << std::endl;
                }
            }
            if (count == 0) std::cout << "\nδ�ҵ������¼" << std::endl;
        }
}

void Record::save(std::string name, int price, std::string info, int cnt) {
    Entry entry;
    //������Ʒ��Ϣ
    entry.name = name;
    entry.price = price;
    entry.info = info;
    entry.cnt = cnt;
    //����ʱ����Ϣ
    time_t nowtime;
    time(&nowtime);
    tm* p = localtime(&nowtime);
    entry.year = p->tm_year + 1900;
    entry.month = p->tm_mon + 1;
    entry.day = p->tm_mday;
    entry.hour = p->tm_hour;
    entry.min = p->tm_min;
    data.push_back(entry);//��������
    std::ofstream ofs(filename, std::ios::binary|std::ios::app);
    ofs << name << ' ' << price << ' ' << info << ' ' << cnt << ' ' << entry.year << ' ' << entry.month << ' ' << entry.day << ' ' << entry.hour << ' ' << entry.min << std::endl;


}

void Record::load() {
        data.clear();
        std::ifstream in(filename, std::ios::binary);
        std::string n, inf;
        int p, c;//��¼������Ʒ��Ϣ
        int y, m, d, h, mi;//��¼������Ʒʱ��
        while (in >>n>>p>>inf>>c>> y >> m>>d>>h>>mi) {//name/price/info/count/year/month/day/hour/min˳���ȡ
            Entry entry;
            entry.name = n;//���δ����¼
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