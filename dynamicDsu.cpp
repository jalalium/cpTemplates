struct edge{
    int a,b,l,r;
    edge(int a,int b,int l,int r)
    {
        this->a=a;
        this->b=b;
        this->l=l;
        this->r=r;
    }
};

struct DynamicDsu{
    struct change{
        int u,v,ru,rv;
        change(int _u,int _v,int _ru,int _rv) :u(_u),v(_v),ru(_ru),rv(_rv){}
    };
    int sz;
    int cc;
    vi par;
    vi rnk;
    stack<change> op;
    DynamicDsu(){}
    DynamicDsu(int n)
    {
        sz =n;
        cc = n;
        par.resize(n);
        rnk.resize(n);
        REP(i,0,n)
        {
            par[i]=i;   
            rnk[i]=0;
        }
    }
    int find(int x)
    {
        return par[x] ==x?x:find(par[x]);
    }
    bool merge(int a, int b)
    {
        int x=find(a);
        int y=find(b);
        if(x == y)
            return false;
        cc--;
        if(rnk[y]>rnk[x])
            swap(y,x);
        op.push(change(y,x,rnk[y],rnk[x]));
        if (rnk[x]==rnk[y])
            rnk[x]++;
        return true;
    }
    void rollback()
    {
        if (op.empty())
            return;
        change did = op.top();
        op.pop();
        cc++; 
        par[did.u]=did.u;
        par[did.v]=did.v;
        rnk[did.u]=did.ru;
        rnk[did.v]=did.rv;
    }
};
struct event{
    int u,v;
    bool good;
    event(int _u,int _v):u(_u),v(_v){}
};

struct QueryTree{
    vector<vector<event> > tree;
    int time;
    vi ans;
    DynamicDsu dsu;
    QueryTree(int T,int n)
    {
        dsu = DynamicDsu(n);
        time =T;
        tree.resize(4*T);
        ans.resize(T);
        ans[0]=n;
    }
    void addIt(int id,int l,int r, int el,int er, event &e)
    {
        if (l<=el&&er<=r)
        {
            tree[id].PB(e);
            return ;
        }
        if (l >er ||r < el) 
            return;
        int mid=(l+r)/2;
        addIt(2*id,l,mid,el,er,e);
        addIt(2*id+1,mid+1,r,el,er,e);
    }
    void addEvent(int l, int r, event e)
    {
        addIt(1,0,time-1,l,r,e);
    }
    void dfs(int id,int l,int r)
    {
        for(event &e :tree[id])
            e.good=dsu.merge(e.u,e.v);
        if (l==r)
            ans[l]=dsu.cc;
        else
        {
            int mid=(l+r)/2;
            dfs(2*id,l,mid);
            dfs(2*id+1,mid+1,r);
        }
    }
    vi solve()
    {
        dfs(1,0,time-1);
        return ans;
    }
};

