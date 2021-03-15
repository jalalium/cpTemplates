class Node{
    public:
        Node *children[26];
    public:
        int cnt = 0;
    public:
        char t;
    public:
        Node(int alphabet, char c)
        {
            REP(i,0,alphabet)
                this->children[i] = NULL;
            t = c;
        }
};
class Trie{
    Node *root;
    int alphabet;
    char start;
    public:
    Trie(int alphabet, char start)
    {
        this->alphabet = alphabet;
        root = new Node(alphabet,'*');
        this->start = start;
    }
    public:
    void insert(string str)
    {
        Node *cur = root;
        REP(i,0,str.L)
        {
            if (cur->children[str[i]-start] == NULL)
            {
                cur->children[str[i]-start] = new Node(alphabet,str[i]);
            }
            cur = cur->children[str[i]-start];
        }
        cur->cnt++;
    }
    public:
    bool exists(string str)
    {
        Node *cur = root;
        REP(i,0,str.L)
        {
            if (cur->children[str[i]-start] == NULL)
                return false;
            cur = cur->children[str[i]-start];
        }
        return (cur->cnt > 0);
    }
    public:
    int count(string str)
    {
        Node *cur = root;
        REP(i,0,str.L)
        {
            if (cur->children[str[i]-start] == NULL)
                return 0;
            cur = cur->children[str[i]-start];
        }
        return (cur->cnt);
    }
    public:
    void erase(string str)
    {
        Node *cur = root;
        REP(i,0,str.L)
        {
            if (cur->children[str[i]-start] == NULL)
                cur->children[str[i]-start] = new Node(alphabet,str[i]);
            cur = cur->children[str[i]-start];
        }
        cur->cnt--;
    }
};

