#include<iostream>

using namespace std;

int main() {
	int n;
	int sum = 1;
	
	cin >> n;
	
	if(n <= 0) {
		cout << "n is wrong";
	}
	
	for(int i = 1; i <= n; ++i) {
		sum += 1;
	}
	
	cout << "Sum_n=" << sum;
	
	return 0;
}
