#include <iostream>
using namespace std;
const int N = 100;
int arr[N], buf[N];
void sol(int L, int R) {
	if (R - L <= 1)return;
	int M = (R + L) / 2;
	sol(L, M);
	sol(M, R);
	int i = L, j = M, k = L;
	while (i < M || j < R) {
		if (i >= M)
			buf[k] = arr[j++];
		else if (j >= R)
			buf[k] = arr[i++];
		else {
			if (arr[i] <= arr[j])
				buf[k] = arr[i++];
			else {
				buf[k] = arr[j++];
			}
		}
		k++;
	}
	for (int k = L; k < R; k++) arr[k] = buf[k];
	return;
}

int main() {
	int n;
	while(cin >> n,n>0&&n<100){
	for (int i = 0; i<n; i++) {
		cin >> arr[i];
	}
	sol(0, n - 1);
	for (int i = 0; i<n; i++) {
		cout << arr[i] << ' ';
	}
	cout << '\n';
	}
}