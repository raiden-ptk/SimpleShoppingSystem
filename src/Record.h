#pragma once
#ifndef RECORD
#define RECORD

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>

class Record {//存储购买记录
    friend class shoppingCart;
private:
    struct Entry {//结构体，存储购买信息
        std::string name, info;
        int price, cnt;//记录购买商品信息
        int year, month, day, hour, min;//记录购买商品时间
    };

    std::vector<Entry> data;
    std::string filename;

public:
    Record() {

    }
    Record(const std::string& filename) : filename(filename) {
        load();//载入历史记录
    }
    void save(std::string name,int price,std::string info,int cnt);//保存并计入文件
    void show();//按时间展示购买记录
    void load();//载入
};

#endif