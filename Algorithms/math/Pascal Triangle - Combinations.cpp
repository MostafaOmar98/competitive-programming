ll C[N][N];
void genComb()
{
    C[0][0] = 1;
    for (int r = 1; r < N; ++r)
    {
        C[r][0] = 1;
        C[r][r] = 1;
        for (int j = 1; j < r; ++j)
        {
            C[r][j] = C[r-1][j] + C[r-1][j-1];
        }
    }
}
