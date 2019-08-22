struct minStack{
    stack<pair<int, int> > st;
    void Pop()
    {
        assert(!st.empty());
        st.pop();
    }
    int getTop()
    {
        assert(!st.empty());
        return st.top().first;
    }
    int getMin()
    {
        assert(!st.empty());
        return st.top().second;
    }
    void Push(int x)
    {
        st.push({x, st.empty() ? x : min(x, getMin())});
    }
    bool empty()
    {
        return st.empty();
    }
};

struct minQueue{
    // pop from s2, push in s1
    minStack s1, s2;
    void Push(int x)
    {
        s1.Push(x);
    }
    int getMin()
    {
        int mn = INT_MAX;
        if (!s1.empty())
            mn = min(mn, s1.getMin());
        if (!s2.empty())
            mn = min(mn, s2.getMin());
        return mn;
    }
    void Pop()
    {
        if (s2.empty())
        {
            while(!s1.empty())
            {
                int ele = s1.getTop();
                s1.Pop();
                s2.Push(ele);
            }
        }
        s2.Pop();
    }
    int getFront()
    {
        if (s2.empty())
        {
            while(!s1.empty())
            {
                int ele = s1.getTop();
                s1.Pop();
                s2.Push(ele);
            }
        }
        return s2.getTop();
    }
};
