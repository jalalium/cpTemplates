class PruferCode{
  vi code;
  vpi edges;
  public:
    PruferCode(vi cc){
      code =cc;
      findEdges();
    }
  private:
    void findEdges(){
      map<int,int> mp;
      set<int> has;
      set<int> wait;
      for (int z: code){
        mp[z]++;
        has.insert(z);
      }
      REP(i,0,code.Z+2)
        if (!has.count(i))
          wait.insert(i);
      REP(i,0,code.Z)
      {
        int now = *wait.B;
        edges.PB(MP(now,code[i]));
        mp[now]++;
        mp[code[i]]--;
        if (mp[code[i]]==0)
        {
          has.erase(code[i]);
          wait.insert(code[i]);
        }
        wait.erase(now);
      }
      assert(wait.Z ==2);
      edges.PB(MP(*wait.B,*wait.RB));
    }
  public:
    vpi getEdges()
    {
      return edges;
    }
};
c
