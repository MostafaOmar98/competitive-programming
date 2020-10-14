/*
 * Phi facts:
 * a^Phi(m) % m = 1 if a, m are coprime
 *  Direct results of that:
 * x^n = x^(n%Phi(m)) for x, m coprime.
 * for prime m -> a^(m - 1) = 1, and x^n = x^(n%(m - 1))
 *
 * x^n = x^(Phi(m) + n % Phi(m)) for non coprime x, m if n >= Phi(m).
 * (OLD STUFF YOU HAVE NEW UNDERSTANDING) Since Phi(m) >= log2(m) (non trivial proof). It's easier to think of the condition as n >= Phi(m). This allows for the spmod implementation below
 * NEW: Think about x^n % m as 2 blocks one in range [0, Phi(m)), other in [Phi(m), infinity).
 * First block values doesn't relate to any other values
 * Second block is cyclic with cycle size Phi(m). So if n >= Phi(m) you take n%Phi(m) and + Phi(m) to move to second block
 * spmod below helps with calculating exponents like that. If the exponent never exceeded Phi(m), it just returns it as it is.
 * If it exceeded, it will take %phi(m) and always add phi(m) to move it to second block. This +mod doesn't affect other modded operations 3ashan mesh far2a law deft phi(m)
 * just be careful about overflow in this case.
 *
 * Count numbers <= n such that gcd(n, i) = d is Phi[n/d]
 *
 * Phi(Phi(n)) <= n/2;
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
long long LCMSum(int n) // LCMSum(n) is summation of LCM(n, i) for all i <= n
{
    return (n * (sum[n] + 1))/2;
}

void preLCMSum()
{
    for (int i = 1; i < MAX_N; ++i)
        for (int j = i; j < MAX_N; j += i)
            sum[j] += 1LL * i * phi[i];
}

long long sumGCD[MAX_N]; // sumGCD[n] is summation of gcd(n, i) for all i <= n
void preSumGCD()
{
    for (int i = 1; i < MAX_N; ++i)
        for (int j = i; j < MAX_N; j += i)
            sumGCD[j] += 1LL * i * phi[j / i];
}


/*
 * Cool way to calculate x^n % m.
 * if n < Phi(m), just directly calculate x^n % m.
 * else: calculate x^e % m, where e = Phi(m) + n%Phi(m).
 * spmod(x, Phi(m)) returns the correct value for n 3alla tool. If it's < Phi(m) it will do the direct calculation, otherwise it will return 'e' mentioned above
 */

// CAREFUL overflow with spmod
int spmod(long long x, int mod)
{
    if (x < mod)
        return x;
    return (x%mod) + mod;
}

int mult(int x, int y, int mod)
{
    return spmod(1LL * x * y, mod);
}

int power(int base, int exp, int mod)
{
    int ret = 1;
    for (; exp; exp /= 2, base = mult(base, base, mod))
        if (exp&1)
            ret = mult(ret, base, mod);
    return ret;
}