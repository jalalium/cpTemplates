class Matrix{
    int n,m;
    vector<vi> mat;
    public:
    Matrix(int n,int m, int type)
    {
        this->n=n;
        this->m=m;
        mat.assign(n,vi(m,0));
        if(type==1)
        {
            REP(i,0,n)
                mat[i][i]=1;
        }
        if(type==2)
        {
            REP(i,0,n)
                REP(j,i,m)
                mat[i][j]=1;
        }
        if (type == 3)
        {
            REP(j,0,m)
                mat[0][j]=1;
            REP(i,1,n)
                mat[i][i-1]=1;
        }
    }
    Matrix(vector<vi> inp)
    {
        this->n = inp.Z;
        this->m = inp[0].Z;
        mat = inp;
    }
    Matrix operator + (const Matrix &b)
    {
        class Matrix out = Matrix(this->n,this->m,0);
        REP(i,0,this->n)
            REP(j,0,this->m)
            out.mat[i][j] = (this->mat[i][j]+b.mat[i][j])%mod;
        return out;
    }
    Matrix operator - (const Matrix &b)
    {
        class Matrix out = Matrix(this->n,this->m,0);
        REP(i,0,this->n)
            REP(j,0,this->m)
            out.mat[i][j] = (this->mat[i][j]-b.mat[i][j]+mod)%mod;
        return out;
    }
    Matrix operator * (const Matrix &b)
    {
        class Matrix out = Matrix(this->n,b.m,0);
        REP(i,0,this->n)
            REP(j,0,b.m)
            REP(x,0,this->m)
            {
                out.mat[i][j] += (this->mat[i][x]*b.mat[x][j])%mod;
                out.mat[i][j] %=mod;
            }
        return out;
    }
    Matrix operator ^ (const int &p)
    {
        return matbin(*this,p);
    }
    Matrix matbin(Matrix a, int b)
    {
        if (b==0)
            return (Matrix(a.n,a.n,1));
        Matrix res = matbin(a,b/2);
        if (b%2)
            return res*res*a;
        else
            return res*res;
    }
    int get(int x,int y)
    {
        return this->mat[x][y];
    }
};

