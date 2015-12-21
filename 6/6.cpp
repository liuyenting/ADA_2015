#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#define weight first
#define edge second
#define source first
#define sink second

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

std::vector<std::pair<int, std::pair<int, int> > > graph;
int n, e;

long long int Kruskal_MST() {
	UnionFind UF(n);
	int u, v;
	long long int T = 0;

	for(int i = 0; i < e; ++i) {
		u = graph[i].edge.source;
		v = graph[i].edge.sink;
		if(!UF.hasCommonRoot(u, v) ) {
			UF.unite(u, v);
			T += graph[i].weight;
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
		u = graph[i].edge.source;
		v = graph[i].edge.sink;
		if(!UF.hasCommonRoot(u, v) ) {
			UF.unite(u, v);
			T += graph[i].weight;
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
	std::cin >> cases;
	while(cases-- >0) {
		// n = number of nodes
		// e = number of edges
		std::cin >> n >> e;

		graph.resize(e);

		for(int i = 0; i < e; ++i) {
			std::cin >> u >> v >> c;
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
				must_w += graph[i].weight;
			}
		}

		std::cout << must_c << ' ' << must_w << std::endl;
	}

	return 0;
}
