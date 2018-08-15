#include <bits/stdc++.h>
using namespace std;
const int N = 128005;
int n, a[N], d[N], c[N], m, l[N], r[N];
long long pre[N];
int root[N], cnt[20*N], tot, ls[20*N], rs[20*N];
long long sum[20*N];
int update(int x, int l, int r, int pos, int val) {
  int y = ++tot;
  cnt[y] = cnt[x] + 1;
  sum[y] = sum[x] + val;
  if (l == r) return y;
  int mid = (l + r) / 2;
  if (pos <= mid) {
    ls[y] = update(ls[x], l, mid, pos, val);
    rs[y] = rs[x];
  } else {
    rs[y] = update(rs[x], mid+1, r, pos, val);
    ls[y] = ls[x];
  }
  return y;
}
long long Query(int x, int y, int k) {
  if (!k) return 0;
  int left = 1, right = n;
  long long ans = 0;
  while (left < right) {
    int mid = (left+right) / 2;
    int num = cnt[ls[y]] - cnt[ls[x]];
    if (k >= num) {
      ans += sum[ls[y]] - sum[ls[x]];
      left = mid+1;
      k -= num;
      x = rs[x], y = rs[y];
    } else {
      right = mid;
      x = ls[x], y = ls[y];
    }
  }
  if (k) ans += (sum[y] - sum[x]) / (cnt[y] - cnt[x]) * k;
  return ans;
}
long long query(int x, int y, int k1, int k2) {
  return Query(x, y, k2) - Query(x, y, k1-1);
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    pre[i] = pre[i-1] + a[i];  
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &d[i]);
    c[i] = d[i] - a[i];
  }
  sort(c+1, c+1+n);
  for (int i = 1; i <= n; i++) {
    int pos = lower_bound(c+1, c+n+1, d[i] - a[i])-c;
    root[i] = update(root[i-1], 1, n, pos, d[i] - a[i]);
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &l[i], &r[i]);
    long long ans = 0;
    int k = (r[i]-l[i]+1)/3;
    ans += 2ll * (pre[r[i]] - pre[l[i] - 1]);
    ans += 2ll * query(root[l[i]-1], root[r[i]], k*2+1, k*3);
    ans += 1ll * query(root[l[i]-1], root[r[i]], k+1, k*2);
    printf("%.1f\n", (double)ans / 2.0);
  }
}
