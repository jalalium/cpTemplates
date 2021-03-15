class SuffixArray{
  vi order;
  vi lcp;
  string str;
  SegmentTree seg;
  public:
  SuffixArray(string in)
  {
    str = in;
    str += '$';
    order.resize(str.L);
    lcp.resize(str.L);
    compute();
    seg = SegmentTree(order);
  }
  void compute()
  {
    vector<pair<char,int> > a;
    vi equi(order.Z);
    vi bij(order.Z);
    REP(i,0,str.L)
      a.PB(MP(str[i],i));
    sort(a.B,a.E);
    REP(i,0,str.L)
      order[i] = a[i].S;
    equi[order[0]]=0;
    int r = 0;
    REP(i,1,str.L)
    {
      if (a[i].F == a[i-1].F)
        equi[order[i]] = r;
      else
        equi[order[i]] = ++r;
    }
    int k = 0;
    while((1<<k) <str.L)
    {
      vector<pair<pi,int> > a(str.L);
      REP(i,0,str.L)
        a[i] = MP(MP(equi[i],equi[(i+(1<<k))%(str.L)]),i);
      sort(a.B,a.E);
      REP(i,0,str.L)
      {
        order[i] = a[i].S;
        bij[order[i]]=i;
      }
      int r = 0;
      equi[order[0]]=0;
      REP(i,1,str.L)
      {
        if (a[i].F == a[i-1].F)
          equi[order[i]]=r;
        else
          equi[order[i]]=++r;
      }
      k++;
    }
    k = 0;
    REP(i,0,str.L-1)
    {
      int p = bij[i];
      int j = order[p-1];
      while(i+k < str.L && j+k <str.L  && str[i+k]==str[j+k])k++;
      lcp[p] = k;
      k = max(k-1,0LL);
    }
  }
  public:
  int count(string ptr)
  {
    int low = 0;
    int hi = str.L-1;
    int res1,res2;
    res1 = 0;
    res2 = 1e9;
    while(low <= hi)
    {
      int mid=(low+hi)/2;
      bool gr = false;
      int i = 0;
      for( i ; i< min((ll)ptr.L,(ll)str.L-order[mid]); i++)
      {
        if (ptr[i] != str[order[mid]+i])
        {
          if (ptr[i] > str[order[mid]+i])
            gr = true;
          break;
        }
      }
      if (i == ptr.L)
      {
        res2=min(res2,mid);
        hi=mid-1;
      }
      else if (!gr)
        hi=mid-1;
      else
        low = mid+1;
    }
    low = 0;
    hi=str.L-1;
    while(low <= hi)
    {
      int mid=(low+hi)/2;
      bool gr = false;
      int i = 0;
      for( i ; i< min((ll)ptr.L,(ll)str.L-order[mid]+1); i++)
      {
        if (ptr[i] != str[order[mid]+i])
        {
          if (ptr[i] > str[order[mid]+i])
            gr = true;
          break;
        }
      }
      if (i == ptr.L)
      {
        res1=max(res1,mid);
        low=mid+1;
      }
      else if (!gr)
        hi=mid-1;
      else
        low = mid+1;
    }
    trace(res2);
    if (res2 == 1e9)
      return -2;
    return (seg.query(res2,res1));
  }
  pi getPosAndLength()
  {
      int res = 0;
      int pos = -1;
      REP(i,1,str.L)
      {
          int low = 0;
          int hi = str.L-1-max(order[i],order[i-1]);
          while(low<=hi)
          {
              int mid = (low+hi)/2;
              bool ok =false;
              int pp;
              if (str.substr(order[i],mid)==str.substr(order[i-1],mid))
              {
                  ok=true;
                  pp = order[i];
              }
              if (ok)
              {
                  if (mid > res)
                  {
                      res = max(res,mid);
                      pos = pp;
                  }        
                  low=mid+1;
              }
              else
                  hi=mid-1;
          }

      }
      return MP(res,pos);
  }
  string longestRepeating()
  {
      pi ans = getPosAndLength();
      if (ans.F==0)
          return "";
      return str.substr(ans.S,ans.F);
  }
  vi get(){
      return order;
  }
  public:
  vi getLcp(){
      return lcp;
  }
  public:
  ll diffSubstrings()
  {
      ll out = 0;
      REP(i,1,str.L)
          out += str.L - order[i] - lcp[i]-1;
      return out;
  }
};
string longestCommonSubstring(string a, string b)
{
    int len = 0;
    string res = a+'%'+b;
    SuffixArray sf = SuffixArray(res);
    vi order = sf.get();
    vi lcp = sf.getLcp();
    vi col(order.Z);
    REP(i,0,order.Z)
    {
        if (order[i] < a.L)
            col[order[i]] = 1;
        else if (order[i] > a.L)
            col[order[i]] = 2;
    }
    int pos = -1;
    REP(i,1,order.Z)
        if (col[order[i]]+col[order[i-1]] == 3)
        {
            if (lcp[i] > len)
            {
                len = max(len,lcp[i]);
                pos = (col[order[i]] == 1?order[i]:order[i-1]);
            }
        }
    return a.substr(pos,len);
}

