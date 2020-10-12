
// odd[i] means palindrome starts at i - odd[i] and ends at i + odd[i]
// even[i] means palindrome starts at i - even[i] - 1, and ends at i + even[i] iff even[i] != 0
void manacher(const string &s, vector<int> &odd, vector<int> &even)
{
    int n = sz(s);
    odd.clear();
    even.clear();
    odd.resize(n);
    even.resize(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(odd[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        odd[i] = --k;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(even[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        even[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
}


// strt[i] -> how many palindromes start at i
// fnsh[i] -> how many palindromes end at i
// countCover[i] -> how many palindromes cover i
const int MAX_N = 2e6 + 5;
long long strt[MAX_N], fnsh[MAX_N], countCover[MAX_N];
void calcCover(const vector<int> &odd, const vector<int> &even)
{
    int n = odd.size();
    for (int i = 0; i < n; ++i)
    {
        // odd
        int st = i - odd[i], en = i + odd[i];
        fnsh[i]++, fnsh[en + 1]--;
        strt[st]++, strt[i + 1]--;


        if (even[i])
        {
            st = i - even[i], en = i + even[i] - 1;
            fnsh[i]++, fnsh[en + 1]--;
            strt[st]++, strt[i]--;
        }
    }

    for (int i = 1; i < n; ++i)
    {
        strt[i] += strt[i - 1];
        fnsh[i] += fnsh[i - 1];
    }
    long long activePalindromes = 0;
    for (int i = 0; i < n; ++i)
    {
        activePalindromes += strt[i];
        countCover[i] = activePalindromes;
        activePalindromes -= fnsh[i];
    }
}