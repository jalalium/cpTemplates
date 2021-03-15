class Factorial{
    int nax;
    vll fa;
    vll in;
    public:
    Factorial(int n)
    {
        nax = n+10;
        fa.assign(nax,1);
        in.resize(nax);
        REP(i,1,nax)
            fa[i] = (fa[i-1]*i)%mod;
        REP(i,0,nax)
            in[i] = mbinp(fa[i],mod-2);
    }
    public:
    ll fac(int x)
    {
        return fa[x];
    }
    public:
    ll inv(int x)
    {
        return in[x];
    }
    public:
    ll comb(int x, int y)
    {
        if (x < y || x < 0 || y < 0)
            return 0;
        return (((fa[x]*in[y])%mod)*in[x-y])%mod;
    }
};

