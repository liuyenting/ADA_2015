#include <iostream>
#include <vector>
#include <algorithm>

typedef struct {
	int start, end;
} Edge;

void dump_graph(std::vector<Edge> & graph) {
	for(int i = 0; i < graph.size(); i++)
		std::cout << graph[i].start << " -> " << graph[i].end << std::endl;
}

void dump_pi(std::vector<int> & pi) {
	for(int i = 1; i <= pi.size(); i++)
		std::cout << "[" << i << "]" << " = " << pi[i] << std::endl;
}

int main(void) {
	int T;
	std::cin >> T;

	int n, m;
	while(T-- > 0) {
		std::cin >> n >> m;

		std::vector<Edge> G1, G2;
		for(int i = 0; i < m; i++) {
			Edge new_edge;
			std::cin >> new_edge.start >> new_edge.end;
			G1.push_back(new_edge);
		}
		for(int i = 0; i < m; i++) {
			Edge new_edge;
			std::cin >> new_edge.start >> new_edge.end;
			G2.push_back(new_edge);
		}

		std::cerr << "--- G1 ---" << std::endl;
		dump_graph(G1);
		std::cerr << "----------" << std::endl;
		std::cerr << "--- G2 ---" << std::endl;
		dump_graph(G2);
		std::cerr << "----------" << std::endl;

		std::vector<int> pi(n+1);
		std::fill(pi.begin(), pi.end(), -1);
		std::cerr << "-- pi-0 --" << std::endl;
		dump_pi(pi);
		std::cerr << "----------" << std::endl;
		int neg_cnt = n;
		for(int i = 0; i < m && neg_cnt > 0; i++) {
			if(pi[G1[i].start] == -1) {
				pi[G1[i].start] = G2[i].start;
				--neg_cnt;
			} else if(pi[G1[i].end] == -1) {
				pi[G1[i].end] = G2[i].end;
				--neg_cnt;
			}
		}
		std::cerr << "-- pi-1 --" << std::endl;
		dump_pi(pi);
		std::cerr << "----------" << std::endl;

		std::cerr << std::endl;
	}

	return 0;
}
