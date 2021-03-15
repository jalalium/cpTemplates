struct Dinic{
    vi ans;
    struct Edge{
        int to;
        int rev;
        int flo;
        int cap;
        Edge(){}
        Edge(int _to,int _rev,int _flo,int _cap):to(_to),rev(_rev),flo(_flo),cap(_cap){}
    };
    vector <vector<Edge> > adj;
    int src,dest;
    int n;
    vi ind;
    vi level;
    Dinic(){}
    Dinic(int _n,int _src,int _dest)
    {
        n=_n;
        src = _src;
        dest= _dest;
        adj.resize(n);
        ind.resize(n);
        level.resize(n);
    }
    void addEdge(int u,int v,int cap,int rcap=0)
    {
        Edge x,y;
        x = Edge(v,adj[v].Z,0,cap);
        y = Edge(u,adj[u].Z,0,rcap);
        adj[u].PB(x);
        adj[v].PB(y);
    }
    bool bfs()
    {
        queue<int> kyou;
        REP(i,0,n)
        {
            level[i]=-1;
            ind[i]=0;
        }
        level[src]=0;
        kyou.push(src);
        while(kyou.Z)
        {
            int frt = kyou.front();
            kyou.pop();
            for(Edge z : adj[frt])
            {
                if (level[z.to]<0&&z.flo<z.cap)
                {
                    level[z.to]=level[frt]+1;
                    kyou.push(z.to);
                }
            }
        }
        return level[dest]!=-1;
    }
    bool bfs2()
    {
        queue<int> kyou;
        REP(i,0,n)
        {
            level[i]=-1;
            ind[i]=0;
        }
        level[src]=0;
        kyou.push(src);
        while(kyou.Z)
        {
            int frt = kyou.front();
            kyou.pop();
            for(Edge z : adj[frt])
            {
                if (level[z.to]<0&&z.flo==z.cap)
                {
                    level[z.to]=level[frt]+1;
                    kyou.push(z.to);
                }
            }
        }
        return level[dest]!=-1;
    }

    int dfs(int x,int flo)
    {
        if(x==dest)
            return flo;
        for(;ind[x]<adj[x].Z;ind[x]++)
        {
            Edge &xx = adj[x][ind[x]];
            if(level[xx.to]!=level[x]+1 || xx.cap==xx.flo)continue;
            int fl = dfs(xx.to,min(flo,xx.cap-xx.flo));
            if (fl!=0)
            {
                xx.flo+=fl;adj[xx.to][xx.rev].flo-=fl;
                return fl;
            }
        }
        return 0;
    }
    int dfs1(int x)
    {
        if(x==dest)
        {
            ans.PB(x);
            return 1;
        }
        for(;ind[x]<adj[x].Z;ind[x]++)
        {
            Edge &xx = adj[x][ind[x]];
            if(level[xx.to]!=level[x]+1 || xx.flo <= 0)continue;
            int fl = dfs1(xx.to);
            if (fl=1)
            {
                xx.flo=0;
                ans.PB(x);
                return 1;
            }
        }
        return 0;
    }
    int maxFlow()
    {
        int ans = 0;
        while(bfs())
        {
            for(int fl = dfs(src,1e9);fl>0;fl=dfs(src,1e9))
            {
                trace(fl);
                trace("RE");
                ans+=fl;
            }       
        }
        return ans;
    }
};

