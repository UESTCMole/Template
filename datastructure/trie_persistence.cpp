// hdu 6191
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <cmath>
#define ll long long
#define ull unsigned long long
using namespace std;
const int N = 100005;
int v[N], f[N];
int n, q;
vector <int> son[N];
int seq[N], cnt, L[N], R[N];
int root[N], nxt[N << 5][2], sum[N << 5], tot;
void dfs(int u, int fa) {
  seq[++cnt] = u;
  L[u] = cnt;
  int sz = son[u].size();
  for (int i = 0; i < sz; i++) {
    int v = son[u][i];
    if (v == fa) continue;
    dfs(v, u);
  }
  R[u] = cnt;
}
int newnode() {
  tot++;
  memset(nxt[tot], 0, sizeof(nxt[tot]));
  return tot;
}
int insert(int rt, int val) {
  int y = ++tot;
  int x = rt;
  int res = tot;
  for (int i = 30; i >= 0; i--) {
    sum[y] = sum[x] + 1;
    nxt[y][0] = nxt[x][0];
    nxt[y][1] = nxt[x][1];
    int num = (val >> i) & 1;
    nxt[y][num] = newnode();
    y = nxt[y][num];
    x = nxt[x][num];
  }
  sum[y] = sum[x] + 1;
  return res;
}
int query(int l, int r, int val) {
  int ans = 0;
  for (int i = 30; i >= 0; i--) {
    int num = (val >> i) & 1;
    if (sum[nxt[r][!num]] - sum[nxt[l][!num]]) {
      l = nxt[l][!num];
      r = nxt[r][!num];
      ans += 1 << i;
    } else {
      l = nxt[l][num];
      r = nxt[r][num];
    }
  }
  return ans;
}
int main() {
  while (scanf("%d%d", &n, &q) != EOF) {
    cnt = tot = 0; for (int i = 1; i <= n; i++) son[i].clear();
    memset(nxt[0], 0, sizeof(nxt));
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int i = 2; i <= n; i++) {
      int f;scanf("%d", &f);
      son[f].push_back(i);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) root[i] = insert(root[i-1], v[seq[i]]);
    while (q--) {
      int u, x;scanf("%d%d", &u, &x);
      printf("%d\n", query(root[L[u]-1], root[R[u]], x));
    }
  }
}

