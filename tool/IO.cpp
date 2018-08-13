ll read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void read(int &v) {
    v=0;char c=0;int p=1;
    while (c<'0' || c>'9'){if(c=='-')p=-1;c=getchar();}
    while (c>='0' && c<='9'){v=(v<<3)+(v<<1)+c-'0';c=getchar();}
    v*=p;
}