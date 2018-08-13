ll A[505], B[505];
ll ksm(ll a, int b) {
  ll res = 1;
  while (b) {
    if (b & 1) res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res % mod;
}
void init() {
  A[0] = 1;
  for (int i = 1; i <= 500; i++) A[i] = (A[i-1] * i) % mod;
  B[500] = ksm(A[500], mod-2);
  for (int i = 499; i >= 0; i--) B[i] = (B[i+1] * (i+1)) % mod;
}
ll C(int i, int j) {
  if (i<j) return 0;
  return A[i]*B[j]%mod*B[i-j]%mod)%mod;
}
