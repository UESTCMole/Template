#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 100;
const double eps = 1e-8;
double a[maxn][maxn];
void gauss_jordan(int n) {
  int i, j, k, r;
  for (i = 0; i < n; i++) {
    r = i;
    for (j = i + 1; j < n; j++) 
      if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
    if (fabs(a[r][i]) < eps) continue;
    if (r != i) for (j = 0; j <= n; j++) swap(a[r][j], a[i][j]);
    for (k = i + 1; k < n; k++) {
      double f = a[k][i] / a[i][i];
      for (j = i; j <= n; j++) a[k][j] -= f * a[i][j];
    }
  }
  for (i = n-1; i >= 0; i--) {
    for (j = i + 1; j < n; j++)
      a[i][n] -= a[j][n] * a[i][j];
    a[i][n] /= a[i][j];
  }
}