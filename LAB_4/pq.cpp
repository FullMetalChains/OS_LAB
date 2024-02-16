#include<bits/stdc++.h>
using namespace std;

int main() {
	int n, tq; cin >> n >> tq; 

	vector<vector<int>> readyQueue, table(n);

	for(int i=0; i<n; i++) {
		int At, Bt, Priority, PId = i+1;
		cin >> At >> Bt >> Priority;
		readyQueue.push_back({ At, Bt, Priority, PId, Bt });
	}
	sort(readyQueue.begin(), readyQueue.end());

	auto comp = [](auto &a, auto &b){
		if(a[2] != b[2])
			return a[2] < b[2];
		else if(a[0] != b[0])
			return a[0] > b[0];
		else
			return a[3] > b[3];
	};
	priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> maxHeap(comp);
	for(int t = 0, i = 0; i < n || !maxHeap.empty();) {
		while(i < n && readyQueue[i][0] <= t)
			maxHeap.push(readyQueue[i++]);

		auto currTask = maxHeap.top(); maxHeap.pop();
		int unit = min(tq, currTask[1]);
		t += unit;

		currTask[1] -= unit;
		if(currTask[1] > 0) {
			maxHeap.push(currTask);
			continue;
		}

		table[currTask[3]-1] = {
			currTask[3],									// ID
			currTask[0],									// At
			currTask[4],											// BT
			currTask[2],									// Q
			t,																// Ct
			t - currTask[0],							// TAt
			t - currTask[0] - currTask[4]	// Wt
		};
	}

	cout << "Pr\tAt\tBt\tQ\tCt\tTAt\tWt\n";
	for(int i=0; i<n; i++) {
		for(auto j : table[i])
			cout << j << "\t";
		cout << "\n";
	}
}