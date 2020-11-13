// search_buckets provides two operations on an array:
// 1) set array[i] = x
// 2) count how many i in [start, end) satisfy array[i] < value
// Both operations take sqrt(N log N) time. Amazingly, because of the cache efficiency this is faster than the
// (log N)^2 algorithm until roughly N = 5,000,000.
template<typename T>
struct search_buckets {
    // values are just the values in order. buckets are sorted in segments of bucket_size (last segment may be smaller)
    int N, bucket_size;
    vector<T> values, buckets;

    search_buckets(const vector<T> &initial = {}) {
        initialize(initial);
    }

    void initialize(const vector<T> &initial) {
        values = buckets = initial;
        N = values.size();
        bucket_size = max(int(1.5 * sqrt(N * log(N))), 20);

        for (int start = 0; start < N; start += bucket_size)
            sort(buckets.begin() + start, buckets.begin() + min(start + bucket_size, N));
    }

    int bucket_less_than(int b_start, T value) {
        auto begin = buckets.begin() + b_start;
        auto end = buckets.begin() + min(b_start + bucket_size, N);
        return lower_bound(begin, end, value) - begin;
    }

    int less_than(int start, int end, T value) {
        int next_bucket = start + (bucket_size - start % bucket_size) % bucket_size;
        int count = 0;

        while (start < min(next_bucket, end))
            count += values[start++] < value ? 1 : 0;

        while (start + bucket_size <= end) {
            count += bucket_less_than(start, value);
            start += bucket_size;
        }

        while (start < end)
            count += values[start++] < value ? 1 : 0;

        return count;
    }

    int prefix_less_than(int n, T value) {
        return less_than(0, n, value);
    }

    void modify(int index, T value) {
        int b_start = index - index % bucket_size;
        int old_pos = b_start + bucket_less_than(b_start, values[index]);
        int new_pos = b_start + bucket_less_than(b_start, value);

        if (old_pos < new_pos) {
            copy(buckets.begin() + old_pos + 1, buckets.begin() + new_pos, buckets.begin() + old_pos);
            new_pos--;
        } else {
            copy_backward(buckets.begin() + new_pos, buckets.begin() + old_pos, buckets.begin() + old_pos + 1);
        }

        buckets[new_pos] = value;
        values[index] = value;
    }
};


int N;
vector<pair<int, int>> teams;

int main() {
    scanf("%d", &N);
    teams.resize(N);

    for (int i = 0; i < N; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a--; b--; c--;
        teams[a] = {b, c};
    }

    search_buckets<int> buckets(vector<int>(N, N));
    long long total = (long long) N * (N - 1) / 2;

    for (int a = 0; a < N; a++) {
        total -= buckets.less_than(0, teams[a].first, teams[a].second);
        buckets.modify(teams[a].first, teams[a].second);
    }

    printf("%lld\n", total);
}