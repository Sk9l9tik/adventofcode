#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>

using ll = long long;
using db = long double;
using str = std::string; 

using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;
using pd = std::pair<db, db>;
#define pb std::push_back
#define mp std::make_pair
#define fi first
#define se second
#define X first
#define Y second

template <class T> using V = std::vector<T>;
template <class T, size_t SZ> using AR = std::array<T, SZ>;
using vi = V<int>;
using vvi = V<vi>;
using vb = V<bool>;
using vvb = V<vb>;
using vll = V<ll>;
using vvll = V<vll>;
using vd = V<db>;
using vs = V<str>;
using vvs = V<vs>;
using vpii = V<pii>;
using vpll = V<pll>;
using vpd = V<pd>;

template <class T> using pair2 = std::pair<T, T>;

template <class T> int isz(const T &a) { return a.size(); }

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define bg(x) x.begin()

template <class T> int lwb(V<T> &a, const T &b) {
  return int(std::lower_bound(all(a), b) - bg(a));
}
template <class T> int upb(V<T> &a, const T &b) {
  return int(std::upper_bound(all(a), b) - bg(a));
}
 
template <class T> using pqg = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <class T> using pql = std::priority_queue<T, std::vector<T>, std::less<T>>;

const int MOD = 998244353;
const int MX = 2e5 + 5;
const ll BIG = 1e18; 
const db PI = acos((db)-1);
const int dx[4]{0, 1, 0, -1}, dy[4]{-1, 0, 1, 0}; // u r d l
const int dy8[8] = {-1,-1, 0, 1, 1, 1, 0,-1}, dx8[8] = { 0,  1, 1, 1, 0,-1,-1,-1}; // u r d l
std::mt19937 rng((uint32_t)std::chrono::steady_clock::now().time_since_epoch().count());

template <class T> bool min(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T> bool max(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}
template <class T, class U> bool min(T &a, const U &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T, class U> bool max(T &a, const U &b) {
  return a < b ? a = b, 1 : 0;
}

struct custom_int_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
 
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
      std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
} hasher;

// DSU
struct DSU{
	std::vector<int> sz, par;
	
	DSU(int n) : sz(n+1, 1), par(n + 1){
		for(int i = 1; i <= n; ++i)
			par[i] = i;
	}
	
	bool is_connected(int u, int v){
		return get_par(u) == get_par(v);
    }
	
	int get_par(int u) {
		//return (u == par[u] ? u : get_par(par[u]));
		
		//эвристика сжатия путей
		return (u == par[u] ? u : par[u] = get_par(par[u])); 
	}
		
	bool connect(int u, int v){
		u = get_par(u), v = get_par(v);
		if (u == v) return false;
		//ранговая эвристика
        if (sz[u] < sz[v]) std::swap(u, v);
		//присоединение v к u
		sz[u] += sz[v];
		par[v] = u;
		return true;
	}
};


// DSURollback
struct DSURollback{
	std::vector<int> sz, par;
	//        ptr куда писать, значение куда писать
	std::vector<std::pair<int*, int>> history;
	
	DSURollback(int n) : sz(n+1), par(n + 1){
		for(int i = 1; i <= n; ++i){
			par[i] = i;
		}
	}
	
	bool is_connected(int u, int v) const{
		return get_par(u) == get_par(v);
	}
	
	int get_par(int u) const {
		return (u == par[u] ? u : get_par(par[u]));
	}
	
	void add_to_history(int* ptr){
		history.emplace_back(ptr, *ptr);
	}
	
	void roll_back(int version){
		while(history.size() > version){
			auto [ptr, val] = history.back();
			history.pop_back();
			*ptr = val;	
		}
	}
	
	int get_version() const{
		return (int)history.size();
	}
	
	bool connect(int u, int v){
		u = get_par(u), v = get_par(v);
		if (u == v) return false;
		if (sz[u] < sz[v]) std::swap(u, v);
		//заполнить изменненые значения
		add_to_history(&sz[u]);
		add_to_history(&par[v]);
		
		//присоединение v к u
		sz[u] += sz[v];
		par[v] = u;
		return true;
	}
};


//fenwick
struct Fenwick {
    int n;
    std::vector<int> f;

    Fenwick(int n) : n(n), f(n + 1, 0) {}

    void add(int i, int v) {
        for (; i <= n; i += i & -i)
			f[i] += v;
			//if we have mod
            //f[i] = ([i] + v) % mod;
    }

    void add_range(int l, int r, int v) {
        add(l, v);
        //if (r + 1 <= n) add(r + 1, (mod - v) % mod);
        if (r + 1 <= n) add(r + 1, -v);
    }

    int get(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i)
			res += f[i];
            //res = (res + f[i]) % mod;
        return res;
    }
};


