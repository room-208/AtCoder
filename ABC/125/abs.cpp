#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
//#pragma GCC optimize ("-O3")
using namespace std;
void _main();
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    _main();
}
typedef long long ll;
const int inf = INT_MAX / 2;
const ll infl = 1LL << 60;
template <class T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b)
{
    if (b < a)
    {
        a = b;
        return 1;
    }
    return 0;
}
//---------------------------------------------------------------------------------------------------
int gcd(int a, int b) { return a ? gcd(b % a, a) : b; }
#define def 0
template <class V, int NV>
struct SegTree
{ //[l,r)
    V comp(V &l, V &r) { return gcd(l, r); };

    vector<V> val;
    SegTree() { val = vector<V>(NV * 2, def); }
    V get(int x, int y, int l = 0, int r = NV, int k = 1)
    {
        if (r <= x || y <= l)
            return def;
        if (x <= l && r <= y)
            return val[k];
        auto a = get(x, y, l, (l + r) / 2, k * 2);
        auto b = get(x, y, (l + r) / 2, r, k * 2 + 1);
        return comp(a, b);
    }
    void update(int i, V v)
    {
        i += NV;
        val[i] = v;
        while (i > 1)
            i >>= 1, val[i] = comp(val[i * 2], val[i * 2 + 1]);
    }
    void add(int i, V v) { update(i, val[i + NV] + v); }
    V operator[](int x) { return get(x, x + 1); }
};
/*---------------------------------------------------------------------------------------------------
　　　　　　　　　　　 ∧＿∧  
　　　　　 ∧＿∧ 　（´<_｀ ）　 Welcome to My Coding Space!
　　　　 （ ´_ゝ`）　/　 ⌒i     
　　　　／　　　＼　 　  |　|     
　　　 /　　 /￣￣￣￣/　　|  
　 ＿_(__ﾆつ/　    ＿/ .| .|＿＿＿＿  
　 　　　＼/＿＿＿＿/　（u　⊃  
---------------------------------------------------------------------------------------------------*/

int N, A[101010];
SegTree<int, 1 << 17> st;
//---------------------------------------------------------------------------------------------------
void _main()
{
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) st.update(i, A[i]);

    int ans = 0;
    rep(i, 0, N)
    {
        int g = 0;
        g = gcd(g, st.get(0, i));
        g = gcd(g, st.get(i + 1, N));
        cout << st.get(0, i) << st.get(i + 1, N) << endl;
        chmax(ans, g);
    }
    cout << ans << endl;
}
