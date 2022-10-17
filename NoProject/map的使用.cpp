#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

// 无论哪种map 都是不能重复插入的，但是可以修改value值

typedef map<string, int> HeroMap; // < Name, ATK >
typedef HeroMap::iterator HeroIt;
typedef unordered_map<string, int> EquipmentMap; // < Name, ATK >
typedef EquipmentMap::iterator EquipIt;
void test01() {
	// 红黑树实现的map
	// 插入
	HeroMap _map;
	_map["赵云"] = 100;
	_map["李白"] = 104;

	_map.insert(HeroMap::value_type("廉颇", 75));

	// 查找
	HeroIt it = _map.find("李白");
	if (it == _map.end()) cout << "没找到!\n";
	else cout << "已找到!\n姓名:" << it->first << "\n基础攻击力:" << it->second << endl;

	// 删除
	HeroIt _it = _map.find("赵云");
	if (_it == _map.end()) cout << "没找到!\n";
	else {
		cout << "姓名:" << _it->first << "\n基础攻击力:" << _it->second << "\n已删除!\n";
		_map.erase(_it);
	}
	_map.erase("李白");
	cout << "已删除 李白\n" << endl;
	
	// 遍历
	HeroIt Tit = _map.begin();
	while (Tit != _map.end()) {
		cout << "姓名:" << Tit->first << " 基础攻击力:" << Tit->second << endl;
		Tit++;
	}
}

void test02() {
	//哈希表实现的hash_map
	// 插入
	EquipmentMap _map;
	_map["王者之剑"] = 200;
	_map["寒冰之矛"] = 300;

	_map.insert(EquipmentMap::value_type("嗜血之书", 250));

	// 查找
	EquipIt it = _map.find("王者之矛");
	if (it == _map.end()) cout << "没找到!\n";
	else cout << "已找到!\n名称:" << it->first << "\n装备攻击力:" << it->second << endl;

	// 删除
	EquipIt _it = _map.find("嗜血之书");
	if (_it == _map.end()) cout << "没找到!\n";
	else {
		cout << "名称:" << _it->first << "\n装备攻击力:" << _it->second << "\n已删除!\n";
		_map.erase(_it);
	}
	_map.erase("王者之剑");
	cout << "已删除 王者之剑\n" << endl;

	//遍历
	EquipIt Tit = _map.begin();
	while (Tit != _map.end()) {
		cout << "名称:" << Tit->first << " 装备攻击力:" << Tit->second << endl;
		Tit++;
	}
}

int main() {
	test01();
	test02();
	return 0;
}