// Feinwick min in 1-indexed
struct FenwickMin {
    std::vector<int> bit;
    int n;
    const int INF = (int)1e9;

    FenwickMin(int n) : n(n), bit(n, INF) {}

    FenwickMin(std::vector<int> a) : FenwickMin(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int getmin(int r) {
        int ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    void add(int idx, int val) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = min(bit[idx], val);
    }
};

// int n = 1e5; // кол-во узлов
// std::vector<std::vector<int>>& adj(n + 1); // используется 1-индексация
// std::vector<bool> visited(n + 1); // тут будем отмечать посещенные вершины
std::vector<std::vector<int>> dfs(int v, std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    visited[v] = true;
    for (int u : adj[v])
        if (!visited[u])
            dfs(u, adj, visited); 
    return adj;
}


std::vector<std::vector<int>> bfs(std::vector<std::vector<int>>& g, int cnt, int start){
    std::queue<int> q;
    std::vector<int> dist(cnt), from(cnt);
    q.push(start);
    from[start] = -1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to: g[v]) {
            if (dist[to] >= dist[v] + 1){
                q.push(to);
                dist[to] = dist[v] + 1;
                from[to] = v;
            }
        }
    }
    return g;
}


//powmod
int binpow(int a, int n){
    int r = 1;
    while(n){
        if (n & 1) r = r * r % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return r;
}

// END TEMPLATE


void part1(){
    str s;
    vs lines;

    while(std::getline(std::cin, s)){
        lines.emplace_back(s);
    }
    
    lines.pop_back();
    str opsline = lines.back();
    lines.pop_back();
    

    vs operations;
    std::stringstream ss(opsline);
    while(ss >> s) {
        operations.push_back(s);
    }

    vvll numbers(isz(operations));

    for(const auto& st : lines){
        std::stringstream sss(st);
        int cnt = 0;
        while(sss >> s && cnt < isz(operations)) {
            numbers[cnt].push_back(std::stoll(s));
            cnt++;
        }
    }


    ll ans{}; 
    
    for(int i = 0, e = isz(operations); i < e; i++) {
        if(numbers[i].empty()) continue;
        
        char op = operations[i][0];
        ll result = numbers[i][0];
        
        for(size_t j = 1; j < numbers[i].size(); j++) {
            if(op == '*') {
                result *= numbers[i][j];
            } else if(op == '+') {
                result += numbers[i][j];
            }
        }
        
        ans += result;
    }
    std::cout << ans << '\n';
}

void part2(){
    str s;
    vs lines;

    while(std::getline(std::cin, s)){
        lines.emplace_back(s);
    }
    
    lines.pop_back();
    str opsline = lines.back();
    lines.pop_back();
    

    vs operations;
    std::stringstream ss(opsline);
    while(ss >> s) {
        operations.push_back(s);
    }


    vvs snumbers(isz(operations));
    
    for(const auto& st : lines) {
        std::stringstream sss(st);
        int cnt = 0;
        while(sss >> s && cnt < isz(operations)) {
            snumbers[cnt].push_back(s);
            cnt++;
        }
    }

    vvll numbers;


    for(int col = 0; col < isz(operations); ++col){
        int maxlen = 0;
        for(const auto& num_str : snumbers[col]) {
            if(num_str.length() > maxlen) {
                maxlen = num_str.length();
            }
        }

        std::cout << 1 << '\n';

        vs aligned = snumbers[col];
        for(auto& num_str : aligned) {
            if(num_str.length() < maxlen) {
                num_str.append(maxlen - num_str.length(), '0');
            }
        }

        std::cout << 2 << '\n';

        // BUG: SEGFAULT
        for(int pos = 0; pos < maxlen; pos++) {
            str vertical_num;
            for(const auto& num_str : aligned) {
                // if(pos < num_str.length()) {
                    vertical_num += num_str[pos];
                // }
            }
            if(!vertical_num.empty()) {
                numbers[col].push_back(stoll(vertical_num));
            }
        }
    }
    std::cout << 3 << '\n';

    reverse(all(numbers));
    reverse(all(operations));

    ll ans{}; 
    
    for(int i = 0, e = isz(operations); i < e; i++) {
        if(numbers[i].empty()) continue;
        
        char op = operations[i][0];
        ll result = numbers[i][0];
        
        for(size_t j = 1; j < numbers[i].size(); j++) {
            if(op == '*') {
                result *= numbers[i][j];
            } else if(op == '+') {
                result += numbers[i][j];
            }
        }
        
        ans += result;
    }
    std::cout << ans << '\n';
}


int32_t main(){
    part2();
}
