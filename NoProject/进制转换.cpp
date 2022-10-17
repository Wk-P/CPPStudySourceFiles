#include <iostream>

using namespace std;

int dec_to_bin(int n) {
	int result = 0, i = 0;
	while (n > 0) {
		result += n % 2 * pow(10, i);
		n /= 2;
		i++;
	}
	return result;
}

int bin_to_dec(int n) {
	int result = 0, i = 0;
	while (n > 0) {
		result += n % 10 * pow(2, i);
		n /= 10;
		i++;
	}
	return result;
}

// 只能十进制以下任意进制转换
int n_to_m() {
	int result = 0, i = 0, n = 0, m = 0, a = 0;
	cout << "当前进制: "; cin >> n;
	cout << "当前进制数: "; cin >> a;
	cout << "目标进制: "; cin >> m;
	while (a > 0) {
		result += a % m * pow(n, i);
		a /= m;
		i++;
	}
	return result;
}

// 10 -> 11
string dec_to_undec(int n) {
	// A = 11
	// 分析每一位对应的11进制 
	string result = "";
	while (n > 0) {
		int temp = n % 11;
		if (temp == 10) { result = 'A' + result; }
		else {
			char ch = temp + '0';
			result = ch + result;
		}
		n /= 11;
	}
	return result;
}

// 11 -> 10
int undec_to_dec(string n) {
	int result = 0, i = 0;
	// 倒序遍历字符串
	for (int k = n.length() - 1; k >= 0; k--, i++) {
		int temp = 0;
		if (n[k] == 'A') {
			temp = 10;
		}
		else {
			temp = (int)(n[k] - '0');
		}
		result += temp * pow(11, i);
	}
	return result;
}

int int_input() {
	int n = 0;
	cout << "输入 = "; cin >> n;
	return n;
}

string str_input() {
	string s = "";
	cout << "输入 = "; cin >> s;
	return s;
}

// 11进制的加减运算
string undec_add(string a, string b) {
	int num1 = undec_to_dec(a), num2 = undec_to_dec(b);
	return dec_to_undec(num1 + num2);
}

int main() {

	/* dec_to_bin(int_input());
	bin_to_dec(int_input()); */
	// n_to_m();	
	cout << dec_to_undec(int_input());
	// undec_to_dec(str_input());
	//cout << undec_add(str_input(), str_input());

	return 0;
}