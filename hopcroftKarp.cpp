class HopcroftKarp{
  vi matched;
  vector<vpi> adj;
  int left;
  int right;
  public:
  HopcroftKarp(vector<vpi> inp,int l, int r)
  {
    adj = inp;
    left = l;
    matched.resize(l);
    REP(i,0,l)
      matched[i] = -1;
    right = r;
  }
  public:
  vi match()
  {
    bool cont = true;
    set<int> lfree,rfree;
    REP(i,0,left)
      lfree.insert(i);
    REP(i,left,left+right)
      rfree.insert(i);
    vector<bool> yet(left,0);
    REP(i,0,left)
      REP(j,0,adj[i].Z)
      if (adj[i][j].S==1 && rfree.count(adj[i][j].F)&& !yet[i])
      {
        yet[i]=true;
        matched[i] = adj[i][j].F;
        adj[i][j].S = 2;
        REP(x,0,adj[adj[i][j].F].Z)
          if (adj[adj[i][j].F][x].F == i)
            adj[adj[i][j].F][x].S = 2;
        rfree.erase(adj[i][j].F);
        lfree.erase(i);
      }
    while(cont)
    {
      vi par(left+right,-1);
      queue<pi> kyou;
      for (int z : lfree)
        kyou.push(MP(z,0));
      int update = -1;
      vi vis(left+right,0);
      while(kyou.Z)
      {
        pi frt = kyou.front();
        kyou.pop();
        if (rfree.count(frt.F))
        {
          update = frt.F;
          break;
        }
        if (frt.S == 0)
        {
          for (pi z : adj[frt.F])
          {
            if (z.S == 1 && !vis[z.F])
            {
              par[z.F]=frt.F;
              vis[z.F] = 1;
              kyou.push(MP(z.F,1));
            }
          }
        }
        else
        {
          for (pi z : adj[frt.F])
          {
            if (z.S == 2 && !vis[z.F])
            {
              par[z.F]=frt.F;
              vis[z.F] = 1;
              kyou.push(MP(z.F,0));
            }
          } 
        }
      }  
      int x = update;
      int cnt = 0;
      while (x != -1 && par[x] != -1)
      {
        REP(i,0,adj[x].Z)
          if (adj[x][i].F == par[x])
          {
            adj[x][i].S = (cnt==0?2:1); 
            if (cnt==0)
            {
              matched[par[x]]=x;
              rfree.erase(x);
              lfree.erase(par[x]);
            }
          }
        REP(i,0,adj[par[x]].Z)
          if (adj[par[x]][i].F == x)
            adj[par[x]][i].S = (cnt==0?2:1); 
        cnt++;
        cnt%=2;
        x=par[x];
      }
      if (update == -1)
        cont = false;
    }
    return matched;
  }
};


