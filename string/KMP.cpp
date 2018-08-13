char s[max_l],t[max_l];
int f[max_l];

void getfail()
{
  int ls=strlen(s),lt=strlen(t);
  int i,j;
  f[0]=j=-1;
  for (i=1;i<ls;i++)
  {
    while (j>=0&&s[j+1]!=s[i])j=f[j];
    if (s[j+1]==s[i])j++;
    f[i]=j;
  }
}

int kmp()
{
  int i,j;
  int cnt=0;
  j=-1;
  for (i=0;i<lt;i++)
  {
    while (j>=0&&s[j+1]!=t[i])j=f[j];
    if (s[j+1]==t[i]) j++;
    if (j==ls-1)
    {
      cnt++;
      j=f[j];
    }
  }
  return cnt;
}
