#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#define pii std::pair<int, int>
#define pip std::pair<int, pii>
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
class UnionFind
{
private:
	int id[MAX] = {0};
	int sz[MAX] = {0};

public:
	UnionFind(int n) {
		for(int i = 0; i < n; ++i) {
			id[i] = i;
			sz[i] = 1;
		}
	}

	int findRoot(int i) {
		while(i != id[i]) {
			id[i] = id[id[i]]; // path Compression
			i = id[i];
		}
		return i;
	}

	int hasCommonRoot(int p, int q) {
		return findRoot(p)==findRoot(q);
	}

	void unite(int p, int q) {
		int i = findRoot(p);
		int j = findRoot(q);

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

long long int Kruskal_MST() {
	UnionFind UF(n);
	int u, v;
	long long int T = 0;

	for(int i = 0; i < e; ++i) {
		u = graph[i].S.F;
		v = graph[i].S.S;
		if(!UF.hasCommonRoot(u, v) ) {
			UF.unite(u, v);
			T += graph[i].F;
		}
	}

	return T;
}

long long int Kruskal_MST_RemoveEdge(int idx) {
	UnionFind UF(n);
	int u, v;
	long long int T = 0;

	for(int i = 0; i < e; ++i) {
		if(i == idx)
			continue;
		u = graph[i].S.F;
		v = graph[i].S.S;
		if(!UF.hasCommonRoot(u, v) ) {
			UF.unite(u, v);
			T += graph[i].F;
		}
	}

	return T;
}

int main() {
	int u, v, c;
	long long int T;

	int must_c;
	long long int must_w;

	int cases;
	inp(&cases);
	while(cases-- >0) {
		// n = number of nodes
		// e = number of edges
		inp(&n);
		inp(&e);

		graph.resize(e);

		for(int i = 0; i < e; ++i) {
			inp(&u);
			inp(&v);
			inp(&c);
			u--;
			v--;
			graph[i] = std::make_pair(c, std::make_pair(u, v));
		}
		// sort the edges in increasing order of cost
		std::sort(graph.begin(), graph.end());

		int W = Kruskal_MST();
		must_c = 0;
		must_w = 0;
		for(int i = 0; i < e; ++i) {
			T = Kruskal_MST_RemoveEdge(i);
			if(T != W) {
				must_c++;
				must_w += graph[i].F;
			}
		}

		printf("%d %d\n", must_c, must_w);
	}

	return 0;
}
