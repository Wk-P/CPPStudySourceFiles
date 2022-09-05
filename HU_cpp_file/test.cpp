#include <iostream>
#define MAX_SIZE 2000

using namespace std;

typedef struct _Point {
	int x, y, index, result;
} _Point;

typedef struct _Array {
	int size;
	int* base;
} _Array;

void bubble_sort_x(_Point* ps, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (ps[j].x > ps[j + 1].x) {
				_Point temp = ps[j];
				ps[j] = ps[j + 1];
				ps[j + 1] = temp;
			}
		}
	}
}

void bubble_sort_index(_Point* ps, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (ps[j].index > ps[j + 1].index) {
				_Point temp = ps[j];
				ps[j] = ps[j + 1];
				ps[j + 1] = temp;
			}
		}
	}
}

void init_len_arr(_Array* len) {
	len->base = new int[2000];
	int i = 0;
	while (1) {
		int in = -1;
		cin >> in;
		if (!in) break;
		len->base[i++] = in;
	}
	len->size = i;
}

_Point* init_point_set(_Point* ps, int* size) {
	ps = new _Point[15];
	int i = 0;
	while (cin >> ps[i].x >> ps[i].y) {
		ps[i].index = i;
		ps[i].result = 0;
		i++;
	}
	*size = i;
	return ps;
}

int main() {
	_Array* len = new _Array;
	_Point* ps = NULL;
	init_len_arr(len);
	int size1 = len->size, size2 = 0;
	ps = init_point_set(ps, &size2);
	// 初始化

	cout << "size1 = " << size1 << "size2 = " << size2 << endl;

	int w = 0, h = 0;
	for (int i = 0; i < size1; i += 2) {
		w += len->base[i];
	}
	for (int i = 1; i < size1; i += 2) {
		h += len->base[i];
	}

	// 输入的点按x轴坐标排序
	bubble_sort_x(ps, size2);
	//print_ps(ps, size2);
	for (int q = 0, p = 1, i = 0, k_left = 0, k_right = len->base[q], hi = h, k = ps[i].x; i < size2;) {
		// test
		if (ps[i].x == 7 && ps[i].y == 6) {
			i++;
			i--;
		}
		/*
			q: len横坐标对应下标 (ki)
			p: len纵坐标移动下标 (hi)
			k: 扫面线的横坐标移动
			i: 点的下标
			hi: 高度变化
		*/
		// 判断扫面线的位置
		if (k != ps[i].x) continue;
		if (k < k_right && k > k_left) {
			// 判断点的坐标
			if (ps[i].y > hi) {
				ps[i].result = -1;
			}
			else if (ps[i].y < hi) {
				ps[i].result = 1;
			}
			// 移动指针
			i++;
			k = ps[i].x;
		}
		else if (k == k_right) {
			if (ps[i].y > hi) {
				ps[i].result = -1;
			}
			else if (ps[i].y < hi - len->base[p]) {
				ps[i].result = 1;
			}
			i++;
			k = ps[i].x;
			q += 2;
			k_left = k_right;
			k_right += len->base[q];
			hi = hi - len->base[p];
			p += 2;
		}
		else {
			q += 2;
			k_left = k_right;
			k_right += len->base[q];
			hi = hi - len->base[p];
			p += 2;
		}
	}
	bubble_sort_index(ps, size2);
	for (int i = 0; i < size2; i++) {
		if (ps[i].result == -1) {
			cout << "out" << endl;
		}
		else if (ps[i].result == 0) {
			cout << "on" << endl;
		}
		else {
			cout << "in" << endl;
		}
	}
	return 0;
}