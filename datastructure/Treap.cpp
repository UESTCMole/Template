class Treap
{
	#define MAXN 300010
	public:
	int tot;
	int root;
	int ls[MAXN],rs[MAXN],fa[MAXN],priority[MAXN],size[MAXN],num[MAXN];
	T val[MAXN];
	Treap()
	{
		//srand(time(0));
		tot=2;root=1;
		val[1]=inf+1;
		val[2]=-inf-1;
		ls[1]=2;fa[2]=1;
		size[1]=2;size[2]=1;
		priority[1]=priority[2]=inf+1;
		num[1]=num[2]=1;
	}
	int newnode()
	{
		++tot;
		priority[tot]=rand();
		size[tot]=1;
		num[tot]=1;
		return tot;
	}
	int begin(){return 2;}
	int end(){return 1;}
	int next(int now)
	{
		if(rs[now]!=0)
		{
			int x=rs[now];
			while(ls[x]!=0)x=ls[x];
			return x;
		}
		while(rs[fa[now]]==now)now=fa[now];
		return fa[now];
	}
	int prev(int now)
	{
		if(ls[now]!=0)
		{
			int x=ls[now];
			while(rs[x]!=0)x=rs[x];
			return x;
		}
		while(ls[fa[now]]==now)now=fa[now];
		return fa[now];
	}
	void _dfs(int now)
	{
		if(ls[now]!=0)_dfs(ls[now]);
		cout<<val[now]<<endl;
		if(rs[now]!=0)_dfs(rs[now]);
	}
	void update(int now)
	{
		size[now]=size[ls[now]]+size[rs[now]]+num[now];
	}
	void left_rotate(int now)
	{
		if(now==root)return;
		int f=fa[now],ff=fa[fa[now]],b=ls[now];
		if(f==root)
		{
			root=now;
			ls[now]=f;fa[f]=now;rs[f]=b;
			if(b!=0)fa[b]=f;
		}
		else
		{
			fa[now]=ff;if(ls[ff]==f)ls[ff]=now;else rs[ff]=now;
			ls[now]=f;fa[f]=now;rs[f]=b;
			if(b!=0)fa[b]=f;
		}
		update(f),update(now);
	}
	void right_rotate(int now)
	{
		if(now==root)return;
		int f=fa[now],ff=fa[fa[now]],b=rs[now];
		if(f==root)
		{
			root=now;
			rs[now]=f;fa[f]=now;ls[f]=b;
			if(b!=0)fa[b]=f;
		}
		else
		{
			fa[now]=ff;if(ls[ff]==f)ls[ff]=now;else rs[ff]=now;
			rs[now]=f;fa[f]=now;ls[f]=b;
			if(b!=0)fa[b]=f;
		}
		update(f),update(now);
	}
	void _insert(int now,T x)
	{
		if(x==val[now])
		{
			num[now]++;
			update(now);
			return;
		}
		if(x<val[now])
		{
			if(ls[now]!=0)_insert(ls[now],x);
			else
			{
				ls[now]=newnode();
				fa[tot]=now;
				val[tot]=x;
			}
			if(priority[now]>priority[ls[now]])right_rotate(ls[now]);
		}
		else
		{
			if(rs[now]!=0)_insert(rs[now],x);
			else
			{
				rs[now]=newnode();
				fa[tot]=now;
				val[tot]=x;
			}
			if(priority[now]>priority[rs[now]])left_rotate(rs[now]);
		}
		update(now);
	}
	void down(int now)
	{
		while(ls[now]!=0 || rs[now]!=0)
		{
			if(ls[now]==0)left_rotate(rs[now]);
			else if(rs[now]==0)right_rotate(ls[now]);
			else
			{
				if(priority[ls[now]]<priority[rs[now]])right_rotate(ls[now]);
				else left_rotate(rs[now]);
			}
		}
		int f=fa[now];
		if(ls[f]==now)ls[f]=0;
		if(rs[f]==now)rs[f]=0;
		while(f!=root)update(f),f=fa[f];
	}
	void _erase(int now,T x)
	{
		if(now==0)return;
		if(val[now]==x)
		{
			num[now]--;
			if(num[now]==0)down(now);
			else update(now);
			return;
		}
		if(x<val[now])_erase(ls[now],x);
		else _erase(rs[now],x);
		update(now);
	}
	T _findkth(int now,int kth)
	{
		if(size[ls[now]]>=kth)return _findkth(ls[now],kth);
		int s=kth-size[ls[now]]-num[now];
		if(s<=0)return val[now];
		return _findkth(rs[now],s);
	}
	int _calc(int now,T x)
	{
		if(now==0)return 0;
		if(x<val[now])return _calc(ls[now],x);
		if(x==val[now])return size[ls[now]];
		return  _calc(rs[now],x)+size[ls[now]]+num[now];
	}
	int _find(int now,T x)
	{
		if(now==0)return -1;
		if(x<val[now])
		{
			int ret=_find(ls[now],x);
			if(ret==-1)return prev(now);
			return ret;
		}
		if(x==val[now])return now;
		if(x>val[now])
		{
			int ret=_find(rs[now],x);
			if(ret==-1)return now;
			return ret;
		}
	}
	void insert(T x)//加数
	{
		_insert(root,x);
	}
	void erase(T x)//删数
	{
		_erase(root,x);
	}
	T findkth(int x)//查找第 k大
	{
		if(x<=0)return -1;
		if(x>size[root]-2)return -1;
		return _findkth(root,x+1);
	}

	int calc(T x)//查询有多少数小于x
	{
		return _calc(root,x)-1;
	}
	T findmin(T x)//查找x的前驱，没有返回-1
	{
		int s=_find(root,x);
		if(val[s]==x)s=prev(s);
		if(val[s]<=-inf)return -1;
		return val[s];
	}
	T findmax(T x)//查找x的后继，没有返回-1
	{
		int s=_find(root,x);
		if(val[s]<=x)s=next(s);
		if(val[s]>=inf)return -1;
		return val[s];
	}
	int find(T x)//返回一个小于等于x且最大的下标
	{
		return _find(root,x);
	}
	void sort()
	{
		_dfs(root);
	}
	int Size()
	{
		return size[root]-2;
	}
};
Treap<int>treap;
