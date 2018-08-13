#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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

void build_ac_machine(node* root)
{
  queue<node*> q;
  q.push(root);
  while (!q.empty())
  {
    node* u=q.front();q.pop();
    for (int i=0;i<26;i++)
    {
      if (u->nxt[i]==NULL)continue;
      if (u!=root)
      {
        node* tmp;
        tmp=u->fail;
        while (tmp!=NULL&&tmp->nxt[i]==NULL)tmp=tmp->fail;
        if (tmp!=NULL)u->nxt[i]->fail=tmp->nxt[i];
        else u->nxt[i]->fail=root;
      }
      else u->nxt[i]->fail=root;
      u->nxt[i]->cnt += u->nxt[i]->fail->cnt;
      q.push(u->nxt[i]);
    }
  }
}

int query(node* root, char s[])
{
  int ans=0;
  node* u=root;
  int len=strlen(s);
  for (int i=0;i<len;i++)
  {
    while (u!=root&&u->nxt[s[i]-'a']==NULL)u=u->fail;
    if (u->nxt[s[i]-'a']!=NULL)u=u->nxt[s[i]-'a'];
    ans+=u->cnt;
  }
  return ans;
}

char s[1000005];
char keyword[55];

int main()
{
  scanf("%d",&T);
  while (T--)
  {
    int n;tot=0;
    scanf("%s",s);scanf("%d",&n);
    node* root=build_node();
    for (int i=0;i<n;i++)
    {
      scanf("%s",keyword);
      add(root,keyword);
    }
    //printf("1\n");
    build_ac_machine(root);
    //printf("2\n");
    printf("%d\n",query(root,s));
  }
}
