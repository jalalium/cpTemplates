class SparseTable{
	vector<vll> sparse;
	int n;
	vi input;
	private: int lg2(int x){
		int out = 0;
		while((1 << out) <= x)
			out++;
		return out-1;
	}
	public: int rmaxpos(int left, int right){
		int len = right-left+1;
		int lg = lg2(len);
		return (input[sparse[left][lg]] > input[sparse[left+len-(1 << lg) ][lg]]? sparse[left][lg]:sparse[left+len-(1 << lg)][lg]);
	}
	public: int rmaxval(int left, int right){
		int len = right-left+1;
		int lg = lg2(len);
		return (input[sparse[left][lg]] > input[sparse[left+len-(1 << lg) ][lg]]? input[sparse[left][lg]]:input[sparse[left+len-(1 << lg)][lg]]);
	}
	public: int rminpos(int left, int right){
		int len = right-left+1;
		int lg = lg2(len);
		return (input[sparse[left][lg]] < input[sparse[left+len-(1 << lg) ][lg]]? sparse[left][lg]:sparse[left+len-(1 << lg)][lg]);
	}
	public: int rminval(int left, int right){
		int len = right-left+1;
		int lg = lg2(len);
		return (input[sparse[left][lg]] < input[sparse[left+len-(1 << lg) ][lg]]? input[sparse[left][lg]]:input[sparse[left+len-(1 << lg)][lg]]);
	}
	public: ll rsum(int left, int right){
		ll ans = 0;
		int pos;
		while (left <= right)
		{
			for(int i = 19; i>=0; i--)
				if ((1 << i) <= right-left+1)
				{
					pos = i;
					break;
				}
		ans += sparse[left][pos];
		left = left + (1<<pos);
		}
		return ans;
	}
	public: SparseTable(vi inp, string operation){
		input= inp;
		n=inp.Z;
		if (operation == "min")
			prepromin();   
		else if (operation == "max")
			prepromax();
		else if (operation == "sum")
			preprosum();
	}
	private: void prepromin(){
		sparse.resize(n);
		int x = lg2(n)+1;
		REP(i,0,n)
			sparse[i].resize(x);
		REP(i,0,n)
			sparse[i][0]=i;
		REP(j,1,x)
			for(int i = 0; i + (1 << (j))-1 < n; i++)
				sparse[i][j] = (input[sparse[i][j-1]] < input[sparse[i+(1<<(j-1))][j-1]] ? sparse[i][j-1] : sparse[i+(1<<(j-1))][j-1]); //min
	}
	void prepromax(){
		sparse.resize(n);
		int x = lg2(n)+1;
		REP(i,0,n)
			sparse[i].resize(x);
		REP(i,0,n)
			sparse[i][0]=i;
		REP(j,1,x)
			for(int i = 0; i + (1 << (j))-1 < n; i++)
				sparse[i][j] = (input[sparse[i][j-1]] > input[sparse[i+(1<<(j-1))][j-1]] ? sparse[i][j-1] : sparse[i+(1<<(j-1))][j-1]); //min
	}
	void preprosum(){
		sparse.resize(n);
		int x = lg2(n)+1;
		REP(i,0,n)
			sparse[i].resize(x);
		REP(i,0,n)
			sparse[i][0]=input[i];
		REP(j,1,x)
			for(int i = 0; i + (1 << (j))-1 < n; i++)
				sparse[i][j] = sparse[i][j-1]+sparse[i+(1<<(j-1))][j-1];
	}
};

