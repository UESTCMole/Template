struct node
{
  node* nxt[26];
  node* fail;
  int cnt;
}no[500005];
int tot,T;

node* build_node()
{
  node* tmp=no+tot;
  tot++;
  tmp->fail=NULL;
  tmp->cnt=0;
  for (int i=0;i<26;i++)
  {
    tmp->nxt[i]=NULL;
  }
  return tmp;
}

void add(node* now,char s[])
{
  int len=strlen(s);
  for (int i=0;i<len;i++)
  {
    if (now->nxt[s[i]-'a']==NULL)
    {
      now->nxt[s[i]-'a']=build_node();
    }
    now=now->nxt[s[i]-'a'];
  }
  now->cnt++;
}
