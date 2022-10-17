#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Int {
public:
    Int() {}
    Int(int a) {
        n = a;
    }
    int getNumber() {
        return n;
    }
    Int& operator=(int a) {
        this->n = a;
        return *this;
    }
    Int operator+(Int& num) {
        Int *ret = new Int(n + num.getNumber());
        return *ret;
    }
    Int operator-(Int& num) {
        Int* ret = new Int(n - num.getNumber());
        return *ret;
    }
    Int operator*(Int& num) {
        Int* ret = new Int(n * num.getNumber());
        return *ret;
    }
    Int operator/(Int& num) {
        if (num.getNumber() == 0) exit(1);
        Int* ret = new Int(n / num.getNumber());
        return *ret;
    }
    Int operator%(Int num) {
        if (num.getNumber() == 0) exit(1);
        Int* ret = new Int(n % num.getNumber());
        return *ret;
    }
    Int mod(Int& num) {
        if (num.getNumber() == 0) exit(1);
        Int* ret = new Int(n % num.getNumber());
        return *ret;
    }
private:
    int n = 0;
};

int operator+(Int& n, int num) {
    return n.getNumber() + num;
}
int operator-(Int& n, int num) {
    return n.getNumber() - num;
}
int operator*(Int& n, int num) {
    return n.getNumber() * num;
}
int operator/(Int& n, int num) {
    return n.getNumber() / num;
}
int mod(Int& n, int num) {
    if (num == 0) exit(1);
    return n.getNumber() % num;
}
int operator%(Int& n, int num) {
    if (num == 0) exit(0);
    return n.getNumber() % num;
}

int operator+(int num, Int& n) {
    return num + n.getNumber();
}
int operator-(int num, Int& n) {
    return num - n.getNumber();
}
int operator*(int num, Int& n) {
    return num * n.getNumber();
}
int operator/(int num, Int& n) {
    return num / n.getNumber();
}
int mod(int num, Int& n) {
    if (n.getNumber() == 0) exit(1);
    return num % n.getNumber();
}
int operator%(int num, Int& n) {
    if (n.getNumber() == 0) exit(1);
    return num % n.getNumber();
}

ostream& operator<<(ostream& os, Int num) {
    os << num.getNumber();
    return os;
}

ostream& operator<<(ostream& os, Int* num) {
    os << num->getNumber();
    return os;
}

int main() {
    Int c;
    cout << "c = " << c << endl;
    Int a = 10;
    Int b = 30;
    cout << a << endl;
    cout << a / b <<     endl;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b + a << endl;
    cout << a * 2 << endl;
    cout << 2 + a << endl;
    cout << a + 2 << endl;
    cout << a / 3 << endl;
    cout << 300 / a << endl;
    cout << 3 % a << endl;
    cout << a % 3 << endl;
    cout << b % a << endl;
    return 0;
}