const int MAX_N = 2e5 + 5, MAX_D = 31;
struct VectorSpace{
    vector<int> basis;
    int size;
    VectorSpace()
    {
        basis.resize(MAX_D);
        size = 0;
    }
    void init()
    {
        fill(all(basis), 0);
        size = 0;
    }
    bool insert(int v)
    {
        for (int i = 0; i < MAX_D; ++i)
        {
            if ((1<<i)&v)
            {
                if (!basis[i])
                {
                    basis[i] = v;
                    size++;
                    return true;
                }
                else
                    v ^= basis[i];
            }
        }
        return false;
    }
};


// vector space with bitsets and getting indices of contributing vectors
// index[i] is a bitset with 1's at the indices of the vectors contributing to this basis vector
// can be changed from bitset to any other datastructure. make sure to cancel out indices that occur even number of times
// can combine basis[i] and index[i] into one bitset with double the size. Any set bit after MAX_N is a contribution index bit
const int MAX_N = 501;
struct VectorSpace{
    bitset<MAX_N> basis[MAX_N];
    bitset<MAX_N> index[MAX_N];
    int s = 0;

    // returns true in case of a new basis vector
    bool insert(bitset<MAX_N> v, int idx)
    {
        bitset<MAX_N> cont;
        for (int i = 0; i < MAX_N; ++i)
        {
            if (v[i])
            {
                if (basis[i].count())
                {
                    v ^= basis[i];
                    cont ^= index[i];
                }
                else
                {
                    basis[i] = v;
                    cont.set(idx);
                    index[i] = cont;
                    s++;
                    return true;
                }
            }
        }
        return false;
    }

    // returns bitset with indices of contributing vectors. all zeros if impossible to construct
    // careful if v is already all zeros. Special case meaning it can be constructed without any vector
    bitset<MAX_N> can(bitset<MAX_N> v)
    {
        bitset<MAX_N> ret;
        for (int i = 0; i < MAX_N; ++i)
        {
            if (v[i])
            {
                if (!basis[i].count())
                {
                    ret.reset();
                    return ret;
                }
                v ^= basis[i];
                ret ^= index[i];
            }
        }
        return ret;
    }
};
