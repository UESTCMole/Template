#include <bits/stdc++.h>
using namespace std;
int n, m;
int from[10005], to[10005], nxt[10005], dfn[105], vis[105], low[105], last[105], tot, num, deg[105];
bool bridge[10005];
void add(int u, int v) {
  // tot from 1 !!!
  tot++; from[tot] = u; to[tot] = v; nxt[tot] = last[u]; last[u] = tot;
}
void dfs(int x, int in_edge) {
  dfn[x] = low[x] = ++num;
  for (int i = last[x]; i; i = nxt[i]) {
    int y = to[i];
    if (!dfn[y]) {
      dfs(y, i);
      low[x] = min(low[x], low[y]);
      if (low[y] > dfn[x]) bridge[i] = bridge[i^1] = true;
    } else if (i != (in_edge ^ 1)) low[x] = min(low[x], dfn[y]);
  } 
}
bool flag = true;
void DFS(int u, int sz, int b1, int b2, int fir) {
  if (u != fir && deg[u] != sz) {
    flag = false;
    return ;
  }
  vis[u] = 1;
  for (int i = last[u]; i; i = nxt[i]) {
    if (i == b1 || i == b2 || vis[to[i]]) continue;
    DFS(to[i], sz, b1, b2, fir);
  }
}
int main() {
  int cas = 0; int T; scanf("%d", &T);
  while (T--) {
    int ans = 0;
    scanf("%d%d", &n, &m);
    memset(last, 0, sizeof(last));
    memset(deg, 0, sizeof(deg));
    memset(bridge, 0, sizeof(bridge));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    tot = 1; num = 0;
    for (int i = 1; i <= m; i++) {
      int u, v; scanf("%d%d", &u, &v);
      add(u, v); add(v, u);
      deg[u]++, deg[v]++;
    }    
    for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i, 0);
    for (int i = 2; i <= tot; i += 2) if (bridge[i]) {
      //printf("%d %d\n", to[i], to[i^1]);
      int u = from[i], v = to[i];
      flag = true;
      if (deg[u] != deg[v]) continue;
      memset(vis, 0, sizeof(vis));
      DFS(u, deg[u] - 1, i, i^1, u); 
      memset(vis, 0, sizeof(vis));
      DFS(v, deg[v] - 1, i, i^1, v);
      if (flag) ans++;
    }
    printf("Case #%d: %d\n", ++cas, ans);
  }
}
