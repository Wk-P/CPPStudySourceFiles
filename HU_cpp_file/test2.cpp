#include <iostream>

using namespace std;

void _print(int* arr, int size) {
	for (int i = 0; i < size;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	int* len = new int[20];
	for (int i = 0; i < 20; i++) {
		len[i] = 0;
	}
	int len_size = 0;
	while (1) {
		int i = 0;
		cin >> i;
		if (!i) break;
		len[len_size++] = i;
	}
	int height = 0;
	for (int i = 1; i < len_size; i += 2) {
		height += len[i];
	}
	int k = 0;
	while (k < 15) {
		int x, y, result = 0;
		cin >> x >> y;
		int xptr = 0, yptr = 1, h = height, x_left = 0, x_right = len[xptr] + x_left;
		for (int i = 0; i < len_size; i += 2) {
			if (x_left < x && x < x_right) {
				if (y < h) {
					result = 1;
				}
				else if (y > h) {
					result = -1;
				}
			}
			else {
				if (x == x_right) {
					if (y > h) {
						result = -1;
					}
					else if (y < h - len[yptr]) {
						result = 1;
					}
				}
				x_left = x_right;
				x_right += len[xptr += 2];
				h -= len[yptr];
				yptr += 2;
			}
		}

		if (result == 0) {
			cout << "on" << endl;
		}
		else if (result == -1) {
			cout << "out" << endl;
		}
		else {
			cout << "in" << endl;
		}
		k++;
	}

	return 0;
}