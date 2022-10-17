#include <iostream>

using namespace std;

class _Animal {
public:
	_Animal() {
		_name = 0;
		_age = 0;
	}
	_Animal(const char* name, int age) {
		_name = (char*)name;
		_age = age;
	}
	~_Animal() {}
	virtual void __show__() {
		if (!_name) {
			cerr << "NULL pointer!" << endl;
			exit(1);
		}
		cout << _name << ":" << _age << endl;
	}
	virtual void __eat__() {
		cout << _name << "is eating." << endl;
	}
private:
	char* _name;
	int _age;
};

class _Dog : public _Animal {
public:
	_Dog() {
		_food = (char*)"meat";
		_nickname = 0;
		_age = 0;
	}
	_Dog(char* nickname, int age) {
		_food = (char*)"meat";
		_nickname = nickname;
		_age = age;
	}
	_Dog(const char* nickname, int age) {
		_food = (char*)"meat";
		_nickname = (char*)nickname;
		_age = age;
	}
	virtual void __show__() {
		if (!_nickname) {
			cerr << "NULL pointer!" << endl;
			exit(1);
		}
		cout << _name << " | " << _nickname << " " << _age << endl;
	}
	void __eat__(const char *food) {
		cout << _nickname << " is eating " << food << endl;
	}
	void __setnickname__(char* nickname) {
		_nickname = nickname;
	}
	void __setnickname__(const char* nickname) {
		_nickname = (char*)nickname;
	}
private:
	const char* _name = "Dog";
	char* _nickname;
	int _age;
	char* _food;
};

class _Golden_Retriever : public _Dog {
public:
	_Golden_Retriever() {
		_nickname = 0;
		_age = 0;
	}
	_Golden_Retriever(char* nickname, int age) {
		_nickname = nickname;
		_age = age;
	}
	_Golden_Retriever(const char* nickname, int age) {
		_nickname = (char*)nickname;
		_age = age;
	}
	~_Golden_Retriever() {}
	void __show__() {
		if (!_nickname) {
			cerr << "NULL pointer!" << endl;
			exit(1);
		}
		cout << _name << " | " << _nickname << " " << _age << endl;
	}
private:
	char* _name = (char*)"Golden Retriever";
	int _age = 0;
	char* _nickname;
};

int main() {
	_Dog* dog1 = new _Dog("Niko", 28);
	dog1->__show__();
	dog1->__setnickname__("ArT");
	dog1->__show__();

	_Golden_Retriever* gr_dog = new _Golden_Retriever("MXX", 10);
	gr_dog->__show__();
	return 0;
}