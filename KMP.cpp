// pi[len - 1] pretty much gets you the next greatest suffix smaller than you that matches
// remember that this algorithm always works on proper prefixes. it doesn't handle anything that has to do with the string itself or the prefix as a substring

int memKMP[MAX_LEN][26];
int getNewLen(int len, char c) // Memoized
{
    if (!len || (len != pattern.size() && pattern[len] == c))
        return len + (pattern[len] == c);
    int &ret = memKMP[len][c - 'a'];
    if (~ret)
        return ret;
    return getNewLen(pi[len - 1], c, id);
}


int getNewLen(int len, char c)
{
    while(len && (len != pattern.size() && c != pattern[len]))
        len = pi[len - 1];
    return len + (pattern[len] == c);
}

// OLD bad abstractions
//void buildPi()
//{
//    pi.clear(); // need clear here or fakes?
//    pi.resize(pattern.size());
//    pi[0] = 0;
//    for (int i = 1; i < sz(pattern); ++i)
//        pi[i] = getNewLen(pi[i - 1], pattern[i]);
//}

vector<int> kmp(const string &s)
{
    vector<int> pi(sz(s));
    for (int i = 1, len = 0; i < sz(s); ++i)
    {
        while(len > 0 && s[len] != s[i])
            len = pi[len - 1];
        len += (s[i] == s[len]);
        pi[i] = len;
    }
    return pi;
}


// don't forget to call buildPi;
int match()
{
    int ret = 0;
    for (int len = 0, i = 0; i < sz(text); ++i)
    {
        len = getNewLen(len, text[i]);
        if (len == sz(pattern))
            ret++;
    }
    return ret;
}


vector<int> preFreq;
void buildPreFreq()
{
    preFreq.resize(sz(pattern) + 1, 0);
    for (int i = 0; i < sz(pattern); ++i)
        preFreq[pi[i]]++;
    for (int len = sz(pattern) - 1; len > 0; --len)
        preFreq[pi[len - 1]] += preFreq[len];

    // if you want to count the prefix itself
    for (int len = 1; len <= sz(pattern); ++len)
        preFreq[len]++;
}