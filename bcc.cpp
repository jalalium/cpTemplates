struct BCC{
    int n;
    vector<vi> adj;
    vector<vpi> bcc;
    vpi st;
    vi disc,low,par;
    int t;
    BCC(){}
    BCC(int n_)
    {
        n=n_;
        adj.resize(n);
        disc.resize(n);
        low.resize(n);
        par.resize(n,-1);
        t = 0;
    }
    void addEdge(int a,int b)
    {
        adj[a].PB(b);
        adj[b].PB(a);
    }
    void dfs(int x, bool root=0)
    {
        disc[x]=low[x]=t++;
        int children = 0;
        for(int z :adj[x])
        {
            if(z!=par[x])
            {
                if (disc[z]==-1)
                {
                    children++;
                    par[z]=x;
                    st.PB(MP(x,z));
                    dfs(z);
                    low[x] = min(low[x],low[z]);
                    if((root && children>1)||(!root && disc[x] <= low[z]))
                    {
                        vpi tmp;
                        while(st.Z&&st.back()!=MP(x,z))
                        {
                            tmp.PB(st.back());
                            st.pop_back();
                        } 
                        tmp.PB(st.back());
                        st.pop_back();
                        bcc.PB(tmp);
                    }
                }
                else if(disc[z] < disc[x])
                {
                    low[x]=min(low[x],disc[z]);
                    st.PB({x,z});
                }
            }
        }
    }
    vector<vpi> calc()
    {
        REP(i,0,n)
            disc[i]=low[i]=-1;
        dfs(0,1);
        if(st.Z)
            bcc.PB(st);
        st.clear();
        return bcc;
    }
};

