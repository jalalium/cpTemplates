class SegmentTree{
  int len;
  vll all;
  vll seg;
  public:
    SegmentTree(){}
    SegmentTree(vll inp)
    {
      len = inp.Z;
      all = inp;
      seg.resize(4*len);
      build(1,0,len-1);
    }
  void build(int id, int l, int r)
  {
    if (l==r)
    {
      seg[id] = all[l];
      return ;
    }
    int mid=(l+r)/2;
    build(2*id,l,mid);
    build(2*id+1,mid+1,r);
    seg[id] = min(seg[2*id],seg[2*id+1]);
  }
  ll query(int id, int l, int r, int sl, int sr)
  {
    if (r < sl || sr < l)
      return 1e18;
    if (sl <= l && sr >= r)
      return seg[id];
    int mid = (l+r)/2;
    return min(query(2*id,l,mid,sl,sr),query(2*id+1,mid+1,r,sl,sr));
  }
  ll query(int l,int r)
  {
      return query(1,0,len-1,l,r);
  }
};



struct LCA{
    vector<vi> adj;
    int n;
    int k;
    int root;
    vi bij;
    vi rbij;
    vi path;
    vi rnk;
    vi in,out;
    SegmentTree seg;
    LCA(){}
    LCA(int n_,int r_)
    {
        n = n_;
        root = r_;
        adj.resize(n);
        bij.resize(n);
        rbij.resize(n);
        in.resize(n);
        out.resize(n);
        rnk.resize(n);
        k = 0;
    }
    void addEdge(int a,int b)
    {
        adj[a].PB(b);
        adj[b].PB(a);
    }
    void dfs(int x, int par,int rk)
    {
        bij[x]=k++;
        rbij[k-1]=x;
        path.PB(bij[x]);
        in[x] = path.Z-1;
        bool in =false;
        rnk[x]=rk;
        for(int z:adj[x])
            if(z!=par)
            {
                in=true;
                dfs(z,x,rk+1);
                path.PB(bij[x]);
                out[x] = path.Z-1;
            }
        if (!in)
        {
        path.PB(bij[x]);
        out[x] = path.Z-1;
        }   
    }
    void process()
    {
        dfs(root,-1,0);
        seg = SegmentTree(path);
    }
    int query(int x,int y)
    {
        int mn = min(in[x],in[y]);
        int mx = max(out[x],out[y]);
        trace(mn);
        trace(mx);
        trace(seg.query(mn,mx));
        return rbij[seg.query(mn,mx)];
    }
    int distance(int x,int y)
    {
        return rnk[x]+rnk[y]-2*rnk[this->query(x,y)];
    }
};

