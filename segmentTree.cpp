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

