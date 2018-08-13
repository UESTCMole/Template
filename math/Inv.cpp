#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#define mod 1000000007
using namespace std;

typedef long long ll;
typedef unsigned long long ull;


ull ksm(ull a)
{
  ull b = mod - 2;
  ull base = a;
  ull res = 1;
  while (b)
  {
    if (b & 1) res = (res * base)%mod;
    base = (base * base) % mod;
    b >>= 1;
  }
  return res % mod;
}

ull inv[1000005];
ull Inv(ull x) { return x == 1 ? 1 : (Inv(mod % x) * (mod - mod / x) + mod) % mod; }

/*
ni[0]=ni[1]=1;
for(int i=2;i<=1000000;i++){
	ni[i]=((LL)mod*mod-(LL)(mod/i)*ni[mod%i])%mod;
}
*/

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  int T;
  for (int i = 1; i <= 1000001; i++) inv[i] = ksm(i);
  ull n, m;
  cin >> T;
  while (T--)
  {
    cin >> n >> m;
    if (m > n) cout << n << endl;
    else
    {
      cout << (((m * (n + 1))+mod) % mod * inv[m+1] + mod) % mod << endl;
    }
  }
}
