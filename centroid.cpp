class Centroid{
    int n;
    vector<set<int> > adj;
    vi par;
    vi has;
    public:
    Centroid(vector<vi> ad)
    {
        n = ad.Z;
        adj.resize(n);
        par.resize(n);
        has.resize(n);
        REP(i,0,n)
            for (int z : ad[i])
            {
                adj[i].insert(z);
                adj[z].insert(i);
            }
        build(0,-1);
    }
    int dfs(int x, int p)
    {
        has[x] = 1;
        for (int z : adj[x])
            if (z!=p)
                has[x] += dfs(z,x);
        return has[x];
    }
    int centroid(int x, int p, int sz)
    {
        for (int z: adj[x])
            if (z != p)
                if (has[z] > sz/2)
                    return centroid(z,x,sz);
        return x;
    }
    void build(int x,int p)
    {
        int n = dfs(x,p);
        int c = centroid(x,p,n);
        if (p == -1)
            p = c;
        par[c] = p;
        vi tmp(adj[c].B,adj[c].E);
        for (int z : tmp)
        {
            adj[z].erase(c);
            adj[c].erase(z);
        }
        for (int z : tmp)
            build(z,c);
    }
    public:
    vi decompose()
    {
        return par;
    }
};

