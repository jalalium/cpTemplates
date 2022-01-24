int girth(vector<vi> &adj)
{
    int n = adj.Z;
    int ans = 1e18;
    REP(i,0,n)
    {
        vi vis(n,0);
        vi dep(n);
        vi par(n);
        queue<int> kyou;
        kyou.push(i);
        dep[i] = 0;
        vis[i] = 1;
        par[i] = -1;
        while(kyou.Z)
        {
            int frt = kyou.front();
            kyou.pop();
            for(int z : adj[frt])
            {
                if (z != par[frt])
                {
                    if (vis[z])
                    {
                        ans = min(ans,dep[frt]+dep[z]+1);
                    }
                    else
                    {
                        par[z] = frt;
                        dep[z] = dep[frt]+1;
                        vis[z] = 1;
                        kyou.push(z);
                    }
                }
            }
        }
    }
    return ans;
}
