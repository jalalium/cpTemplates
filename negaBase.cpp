vi negaBase(int got,int base)
{
    vi out;
    int num=got;
    while(num)
    {
        int i = num%base;
        num/=base;
        if(i<0)
        {
            i+=abs(base);
            num++;
        }       
        out.PB(i);
    }
   // reverse(out.B,out.E);
    return out;
}

