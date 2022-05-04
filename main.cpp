#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class MySet {
private:
	double* arr;
	int size;
	int tail;
public:
	friend ostream& operator<<(ostream& stream, MySet& set);
	MySet() {
		arr = NULL;
		size = 0;
		tail = 0;
	}

	void _print() {
		for (int i = 0; i < this->size; i++) {
			cout << arr[i] << ",";
		}
		cout << endl;
	}


	void add(double newElement) {
		if (tail == size) { return; }
		arr[tail] = newElement;
		tail++;
	}
	void Init(int size) {
		this->size = size;
		this->arr = new double[size];
		for (int i = 0; i < size; i++) {
			this->arr[i] = 0;
		}
	}
	void Init(int size, double arr[]) {
		this->size = size;
		delete []this->arr;
		this->arr = new double[size];
		for (int i = 0; i < this->size; i++) {
			this->arr[i] = arr[i];
		}
	}
	int getSize() { return size; }
	int operator[](double);
	void sort();
	void operator=(const MySet&);
	MySet operator+(double number);
	MySet operator+(const MySet&); 
	MySet operator*(const MySet&); 
	MySet operator-(const MySet&);
};

void MySet::sort() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size-i; j++) {
			if (arr[i] > arr[j]) {
				double temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void MySet::operator=(const MySet& set) {
	size = set.size;
	arr = set.arr;
	tail = set.tail;
}

MySet MySet::operator+(double number) {
	MySet newSet;
	newSet.Init(this->size+1);
	for (int i = 0; i < this->size; i++) {
		newSet.arr[i] = this->arr[i];
	}
	newSet.arr[this->size] = number;
	newSet.sort();
	return newSet;
}

MySet MySet::operator+(const MySet& set) {
	MySet newSet;
	int max_size = this->size + set.size;
	double *new_arr = new double[max_size];
	int i = 0;
	for (int t = 0, s = 0; t < this->size && s < set.size;) {
		if (this->arr[t] == set.arr[s]) {
			new_arr[i] = this->arr[t];
			t++;
			s++;
		}
		else if (this->arr[t] > set.arr[s]) {
			new_arr[i] = set.arr[s];
			s++;
		}
		else {
			new_arr[i] = this->arr[t];
			t++;
		}
		i++;
	}
	newSet.Init(max_size, new_arr);
	newSet.sort();
	return newSet;
}

MySet MySet::operator*(const MySet& set) {
	MySet newSet;
	int max_size = min(size, set.size);
	double* new_arr = new double[max_size];
	int i = 0;
	for (int t = 0, s = 0; t < this->size && s < set.size;) {
		if (this->arr[t] == set.arr[s]) {
			new_arr[i] = this->arr[t];
			i++;
			t++;
			s++;
		}
		else if (this->arr[t] > set.arr[s]) {
			s++;
		}
		else {
			t++;
		}
	}
	newSet.Init(max_size, new_arr);
	newSet.sort();
	return newSet;
}

MySet MySet::operator-(const MySet& set) {
	MySet resultSet;
	MySet C = *this * set;
	resultSet.Init(this->size);
	int i = 0;
	for (int as = 0, cs = 0;as < this->size;) {
		if (this->arr[as] == C.arr[cs]) {
			as++;
			cs++;
		}
		else if (this->arr[as] > C.arr[cs]) {
			resultSet.arr[i] = C.arr[cs];
			i++;
			cs++;
		}
		else {
			resultSet.arr[i] = this->arr[as];
			i++;
			as++;
		}
	}
	resultSet.sort();
	return resultSet;
}

int MySet::operator[](double number) {
	sort();
	for (int i = 0; i < size; i++) {
		if (arr[i] == number) {
			return i + 1;
		}
	}
	return -1;
}

ostream& operator<<(ostream &stream, MySet& set) {
	for (int i = 0; i < set.getSize(); i++) {
		stream << set.arr[i];
	}
	return stream;
}

int inputSet(string filename, MySet& set) {
	string numLines;
	string bufFloat;

	ifstream ifile("input.txt", ios::in);
	if (!ifile) {
		return -1;
	}

	getline(ifile, numLines);
	set.Init((int)stod(numLines));
	for (int i = 0; i < stod(numLines) + 1; i++) {
		getline(ifile, bufFloat);
		set.add(stod(bufFloat));
	}
	ifile.close();
	return set.getSize();
}

int main() {
	MySet A, B, C, D;

	if (inputSet("input.txt", A) < 0) {
		cerr << "Input File Error" << endl;
		return -1;
	}

	B = A;
	for (int i = 1; i <= 10; i++) B = B + 0.1 * i;

	C = A * B;
	D = B - C;

	ofstream ofile("output.txt", ios::out|ios::app);
	ofile << D;
	ofile << B[50.5] << endl;
	ofile.close();
	return 0;

}
