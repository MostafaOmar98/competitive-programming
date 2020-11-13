int n;
const int MAX_N = 2e5 + 5, MAX_V = 1e6 + 5;
bool isPrime[MAX_V];
int ans;
vector<int> divs[2 * MAX_N];
void sieve()
{
    clr(isPrime, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAX_V; ++i)
    {
        if (isPrime[i])
        {
            for (int j = 2 * i; j < MAX_V; j += i)
                isPrime[j] = false;
        }
    }
}

ll B[2 * MAX_N];

int main()
{
    sieve();
    for (ll x = l; x <= r; ++x)
        B[x - l] = x;
    vector<ll> primes;
    for (int p = 2; p < MAX_V; ++p)
    {
        if (isPrime[p])
        {
            for (ll x = (l + p - 1)/p * p; x <= r; x += p)
            {
                primes.push_back(p);
                while(B[x - l]%p == 0)
                    B[x - l] /= p;
            }
        }
    }

    for (ll x = l; x <= r; ++x)
        if (B[x - l] > 1)
            primes.push_back(B[x - l]);

    sort(all(primes));
    primes.resize(unique(primes.begin(), primes.end()) - primes.begin());
    cerr << sz(primes) << '\n';
    cout << solve(primes) << '\n';

    return 0;
}