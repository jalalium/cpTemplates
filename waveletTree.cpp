class WaveletTree{
    typedef vector<int>::iterator it;
    vector<vi> pre;
    int mx;
    public:
    WaveletTree(vi &inp, int delta)
    {
        pre.resize(4*inp.Z);
        mx = delta+1;
        build(inp.B,inp.E,0,mx-1,1);
    }
    void build(it b, it e, int l, int r, int d)
    {
        if (l == r)
            return;
        int mid = (l+r)/2;
        pre[d].PB(0);
        for (it x = b; x != e; x++)
            pre[d].PB(pre[d].back()+(*x<=mid));
        it p = stable_partition(b,e,[=](int i){return i <= mid;});
        build(b,p,l,mid,2*d);
        build(p,e,mid+1,r,2*d+1);
    }
    int occurrenceOf(int c, int i)
    {
        i++;
        int l = 0;
        int r = mx-1;
        int d = 1;
        int mid;
        int shift;
        while(l != r)
        {
            int mid = (l+r)/2;
            shift = pre[d][i];
            d*=2;
            if (c <= mid)
            {
                i = shift;
                r= mid;
            }
            else
            {
                i -= shift;
                l = mid+1;
                d++;
            }
        }
        return i;
    }
    int kthSmallest(int k, int i, int j)
    {
        j++;
        int l = 0,r=mx-1,d=1,ri,rj;
        while(l!= r)
        {
            int mid = (l+r)/2;
            ri = pre[d][i];
            rj = pre[d][j];
            d *= 2;
            if (k <= rj-ri)
            {
                i = ri;
                j = rj;
                r = mid;
            }
            else
            {
                k -= rj-ri;
                i -= ri;
                j -= rj;
                l = mid+1;
                d++;
            }
        }
        return r;
    }
    int rectangle(int i, int j, int a, int b, int d=1){
        if (b < a || j < i)
            return 0;
        int l = a, r = b;
        if (b < l || a > r)
            return 0;
        if (l <= a & r >= b)
            return j-i;
        int mid = (a+b)/2, ri=pre[d][i], rj= pre[d][j];
        return rectangle(ri,rj,a,mid,d*2)+rectangle(i-ri,j-rj,mid+1,b,2*d+1);
    }
};

