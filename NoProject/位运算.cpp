#include <iostream>

using namespace std;

int number_reverse(int num) {
	int result = 0;
	while (num != 0) {
		result = result * 10 + num % 10;
		num /= 10;
	}
	return result;
}
int main() {
	int number = -1230;
	cout << number << " --> " << number_reverse(number) << endl;
	cout << ~(1 << 31) << endl;
	cout << (1 << 31) + 1 << endl;
	return 0;
}