
// Returns "0" instead of empty string when number is 0. Adjust if empty string is needed
void trim(string &s)
{
    reverse(s.begin(), s.end());
    while(!s.empty() && s.back() == '0')
        s.pop_back();
    reverse(s.begin(), s.end());
    if (s.empty())
        s = "0";
}

bool isZero(string s)
{
    trim(s);
    return s == "0";
}

// a >= b
// a, b positive
string subtract(string a, string b)
{
    // not needed if handled by trim
    if (a == b)
        return "0";
    reverse(b.begin(), b.end());
    reverse(a.begin(), a.end());
    while(sz(b) < sz(a))
        b += '0';
    string res;

    for (int i = 0, carry = 0; i < sz(a); ++i)
    {
        int x = a[i] - '0', y = b[i] - '0';
        if (x >= y + carry)
        {
            res += (x - y - carry) + '0';
            carry = 0;
        }
        else
        {
            res += (x + 10 - y - carry) + '0';
            carry = 1;
        }
    }
    reverse(res.begin(), res.end());
    trim(res);
    return res;
}