#include "stdio.h"
#include "string.h"
#include <vector>
#include <algorithm>
using namespace std;
#define pii pair<int, int>
#define pip pair<int, pii>
#define F first
#define S second

inline void inp(int *n) { // fast input function
	*n = 0;
	int ch = getchar_unlocked();
	int sign = 1;
	while(ch < '0' || ch > '9') {
		if(ch == '-')
			sign = -1;
		ch = getchar_unlocked();
	}
	while(ch >= '0' && ch <= '9')
		(*n) = ((*n)<<3) + ((*n)<<1) + ch - '0', ch = getchar_unlocked();
	*n = (*n)*sign;
}

const int MAX = 1000000;

// class implementing Union Find Data Structure with Path Compression
class Union_Find
{
private:
	int id[MAX] = {0};
	int sz[MAX] = {0};

public:
	Union_Find(int n) { // class constructor
		for(int i = 0; i < n; ++i) {
			id[i] = i;
			sz[i] = 1;
		}
	}

	int root(int i) {
		while(i != id[i]) {
			id[i] = id[id[i]]; // path Compression
			i = id[i];
		}
		return i;
	}
	int find(int p, int q) {
		return root(p)==root(q);
	}
	void unite(int p, int q) {
		int i = root(p);
		int j = root(q);

		if(sz[i] < sz[j]) {
			id[i] = j;
			sz[j] += sz[i];
		} else {
			id[j] = i;
			sz[i] += sz[j];
		}
	}
};

std::vector< pip > graph;
int n, e;
long long int T;

void Kruskal_MST() {
	Union_Find UF(n);
	int u, v;

	for(int i = 0; i < e; ++i) {
		u = graph[i].S.F;
		v = graph[i].S.S;
		if(!UF.find(u, v) ) {
			UF.unite(u, v);
			T += graph[i].F;
			// printf("%d -> %d, w = %d, T = %d\n", u, v, graph[i].F, T);
		}
	}
}

void Kruskal_MST_RemoveEdge(int idx) {
	Union_Find UF(n);
	int u, v;

	for(int i = 0; i < e; ++i) {
		if(i==idx)
			continue;
		u = graph[i].S.F;
		v = graph[i].S.S;
		if(!UF.find(u, v) ) {
			//			printf("uniting %d and %d\n",u,v );
			UF.unite(u, v);
			T += graph[i].F;
			// printf("%d -> %d, w = %d, T = %d\n", u, v, graph[i].F, T);
		}
	}
}

int main() {
	int u, v, c;

	int t;
	std::cin >> t; // t = test cases.
	while(t-->0) {
		u = 0; v = 0; c = 0;

		std::cin >> n >> e;       // n = number of nodes, e = number of edges.

		graph.resize(e);

		for(int i = 0; i < e; ++i) {
			std::cin >> u >> v >> c;
			u--;
			v--;
			graph[i] = pip( c, pii(u,v));
		}
		sort(graph.begin(), graph.end()); // sort the edges in increasing order of cost

		T = 0;
		Kruskal_MST();
		int W = T;
		int cnt = 0, wei = 0;
		for(int i = 0; i < e; ++i) {
			T = 0;
			Kruskal_MST_RemoveEdge(i);
			if(T > W) {
				cnt++;
				wei += graph[i].F;
			}
		}
		// printf("cnt = %d, prc = %d\n", cnt, wei);
		printf("%d %d\n", cnt, wei);
	}

	// printf("%lld\n",T);
	return 0;
}
