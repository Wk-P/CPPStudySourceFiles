#include <iostream>
#include <exception>
using namespace std;

class DivideNumberException : public exception {
public:
	const char* what() const {
		return "Integer divided by zero!\n";
	}
};

float divide(float a, float b) {
	if (b == 0) {
		throw DivideNumberException();
	}
}

int main() {
	float a, b;
	cout << "输入两个数:";
	cin >> a >> b;
	try {
		divide(a, b);
	}
	catch (DivideNumberException e) {
		cout << e.what();
	}
}