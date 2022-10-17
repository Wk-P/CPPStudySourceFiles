#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    int mod = 0;
    while (b != 1) {
        mod = a % b;
        if (mod == 0) return b;
        a = b;
        b = mod;
    }
    return mod;
}

void print_vector(vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << " " << vec[i];
    }
    cout << endl;
}

void swap(int* a, int* b) {
    int temp = *a;
    a = b;
    *b = temp;
}

void print_ptr(int length) {
    for (int i = 0; i < length; i++) {
        cout << "  ";
    }
    cout << " x" << endl;
}

void rotate(vector<int>& nums, int k) {
    // 时间换空间
    int n = nums.size();
    int range = gcd(n, k);
    int i = 0, x = 0, temp = nums[x];
    while (i < range) {
        if ((x + k - i) % n != 0) {
            x = (x + k) % n;
            swap(temp, nums[x]);
        }
        else {
            x = ++i;
            swap(nums[x - 1], temp);
            temp = nums[x];
        }
    }
    swap(nums[x], temp);
}

int main() {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8};
    print_vector(vec);
    cout << "--------------" << endl;
    rotate(vec, 3);
    print_vector(vec);
	return 0;
}