#include <iostream>
using namespace std;

void get_ploy_add(int* poly, int size) {
	for (int i = 0; i < size; i++) {
		int c = 0, e = 0;
		cin >> c >> e;
		poly[e] += c;
	}
}

int main() {
	int poly[1000] = { 0, };
	int size = 0, term_count = 0;
	cin >> size;
	for (int i = 0; i < size; i++) {
		int term_size = 0;
		cin >> term_size;
		get_ploy_add(poly, term_size);
	}
	for (int i = 0; i < 1000; i++) {
		if (poly[i] != 0) {
			term_count++;
		}
	}
	cout << term_count << endl;
	for (int i = 1000 - 1; i >= 0; i--) {
		if (poly[i] != 0) {
			cout << poly[i] << " " << i << endl;
		}
	}

	return 0;
}