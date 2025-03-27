#pragma once
#ifndef RECORD
#define RECORD

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>

class Record {//�洢�����¼
    friend class shoppingCart;
private:
    struct Entry {//�ṹ�壬�洢������Ϣ
        std::string name, info;
        int price, cnt;//��¼������Ʒ��Ϣ
        int year, month, day, hour, min;//��¼������Ʒʱ��
    };

    std::vector<Entry> data;
    std::string filename;

public:
    Record() {

    }
    Record(const std::string& filename) : filename(filename) {
        load();//������ʷ��¼
    }
    void save(std::string name,int price,std::string info,int cnt);//���沢�����ļ�
    void show();//��ʱ��չʾ�����¼
    void load();//����
};

#endif