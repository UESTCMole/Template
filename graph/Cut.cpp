#include <bits/stdc++.h>
using namespace std;
int n, m;
int from[M], to[M], nxt[M], last[N], tot, dfn[N], low[N], root;
bool cut[N];
void add(int u, int v) {
  // tot from 1 !!!
  tot++; from[tot] = u; to[tot] = v; nxt[tot] = last[u]; last[u] = tot;
}
void dfs(int x) {
  dfn[x] = low[x] = ++num;
  int flag = 0;
  for (int i = last[x]; i; i = nxt[i]) {
    int y = to[i];
    if (!dfn[y]) {
      dfs(y);
      low[x] = min(low[x], low[y]);
      if (low[y] >= dfn[x]) {
        flag++;
        if (x != root || flag > 1) cut[x] = true;
      }
    } else low[x] = min(low[x], dfn[y]);
  }
}
int main() {
  scanf("%d %d", &n, &m);
  tot = 1;
  for (int i = 1; i <= m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    if (u == v) continue;
    add(u, v), add(v, u);
  }
  for (int i = 1; i <= n; i++) if (dfn[i]) {
    root = i, dfs(i);
  }
  for (int i = 1; i <= n; i++) if (cut[i]) printf("%d ", i);//for test
}
