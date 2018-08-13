#include <math.h>
int euler_phi(int n) {
    int ans = n;
    int m = sqrt(n + 0.5);
    for (int i = 2; i <= m; i++) {
        if (n%i == 0) {
            ans = ans/i*(i-1);
            while (n%i == 0) n /= i;
        }
    }
    if (n > 1) ans = ans/n*(n-1); //if n is a prime
    return ans;
}

void phi_table(int n, int phi[]) {
    for (int i = 1; i <= n; i++) phi[i] = i;
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j]/i*(i-1);
            }
        }
    }
}