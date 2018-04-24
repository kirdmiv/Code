#include <bits/stdc++.h>
using namespace std;
// TEMPLATE HERE
 
#define int long long
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
// #define ALLOC
   
#define MAX INT_MAX
#define MIN INT_MIN
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0;i < n;i++)
#define ft first
#define st second
#define pb push_back
   
   
#ifdef ALLOC
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
    assert((mpos += n) <= MAX_MEM);
    return (void *)(mem + mpos - n);
}
inline void operator delete ( void * ) noexcept { }
#endif
   
// TEMPLATE END
   
// CODE HERE
struct Solver{
    vi ans, used;
    vector<vi> g;
    int n, m, s;
    void dfs(int v){
        ans.pb(v + 1);
        used[v] = 1;
        bool f = 0;
        for (int u : g[v]) if (!used[u]) {
            dfs(u);
            ans.pb(v + 1); 
        }
    }
    Solver(){
        cin >> n >> m >> s;
        --s;
        g.resize(n);
        used.resize(n);
        forn(i, m){
            int v, u;
            cin >> v >> u;
            g[--v].pb(--u);
            g[u].pb(v);
        }
        dfs(s);
        cout << ans.size() << '\n';
        for (int u : ans) cout << u << ' ';
        cout << '\n';
    }   
};
   
// CODE END
   
signed main(){
    int t  = 1;
#ifdef LOCAL
    assert(freopen("input.txt", "r", stdin));
    cin >> t;
#else
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    // string FN = "cut";
    // freopen((FN + ".in").c_str(), "r", stdin);
    // freopen((FN + ".out").c_str(), "w", stdout);
#endif
    while(t--){
#ifdef LOCAL
        clock_t t_elapsed = clock();
#endif
        Solver a;
#ifdef LOCAL
        cout << setprecision(5) << fixed <<"Elapsed: " << fabs(clock() - t_elapsed) / CLOCKS_PER_SEC << " sec.\n";
#endif
    }
   
}