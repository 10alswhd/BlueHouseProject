int main()
{
    trie mytrie;
    char *s[] = {"tree","trie","algo","assoc","all","also","ass"};
    for(int i=0;i<sizeof(s)/sizeof(*s);i++)
    {
        mytrie.insert_word(s[i]);
    }

    mytrie.display();

    if(mytrie.search_word("all") == true) cout << "all exist" << endl;
    else cout << "all do not exist" << endl;

    mytrie.delete_word("all");

    if(mytrie.search_word("all") == true) cout << "all exist" << endl;
    else cout << "all do not exist" << endl;

    mytrie.display();
}
