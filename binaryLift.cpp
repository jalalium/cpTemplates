class BinaryLift{
	vector<vi> binlift;
	int n;
	public:
		BinaryLift(vi rnk, vi par){
			n = (int)par.Z;
			binlift.resize(n);
			REP(i,0,n)
				binlift[i].resize(20);
			REP(i,0,n)
				binlift[i][0] = par[i];
			REP(j,1,20)
				REP(i,0,n)
				{
					if ((1 <<j) <rnk[i])
						binlift[i][j]=binlift[binlift[i][j-1]][j-1];
					else
						binlift[i][j]=-1;
				}
		}
	public:
		int get_kth_ancestor(int x, int k)
		{
			int pt = x;
			for (int i = 19; i >= 0; i--)
			{
				if (pt==-1)
					exit(0);
				if (k&(1<<i))
					pt=binlift[pt][i];
			}
			return pt;
		}
	public:
		int get_th_ancestor(int x, int k)
		{
			int pt = x;
			for (int i = 19; i >= 0; i--)
			{
				if (k&(1<<i))
					pt=binlift[pt][i];
			}
			return pt;
		}
};
c
