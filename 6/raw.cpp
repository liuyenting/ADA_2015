#include <iostream>
#include <vector>
#include <functional>
#include <stack>
#include <algorithm>
using namespace std;
const int maxN = 50007;
class Edge
{
public:
	int s;
	int t;
	int cost;
	Edge(int a, int b, int c) {
		this->s = a;
		this->t = b;
		this->cost = c;
	}
};

int dfn[maxN];
int low[maxN];
int set[maxN];
int timestamp;
stack<int> sta;
vector<Edge> edges;
vector<pair<int,long long> > links[maxN]; // des, no.
pair<int,long long> dfs(int,bool*,long long );
namespace std
{
template <typename T,typename U>std::pair<T,U>
operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
	return (l.first + r.first, l.second + r.second);
}
}
void tarjan(int,int);
int findRoot(int);
void unionSet(int,int);
int main(int argc,char* argv[]) {
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;

		// init
		for(int i=0; i<n; i++) {
			set[i] = i;
			dfn[i] = low[i] = -1;
			timestamp = 0;
		}
		while(sta.size()) {
			sta.pop();
		}
		edges.clear();
		pair<int,long long> ans = make_pair(0,0);

		// input
		for(int i=0; i<m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			a--, b--;
			edges.push_back(Edge(a, b, c));
		}
		sort(edges.begin(), edges.end(), [](Edge x, Edge y) {
			return x.cost < y.cost;
		});

		int l = 0;
		int r = 0;

		while(l < m) {
			for(int i=0; i<n; i++) {
				dfn[i] = low[i] = -1;
				timestamp = 0;
				links[i].clear();
			}
			while(sta.size()) {
				sta.pop();
			}
			Edge base = edges[l];
			for(r=l; r<=m; r++) {
				if(r<m && edges[r].cost == base.cost) {
					Edge now = edges[r];
					now.s = findRoot(now.s);
					now.t = findRoot(now.t);
					if(now.s==now.t) {
						continue;
					} else {
						links[now.s].push_back(make_pair(now.t, r));
						links[now.t].push_back(make_pair(now.s, r));
					}
				} else {
					break;
				}
			}
			for(int i=l; i<r; i++) {
				tarjan(findRoot(edges[i].s), -1);
				tarjan(findRoot(edges[i].t), -1);
			}
			bool visited[maxN] = {false};
			for(int i=l; i<r; i++) {
				ans = ans + dfs(findRoot(edges[i].s), visited, base.cost);
				ans = ans + dfs(findRoot(edges[i].t), visited, base.cost);
			}
			l = r;
		}
		cout << ans.first << " " << ans.second << endl;
	}
}
pair<int,long long> dfs(int u, bool* visited, long long c) {
	pair<int,long long> ans;
	if(visited[u]) return make_pair(0,0);
	visited[u] = true;
	for(int i=0; i<links[u].size(); i++) {
		if(findRoot(u) != findRoot(links[u][i].first)) {
			ans = ans + make_pair(1, c);
		}
		unionSet(links[u][i].first, u);
		ans = ans + dfs(links[u][i].first, visited, c);
	}
	return ans;
}
void tarjan(int u, int e) {
	u = findRoot(u);
	dfn[u] = low[u] = timestamp++;
	sta.push(u);
	for(int i=0; i<links[u].size(); i++) {
		if(links[u][i].second == e || findRoot(links[u][i].first) == u) continue;
		int v = findRoot(links[u][i].first);
		if(dfn[v] == -1) { // not visited
			tarjan(v, links[u][i].second);
			low[u] = min(low[u], low[v]);
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(dfn[u] == low[u]) {
		while(true) {
			int v = sta.top();
			sta.pop();
			if(u==v) break;
			unionSet(u, v);
		}
	}
}
int findRoot(int a) {
	return (set[a] == a) ? a : set[a] = findRoot(set[a]);
}
void unionSet(int a, int b) {
	set[findRoot(a)] = findRoot(b);
}
