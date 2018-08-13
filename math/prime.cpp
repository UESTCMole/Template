int v[max_n], prime[max_n], m;
//O(NloglogN)

void primes(int n) {
    int m = sqrt(n+0.5);
    memset(v, 0, sizeof(v));
    for (int i = 2; i <= m; i++) {
        if (!vis[i]) {
            for (int j = i*i; j <= n; j+=i) v[j] = 1;
        }
    }
}


//O(N)

void primes(int n) {
    memset(v, 0, sizeof(v));
    m = 0;
    for (int i = 2; i <= n; i++) {
        if (v[i] == 0) {//i is prime
            v[i] = i;
            prime[++m] = i;
        }
        for (int j = 1; j <= m; j++) {
            if (prime[j] > v[i] || prime[j] > n/i) break;
            v[i*prime[j]] = prime[j];
        }
    }
}