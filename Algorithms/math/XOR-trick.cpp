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