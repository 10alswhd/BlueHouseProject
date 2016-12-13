#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main(int, char**) {
  int n = 0;
	cin >> n;
	vector<vector<pair<int, int> > > g(n);
	vector<bool> u(n, false);
	vector<int> d(n, INT_MAX); d[0] = 0;
	vector<int> p(n, -1);

	for (int i = 0; i < g.size(); i++) {
		int vc = 0;
		cin >> vc;
		g[i].resize(vc);
		int node = 0, weight = 0;
		for (int j = 0; j < vc; j++) {
			cin >> node >> weight;
			g[i][j] = make_pair(node, weight);
		}
	}

	int from = 0, to = 0;
	cin >> from >> to;
  
	while (true) {
		int ix = 0, mv = INT_MAX;
		bool exists = false;
		for (int i = 0; i < d.size(); i++) {
			if (u[i] == false && d[i] <= mv) {
				ix = i;
				mv = d[i];
				exists = true;
			}
		}
		if (!exists || d[ix] == INT_MAX) break;
	
		u[ix] = true;

		for (int i = 0; i < g[ix].size(); i++) {
			if (d[g[ix][i].first] > d[ix] + g[ix][i].second) {
				d[g[ix][i].first] = d[ix] + g[ix][i].second;
				p[g[ix][i].first] = ix;
			}
		}
	}

	int ix = to;
	do {
		cout << ix << " <- ";
		ix = p[ix];
	} while (p[ix] != -1);
	cout << from << endl;
	
	return 0;
}
