#include<iostream>
#include"database.h"
int main() {
	database shop;//һ���̵�����ݿ�
	shop.database_Init();
	while (true) {
		system("cls");
		std::cout << "\n------���繺��ϵͳ��ҳ------" << std::endl;
		std::cout << "\n[A]�û�ע��" << std::endl;
		std::cout << "[B]�û���¼" << std::endl;
		std::cout << "[C]�����Ʒ" << std::endl;
		std::cout << "[D]����Աѡ��" << std::endl;
		std::cout << "[E]�˳�" << std::endl;
		std::cout << "\n��ѡ�����Ĳ�����" << std::endl;

		std::string button;
		std::cin >> button;

		if (button == "A") {//�����û�ע��
			shop.conSignUp();
		}
		else if (button == "B") {//�û���¼
			shop.conSignIn();
		}
		else if (button == "C") {//�����Ʒ
			shop.showGoods();
		}
		else if (button == "D") {//����Աѡ��
			shop.manSignIn();
		}
		else if (button == "E") {
			break;
		}
		else {
			std::cout << "���ṩ�ķ���ѡ�����������³���QwQ" << std::endl;
		}
		Sleep(700);
	}
}