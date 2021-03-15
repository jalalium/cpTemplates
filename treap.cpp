struct Treap{
    struct node{
        int val;
        int prio;
        int siz;
        struct node *l,*r;
    };
    string  str;
    int pp=0;
    int n;
    node *root;
    node* all;
    int sz(node* t)
    {
        return t?t->siz:0;
    }
    void upd_sz(node *t)
    {
        if(t)t->siz=sz(t->l)+1+sz(t->r);
    }
    Treap(){}
    Treap(string str)
    {
        srand(1337);
        this->str = str;
        this->n=str.L;
        all = (node*)malloc(sizeof(node)*600010);
        init();
    }
    node *initNode(int val)
    {
        node *xx = &all[pp++];
        xx->val=val;
        int f =rand();
        xx->prio =f;
        xx->siz=1;
        return xx;
    }
    void merge(node * &t,node *l,node *r)
    {
        if (!l||!r)t=l?l:r;
        else if (l->prio>r->prio)
        {
            merge(l->r,l->r,r);
            t=l;
        }
        else
        {
            merge(r->l,l,r->l);
            t=r;
        }
        upd_sz(t);
    }
    void split(node *t,node* &l,node* &r,int pos,int add=0)
    {
        if(!t)
            return void(l=r=NULL);
        int cur = add + sz(t->l);
        if(cur <=pos)
            split(t->r,t->r,r,pos,cur+1),l=t;
        else
            split(t->l,l,t->l,pos,add),r=t;
        upd_sz(t);
    }
    void init()
    {
        root = NULL;
        REP(i,0,n)
        {
            merge(root,root,initNode(str[i]-'A'));
        }
    }
    int range_query(node *t,int l,int r)
    {
        node *x,*y,*z;
        split(t,x,y,l-1);
        split(y,t,z,r-l);
        int ans = t->val;
        merge(y,x,t);
        merge(t,y,z);
        //free(x);
        //free(y);
        //free(z);
        return ans;
    }
    int query(int l,int r)
    {
        return range_query(root,l,r);
    }
    void upd(int l,int r,int pos)
    {
        node *x,*y,*z;
        split(root,x,z,l-1);
        split(z,y,z,r-l);
        merge(x,x,z);
        node *x2,*z2;
        split(x,x2,z2,pos);
        merge(root,x2,y);
        merge(root,root,z2);
    }
};

