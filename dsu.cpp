struct DSU{
    vi par;
    vi siize;
    DSU(int n)
    {
        par.resize(n);
        siize.resize(n);
        REP(i,0,n)
        {
            par[i]=i;
            siize[i]=1;
        }
    }
    int get(int x)
    {
        return (x == par[x] ? x : par[x] = get(par[x]));
    }
    void merge(int a, int b)
    {
        int x = get(a);
        int y = get(b);
        if (x == y)return;
        if (siize[x] < siize[y])swap(x,y);par[y] = x;siize[x] += siize[y];
    }
};

