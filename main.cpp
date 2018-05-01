#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long ll;

struct st {
    ll f;
    ll s;
    ll t;
};

ll find(ll i, st arr[], ll l, ll r) {
    if (r >= l) {
        ll mid = l + (r - l) / 2;
        if (arr[mid].f == i)
            return mid;
        if (arr[mid].f > i)
            return find(i, arr, l, mid - 1);
        return find(i, arr, mid + 1, r);
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    st g[n];

    ll a, b;
    for (ll i = 0; i < n; i++) {
        cin >> a >> b;
        g[i].f = a;
        g[i].s = a + b;
        g[i].t = 0;
    }

    sort(g, g + n, [](st st1, st st2) { return st1.f < st2.f; });
    ll v, max_l = 0;
    for (ll i = 0; i < n; i++) {
        v = g[i].f;
        while (v == g[i].f) {
            ll neigh = find(g[i].s, g, 0, n);
            if (neigh != -1) {
                ll &path = g[neigh].t;
                path = max(path, g[i].t + 1);
                max_l = max(path, max_l);
            }
            i++;
        }
    }

    cout << max_l + 1;

    return 0;
}
