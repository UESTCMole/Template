#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T, n, q;
struct Edge
{
  int u, v, c1, c2, nxt;
}e1[200005];
int tot1, tot2;
int last[100005];

void add1(int u, int v, int c1, int c2)
{
  tot1++;
  e1[tot1].u = u, e1[tot1].v = v, e1[tot1].c1 = c1, e1[tot1].c2 = c2, e1[tot1].nxt = last[u], last[u] = tot1;
}


int d[100005], f[100005], g[100005];
int up[100005][32];

void bfs()
{
  queue <int> q;
  q.push(1);
  d[1] = 1;
  while (!q.empty())
  {
    int u = q.front();q.pop();
    for (int i = last[u]; i; i = e1[i].nxt)
    {
      int v = e1[i].v;
      if (d[v]) continue;
      d[v] = d[u] + 1;
      f[v] = f[u] + e1[i].c1;
      g[v] = g[u] + e1[i].c2;
      up[v][0] = u;
      for (int j = 1; j <= 19; j++)
      {
        up[v][j] = up[up[v][j-1]][j-1];
      }
      q.push(v);
    }
  }
}

int lca(int x, int y)
{
  //printf("%d %d\n", d[x], d[y]);
  if (d[x] > d[y]) swap(x, y);
  for (int i = 19; i >= 0; i--)
    if (d[up[y][i]] >= d[x]) y = up[y][i];
  if (x == y) return x;
  //printf("x=%d,y=%d\n", x, y);
  for (int i = 19; i >= 0; i--)
  {
    if (up[x][i] != up[y][i])
    {
      x = up[x][i];
      y = up[y][i];
    }
  }
  return up[x][0];
}

int main()
{
  scanf("%d", &T);
  while (T--)
  {
    int sum = 0;
    scanf("%d", &n);
    tot1 = tot2 = 0;
    memset(d, 0, sizeof(d));
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(last, 0, sizeof(last));
    for (int i = 1; i <= n-1; i++)
    {
      int u, v, c1, c2;
      scanf("%d%d%d%d", &u, &v, &c1, &c2);
      add1(u, v, c1, c2);
      add1(v, u, c2, c1);
      sum += (c1+c2);
    }
    bfs();
    //for (int i = 1; i <= 5; i++)
    //{
      //printf("%d %d\n", f[i], g[i]);
    //}
    scanf("%d", &q);
    while (q--)
    {
      int x, y;
      scanf("%d%d", &x, &y);
      int tmp = lca(x, y);
      //printf("%lld %d\n", sum, tmp);
      printf("%d\n", sum - (g[y] + f[x] - g[tmp] - f[tmp]));
    }
  }
}
