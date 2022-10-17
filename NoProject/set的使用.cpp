#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;

typedef set<char> CharSet;
typedef set<char>::iterator CSetIt;
typedef unordered_set<char> USet;
typedef unordered_set<char>::iterator USetIt;
void test01() {
	CharSet set1;
	char sa[6] = { 'A', 'B', 'C', 'D', 'E', 'F' };
	CharSet set2;
	for (int i = 0; i < 6; i++) {
		set2.insert(sa[i]);
	}

	// 插入
	// 有序插入，始终放在顺序位置
	set1.insert('S');
	//CSetIt it = set1.end();
	set1.insert('B');

	for (CSetIt itt = set1.begin(); itt != set1.end(); itt++) {
		cout << *itt << " ";
	}
	cout << endl;

	// 查找
	CSetIt it = set2.find('B');
	if (it == set2.end()) cout << "没找到！\n";
	else cout << "找到了！\n" << *it << endl;

	// 删除
	if (set2.erase('C')) cout << "删除成功!\n";
	else cout << "删除失败!\n";
}

void test02() {
	// 插入
	USet set;
	set.insert('S');
	set.insert('B');
	for (USetIt it = set.begin(); it != set.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	// 查找
	USetIt it = set.find('A');
	if (it == set.end()) cout << "没找到！\n";
	else cout << "找到了！\n" << *it << endl;

	// 删除
	if (set.erase('B')) cout << "删除成功!\n";
	else cout << "删除失败!\n";
}

int main() {
	//test01();
	test02();
	return 0;
}