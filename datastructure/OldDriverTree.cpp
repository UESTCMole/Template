typedef long long LL;
struct ODT {
	struct node {
		int l, r;
		mutable LL v;
		node(int L, int R = -1, LL V=0) : l(L), r(R), v(V) {}
		bool operator < (const node& o) const {
			return l < o.l;
		}
	};

	set<node> s;
	vector< pair<LL, int> > vp;
	ODT(int n, LL x=0) {
		s.insert(node(1, n, x));
	}

	set<node>::iterator split(int pos) {
		auto it = s.lower_bound(node(pos));
		if (it != s.end() && it->l == pos) return it;
		--it;
		if (pos > it->r) return s.end();
		int L = it->l, R = it->r;
		LL V = it->v;
		s.erase(it);
		s.insert(node(L, pos - 1, V));
		return s.insert(node(pos, R, V)).first;
	}

	void add(int l, int r, LL val=1) {
		split(l);
		auto itr = split(r + 1), itl = split(l);
		for (; itl != itr; ++itl) itl->v += val;
	}

	void assign(int l, int r, LL val=0) {
		split(l);
		auto itr = split(r + 1), itl = split(l);
		s.erase(itl, itr);
		s.insert(node(l, r, val));
	}

	LL rank(int l, int r, int k, bool reversed=0) {
		if (reversed) k = r - l + 2 - k;
		split(l);
		auto itr = split(r + 1), itl = split(l);
		vp.clear();
		for (; itl != itr; ++itl)
			vp.push_back({itl->v, itl->r - itl->l + 1});
		sort(vp.begin(), vp.end());
		for (auto i : vp) {
			k -= i.second;
			if (k <= 0) return i.first;
		}
		return -1;
	}

	LL pow(LL x, int y, int mod) {
		x %= mod;
		LL res = 1;
		for (; y; y >>= 1, x = (x * x) % mod)
			if (y & 1) res = (res * x) % mod;
		return res;
	}

	LL sum(int l, int r, int ex, int mod) {
		split(l);
		auto itr = split(r + 1), itl = split(l);
		LL res = 0;
		for (; itl != itr; ++itl)
			res = (res + (LL)(itl->r - itl->l + 1) * pow(itl->v, ex, mod)) % mod;
		return res;
	}
};
