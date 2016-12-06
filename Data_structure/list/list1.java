public class List
{
    public static final List EMPTY_LIST = new List();
    
    public List(int n, List rest)
    {
        this.n = n;
        this.rest = rest;
    }

    public boolean isEmpty() { return this == EMPTY_LIST; }
    
    public int head() { return n; }
    
    public List tail() { return rest; }
    
    public List cons(int n) { return new List(n, this); }
    
    public List reverse()
    {
        List list = this;
        List reversed = EMPTY_LIST;
        while(!list.isEmpty())
        {
            reversed = new List(list.head(), reversed);
            list = list.tail();
        }
        return reversed;
    }   

    private List rest;
    private int n;

    private List() {}
}
