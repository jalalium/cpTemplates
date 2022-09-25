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
      seg.resize(2*len);
      build(0,0,len-1);
    }
  void build(int id, int l, int r)
  {
    if (l==r)
    {
      seg[id] = all[l];
      return ;
    }
    int mid=(l+r)/2;
    build(id+1,l,mid);
    build(id + 2 * (mid - l +1),mid+1,r);
    seg[id] = seg[id + 1] + seg[id + 2 * (mid - l +1)];
  }
  ll query(int id, int l, int r, int sl, int sr)
  {
    if (r < sl || sr < l)
      return 0;
    if (sl <= l && sr >= r)
      return seg[id];
    int mid = (l+r)/2;
    return query(id + 1,l,mid,sl,sr)+ query(id+2 * (mid-l+1),mid+1,r,sl,sr);
  }
  ll query(int l,int r)
  {
      return query(0,0,len-1,l,r);
  }
  void update(int idx, int l, int r, int pos, int val)
  {
	  if (!(pos >= l && pos <= r))
		  return;
	  if (pos == l && pos == r)
	  {
		  seg[idx] = val;
		  return;
	  }
	  int mid = (l + r) / 2;
	  update(idx + 1, l, mid, pos, val);
	  update(idx + 2 * (mid-l+1), mid + 1, r, pos, val);
	  seg[idx] = seg[idx + 1] + seg[idx + 2 * (mid-l+1)];
  }
  void update(int pos, int val)
  {
	  update(0, 0, len - 1, pos, val);
  }
};
