#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int get_length(int *signal, int size) {
	int outer = 0, inner = 0;
	while (outer <= size) {
		outer++;
		inner++;
		if (signal[outer] == 0) {
			inner += signal[outer + 1];
		}
	}
	return inner;
}

int  get_Tmethod(int *signal, int size, int T) {
	int result = signal[0];
	// i 指向signal当前数组位置， n 指向实际数组位置
	int outer = 0, inner = 0;
	while (outer <= T && inner < size) {
		if (outer == T) {
			return result;
		}
		outer++;
		inner++;
		if (signal[outer] == 0) {
			inner += signal[outer + 1];
			if (T >= inner) {
				outer += 2;
				result += signal[outer];
			}
			else {
				return result;
			}
		}
		else {
			result += signal[outer];
		}
	}
	return result;
}

void get_Mmethod(int *signal, int size, int min, int max) {
	if (min < 0 || max > get_length(signal, size)) cout << "-1" << endl;
	int _min = 0, _max = 0;
	_min = get_Tmethod(signal, size, min);
	_max = _min;
	int result = _min;
	
	while (min <= max) {
		if (signal[min] == 0) {
			min += 2;
			result += signal[min];
		}
		if (result > _max) {
			_max = result;
		}
		else if (result < _min) {
			_min = result;
		}
		min++;
		result += signal[min];
	}
	cout << _min << " " << _max << endl;
}

int stringToInt(string str) {
	int flag = 0; // flag = 0 正 
	int i = 0;
	if (str[0] == '-') {
		flag = 1;
		i = 1;
	}
	if (str[0] == '0') {
		i = 2;
	}
	int result = 0;
	while (str[i] != '\0' && str[i] != ' ') {
		result = 10 * result + str[i] - '0';
		i++;
	}
	if (!flag) return result;
	else return -result;
}

void print_array(int *arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	string line;
	int signal[1000] = { 0, };
	ifstream myfile("zsignal.txt");

	int size = 0;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			// 类型转化
			if (line[0] == '0') {
				size++;
				signal[size - 1] = 0;
				signal[size] = stringToInt(line);
			}
			else {
				signal[size] = stringToInt(line);
			}
			size++;
		}
		myfile.close();
	}
	else cout << "zsignal.txt Error!";
	
	print_array(signal, size);
	// 读取stdin
	char in = 0;
	while (cin >> in) {
		if (in == 'T') {
			int T = 0;
			cin >> T;
			cout << get_Tmethod(signal, size, T) << endl;
		}
		else if (in == 'M') {
			int max = 0, min = 0;
			cin >> min >> max;
			get_Mmethod(signal, size, min, max);
		}
	}

	return 0;
}