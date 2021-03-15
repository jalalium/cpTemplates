vi kmp(string str)
{
    vi out;
    out.assign(str.L,0);
    int i = 1;
    int pos = 0;
    while(i < str.L)
    {
        if (str[i]==str[pos])
        {
            pos++;
            out[i]=pos;
            i++;
        }
        else
        {
            if (pos !=0)
            {
                pos = out[pos-1];
            }
            else
            {
                out[i] = 0;
                i++;
            }
        }
    }
    return out;
}

