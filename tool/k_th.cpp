void quickSelect(int a[], int l, int r, int rank) {
  int i = l, j = r;
  unsigned mid = a[(l + r) / 2];
  do {
    while (a[i] < mid) ++i;
    while (a[j] > mid) --j;
    if (i <= j) {
      swap(a[i], a[j]);
      ++i; --j;
    }
  } while (i <= j);
  if (l <= j && rank <= j-l+1) quickSelect(l, j, rank);
  if (i <= r && rank >= i-l+1) quickSelect(i, r, rank-(i-l));
}