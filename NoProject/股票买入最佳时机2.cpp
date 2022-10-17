#include <iostream>

using namespace std;

void print_matrix(int** dp, int size) {
	for (int i = 0; i < size; i++) {
		cout << "{ ";
		for (int j = 0; j < size; j++) {
			cout.width(2); 
			cout.fill(' ');
			cout << dp[i][j];
			cout << " ";
		}
		cout << "}\n";
	}
}

int** init_matrix_size_2(int size) {
	int** a = new int* [size];
	for (int i = 0; i < size; i++) {
		a[i] = new int[2];
		a[i][0] = 0;
		a[i][1] = 0;
	}
	return a;
}

int best_time_for_selling(int *prices, int size) {
	// 动态规划太难 先写个简单的
	int insure_max = 0;
	for (int i = 1; i < size; i++) {
		if (prices[i] > prices[i - 1]) {
			insure_max += prices[i] - prices[i - 1];
		}
	}
	// return insure_max;
	// 动规实现
	/*
		假设初始资金为 x
		对于第 i 天
		1.手上没有股票
			买入		：当日剩的钱 = 上次卖的钱 - 本次买入价
			不买入	：当日剩的钱 = 上次卖的钱
		2.手上有股票
			卖出		：当日剩的钱 = 上次买入的钱 + 本次卖出价
			不卖出	：当日剩的钱 = 上次买入的钱
		用最终一天的剩余 - x = 所获得的利润

		所以第i天就有两种情况，我们分情况讨论
		dp[i][0] 表示第i天结束时手上没有股票时当日剩余
		dp[i][1] 表示第i天结束时手上持有股票时当日剩余
	*/
	int **dp = init_matrix_size_2(size);
	int flag = 0; // 手上有没有股票
	// 令 x = 0
	dp[0][0] = 0;				// 第一天不买
	dp[0][1] = 0 - prices[0];	// 第一天买入
	for (int i = 1; i < size; i++) {
		dp[i][0] = max(dp[i - 1][1] + prices[i], dp[i - 1][0]);
		dp[i][1] = max(dp[i - 1][0] - prices[i], dp[i - 1][1]);
	}

	insure_max = dp[size - 1][0];
	if (insure_max < 0) return 0;
	return insure_max;
}

int main() {
	int arr[] = {7, 1, 5, 3, 4, 6};
	int size = sizeof(arr) / sizeof(int);
	cout << best_time_for_selling(arr, size);
	return 0;
}