void Rank(int k , vector<int> &SA , vector<int> &RA) {
    vector<int> tRA = RA;
    int n = SA.size();
    int r = RA[SA[0]] = 0;
    for (int i = 1; i < n; ++i) {
        if (tRA[SA[i]] != tRA[SA[i-1]] || tRA[(SA[i]+k)%n] != tRA[(SA[i-1]+k)%n]) ++r;
        RA[SA[i]] = r;
    }
}

void countSort(int k, vector<int> &SA, vector<int> &RA) {
    int N = SA.size();
    int maxi = max(N, 300); // change 300 if integers not chars
    vector<int> buckets(maxi);
    for (int i = 0; i < N; ++i)
        ++buckets[RA[(SA[i]+k)%N]];

    int sum = 0;
    for (int i = 0; i < maxi; ++i) {
        int temp = buckets[i];
        buckets[i] = sum;
        sum += temp;
    }

    vector<int> tSA = SA;
    for (int i = 0; i < N; ++i) {
        int newRank = buckets[RA[(tSA[i]+k)%N]]++;
        SA[newRank] = tSA[i];
    }
}

vector<int> SuffixArray(string s) {
    s.push_back(0); // make sure min(s) > 0 , remove this line if you want to sort cyclic shifts

    int n = s.size();
    vector<int> SA(n) , RA(n);
    for (int i = 0 ;i < n ;i++) {
        SA[i] = i;
        RA[i] = s[i];
    }

    for (int i = 0 ;(1 << i) <= n; ++i) {
        countSort(1 << i , SA , RA);
        countSort(0 , SA , RA);
        Rank(1 << i , SA , RA);
        if (RA[SA.back()] == n - 1) break;
    }

    SA.erase(SA.begin()); // remove this line if you want to sort cyclic shifts
    return SA;
}

vector<int> LCP (const string &s , const vector<int> &sa) {
    int n = s.size();
    vector<int> lcp(n - 1) , rank(n);
    for (int i = 0 ;i < n ;i++)
        rank[sa[i]] = i;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        k = max(0 , k - 1);
    }

    return lcp;
}