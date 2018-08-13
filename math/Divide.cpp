int c[maxn], p[maxn];
// n = \sum_{i = 1}{n} c[i]^p[i]
void divide(int n) {
    m = 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            p[++m] = i;
            c[m] = 0;
            while (n % i == 0) {
                n /= i;
                c[m]++;
            }
        } 
    }
    if (n > 1) {
        p[++m] = n;
        c[m] = 1;
    }
}