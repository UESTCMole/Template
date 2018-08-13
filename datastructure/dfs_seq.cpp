vector <int> son[N];
int seq[N], cnt, L[N], R[N];
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
