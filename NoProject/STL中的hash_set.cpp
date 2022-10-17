#include <unordered_set>
#include <iostream>

/* STL中的unordered_set 就是hash_set
	使用哈希函数构成哈希表
*/
using namespace std;

template<typename T>
void print_set(unordered_set<T>& uset) {
	for (auto it = uset.begin(); it != uset.end();it++) {
		cout << *it << endl;
	}
	cout << endl;
}

int main() {

	// 基本用法
	unordered_set<string> hash_set1;
	hash_set1.insert("I need an Apple!");
	string str = "What would you want to do?";
	hash_set1.insert(str);
	print_set(hash_set1);

	return 0;
}