#include"tools.h"
bool match(std::string key, std::string name) {//�ж��Ƿ��к��û�����Ĺؼ�����ص���Ʒ
	int key_len = key.length();
	int name_len = name.length();
	for (int i = 0; i < key_len; i++) {
		for (int j = 0; j < name_len; j++) {
			if (key[i] == name[j]) return 1;
		}
	}
	return 0;
}