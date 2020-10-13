/*
 * Phi facts
 * a^Phi(m) % m = 1 if a, m are coprime
 *  Direct results of that:
 * x^n = x^(n%Phi(m)) for x, m coprime.
 * for prime m -> a^(m - 1) = 1, and x^n = x^(n%(m - 1))
 *
 * x^n = x^(Phi(m) + n % Phi(m)) for non coprime x, m if x, m, and n >= log2(m)
 *
 * Count numbers <= n such that gcd(n, i) = d is Phi[n/d]
 */


// number of elements <= n coprime to n
// phi(1) = 1
int phi(int n)
{
    if (n == 1) // special return for 1?
        return 1;
    int ans = n;
    for (int i = 2; i <= n/i; ++i)
    {
        if (n%i == 0)
        {
            ans -= ans/i;
            while(n%i == 0)
                n /= i;
        }
    }
    if (n > 1)
        ans -= ans/n;
    return ans;
}

const int MAX_N = 1e6 + 5;
int phi[MAX_N];
void calcPhi()
{
    phi[1] = 1; // special value for 1?
    for (int i = 2; i < MAX_N; ++i)
        phi[i] = i;
    for (int i = 2; i < MAX_N; ++i)
        if (phi[i] == i)
            for (int j = i; j < MAX_N; j += i)
                phi[j] -= phi[j]/i;
}


long long sum[MAX_N]; // sum[n] is Summation d * phi[d] for all divisors d of n
long long LCMSum(int n)
{
    return (n * (sum[n] + 1))/2;
}

void preLCMSum()
{
    for (int i = 1; i < MAX_N; ++i)
        for (int j = i; j < MAX_N; j += i)
            sum[j] += 1LL * i * phi[i];
}