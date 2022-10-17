#include <iostream>
#include <map>
using namespace std;

class poly {
private:
	map<int, int> coef;  // <exp, cons>
public:
	poly() {}
	void add_item(int e, int c) {
		auto find_result = this->coef.find(e);
		if (find_result != this->coef.end()) find_result->second += c;
		else this->coef[e] = c;
	}
	poly& poly_mult(poly& p) {
		poly* new_poly = new poly();
		for (map<int, int>::iterator item_f = p.coef.begin(); item_f != p.coef.end();item_f++) {
			for (map<int, int>::iterator item_s = this->coef.begin(); item_s != this->coef.end(); item_s++) {
				new_poly->add_item(item_f->first + item_s->first, item_f->second * item_s->second);
			}
		}
		return *new_poly;
	}
	void show_poly() {
		for (map<int, int>::iterator it = coef.begin(); it != coef.end(); it++) {
			if (it->second == 0) coef.erase(it++);
			else it++;
		}
		cout << this->coef.size() << endl;
		for (map<int, int>::reverse_iterator item = coef.rbegin(); item != coef.rend(); item++) {
			cout << item->second << " " << item->first << endl;
		}
	}
};

int main() {
	int poly_size = 0; cin >> poly_size;
	poly* poly_array = new poly[poly_size];
	for (int i = 0; i < poly_size; i++) {
		int item_size = 0; cin >> item_size;
		poly_array[i] = poly();
		for (int j = 0; j < item_size; j++) {
			int c = 0, e = 0;
			cin >> c >> e;
			if (c == 0) continue;
			poly_array[i].add_item(e, c);
		}
	}
	poly mult_result = poly_array[0];
	for (int i = 1; i < poly_size; i++) {
		mult_result = mult_result.poly_mult(poly_array[i]);
	}
	mult_result.show_poly();

	return 0;
}