#include <bits/stdc++.h>

using namespace std;

int n;
vector < int > G[max_n];
int match[max_n];
bool used[max_n];

void add_edge(int u, int v) { G[u].push_back(v); G[v].push_back(u); }

bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); ++i) {
        int u = G[v][i];
        int w = match[u];
        if (w < 0 || (!used[w] && dfs(w))) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int bipartite_matching() {
    int ans = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; i++) {
        if (match[i] < 0) {
            memset(used, 0, sizeof(used));
            if (dfs(i)) ans++;
        }
    }
    return ans;
}