struct PersistentSeg{
    struct node{
        node *l,*r;
        int sum;
        node(int val):l(nullptr),r(nullptr),sum(val){}
        node(node *a,node *b)
        {
            l=a;
            r=b;
            sum=0;
            if(a)
                sum+=a->sum;
            if(b)
                sum+=b->sum;
        }
    };
    vector<vector<node*>> states;
    vi vals;
    int len;
    PersistentSeg(vi a)
    {
        vals=a;
        len =a.Z;
        node *root;
        root = build(0,len-1);
        vector<node*> xx;
        xx.PB(root);
        states.PB(xx);
    }
    node* build(int l,int r)
    {
        if(l==r)
            return new node(vals[l]);
        int mid = (l+r)/2;
        return new node(build(l,mid),build(mid+1,r));
    }
    int getSum(node *root, int l,int r, int sl,int sr)
    {
        if (r < sl || l > sr)
            return 0;
        if (l>=sl&&r<=sr)
            return root->sum;
        int mid = (l+r)/2;
        return (getSum(root->l,l,mid,sl,sr)+getSum(root->r,mid+1,r,sl,sr));
    }
    int getSum(int k,int l,int r)
    {
        return getSum(states[k].back(),0,len-1,l,r);
    }
    node *update(node *root,int l,int r,int pos,int val)
    {
        if (l==r)
            return new node(val);
        int mid=(l+r)/2;
        if (pos<=mid)
            return new node(update(root->l,l,mid,pos,val),root->r);
        else
            return new node(root->l,update(root->r,mid+1,r,pos,val));
    }
    void update(int k,int pos,int val)
    {
        node* upd = update(states[k].back(),0,len-1,pos,val);
        states[k].PB(upd);
    }
    void copy(int k)
    {
        node *copy = states[k].back();
        vector<node*> xx;
        xx.PB(copy);
        states.PB(xx);
    }
};

